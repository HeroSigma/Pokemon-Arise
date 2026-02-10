# Speaker Name System

This document explains how to use the new speaker name system that displays who is speaking in textboxes without requiring you to manually add the NPC name before the text.

## Overview

The speaker name system automatically displays the name of the current speaker at the beginning of dialogue text, formatted in light blue to distinguish it from the main dialogue text (which appears in dark gray). The name appears as "Speaker Name: " followed by the dialogue text.

## How It Works

When a speaker name is set, it gets automatically prepended to any dialogue text that appears in textboxes. The speaker name is displayed in light blue text with a colon and space, followed by the dialogue text in dark gray for better readability.

**Example:**
- Without speaker name: `"Hello! How are you doing?"`
- With speaker name "Prof. Oak": `"Prof. Oak: Hello! How are you doing?"`

## Usage

### In Scripts

Use the existing script commands that support speaker names:

```
setspeaker Prof. Oak
msgbox SomeDialogueText, MSGBOX_DEFAULT
```

### In Code

```c
// Set the speaker name
SetSpeakerName(_("Prof. Oak"));

// Show a message - the speaker name will automatically be prepended
ShowFieldMessage(_("Hello! How are you doing?"));

// Clear the speaker name when done
ClearSpeakerName();
```

### Automatic Usage

The system automatically works for:
- **Trainer battles**: Trainer names are automatically set as speakers during battle intro speeches
- **Script messages**: Any script command that previously supported speaker names will continue to work
- **Frontier facilities**: Battle Pyramid and Trainer Hill automatically set facility trainer names

## Functions

### SetSpeakerName(const u8 *name)
Sets the current speaker name. This name will be prepended to all subsequent dialogue until cleared.

### ClearSpeakerName(void)
Clears the current speaker name. Subsequent dialogue will not have a speaker name.

### gCurrentSpeakerName
Global variable that holds the current speaker name (can be NULL).

## Configuration

### Suppressing Speaker Names

You can disable speaker name display by setting the `OW_FLAG_SUPPRESS_SPEAKER_NAME` flag:

```c
// In include/config/overworld.h, set to a real flag ID:
#define OW_FLAG_SUPPRESS_SPEAKER_NAME FLAG_UNUSED_0x264

// Then in game or script:
setflag FLAG_UNUSED_0x264  // Disable speaker names
clearflag FLAG_UNUSED_0x264  // Re-enable speaker names
```

## Technical Details

- Speaker names are automatically cleared when textboxes are hidden or stopped
- The system uses text color control codes to format the speaker name in light blue and dialogue text in dark gray
- The speaker name is prepended to the message text before it's displayed with automatic line wrapping for long names
- No additional windows or UI elements are created - everything happens within the existing textbox

## Benefits

1. **Clean Integration**: No separate nameplate windows that could cause visual issues
2. **Automatic Management**: Speaker names are automatically cleared when appropriate
3. **Backward Compatible**: All existing script commands continue to work
4. **Configurable**: Can be disabled via flag if needed
5. **Consistent Formatting**: Speaker names always appear in the same color and format

## Migration from Old System

If you were previously manually adding speaker names to your dialogue text, you can now:

1. Remove the speaker names from your dialogue strings
2. Use `SetSpeakerName()` before showing the dialogue
3. The system will automatically format and display the speaker name

This provides cleaner, more maintainable dialogue scripts and consistent formatting across your game.
