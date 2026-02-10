#include "global.h"
#include "constants/songs.h"
#include "bg.h"
#include "decoration.h"
#include "event_scripts.h"
#include "event_object_movement.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "international_string_util.h"
#include "item.h"
#include "item_icon.h"
#include "item_menu.h"
#include "constants/items.h"
#include "list_menu.h"
#include "mail.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "player_pc.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "window.h"
#include "menu_specialized.h"

// Top level PC menu options
enum {
    // MENU_ITEMSTORAGE,     // DISABLED: Item Storage functionality removed
    // MENU_MAILBOX,         // DISABLED: Mailbox functionality removed
    MENU_DECORATION,
    MENU_TURNOFF
};

// Item storage menu options - DISABLED: Item Storage functionality removed
/*
enum {
    MENU_WITHDRAW,
    MENU_DEPOSIT,
    MENU_TOSS,
    MENU_EXIT
};
*/

// Windows for the main menus (top level menu, and item storage menu)
enum {
    WIN_MAIN_MENU,
    WIN_MAIN_MENU_BEDROOM,
    WIN_ITEM_STORAGE_MENU,
};

// Windows for item storage (while viewing the PC's item inventory)
enum {
    ITEMPC_WIN_LIST,
    ITEMPC_WIN_MESSAGE,
    ITEMPC_WIN_ICON,
    ITEMPC_WIN_TITLE,
    ITEMPC_WIN_QUANTITY,
    ITEMPC_WIN_YESNO,
    ITEMPC_WIN_COUNT
};
 // When showing the main list, the first window to this window are drawn
#define ITEMPC_WIN_LIST_END ITEMPC_WIN_TITLE

// Message IDs for Item Storage
enum {
    MSG_SWITCH_WHICH_ITEM = 0xFFF7,
    MSG_OKAY_TO_THROW_AWAY,
    MSG_TOO_IMPORTANT,
    MSG_NO_MORE_ROOM,
    MSG_THREW_AWAY_ITEM,
    MSG_HOW_MANY_TO_TOSS,
    MSG_WITHDREW_ITEM,
    MSG_HOW_MANY_TO_WITHDRAW,
    MSG_GO_BACK_TO_PREV
};

#define TAG_ITEM_ICON    5110
#define TAG_SCROLL_ARROW 5112

// Item list ID for toSwapPos to indicate an item is not currently being swapped
#define NOT_SWAPPING 0xFF

#define SWAP_LINE_LENGTH 7

/*
// DISABLED: Item Storage functionality removed
struct ItemStorageMenu
{
    struct ListMenuItem listItems[PC_ITEMS_COUNT + 1];
    u8 itemNames[PC_ITEMS_COUNT + 1][ITEM_NAME_LENGTH + 10];
    u8 windowIds[ITEMPC_WIN_COUNT];
    u8 toSwapPos;
    u8 spriteId;
    u8 swapLineSpriteIds[SWAP_LINE_LENGTH];
};
*/

static void InitPlayerPCMenu(u8);
static void PlayerPCProcessMenuInput(u8);
// DISABLED: Item Storage functionality removed
// static void InitItemStorageMenu(u8, u8);

// DISABLED: Mailbox functionality removed
/*
static u8 GetMailboxMailCount(void);
static void Mailbox_CompactMailList(void);
static void Mailbox_DrawMailboxMenu(u8);
static void Mailbox_ProcessInput(u8);
static void Mailbox_PrintWhatToDoWithPlayerMailText(u8);
static void Mailbox_ReturnToPlayerPC(u8);
static void Mailbox_PrintMailOptions(u8);
static void Mailbox_MailOptionsProcessInput(u8);
*/

// DISABLED: Item Storage and Mailbox functionality removed
/*
static void PlayerPC_ItemStorage(u8);
static void PlayerPC_Mailbox(u8);
*/
static void PlayerPC_Decoration(u8);
static void PlayerPC_TurnOff(u8);

