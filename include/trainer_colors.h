#ifndef GUARD_TRAINER_COLORS_H
#define GUARD_TRAINER_COLORS_H

#include "global.h"

// Convert RGB (0-31) to GBA color format (0-31, 0-31, 0-31) -> 0x7FFF
#define RGB2(r, g, b) ((r) | ((g) << 5) | ((b) << 10))

// Structure to hold RGB color values (0-31 each)
typedef struct {
    u8 r;
    u8 g;
    u8 b;
} TrainerColor;

// Function to get the color for a trainer class
const TrainerColor* GetTrainerClassColor(u8 trainerClass);

// Function to get the text color for a trainer class in GBA color format
// Returns a GBA color (0x7FFF format) based on the trainer's class
u16 GetTrainerClassTextColor(u8 trainerClass);

#endif // GUARD_TRAINER_COLORS_H
