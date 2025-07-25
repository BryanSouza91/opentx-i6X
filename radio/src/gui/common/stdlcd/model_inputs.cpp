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

#define _STR_MAX(x)                     "/" #x
#define STR_MAX(x)                     _STR_MAX(x)

uint8_t getExposCount()
{
  uint8_t count = 0;
  uint8_t ch ;
  
  for (int i=MAX_EXPOS-1 ; i>=0; i--) {
    ch = EXPO_VALID(expoAddress(i));
    if (ch != 0) {
      count++;
    }
  }
  return count;
}

bool reachExposLimit()
{
  if (getExposCount() >= MAX_EXPOS) {
    POPUP_WARNING(STR_NOFREEEXPO);
    return true;
  }
  return false;
}

// TODO avoid this global s_currCh on ARM boards ...
int8_t s_currCh;
void insertExpo(uint8_t idx)
{
  pauseMixerCalculations();
  ExpoData * expo = expoAddress(idx);
  memmove(expo+1, expo, (MAX_EXPOS-(idx+1))*sizeof(ExpoData));
  memclear(expo, sizeof(ExpoData));
  expo->srcRaw = (s_currCh > 4 ? MIXSRC_Rud - 1 + s_currCh : MIXSRC_Rud - 1 + channelOrder(s_currCh));
  expo->curve.type = CURVE_REF_EXPO;
  expo->mode = 3; // pos+neg
  expo->chn = s_currCh - 1;
  expo->weight = 100;
  resumeMixerCalculations();
  storageDirty(EE_MODEL);
}

void copyExpo(uint8_t idx)
{
  pauseMixerCalculations();
  ExpoData * expo = expoAddress(idx);
  memmove(expo+1, expo, (MAX_EXPOS-(idx+1))*sizeof(ExpoData));
  resumeMixerCalculations();
  storageDirty(EE_MODEL);
}

bool swapExpos(uint8_t & idx, uint8_t up)
{
  ExpoData * x, * y;
  int8_t tgt_idx = (up ? idx-1 : idx+1);
  
  x = expoAddress(idx);
  
  if (tgt_idx < 0) {
    if (x->chn == 0)
      return false;
    x->chn--;
    return true;
  }
  
  if (tgt_idx == MAX_EXPOS) {
    if (x->chn == NUM_INPUTS-1)
      return false;
    x->chn++;
    return true;
  }
  
  y = expoAddress(tgt_idx);
  if (x->chn != y->chn || !EXPO_VALID(y)) {
    if (up) {
      if (x->chn>0) x->chn--;
      else return false;
    }
    else {
      if (x->chn<NUM_INPUTS-1) x->chn++;
      else return false;
    }
    return true;
  }
  
  pauseMixerCalculations();
  memswap(x, y, sizeof(ExpoData));
  resumeMixerCalculations();
  
  idx = tgt_idx;
  return true;
}

void deleteExpo(uint8_t idx)
{
  pauseMixerCalculations();
  ExpoData * expo = expoAddress(idx);
  int input = expo->chn;
  memmove(expo, expo+1, (MAX_EXPOS-(idx+1))*sizeof(ExpoData));
  memclear(&g_model.expoData[MAX_EXPOS-1], sizeof(ExpoData));
  if (!isInputAvailable(input)) {
    memclear(&g_model.inputNames[input], LEN_INPUT_NAME);
  }
  resumeMixerCalculations();
  storageDirty(EE_MODEL);
}

void onExposMenu(const char * result)
{
  uint8_t chn = expoAddress(s_currIdx)->chn + 1;
  
  if (result == STR_EDIT) {
    pushMenu(menuModelExpoOne);
  }
  else if (result == STR_INSERT_BEFORE || result == STR_INSERT_AFTER) {
    if (!reachExposLimit()) {
      s_currCh = chn;
      if (result == STR_INSERT_AFTER) { s_currIdx++; menuVerticalPosition++; }
      insertExpo(s_currIdx);
      pushMenu(menuModelExpoOne);
    }
  }
  else if (result == STR_COPY || result == STR_MOVE) {
    s_copyMode = (result == STR_COPY ? COPY_MODE : MOVE_MODE);
    s_copySrcIdx = s_currIdx;
    s_copySrcCh = chn;
    s_copySrcRow = menuVerticalPosition;
  }
  else if (result == STR_DELETE) {
    deleteExpo(s_currIdx);
  }
}