// DISABLED: Mailbox functionality removed
/*
static void Mailbox_DoMailMoveToBag(u8);
static void Mailbox_DoMailRead(u8);
static void Mailbox_MoveToBag(u8);
static void Mailbox_Give(u8);
static void Mailbox_Cancel(u8);

static void Mailbox_CancelMoveToBag(u8);
static void Mailbox_HandleConfirmMoveToBag(u8);
static void Mailbox_AskConfirmMoveToBag(u8);
static void Mailbox_DoGiveMailPokeMenu(u8);
static void Mailbox_NoPokemonForMail(u8);

static void Mailbox_FadeAndReadMail(u8);
static void Mailbox_ReturnToFieldFromReadMail(void);
static void Mailbox_ReshowAfterMail(void);
static void Mailbox_HandleReturnToProcessInput(u8);
static void Mailbox_UpdateMailListAfterDeposit(void);
*/

// DISABLED: Item Storage functionality removed
/*
static void ItemStorage_Withdraw(u8);
static void ItemStorage_Deposit(u8);
static void ItemStorage_Toss(u8);
static void ItemStorage_Exit(u8);
static void ItemStorage_TossItemYes(u8);
static void ItemStorage_TossItemNo(u8);

static void ItemStorageMenuPrint(const u8 *);
static void ItemStorageMenuProcessInput(u8);
static void SetPlayerPCListCount(u8);
static void ItemStorage_HandleReturnToProcessInput(u8);

static void ItemStorage_Enter(u8, bool8);
static void ItemStorage_CreateListMenu(u8);
static void ItemStorage_ProcessInput(u8);
static void Task_ItemStorage_Deposit(u8);
static void ItemStorage_ReshowAfterBagMenu(void);
static void ItemStorage_DoItemWithdraw(u8);
static void ItemStorage_DoItemToss(u8);
static void ItemStorage_HandleQuantityRolling(u8);
static void ItemStorage_ExitItemList(u8);
static void ItemStorage_StartItemSwap(u8);
static void ItemStorage_DoItemAction(u8);
static void ItemStorage_FinishItemSwap(u8, bool8);
static void ItemStorage_HandleRemoveItem(u8);
static void ItemStorage_HandleErrorMessageInput(u8);
static void ItemStorage_ReturnToListInput(u8);

static const u8 *ItemStorage_GetMessage(u16);
static void CopyItemName_PlayerPC(u8 *, u16);

static void ItemStorage_Init(void);
static void ItemStorage_DrawSwapArrow(u8, u8, u8);
static void ItemStorage_RemoveWindow(u8);
static void ItemStorage_UpdateSwapLinePos(u8);
static void ItemStorage_ProcessItemSwapInput(u8);
static void ItemStorage_EraseItemIcon(void);
static void ItemStorage_DrawItemIcon(u16);
static void ItemStorage_PrintDescription(s32);
static void ItemStorage_EraseMainMenu(u8);
static void ItemStorage_MoveCursor(s32, bool8, struct ListMenu *);
static void ItemStorage_PrintMenuItem(u8, u32, u8);
*/

static EWRAM_DATA const u8 *sTopMenuOptionOrder = NULL;
static EWRAM_DATA u8 sTopMenuNumOptions = 0;
EWRAM_DATA struct PlayerPCItemPageStruct gPlayerPCItemPageInfo = {};
// DISABLED: Item Storage functionality removed
// static EWRAM_DATA struct ItemStorageMenu *sItemStorageMenu = NULL;

