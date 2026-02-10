#include "global.h"
#include "menu.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "event_data.h"
#include "match_call.h"
#include "field_message_box.h"
#include "text_window.h"
#include "script.h"
#include "field_name_box.h"

static EWRAM_DATA u8 sFieldMessageBoxMode = 0;
EWRAM_DATA u8 gWalkAwayFromSignpostTimer = 0;

// Speaker name system
const u8 *gCurrentSpeakerName = NULL;
static void DrawSpeakerNameInTextbox(void);

static void ExpandStringAndStartDrawFieldMessage(const u8 *, bool32);
static void StartDrawFieldMessage(void);

void InitFieldMessageBox(void)
{
    sFieldMessageBoxMode = FIELD_MESSAGE_BOX_HIDDEN;
    gTextFlags.canABSpeedUpPrint = FALSE;
    gTextFlags.useAlternateDownArrow = FALSE;
    gTextFlags.autoScroll = FALSE;
    gTextFlags.forceMidTextSpeed = FALSE;
}

#define tState data[0]

static void Task_DrawFieldMessage(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->tState)
    {
        case 0:
            if (gMsgIsSignPost)
                LoadSignPostWindowFrameGfx();
            else
                LoadMessageBoxAndBorderGfx();
            task->tState++;
            break;
        case 1:
        {
            u32 nameboxWinId = GetNameboxWindowId();
            DrawDialogueFrame(0, TRUE);
            if (nameboxWinId != WINDOW_NONE)
                DrawNamebox(nameboxWinId, NAME_BOX_BASE_TILE_NUM - NAME_BOX_BASE_TILES_TOTAL, TRUE);
            task->tState++;
            break;
        }
        case 2:
            if (RunTextPrintersAndIsPrinter0Active() != TRUE)
            {
                sFieldMessageBoxMode = FIELD_MESSAGE_BOX_HIDDEN;
                DestroyTask(taskId);
            }
    }
}

#undef tState

static void CreateTask_DrawFieldMessage(void)
{
    CreateTask(Task_DrawFieldMessage, 0x50);
}

static void DestroyTask_DrawFieldMessage(void)
{
    u8 taskId = FindTaskIdByFunc(Task_DrawFieldMessage);
    if (taskId != TASK_NONE)
        DestroyTask(taskId);
}

bool8 ShowFieldMessage(const u8 *str)
{
    if (sFieldMessageBoxMode != FIELD_MESSAGE_BOX_HIDDEN)
        return FALSE;
    ExpandStringAndStartDrawFieldMessage(str, TRUE);
    sFieldMessageBoxMode = FIELD_MESSAGE_BOX_NORMAL;
    return TRUE;
}

static void Task_HidePokenavMessageWhenDone(u8 taskId)
{
    if (!IsMatchCallTaskActive())
    {
        sFieldMessageBoxMode = FIELD_MESSAGE_BOX_HIDDEN;
        DestroyTask(taskId);
    }
}

bool8 ShowPokenavFieldMessage(const u8 *str)
{
    if (sFieldMessageBoxMode != FIELD_MESSAGE_BOX_HIDDEN)
        return FALSE;
    StringExpandPlaceholders(gStringVar4, str);
    CreateTask(Task_HidePokenavMessageWhenDone, 0);
    StartMatchCallFromScript(str);
    sFieldMessageBoxMode = FIELD_MESSAGE_BOX_NORMAL;
    return TRUE;
}

bool8 ShowFieldAutoScrollMessage(const u8 *str)
{
    if (sFieldMessageBoxMode != FIELD_MESSAGE_BOX_HIDDEN)
        return FALSE;
    sFieldMessageBoxMode = FIELD_MESSAGE_BOX_AUTO_SCROLL;
    ExpandStringAndStartDrawFieldMessage(str, FALSE);
    return TRUE;
}

static bool8 UNUSED ForceShowFieldAutoScrollMessage(const u8 *str)
{
    sFieldMessageBoxMode = FIELD_MESSAGE_BOX_AUTO_SCROLL;
    ExpandStringAndStartDrawFieldMessage(str, TRUE);
    return TRUE;
}

// Same as ShowFieldMessage, but instead of accepting a
// string arg it just prints whats already in gStringVar4
bool8 ShowFieldMessageFromBuffer(void)
{
    if (sFieldMessageBoxMode != FIELD_MESSAGE_BOX_HIDDEN)
        return FALSE;
    sFieldMessageBoxMode = FIELD_MESSAGE_BOX_NORMAL;
    StartDrawFieldMessage();
    return TRUE;
}

