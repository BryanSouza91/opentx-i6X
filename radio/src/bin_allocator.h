/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x 
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
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

 
#ifndef _BIN_ALLOCATOR_H_
#define _BIN_ALLOCATOR_H_

#include "debug.h"
#include <cstddef> // For size_t
#include <cstring> // For memset (instead of memclear if not defined elsewhere)

// Assuming PACK is a macro that ensures no padding between members
// (often __attribute__((packed)) for GCC/Clang or #pragma pack for MSVC)
template <int SIZE_SLOT, int NUM_BINS> class BinAllocator {
private:
    PACK(struct Bin {
        char data[SIZE_SLOT];
        // In a true free list, 'data' would be a union with 'size_t next_free_index;'
        // but for a simpler optimization, we'll just track 'Used' and calculate index.
        bool Used; // Still needed for free, if not using a full free list with union
    });
    Bin Bins[NUM_BINS];
    int NoUsedBins;

    // For a faster malloc, we could track the last found free bin
    size_t lastFreeBinIndex; // Hint for malloc to start searching

public:
    BinAllocator() : NoUsedBins(0), lastFreeBinIndex(0) {
        // memset is standard C++ for clearing memory
        std::memset(Bins, 0, sizeof(Bins));
    }

    // Optimized free using pointer arithmetic
    bool free(void * ptr) {
        if (!is_member(ptr)) {
            return false;
        }

        // Calculate the index of the bin using pointer arithmetic.
        // This relies on Bins being a contiguous array and data being at offset 0 within Bin.
        // (reinterpret_cast<char*>(ptr) - reinterpret_cast<char*>(&Bins[0])) gives byte offset from start of Bins array.
        // Divide by sizeof(Bin) to get the element index.
        size_t binIndex = (reinterpret_cast<char*>(ptr) - reinterpret_cast<char*>(&Bins[0])) / sizeof(Bin);

        // Additional sanity check: ensure the pointer truly points to the start of a bin's data
        // This is important if `ptr` could potentially point *within* a bin's data, not just its start.
        if (binIndex >= NUM_BINS || ptr != Bins[binIndex].data) {
             return false; // Pointer is not at the start of a known bin's data area
        }

        if (Bins[binIndex].Used) {
            Bins[binIndex].Used = false;
            --NoUsedBins;
            // Update the hint for malloc if this freed bin is before the current hint
            if (binIndex < lastFreeBinIndex) {
                lastFreeBinIndex = binIndex;
            }
            return true;
        }
        return false;
    }

    bool is_member(void * ptr) {
        // More robust check: ptr must be within the bounds of the entire Bins array,
        // and aligned to the start of a Bin's data.
        char* start_address = reinterpret_cast<char*>(&Bins[0]);
        char* end_address = reinterpret_cast<char*>(&Bins[NUM_BINS - 1]) + sizeof(Bin); // End of the last bin

        return (reinterpret_cast<char*>(ptr) >= start_address && reinterpret_cast<char*>(ptr) < end_address &&
                ((reinterpret_cast<char*>(ptr) - start_address) % sizeof(Bin)) == 0);
    }

    // Optimized malloc: Start search from lastFreeBinIndex
    void * malloc(size_t size) {
        if (size > SIZE_SLOT) {
            return nullptr;
        }
        if (NoUsedBins >= NUM_BINS) {
            return nullptr;
        }

        // Start search from lastFreeBinIndex, and wrap around if necessary
        for (size_t n = 0; n < NUM_BINS; ++n) {
            size_t currentIdx = (lastFreeBinIndex + n) % NUM_BINS;
            if (!Bins[currentIdx].Used) {
                Bins[currentIdx].Used = true;
                ++NoUsedBins;
                lastFreeBinIndex = currentIdx; // Update hint for next malloc
                return Bins[currentIdx].data;
            }
        }
        return nullptr;
    }

    size_t size(void * ptr) {
        return is_member(ptr) ? SIZE_SLOT : 0;
    }

    bool can_fit(void * ptr, size_t size) {
        return is_member(ptr) && size <= SIZE_SLOT;
    }

    unsigned int capacity() { return NUM_BINS; }
    unsigned int size() { return NoUsedBins; }
};

#if defined(SIMU)
typedef BinAllocator<39,300> BinAllocator_slots1;
typedef BinAllocator<79,100> BinAllocator_slots2;
#else
typedef BinAllocator<27,200> BinAllocator_slots1;
typedef BinAllocator<91,50> BinAllocator_slots2;
#endif

#if defined(USE_BIN_ALLOCATOR)
extern BinAllocator_slots1 slots1;
extern BinAllocator_slots2 slots2;

void *bin_l_alloc (void *ud, void *ptr, size_t osize, size_t nsize);
#endif

#endif // _BIN_ALLOCATOR_H_