// DISABLED: Item Storage and Mailbox text strings removed
/*
static const u8 sText_WithdrawItem[] = _("WITHDRAW ITEM");
static const u8 sText_DepositItem[] = _("DEPOSIT ITEM");
static const u8 sText_TossItem[] = _("TOSS ITEM");
static const u8 sText_Mailbox[] = _("MAILBOX");

static const u8 sText_WithdrawHowManyItems[] = _("Withdraw how many\n{STR_VAR_1}?");
static const u8 sText_WithdrawXItems[] = _("Withdrew {STR_VAR_2}\n{STR_VAR_1}.");
static const u8 sText_NoRoomInBag[] = _("There is no more\nroom in the BAG.");
static const u8 sText_TooImportantToToss[] = _("That's much too\nimportant to toss\nout!");

static const u8 *const sItemStorage_OptionDescriptions[] =
{
    [MENU_WITHDRAW] = COMPOUND_STRING("Take out items from the PC."),
    [MENU_DEPOSIT]  = COMPOUND_STRING("Store items in the PC."),
    [MENU_TOSS]     = COMPOUND_STRING("Throw away items stored in the PC."),
    [MENU_EXIT]     = gText_GoBackPrevMenu,
};
*/

static const struct MenuAction sPlayerPCMenuActions[] =
{
    // [MENU_ITEMSTORAGE] = { COMPOUND_STRING("ITEM STORAGE"), {PlayerPC_ItemStorage} },  // DISABLED: Item Storage functionality removed
    // [MENU_MAILBOX]     = { sText_Mailbox,                   {PlayerPC_Mailbox} },      // DISABLED: Mailbox functionality removed
    [MENU_DECORATION]  = { COMPOUND_STRING("DECORATION"),   {PlayerPC_Decoration} },
    [MENU_TURNOFF]     = { COMPOUND_STRING("TURN OFF"),     {PlayerPC_TurnOff} }
};

static const u8 sBedroomPC_OptionOrder[] =
{
    // MENU_ITEMSTORAGE,  // DISABLED: Item Storage functionality removed
    // MENU_MAILBOX,      // DISABLED: Mailbox functionality removed
    MENU_DECORATION,
    MENU_TURNOFF
};
#define NUM_BEDROOM_PC_OPTIONS ARRAY_COUNT(sBedroomPC_OptionOrder)

static const u8 sPlayerPC_OptionOrder[] =
{
    // MENU_ITEMSTORAGE,  // DISABLED: Item Storage functionality removed
    // MENU_MAILBOX,      // DISABLED: Mailbox functionality removed
    MENU_TURNOFF
};
#define NUM_PLAYER_PC_OPTIONS ARRAY_COUNT(sPlayerPC_OptionOrder)

// DISABLED: Item Storage menu actions removed
/*
static const struct MenuAction sItemStorage_MenuActions[] =
{
    [MENU_WITHDRAW] = { sText_WithdrawItem, {ItemStorage_Withdraw} },
    [MENU_DEPOSIT]  = { sText_DepositItem,  {ItemStorage_Deposit} },
    [MENU_TOSS]     = { sText_TossItem,     {ItemStorage_Toss} },
    [MENU_EXIT]     = { gText_Cancel,       {ItemStorage_Exit} }
};
*/

// DISABLED: Mailbox mail options removed
/*
const struct MenuAction gMailboxMailOptions[] =
{
    { COMPOUND_STRING("READ"),        {Mailbox_DoMailRead} },
    { COMPOUND_STRING("MOVE TO BAG"), {Mailbox_MoveToBag} },
    { COMPOUND_STRING("GIVE"),        {Mailbox_Give} },
    { gText_Cancel2,                  {Mailbox_Cancel} }
};
*/

static const struct WindowTemplate sWindowTemplates_MainMenus[] =
{
    [WIN_MAIN_MENU] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 9,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 1
    },
    [WIN_MAIN_MENU_BEDROOM] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 9,
        .height = 8,
        .paletteNum = 15,
        .baseBlock = 1
    },
    // DISABLED: Item Storage window template removed
    /*
    [WIN_ITEM_STORAGE_MENU] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 10,
        .height = 8,
        .paletteNum = 15,
        .baseBlock = 1
    }
    */
};