static void ExpandStringAndStartDrawFieldMessage(const u8 *str, bool32 allowSkippingDelayWithButtonPress)
{
    TrySpawnNamebox(NAME_BOX_BASE_TILE_NUM);
    StringExpandPlaceholders(gStringVar4, str);
    DrawSpeakerNameInTextbox();
    AddTextPrinterForMessage(allowSkippingDelayWithButtonPress);
    CreateTask_DrawFieldMessage();
}

static void StartDrawFieldMessage(void)
{
    DrawSpeakerNameInTextbox();
    AddTextPrinterForMessage(TRUE);
    CreateTask_DrawFieldMessage();
}

void HideFieldMessageBox(void)
{
    DestroyTask_DrawFieldMessage();
    ClearDialogWindowAndFrame(0, TRUE);
    DestroyNamebox();
    sFieldMessageBoxMode = FIELD_MESSAGE_BOX_HIDDEN;
}

u8 GetFieldMessageBoxMode(void)
{
    return sFieldMessageBoxMode;
}

bool8 IsFieldMessageBoxHidden(void)
{
    if (sFieldMessageBoxMode == FIELD_MESSAGE_BOX_HIDDEN)
        return TRUE;
    return FALSE;
}

static void UNUSED ReplaceFieldMessageWithFrame(void)
{
    DestroyTask_DrawFieldMessage();
    DrawStdWindowFrame(0, TRUE);
    sFieldMessageBoxMode = FIELD_MESSAGE_BOX_HIDDEN;
}

void StopFieldMessage(void)
{
    DestroyTask_DrawFieldMessage();
    gCurrentSpeakerName = NULL; // Clear speaker name when stopping
    sFieldMessageBoxMode = FIELD_MESSAGE_BOX_HIDDEN;
}

// Speaker name management functions
void SetSpeakerName(const u8 *name)
{
    gCurrentSpeakerName = name;
}

void ClearSpeakerName(void)
{
    gCurrentSpeakerName = NULL;
}

// Draw speaker name inside the textbox area
static void DrawSpeakerNameInTextbox(void)
{
    if (gCurrentSpeakerName == NULL)
        return;
    
    // Skip drawing speaker name if suppressed via config flag
    if (OW_FLAG_SUPPRESS_SPEAKER_NAME && FlagGet(OW_FLAG_SUPPRESS_SPEAKER_NAME))
        return;

    // Create a formatted string with speaker name and color codes
    u8 speakerText[128];
    
    // Use color control codes to make speaker name stand out
    // Format: [FC][01][03] = color light gray, then speaker name, then [FC][01][01] = back to white
    speakerText[0] = EXT_CTRL_CODE_BEGIN;
    speakerText[1] = EXT_CTRL_CODE_COLOR;
    speakerText[2] = TEXT_COLOR_LIGHT_BLUE;
    
    u32 pos = 3;
    StringCopy(&speakerText[pos], gCurrentSpeakerName);
    pos += StringLength(gCurrentSpeakerName);
    
    // Add colon and space
    speakerText[pos++] = CHAR_COLON;
    speakerText[pos++] = CHAR_SPACE;
    
    // Reset to gray text color for dialogue
    speakerText[pos++] = EXT_CTRL_CODE_BEGIN;
    speakerText[pos++] = EXT_CTRL_CODE_COLOR;
    speakerText[pos++] = TEXT_COLOR_DARK_GRAY;
    speakerText[pos] = EOS;
    
    // Prepend speaker name to the current message
    u8 tempBuffer[1024];
    StringCopy(tempBuffer, speakerText);
    StringAppend(tempBuffer, gStringVar4);
    
    // Ensure text fits within textbox by adding line breaks if needed
    // Standard textbox is about 27 characters wide
    u32 maxLineLength = 25; // Leave some margin
    u32 speakerNameLength = StringLength(gCurrentSpeakerName) + 2; // +2 for ": "
    
    // Check if we need to add a line break after speaker name
    if (speakerNameLength > maxLineLength - 5) // If speaker name is too long
    {
        // Add newline after speaker name
        u8 finalBuffer[1024];
        StringCopy(finalBuffer, speakerText);
        u32 len = StringLength(finalBuffer);
        finalBuffer[len] = CHAR_NEWLINE;
        finalBuffer[len + 1] = EOS;
        StringAppend(finalBuffer, gStringVar4);
        StringCopy(gStringVar4, finalBuffer);
    }
    else
    {
        StringCopy(gStringVar4, tempBuffer);
    }
}