#if LCD_W >= 212
#define EXPO_LINE_WEIGHT_POS           8*FW+8
#define EXPO_LINE_SRC_POS              9*FW+3
#define EXPO_LINE_CURVE_POS            12*FW+11
#define EXPO_LINE_TRIM_POS             19*FW-2
#define EXPO_LINE_SWITCH_POS           20*FW
#define EXPO_LINE_SIDE_POS             25*FW
#define EXPO_LINE_FM_POS               12*FW+11
#define EXPO_LINE_SELECT_POS           5*FW+2
#define EXPO_LINE_NAME_POS             LCD_W-LEN_EXPOMIX_NAME*FW-MENUS_SCROLLBAR_WIDTH

void displayExpoInfos(coord_t y, ExpoData * ed)
{
  drawCurveRef(EXPO_LINE_CURVE_POS, y, ed->curve, 0);
  drawSwitch(EXPO_LINE_SWITCH_POS, y, ed->swtch, 0);
}

void displayExpoLine(coord_t y, ExpoData * ed)
{
  drawSource(EXPO_LINE_SRC_POS, y, ed->srcRaw, 0);

  if (ed->carryTrim != TRIM_ON) {
    lcdDrawChar(EXPO_LINE_TRIM_POS, y, ed->carryTrim > 0 ? '-' : STR_RETA123[-ed->carryTrim]);
  }

  if (!ed->flightModes || ((ed->curve.value || ed->swtch) && ((get_tmr10ms() / 200) & 1)))
    displayExpoInfos(y, ed);
  else
    displayFlightModes(EXPO_LINE_FM_POS, y, ed->flightModes);

  if (ed->name[0]) {
    lcdDrawSizedText(EXPO_LINE_NAME_POS, y, ed->name, sizeof(ed->name), ZCHAR);
  }
  
#if LCD_DEPTH > 1
  if (ed->mode!=3) {
    lcdDrawChar(EXPO_LINE_SIDE_POS, y, ed->mode == 2 ? 126 : 127);
  }
#endif
}
#else
#define EXPO_LINE_WEIGHT_POS           7*FW+8
#define EXPO_LINE_SRC_POS              8*FW+3
#define EXPO_LINE_INFOS_POS            11*FW+11
#define EXPO_LINE_CURVE_POS            11*FW+11
#define EXPO_LINE_SWITCH_POS           17*FW
#define EXPO_LINE_SIDE_POS             20*FW+2
#define EXPO_LINE_SELECT_POS           4*FW+2

void displayExpoInfos(coord_t y, ExpoData * ed)
{
  drawCurveRef(EXPO_LINE_CURVE_POS, y, ed->curve, 0);
  drawSwitch(EXPO_LINE_SWITCH_POS, y, ed->swtch, 0);
  if (ed->mode != 3) {
    lcdDrawChar(EXPO_LINE_SIDE_POS, y, ed->mode == 2 ? 126 : 127);
  }
}

void displayExpoLine(coord_t y, ExpoData * ed)
{
  drawSource(EXPO_LINE_SRC_POS, y, ed->srcRaw, 0);
  
  if (ed->name[0])
    lcdDrawSizedText(EXPO_LINE_INFOS_POS, y, ed->name, LEN_EXPOMIX_NAME, ZCHAR);
  else if (!ed->flightModes || ((ed->curve.value || ed->swtch) && ((get_tmr10ms() / 200) & 1)))
    displayExpoInfos(y, ed);
  else
    displayFlightModes(EXPO_LINE_INFOS_POS+9*FWNUM, y, ed->flightModes);
}
#endif