// DISABLED: Item Storage functionality removed
/*
static const struct YesNoFuncTable ItemTossYesNoFuncs =
{
    ItemStorage_TossItemYes,
    ItemStorage_TossItemNo
};

static const struct ListMenuTemplate sListMenuTemplate_ItemStorage =
{
    .items = NULL,
    .moveCursorFunc = ItemStorage_MoveCursor,
    .itemPrintFunc = ItemStorage_PrintMenuItem,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 9,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = FALSE,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = FONT_NARROW,
    .cursorKind = CURSOR_BLACK_ARROW,
    .textNarrowWidth = 74,
};

static const struct WindowTemplate sWindowTemplates_ItemStorage[ITEMPC_WIN_COUNT] =
{
    [ITEMPC_WIN_LIST] = {
        .bg = 0,
        .tilemapLeft = 16,
        .tilemapTop = 1,
        .width = 13,
        .height = 18,
        .paletteNum = 15,
        .baseBlock = 0x0001
    },
    [ITEMPC_WIN_MESSAGE] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 13,
        .width = 13,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x00EB
    },
    [ITEMPC_WIN_ICON] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 8,
        .width = 3,
        .height = 3,
        .paletteNum = 15,
        .baseBlock = 0x0153
    },
    [ITEMPC_WIN_TITLE] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 13,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x0139
    },
    [ITEMPC_WIN_QUANTITY] = {
        .bg = 0,
        .tilemapLeft = 8,
        .tilemapTop = 9,
        .width = 6,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x015C
    },
    [ITEMPC_WIN_YESNO] = {
        .bg = 0,
        .tilemapLeft = 9,
        .tilemapTop = 7,
        .width = 5,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x0168
    }
};

static const u8 sSwapArrowTextColors[] = {TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY, TEXT_COLOR_DARK_GRAY};
*/

// DISABLED: PC Items initialization removed
/*
void NewGameInitPCItems(void)
{
    u8 i = 0;
    CpuFastFill(0, gSaveBlock1Ptr->pcItems, sizeof(gSaveBlock1Ptr->pcItems));

    while (TRUE)
    {
        if (sNewGamePCItems[i][0] == ITEM_NONE || sNewGamePCItems[i][1] == 0)
            break;
        if (AddPCItem(sNewGamePCItems[i][0], sNewGamePCItems[i][1]) != TRUE)
            break;
        i++;
    }
}
*/

void BedroomPC(void)
{
    sTopMenuOptionOrder = sBedroomPC_OptionOrder;
    sTopMenuNumOptions = NUM_BEDROOM_PC_OPTIONS;
    DisplayItemMessageOnField(CreateTask(TaskDummy, 0), gText_WhatWouldYouLike, InitPlayerPCMenu);
}

void PlayerPC(void)
{
    sTopMenuOptionOrder = sPlayerPC_OptionOrder;
    sTopMenuNumOptions = NUM_PLAYER_PC_OPTIONS;
    DisplayItemMessageOnField(CreateTask(TaskDummy, 0), gText_WhatWouldYouLike, InitPlayerPCMenu);
}

#define tUsedSlots  data[1]
#define tQuantity   data[2]
#define tInTossMenu data[3]
#define tWindowId   data[4]
#define tListTaskId data[5]

static void InitPlayerPCMenu(u8 taskId)
{
    s16 *data;
    struct WindowTemplate windowTemplate;
    data = gTasks[taskId].data;

    if (sTopMenuNumOptions == NUM_PLAYER_PC_OPTIONS)
        windowTemplate = sWindowTemplates_MainMenus[WIN_MAIN_MENU];
    else // Bedroom PC
        windowTemplate = sWindowTemplates_MainMenus[WIN_MAIN_MENU_BEDROOM];

    windowTemplate.width = GetMaxWidthInSubsetOfMenuTable(sPlayerPCMenuActions, sTopMenuOptionOrder, sTopMenuNumOptions);
    tWindowId = AddWindow(&windowTemplate);
    SetStandardWindowBorderStyle(tWindowId, FALSE);
    PrintMenuActionTextsInUpperLeftCorner(tWindowId, sTopMenuNumOptions, sPlayerPCMenuActions, sTopMenuOptionOrder);
    InitMenuInUpperLeftCornerNormal(tWindowId, sTopMenuNumOptions, 0);
    ScheduleBgCopyTilemapToVram(0);
    gTasks[taskId].func = PlayerPCProcessMenuInput;
}

