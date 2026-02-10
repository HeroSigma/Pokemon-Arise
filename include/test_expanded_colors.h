#ifndef GUARD_TEST_EXPANDED_COLORS_H
#define GUARD_TEST_EXPANDED_COLORS_H

#include "text.h"

// Test function to demonstrate expanded text colors
void TestExpandedTextColors(void);

// Helper function to set text colors with validation
void SetTextColors(struct TextPrinterTemplate *template, u8 fgColor, u8 bgColor, u8 shadowColor);

// Example colorful text strings using extended colors
extern const u8 gText_ColorfulMessage[];
extern const u8 gText_SuccessMessage[];
extern const u8 gText_WarningMessage[];
extern const u8 gText_ErrorMessage[];
extern const u8 gText_InfoMessage[];

// Convenience macros for common color combinations
#define TEXT_COLORS_SUCCESS     TEXT_COLOR_LIME, TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY
#define TEXT_COLORS_WARNING     TEXT_COLOR_ORANGE, TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY
#define TEXT_COLORS_ERROR       TEXT_COLOR_MAROON, TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY
#define TEXT_COLORS_INFO        TEXT_COLOR_CYAN, TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY
#define TEXT_COLORS_LEGENDARY   TEXT_COLOR_GOLD, TEXT_COLOR_NAVY, TEXT_COLOR_DARK_GRAY
#define TEXT_COLORS_SHINY       TEXT_COLOR_PINK, TEXT_COLOR_TRANSPARENT, TEXT_COLOR_PURPLE

#endif // GUARD_TEST_EXPANDED_COLORS_H
