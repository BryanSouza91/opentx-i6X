/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 * th9x - http://code.google.com/p/th9x
 * er9x - http://code.google.com/p/er9x
 * gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "opentx.h"
#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_dma.h"
#include "stm32f0xx_spi.h" // Include SPI header
#include "hal.h" // Include the updated hal.h for shared definitions

// External display buffer
extern display_t displayBuf[DISPLAY_BUFFER_SIZE];

// --- FIX: Correct Strobe Pulse Pattern ---
// The strobe pattern is corrected to generate a HI -> LO pulse, which is required
// by the LCD controller to latch data. The original code produced LO -> HI.
// This is not used for SPI, but kept for compatibility if other parts of code still reference it.
const uint32_t lcd_rd_strobe_patterns[] = {
    ((uint32_t)1 << LCD_RD_PIN_NUMBER),        // Set pin HIGH
    ((uint32_t)1 << (LCD_RD_PIN_NUMBER + 16))  // Set pin LOW (by writing to BRR part of BSRR)
};

// LCD command definitions and GPIO macros are now in hal.h
// const static unsigned char lcdInitSequence[] uses LCD_CMD_* from hal.h
const static unsigned char lcdInitSequence[] = {
    LCD_CMD_RESET,          // Soft reset
    LCD_CMD_DISPLAY_OFF,    // Display OFF
    LCD_CMD_MODE_RAM,       // Normal display mode
    LCD_CMD_BIAS_1_6,       // Set bias (1/6)
    LCD_CMD_COM_NORMAL,     // COM scan direction (Normal)
    LCD_CMD_SEG_INVERSE,    // SEG output direction (Inverse)
    LCD_CMD_POWERCTRL_ALL_ON, // All built-in power circuits on
    LCD_CMD_REG_RATIO_011,  // Regulator resistor ratio
    LCD_CMD_EV,             // Set Electronic Volume (contrast)
    LCD_CONTRAST_DEFAULT,   // Default contrast value
    LCD_CMD_SET_STARTLINE,  // Set display start line (e.g., 0x40 for line 0)
    // LCD_CMD_SET_PAGESTART, // These are sent per-page or as needed, not in initial sequence
    // LCD_CMD_SET_COL_LO,    // These are sent per-page or as needed, not in initial sequence
    // LCD_CMD_SET_COL_HI,    // These are sent per-page or as needed, not in initial sequence
    LCD_CMD_DISPLAY_ON      // Display ON
};
// Global state variables for non-blocking refresh
volatile bool lcd_busy = false; // Flag to indicate if LCD DMA transfer is in progress
bool lcdInitFinished = false; // Flag to indicate if LCD initialization is complete

// Forward Declarations
static void lcdWriteCommand(uint8_t byte);
static void lcdStart(void);
static void lcdReset(void);
void lcdHardwareInit(void);
void lcdRefresh(void); // No longer takes 'wait' parameter
void lcdWaitForRefresh(void);

// Forward declaration for telemetry DMA TX ISR dispatch function
extern "C" void telemetry_dma_tx_isr_dispatch(void);
// Forward declaration for AUX4_SERIAL DMA RX ISR dispatch function (if needed)
// extern "C" void aux4_serial_dma_rx_isr_dispatch(void);


/**
 * @brief Sends a command byte to the LCD controller via SPI.
 * This function blocks until the command is sent.
 */
static void lcdWriteCommand(uint8_t byte)
{
  lcdWaitForRefresh(); // Ensure any ongoing DMA transfer is complete

  LCD_A0_LOW(); // Set A0 (Data/Command) pin low for command
  LCD_NCS_LOW(); // Assert Chip Select (NCS) low

  // Wait for TXE (Transmit buffer empty) flag to be set
  while ((LCD_SPI->SR & SPI_SR_TXE) == 0) {
    // Wait
  }
  // Clear RXNE (Receive buffer not empty) by reading DR, if in full-duplex mode
  // (void)LCD_SPI->DR; // Uncomment if you need to clear RXNE explicitly, otherwise data will be discarded.

  LCD_SPI->DR = byte; // Send the command byte

  // Wait for RXNE (Receive buffer not empty) flag to be set, indicating transfer complete
  // This implicitly waits for the transmission to finish.
  while ((LCD_SPI->SR & SPI_SR_RXNE) == 0) {
    // Wait
  }
  (void)LCD_SPI->DR; // Read DR to clear RXNE flag

  LCD_NCS_HIGH(); // De-assert Chip Select (NCS) high
}