void menuModelExposAll(event_t event)
{
  int8_t sub = menuVerticalPosition - HEADER_LINE;
  
  if (s_editMode > 0) {
    s_editMode = 0;
  }
  
  uint8_t chn = expoAddress(s_currIdx)->chn + 1;
  
  switch (event) {
    case EVT_ENTRY:
    case EVT_ENTRY_UP:
      s_copyMode = 0;
      s_copyTgtOfs = 0;
      break;
    case EVT_KEY_LONG(KEY_EXIT):
      if (s_copyMode && s_copyTgtOfs == 0) {
        deleteExpo(s_currIdx);
        killEvents(event);
        event = 0;
      }
      // no break
    case EVT_KEY_BREAK(KEY_EXIT):
      if (s_copyMode) {
        if (s_copyTgtOfs) {
          // cancel the current copy / move operation
          if (s_copyMode == COPY_MODE) {
            deleteExpo(s_currIdx);
          }
          else {
            do {
              swapExpos(s_currIdx, s_copyTgtOfs > 0);
              s_copyTgtOfs += (s_copyTgtOfs < 0 ? +1 : -1);
            } while (s_copyTgtOfs != 0);
            storageDirty(EE_MODEL);
          }
          menuVerticalPosition = s_copySrcRow;
          s_copyTgtOfs = 0;
        }
        s_copyMode = 0;
        event = 0;
      }
      break;
    case EVT_KEY_BREAK(KEY_ENTER):
      if ((!s_currCh || (s_copyMode && !s_copyTgtOfs)) && !READ_ONLY()) {
        s_copyMode = (s_copyMode == COPY_MODE ? MOVE_MODE : COPY_MODE);
        s_copySrcIdx = s_currIdx;
        s_copySrcCh = chn;
        s_copySrcRow = sub;
        break;
      }
      // no break
    case EVT_KEY_LONG(KEY_ENTER):
      killEvents(event);
      if (s_copyTgtOfs) {
        s_copyMode = 0;
        s_copyTgtOfs = 0;
      }
      else {
        if (READ_ONLY()) {
          if (!s_currCh) {
            pushMenu(menuModelExpoOne);
          }
        }
        else {
          if (s_copyMode) s_currCh = 0;
          if (s_currCh) {
            if (reachExposLimit()) break;
            insertExpo(s_currIdx);
            pushMenu(menuModelExpoOne);
            s_copyMode = 0;
          }
          else {
            event = 0;
            s_copyMode = 0;
            POPUP_MENU_ADD_ITEM(STR_EDIT);
            POPUP_MENU_ADD_ITEM(STR_INSERT_BEFORE);
            POPUP_MENU_ADD_ITEM(STR_INSERT_AFTER);
            POPUP_MENU_ADD_ITEM(STR_COPY);
            POPUP_MENU_ADD_ITEM(STR_MOVE);
            POPUP_MENU_ADD_ITEM(STR_DELETE);
            POPUP_MENU_START(onExposMenu);
          }
        }
      }
      break;
    case EVT_KEY_LONG(KEY_LEFT):
    case EVT_KEY_LONG(KEY_RIGHT):
      if (s_copyMode && !s_copyTgtOfs) {
        if (reachExposLimit()) break;
        s_currCh = chn;
        if (event == EVT_KEY_LONG(KEY_RIGHT)) { s_currIdx++; menuVerticalPosition++; }
        insertExpo(s_currIdx);
        pushMenu(menuModelExpoOne);
        s_copyMode = 0;
        killEvents(event);
      }
      break;
    case EVT_KEY_FIRST(KEY_UP):
    case EVT_KEY_REPT(KEY_UP):
    case EVT_KEY_FIRST(KEY_DOWN):
    case EVT_KEY_REPT(KEY_DOWN):
#if defined(ROTARY_ENCODER_NAVIGATION)
    case EVT_ROTARY_RIGHT:
    case EVT_ROTARY_LEFT:
#endif
      if (s_copyMode) {
        uint8_t next_ofs = (IS_PREVIOUS_EVENT(event) ? s_copyTgtOfs - 1 : s_copyTgtOfs + 1);
        
        if (s_copyTgtOfs==0 && s_copyMode==COPY_MODE) {
          // insert a mix on the same channel (just above / just below)
          if (reachExposLimit()) break;
          copyExpo(s_currIdx);
          if (IS_NEXT_EVENT(event))
            s_currIdx++;
          else if (sub-menuVerticalOffset >= 6)
            menuVerticalOffset++;
        }
        else if (next_ofs==0 && s_copyMode==COPY_MODE) {
          // delete the mix
          deleteExpo(s_currIdx);
          if (IS_PREVIOUS_EVENT(event))
            s_currIdx--;
        }
        else {
          // only swap the mix with its neighbor
          if (!swapExpos(s_currIdx, IS_PREVIOUS_EVENT(event)))
            break;
          storageDirty(EE_MODEL);
        }
        
        s_copyTgtOfs = next_ofs;
      }
      break;
  }
  
  lcdDrawNumber(FW*sizeof(TR_MENUINPUTS)+FW+FW/2, 0, getExposCount(), RIGHT);
  lcdDrawText(FW*sizeof(TR_MENUINPUTS)+FW+FW/2, 0, STR_MAX(MAX_EXPOS));

#if LCD_DEPTH > 1
  // Value
  uint8_t index = expoAddress(s_currIdx)->chn;
  if (!s_currCh) {
    lcdDrawNumber(127, 2, calcRESXto1000(anas[index]), PREC1|TINSIZE|RIGHT);
  }
#endif
  
  SIMPLE_MENU(STR_MENUINPUTS, menuTabModel, MENU_MODEL_INPUTS, HEADER_LINE + s_maxLines);

#if LCD_DEPTH > 1
  // Gauge
  if (!s_currCh) {
    drawGauge(127, 1, 58, 6, anas[index], 1024);
  }
#endif
  
  sub = menuVerticalPosition - HEADER_LINE;
  s_currCh = 0;
  int cur = 0;
  int i = 0;
  
  for (int ch=1; ch<=NUM_INPUTS; ch++) {
    ExpoData * ed;
    coord_t y = MENU_HEADER_HEIGHT+1+(cur-menuVerticalOffset)*FH;
    if (i<MAX_EXPOS && (ed=expoAddress(i))->chn+1 == ch && EXPO_VALID(ed)) {
      if (cur-menuVerticalOffset >= 0 && cur-menuVerticalOffset < NUM_BODY_LINES) {
        drawSource(0, y, ch, 0);
      }
      uint8_t mixCnt = 0;
      do {
        if (s_copyMode) {
          if (s_copyMode == MOVE_MODE && cur-menuVerticalOffset >= 0 && cur-menuVerticalOffset < NUM_BODY_LINES && s_copySrcCh == ch && s_copyTgtOfs != 0 && i == (s_copySrcIdx + (s_copyTgtOfs<0))) {
            lcdDrawRect(18, y-1, LCD_W-18, 9, DOTTED);
            cur++; y+=FH;
          }
          if (s_currIdx == i) {
            sub = cur;
            menuVerticalPosition = cur + HEADER_LINE;
            s_currCh = ch;
          }
        }
        else if (sub == cur) {
          s_currIdx = i;
        }
        if (cur-menuVerticalOffset >= 0 && cur-menuVerticalOffset < NUM_BODY_LINES) {
          LcdFlags attr = ((s_copyMode || sub != cur) ? 0 : INVERS);
          
          GVAR_MENU_ITEM(EXPO_LINE_WEIGHT_POS, y, ed->weight, MIN_EXPO_WEIGHT, 100, RIGHT | attr | (mixState[i].activeExpo ? BOLD : 0), 0, 0); // Using mixState.activeExpo
          displayExpoLine(y, ed);
          
          if (s_copyMode) {
            if ((s_copyMode==COPY_MODE || s_copyTgtOfs == 0) && s_copySrcCh == ch && i == (s_copySrcIdx + (s_copyTgtOfs<0))) {
              /* draw a border around the raw on selection mode (copy/move) */
              lcdDrawRect(EXPO_LINE_SELECT_POS, y-1, LCD_W-EXPO_LINE_SELECT_POS, 9, s_copyMode == COPY_MODE ? SOLID : DOTTED);
            }
            if (cur == sub) {
              /* invert the raw when it's the current one */
              lcdDrawSolidFilledRect(EXPO_LINE_SELECT_POS+1, y, LCD_W-EXPO_LINE_SELECT_POS-2, 7);
            }
          }
        }
        cur++; y+=FH; mixCnt++; i++; ed++;
      } while (i<MAX_EXPOS && ed->chn+1 == ch && EXPO_VALID(ed));
      if (s_copyMode == MOVE_MODE && cur-menuVerticalOffset >= 0 && cur-menuVerticalOffset < NUM_BODY_LINES && s_copySrcCh == ch && i == (s_copySrcIdx + (s_copyTgtOfs<0))) {
        lcdDrawRect(EXPO_LINE_SELECT_POS, y-1, LCD_W-EXPO_LINE_SELECT_POS, 9, DOTTED);
        cur++;
      }
    }
    else {
      uint8_t attr = 0;
      if (sub == cur) {
        s_currIdx = i;
        s_currCh = ch;
        if (!s_copyMode) {
          attr = INVERS;
        }
      }
      if (cur-menuVerticalOffset >= 0 && cur-menuVerticalOffset < NUM_BODY_LINES) {
        drawSource(0, y, ch, attr);
        if (s_copyMode == MOVE_MODE && s_copySrcCh == ch) {
          lcdDrawRect(EXPO_LINE_SELECT_POS, y-1, LCD_W-EXPO_LINE_SELECT_POS, 9, DOTTED);
        }
      }
      cur++;
    }
  }
  s_maxLines = cur;
  if (sub >= s_maxLines-1) {
    menuVerticalPosition = s_maxLines - 1 + HEADER_LINE;
  }
}
