#include "global.h"
#include "battle.h"
#include "text.h"
#include "trainer_colors.h"

// Helper function to set text color for a trainer's name
// Saves the current text colors and returns them in the provided pointers
// so they can be restored later with RestoreTextColors()
void SetTrainerNameColor(u8 trainerClass, u8 *savedFgColor, u8 *savedBgColor, u8 *savedShadowColor)
{
    u16 color = GetTrainerClassTextColor(trainerClass);
    
    // Save current colors
    SaveTextColors(savedFgColor, savedBgColor, savedShadowColor);
    
    // Extract RGB components from the color
    u8 r = (color >> 0) & 0x1F;
    u8 g = (color >> 5) & 0x1F;
    u8 b = (color >> 10) & 0x1F;
    
    // Set new text color
    GenerateFontHalfRowLookupTable(r, g, b);
}

// Helper function to print trainer name with appropriate color
// Returns the x position after the printed text
s32 PrintTrainerNameWithColor(u8 windowId, const u8 *name, u8 trainerClass, u8 x, u8 y, u8 letterSpacing, u8 lineSpacing)
{
    u8 savedFgColor, savedBgColor, savedShadowColor;
    s32 width;
    
    // Set the trainer's name color
    SetTrainerNameColor(trainerClass, &savedFgColor, &savedBgColor, &savedShadowColor);
    
    // Print the name using the standard text printing function
    // We've already set the color with GenerateFontHalfRowLookupTable
    width = AddTextPrinterParameterized(
        windowId, 
        FONT_NORMAL, 
        name,  // text
        x,     // x
        y,     // y
        letterSpacing, 
        NULL   // callback
    );
    
    // Restore original colors
    RestoreTextColors(&savedFgColor, &savedBgColor, &savedShadowColor);
    GenerateFontHalfRowLookupTable(savedFgColor, savedBgColor, savedShadowColor);
    
    return width;
}