/**
 * @brief Initializes the LCD hardware (GPIO, SPI, DMA).
 */
void lcdHardwareInit()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef SPI_InitStructure;

  // Enable clocks for GPIO, SPI, and DMA
  RCC_AHBPeriphClockCmd(LCD_RCC_AHB1Periph_GPIO | RCC_AHBPeriph_DMA1, ENABLE);
  RCC_APB1PeriphClockCmd(LCD_RCC_APB1Periph, ENABLE);

  // Configure LCD control pins (NCS, A0, RST) as General Purpose Output Push-Pull
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // High speed for control signals
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_InitStructure.GPIO_Pin = LCD_NCS_GPIO_PIN;
  GPIO_Init(LCD_NCS_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LCD_RST_GPIO_PIN;
  GPIO_Init(LCD_RST_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LCD_A0_GPIO_PIN;
  GPIO_Init(LCD_A0_GPIO, &GPIO_InitStructure);

  // Set NCS and A0 high initially (inactive)
  LCD_NCS_HIGH();
  LCD_A0_HIGH();

  // Configure SPI pins (SCK, MOSI) as Alternate Function Push-Pull
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = LCD_CLK_GPIO_PIN | LCD_MOSI_GPIO_PIN;
  GPIO_Init(LCD_SPI_GPIO, &GPIO_InitStructure);

  // Connect SPI pins to their Alternate Functions
  GPIO_PinAFConfig(LCD_SPI_GPIO, LCD_MOSI_GPIO_PinSource, LCD_GPIO_AF);
  GPIO_PinAFConfig(LCD_SPI_GPIO, LCD_CLK_GPIO_PinSource, LCD_GPIO_AF);

  // SPI peripheral configuration
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx; // Transmit only (MOSI)
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  // --- IMPORTANT CHANGE: Set SPI Mode to 0 (CPOL=Low, CPHA=1Edge) ---
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; // Clock polarity: Clock is low when idle
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; // Clock phase: Data captured on 1st edge
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; // Software NSS management
  // Baud Rate Prescaler: PCLK1 (48MHz) / 2 = 24MHz. Adjust as needed.
  // For a 5MHz target, 48MHz / 8 = 6MHz, 48MHz / 16 = 3MHz. Let's start with /8.
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; // PCLK1/8 = 6MHz
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7; // Not typically used for LCD, can be default

  SPI_Init(LCD_SPI, &SPI_InitStructure);

  SPI_Cmd(LCD_SPI, ENABLE); // Enable the SPI peripheral

  // DMA configuration for SPI TX
  DMA_DeInit(LCD_DMA_Stream);
  DMA_InitTypeDef DMA_InitStructure;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&LCD_SPI->DR; // SPI Data Register
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)displayBuf; // Source: LCD display buffer
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST; // Memory to Peripheral
  DMA_InitStructure.DMA_BufferSize = DISPLAY_BUFFER_SIZE; // Total size of display buffer
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // Peripheral address (DR) does not increment
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // Memory address increments
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 8-bit data
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; // 8-bit data
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; // One-shot transfer
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(LCD_DMA_Stream, &DMA_InitStructure);

  // Enable DMA Transfer Complete Interrupt
  DMA_ITConfig(LCD_DMA_Stream, DMA_IT_TC, ENABLE);
  NVIC_SetPriority(LCD_DMA_Stream_IRQn, 0); // Set high priority
  NVIC_EnableIRQ(LCD_DMA_Stream_IRQn);
}

/**
 * @brief DMA Interrupt Service Routine for LCD SPI TX.
 * This ISR is called when the DMA transfer for the entire display buffer is complete.
 */
