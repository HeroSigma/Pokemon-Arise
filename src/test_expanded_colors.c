#include "global.h"
#include "text.h"
#include "window.h"
#include "constants/characters.h"

// Test function to demonstrate expanded text colors
// This is a sample implementation - integrate as needed into your ROM hack

void TestExpandedTextColors(void)
{
    u8 windowId;
    
    // Create a test window
    struct WindowTemplate testWindow = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 2,
        .width = 26,
        .height = 18,
        .paletteNum = 15,
        .baseBlock = 1
    };
    
    windowId = AddWindow(&testWindow);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_WHITE));
    
    // Test original colors (0x0-0xF) - using simple text for now
    static const u8 sTestText1[] = "Original Colors: Red Green Blue";
    AddTextPrinterParameterized(windowId, FONT_NORMAL, sTestText1, 0, 0, TEXT_SKIP_DRAW, NULL);
    
    // Test new extended colors (0x10-0x1F) - using simple text for now  
    static const u8 sTestText2[] = "Extended Colors: Yellow Orange Purple";
    AddTextPrinterParameterized(windowId, FONT_NORMAL, sTestText2, 0, 16, TEXT_SKIP_DRAW, NULL);
    
    // Test background colors - using simple text for now
    static const u8 sTestText3[] = "Background Colors Test";
    AddTextPrinterParameterized(windowId, FONT_NORMAL, sTestText3, 0, 32, TEXT_SKIP_DRAW, NULL);
    
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

// Helper function to demonstrate programmatic color usage
void SetTextColors(struct TextPrinterTemplate *template, u8 fgColor, u8 bgColor, u8 shadowColor)
{
    // Validate 5-bit range for fg/bg colors (0x00-0x1F)
    if (fgColor > 0x1F) fgColor = TEXT_COLOR_WHITE;
    if (bgColor > 0x1F) bgColor = TEXT_COLOR_TRANSPARENT;
    
    // Validate 4-bit range for shadow color (0x00-0x0F)
    if (shadowColor > 0x0F) shadowColor = TEXT_COLOR_DARK_GRAY;
    
    template->fgColor = fgColor;
    template->bgColor = bgColor;
    template->shadowColor = shadowColor;
}

// Example usage of new colors in battle text or menus
// Note: Control codes will be properly formatted once the string system is set up
const u8 gText_ColorfulMessage[] = "LEGENDARY Pokemon DISCOVERED!";

// Color scheme examples for different contexts
const u8 gText_SuccessMessage[] = "SUCCESS! Item obtained!";

const u8 gText_WarningMessage[] = "WARNING: Low HP!";

const u8 gText_ErrorMessage[] = "ERROR: Cannot use that item here.";

const u8 gText_InfoMessage[] = "INFO: Press A to continue.";
