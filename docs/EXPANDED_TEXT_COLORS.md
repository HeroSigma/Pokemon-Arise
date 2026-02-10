# Expanded Text Color System

This document describes the expanded text color system that supports 32 unique colors instead of the original 16.

## Overview

The text color system has been expanded from 4-bit (16 colors) to 5-bit (32 colors) for foreground and background colors, providing more creative options for text styling in Pokemon ROM hacks.

## Technical Changes

### Structure Modifications
- `TextPrinterTemplate.fgColor`: Expanded from 4-bit to 5-bit (32 colors)
- `TextPrinterTemplate.bgColor`: Expanded from 4-bit to 5-bit (32 colors)
- `TextPrinterTemplate.shadowColor`: Kept at 4-bit (16 colors)
- `FontInfo` structure: Same expansions as above

### New Color Constants

#### Original Colors (0x0-0xF)
```c
#define TEXT_COLOR_TRANSPARENT  0x0
#define TEXT_COLOR_WHITE        0x1
#define TEXT_COLOR_DARK_GRAY    0x2
#define TEXT_COLOR_LIGHT_GRAY   0x3
#define TEXT_COLOR_RED          0x4
#define TEXT_COLOR_LIGHT_RED    0x5
#define TEXT_COLOR_GREEN        0x6
#define TEXT_COLOR_LIGHT_GREEN  0x7
#define TEXT_COLOR_BLUE         0x8
#define TEXT_COLOR_LIGHT_BLUE   0x9
#define TEXT_DYNAMIC_COLOR_1    0xA // Usually white
#define TEXT_DYNAMIC_COLOR_2    0xB // Usually white w/ tinge of green
#define TEXT_DYNAMIC_COLOR_3    0xC // Usually white
#define TEXT_DYNAMIC_COLOR_4    0xD // Usually aquamarine
#define TEXT_DYNAMIC_COLOR_5    0xE // Usually blue-green
#define TEXT_DYNAMIC_COLOR_6    0xF // Usually cerulean
```

#### Extended Colors (0x10-0x1F)
```c
#define TEXT_COLOR_YELLOW       0x10
#define TEXT_COLOR_ORANGE       0x11
#define TEXT_COLOR_PURPLE       0x12
#define TEXT_COLOR_PINK         0x13
#define TEXT_COLOR_BROWN        0x14
#define TEXT_COLOR_LIME         0x15
#define TEXT_COLOR_CYAN         0x16
#define TEXT_COLOR_MAGENTA      0x17
#define TEXT_COLOR_GOLD         0x18
#define TEXT_COLOR_SILVER       0x19
#define TEXT_COLOR_MAROON       0x1A
#define TEXT_COLOR_NAVY         0x1B
#define TEXT_COLOR_OLIVE        0x1C
#define TEXT_COLOR_TEAL         0x1D
#define TEXT_COLOR_INDIGO       0x1E
#define TEXT_COLOR_VIOLET       0x1F
```

## Usage Examples

### Using Extended Colors in Text
```c
// Example: Display text in yellow
const u8 yellowText[] = _("{FC}{01}{10}This text is yellow!{FF}");

// Example: Display text in purple with white background
const u8 purpleText[] = _("{FC}{04}{12}{01}{00}Purple text on white!{FF}");
```

### Control Code Format
- `{FC}` - Extended control code begin
- `{01}` - Color control code
- `{XX}` - Color value (0x00-0x1F for foreground/background)

### Programming Usage
```c
// Set up a text printer with extended colors
struct TextPrinterTemplate template;
template.fgColor = TEXT_COLOR_GOLD;      // 5-bit value (0x18)
template.bgColor = TEXT_COLOR_NAVY;      // 5-bit value (0x1B)
template.shadowColor = TEXT_COLOR_DARK_GRAY; // 4-bit value (0x2)
```

## Compatibility Notes

- All original 16 colors (0x0-0xF) remain unchanged
- Existing code using 4-bit colors will continue to work
- New colors (0x10-0x1F) are only available for foreground and background
- Shadow colors remain limited to 16 colors (0x0-0xF)

## Memory Impact

- Minimal memory overhead due to bit field packing
- Lookup table size remains unchanged
- No performance impact on text rendering

## Color Palette Recommendations

When designing text with the extended colors:

1. **High Contrast**: Use light colors on dark backgrounds or vice versa
2. **Readability**: Test colors on actual GBA hardware or accurate emulators
3. **Consistency**: Establish a color scheme for your ROM hack
4. **Accessibility**: Consider colorblind-friendly combinations

## Implementation Status

✅ Bit field expansion completed
✅ Color constants added
✅ Core text system updated
⏳ Testing and validation in progress
⏳ Documentation completion

---

**Note**: This expanded color system is compatible with the existing Pokemon Emerald text engine and maintains backward compatibility with all original features.
