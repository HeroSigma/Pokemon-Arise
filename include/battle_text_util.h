#ifndef GUARD_BATTLE_TEXT_UTIL_H
#define GUARD_BATTLE_TEXT_UTIL_H

#include "global.h"

// Sets the text color for a trainer's name based on their class
// Saves the current text colors to the provided pointers
void SetTrainerNameColor(u8 trainerClass, u8 *savedFgColor, u8 *savedBgColor, u8 *savedShadowColor);

// Prints a trainer's name with their class-appropriate color
// Returns the x position after the printed text
s32 PrintTrainerNameWithColor(u8 windowId, const u8 *name, u8 trainerClass, u8 x, u8 y, u8 letterSpacing, u8 lineSpacing);

#endif // GUARD_BATTLE_TEXT_UTIL_H