static void PlayerPCProcessMenuInput(u8 taskId)
{
    s16 *data;
    s8 inputOptionId;

    data = gTasks[taskId].data;
    if (sTopMenuNumOptions > 3)
        inputOptionId = Menu_ProcessInput();
    else
        inputOptionId = Menu_ProcessInputNoWrap();

    switch (inputOptionId)
    {
    case MENU_NOTHING_CHOSEN:
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        ClearStdWindowAndFrameToTransparent(tWindowId, FALSE);
        ClearWindowTilemap(tWindowId);
        RemoveWindow(tWindowId);
        ScheduleBgCopyTilemapToVram(0);
        gTasks[taskId].func = PlayerPC_TurnOff;
        break;
    default:
        ClearStdWindowAndFrameToTransparent(tWindowId, FALSE);
        ClearWindowTilemap(tWindowId);
        RemoveWindow(tWindowId);
        ScheduleBgCopyTilemapToVram(0);
        gTasks[taskId].func = sPlayerPCMenuActions[sTopMenuOptionOrder[inputOptionId]].func.void_u8;
        break;
    }
}

void ReshowPlayerPC(u8 var)
{
    DisplayItemMessageOnField(var, gText_WhatWouldYouLike, InitPlayerPCMenu);
}

// DISABLED: Item Storage and Mailbox functionality removed
/*
static void PlayerPC_ItemStorage(u8 taskId)
{
    InitItemStorageMenu(taskId, MENU_WITHDRAW);
    gTasks[taskId].func = ItemStorageMenuProcessInput;
}

static void PlayerPC_Mailbox(u8 taskId)
{
    gPlayerPCItemPageInfo.count = GetMailboxMailCount();

    if (gPlayerPCItemPageInfo.count == 0)
    {
        // Mailbox cannot be opened if no mail is in PC
        DisplayItemMessageOnField(taskId, gText_NoMailHere, ReshowPlayerPC);
    }
    else
    {
        gPlayerPCItemPageInfo.cursorPos = 0;
        gPlayerPCItemPageInfo.itemsAbove = 0;
        gPlayerPCItemPageInfo.scrollIndicatorTaskId = TASK_NONE;
        Mailbox_CompactMailList();
        SetPlayerPCListCount(taskId);
        if (MailboxMenu_Alloc(gPlayerPCItemPageInfo.count) == TRUE)
        {
            ClearDialogWindowAndFrame(0, FALSE);
            Mailbox_DrawMailboxMenu(taskId);
            gTasks[taskId].func = Mailbox_ProcessInput;
        }
        else
        {
            // Alloc failed, exit Mailbox
            DisplayItemMessageOnField(taskId, gText_NoMailHere, ReshowPlayerPC);
        }
    }
}
*/

static void PlayerPC_Decoration(u8 taskId)
{
    DoPlayerRoomDecorationMenu(taskId);
}

static void PlayerPC_TurnOff(u8 taskId)
{
    if (sTopMenuNumOptions == NUM_BEDROOM_PC_OPTIONS) // Flimsy way to determine if Bedroom PC is in use
    {
        if (gSaveBlock2Ptr->playerGender == MALE)
            ScriptContext_SetupScript(LittlerootTown_BrendansHouse_2F_EventScript_TurnOffPlayerPC);
        else
            ScriptContext_SetupScript(LittlerootTown_MaysHouse_2F_EventScript_TurnOffPlayerPC);
    }
    else
    {
        ScriptContext_Enable();
    }
    DestroyTask(taskId);
}

// DISABLED: All Item Storage and Mailbox functionality has been removed
// This includes hundreds of lines of code for:
// - Item Storage menu system
// - Mailbox functionality 
// - PC item management
// - Item withdraw/deposit/toss operations
// - Mail handling
// - UI and window management for these features
// All functions have been commented out to disable this functionality