extern "C" void LCD_DMA_Stream_IRQHandler()
{
  DEBUG_INTERRUPT(INT_LCD); // Assuming INT_LCD is defined for debug

  // Check if the Transfer Complete interrupt flag is set for the LCD DMA stream (DMA1 Channel 2)
  if (DMA_GetITStatus(DMA1_IT_TC2) != RESET)
  {
    DMA_ClearITPendingBit(DMA1_IT_TC2); // Clear the TC flag

    LCD_SPI->CR2 &= ~SPI_CR2_TXDMAEN; // Disable SPI TX DMA request
    LCD_DMA_Stream->CCR &= ~DMA_CCR_EN; // Disable DMA channel

    // Wait for SPI to finish sending any remaining data in its buffer
    // The DMA TC interrupt fires when the last byte is transferred to the SPI DR,
    // but the SPI peripheral might still be busy sending it out.
    while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) == SET) {
      // Wait for SPI BSY flag to clear
    }

    LCD_NCS_HIGH(); // De-assert Chip Select (NCS)
    LCD_A0_HIGH(); // Set A0 high for data mode (or default idle state)

    lcd_busy = false; // Mark LCD as not busy
  }
  // Check for Telemetry RX DMA (DMA1 Channel 3) if this ISR handles multiple channels
  if (DMA_GetITStatus(DMA1_IT_TC3) != RESET) {
      DMA_ClearITPendingBit(DMA1_IT_TC3);
      // Assuming there's a specific handler for telemetry RX DMA
      // telemetry_dma_rx_isr_dispatch(); // Uncomment and implement if needed
  }
}


/**
 * @brief Performs a hardware reset of the LCD.
 */
static void lcdReset()
{
  LCD_RST_LOW();
  delay_ms(10); // Increased reset pulse duration for robustness
  LCD_RST_HIGH();
  delay_ms(100); // Increased delay after reset before sending commands
}

/**
 * @brief Sends the initial sequence of commands to the LCD.
 * This function should be called after hardware initialization and reset.
 */
static void lcdStart()
{
  // Iterate through the predefined initialization sequence array
  for (uint32_t i = 0; i < sizeof(lcdInitSequence); i++) {
    lcdWriteCommand(lcdInitSequence[i]);
  }
}

/**
 * @brief Initializes the LCD. Performs hardware setup, reset, and sends initial commands.
 */
void lcdInit()
{
  lcdHardwareInit(); // Setup GPIO, SPI, DMA
  lcdReset();        // Perform hardware reset
  lcdStart();        // Send initial commands
  lcdClear();        // Clear the display buffer (all pixels off)
  lcdRefresh();      // Trigger the first DMA transfer to display the cleared screen/checkerboard
  lcdInitFinished = true; // Mark initialization as complete
}

/**
 * @brief Turns the LCD display off.
 */
void lcdOff()
{
  lcdWaitForRefresh(); // Wait for any ongoing transfer to complete
  lcdWriteCommand(0xAE); // Display OFF command
  delay_ms(3); // Wait for capacitors to drain (as per datasheet/common practice)
}

/**
 * @brief Sets the internal reference voltage (contrast).
 */
void lcdSetRefVolt(uint8_t val)
{
  lcdWaitForRefresh(); // Wait for any ongoing transfer to complete
  lcdWriteCommand(0x81); // Set Electronic Volume (contrast) command
  lcdWriteCommand(val); // Send the contrast value (0-63 for ST7565/ST7567)
}

/**
 * @brief Kicks off a non-blocking refresh of the entire LCD screen using DMA.
 * The actual transfer is handled by the DMA and its ISR.
 */
void lcdRefresh()
{
  if (lcd_busy) {
    return; // A refresh is already in progress
  }

  lcd_busy = true; // Mark LCD as busy

  // Set A0 high for data transfer
  LCD_A0_HIGH();
  // Assert Chip Select (NCS) low
  LCD_NCS_LOW();

  // Disable DMA channel before reconfiguring
  LCD_DMA_Stream->CCR &= ~DMA_CCR_EN;

  // Set memory address and data count for the DMA transfer
  // The DMA will read from displayBuf and write to SPI_DR
  LCD_DMA_Stream->CMAR = (uint32_t)displayBuf;
  LCD_DMA_Stream->CNDTR = DISPLAY_BUFFER_SIZE; // Transfer the entire buffer

  // Enable DMA channel and enable SPI TX DMA request
  LCD_DMA_Stream->CCR |= DMA_CCR_EN;
  LCD_SPI->CR2 |= SPI_CR2_TXDMAEN;
}

/**
 * @brief Blocks until any ongoing DMA-based refresh is complete.
 */
void lcdWaitForRefresh()
{
  while (lcd_busy) {
    // Wait...
  }
}
