#include "global.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "task.h"
#include "overworld.h"
#include "shop.h"
#include "sound.h"
#include "strings.h"
#include "window.h"
#include "field_screen_effect.h"
#include "constants/item.h"
#include "constants/songs.h"
#include "constants/rgb.h"

// Menu actions for the store interface. The text pointers are assigned
// at runtime using the pocket name string table to avoid non-constant
// initializers.
static struct MenuAction sStoreMenuActions[6] =
{
    {NULL, {.void_u8 = NULL}},
    {NULL, {.void_u8 = NULL}},
    {NULL, {.void_u8 = NULL}},
    {NULL, {.void_u8 = NULL}},
    {NULL, {.void_u8 = NULL}},
    {NULL, {.void_u8 = NULL}},
};

// Item lists for each pocket category.
static const u16 sStoreItems_Items[] =
{
    ITEM_BLACK_FLUTE,
    ITEM_ESCAPE_ROPE,
    ITEM_FLUFFY_TAIL,
    ITEM_HONEY,
    ITEM_LURE,
    ITEM_MAX_HONEY,
    ITEM_MAX_LURE,
    ITEM_MAX_REPEL,
    ITEM_POKE_DOLL,
    ITEM_POKE_TOY,
    ITEM_REPEL,
    ITEM_SUPER_LURE,
    ITEM_SUPER_REPEL,
    ITEM_WHITE_FLUTE,
    
};

static const u16 sStoreItems_Medicine[] =
{
    ITEM_ANTIDOTE,
    ITEM_AWAKENING,
    ITEM_BERRY_JUICE,
    ITEM_BIG_MALASADA,
    ITEM_BURN_HEAL,
    ITEM_CALCIUM,
    ITEM_CARBOS,
    ITEM_CASTELIACONE,
    ITEM_ELIXIR,
    ITEM_ENERGY_POWDER,
    ITEM_ENERGY_ROOT,
    ITEM_ETHER,
    ITEM_FRESH_WATER,
    ITEM_FULL_HEAL,
    ITEM_FULL_RESTORE,
    ITEM_HEAL_POWDER,
    ITEM_HP_UP,
    ITEM_HYPER_POTION,
    ITEM_ICE_HEAL,
    ITEM_IRON,
    ITEM_LAVA_COOKIE,
    ITEM_LEMONADE,
    ITEM_LUMIOSE_GALETTE,
    ITEM_MAX_ELIXIR,
    ITEM_MAX_ETHER,
    ITEM_MAX_POTION,
    ITEM_MAX_REVIVE,
    ITEM_MOOMOO_MILK,
    ITEM_OLD_GATEAU,
    ITEM_PARALYZE_HEAL,
    ITEM_PEWTER_CRUNCHIES,
    ITEM_POTION,
    ITEM_PP_MAX,
    ITEM_PP_UP,
    ITEM_PROTEIN,
    ITEM_REVIVAL_HERB,
    ITEM_REVIVE,
    ITEM_SACRED_ASH,
    ITEM_SHALOUR_SABLE,
    ITEM_SODA_POP,
    ITEM_SUPER_POTION,
    ITEM_SWEET_HEART,
    ITEM_ZINC,
    
};

static const u16 sStoreItems_Battle[] =
{
    ITEM_ABOMASITE,
    ITEM_ABSOLITE,
    ITEM_ADAMANT_MINT,
    ITEM_AERODACTYLITE,
    ITEM_AGGRONITE,
    ITEM_ALAKAZITE,
    ITEM_ALORAICHIUM_Z,
    ITEM_ALTARIANITE,
    ITEM_AMPHAROSITE,
    ITEM_AUDINITE,
    ITEM_BANETTITE,
    ITEM_BEEDRILLITE,
    ITEM_BLACK_AUGURITE,
    ITEM_BLASTOISINITE,
    ITEM_BLAZIKENITE,
    ITEM_BOLD_MINT,
    ITEM_BRAVE_MINT,
    ITEM_BUGINIUM_Z,
    ITEM_CALM_MINT,
    ITEM_CAMERUPTITE,
    ITEM_CAREFUL_MINT,
    ITEM_CHARIZARDITE_X,
    ITEM_CHARIZARDITE_Y,
    ITEM_CLEVER_FEATHER,
    ITEM_DARKINIUM_Z,
    ITEM_DECIDIUM_Z,
    ITEM_DIANCITE,
    ITEM_DIRE_HIT,
    ITEM_DRAGONIUM_Z,
    ITEM_DYNAMAX_CANDY,
    ITEM_EEVIUM_Z,
    ITEM_ELECTRIUM_Z,
    ITEM_EXP_CANDY_L,
    ITEM_EXP_CANDY_M,
    ITEM_EXP_CANDY_S,
    ITEM_EXP_CANDY_XL,
    ITEM_EXP_CANDY_XS,
    ITEM_FAIRIUM_Z,
    ITEM_FAIRY_FEATHER,
    ITEM_FIGHTINIUM_Z,
    ITEM_FIRIUM_Z,
    ITEM_FLYINIUM_Z,
    ITEM_GALLADITE,
    ITEM_GARCHOMPITE,
    ITEM_GARDEVOIRITE,
    ITEM_GENGARITE,
    ITEM_GENIUS_FEATHER,
    ITEM_GENTLE_MINT,
    ITEM_GHOSTIUM_Z,
    ITEM_GLALITITE,
    ITEM_GRASSIUM_Z,
    ITEM_GROUNDIUM_Z,
    ITEM_GUARD_SPEC,
    ITEM_GYARADOSITE,
    ITEM_HASTY_MINT,
    ITEM_HEALTH_FEATHER,
    ITEM_HERACRONITE,
    ITEM_HOUNDOOMINITE,
    ITEM_ICIUM_Z,
    ITEM_IMPISH_MINT,
    ITEM_INCINIUM_Z,
    ITEM_JOLLY_MINT,
    ITEM_KANGASKHANITE,
    ITEM_KOMMONIUM_Z,
    ITEM_LATIASITE,
    ITEM_LATIOSITE,
    ITEM_LAX_MINT,
    ITEM_LONELY_MINT,
    ITEM_LOPUNNITE,
    ITEM_LUCARIONITE,
    ITEM_LUNALIUM_Z,
    ITEM_LYCANIUM_Z,
    ITEM_MANECTITE,
    ITEM_MARSHADIUM_Z,
    ITEM_MAWILITE,
    ITEM_MEDICHAMITE,
    ITEM_METAGROSSITE,
    ITEM_MEWNIUM_Z,
    ITEM_MEWTWONITE_X,
    ITEM_MEWTWONITE_Y,
    ITEM_MILD_MINT,
    ITEM_MIMIKIUM_Z,
    ITEM_MODEST_MINT,
    ITEM_MUSCLE_FEATHER,
    ITEM_NAIVE_MINT,
    ITEM_NAUGHTY_MINT,
    ITEM_NORMALIUM_Z,
    ITEM_PIDGEOTITE,
    ITEM_PIKANIUM_Z,
    ITEM_PIKASHUNIUM_Z,
    ITEM_PINSIRITE,
    ITEM_POISONIUM_Z,
    ITEM_PRETTY_FEATHER,
    ITEM_PRIMARIUM_Z,
    ITEM_PSYCHIUM_Z,
    ITEM_QUIET_MINT,
    ITEM_RAGECANDYBAR,
    ITEM_RAGE_CANDY_BAR,
    ITEM_RARE_CANDY,
    ITEM_RASH_MINT,
    ITEM_RELAXED_MINT,
    ITEM_RESIST_FEATHER,
    ITEM_ROCKIUM_Z,
    ITEM_SABLENITE,
    ITEM_SALAMENCITE,
    ITEM_SASSY_MINT,
    ITEM_SCEPTILITE,
    ITEM_SCIZORITE,
    ITEM_SERIOUS_MINT,
    ITEM_SHARPEDONITE,
    ITEM_SLOWBRONITE,
    ITEM_SNORLIUM_Z,
    ITEM_SOLGANIUM_Z,
    ITEM_STEELIUM_Z,
    ITEM_STEELIXITE,
    ITEM_SWAMPERTITE,
    ITEM_SWIFT_FEATHER,
    ITEM_TAPUNIUM_Z,
    ITEM_TIMID_MINT,
    ITEM_TYRANITARITE,
    ITEM_ULTRANECROZIUM_Z,
    ITEM_VENUSAURITE,
    ITEM_WATERIUM_Z,
    
};

static const u16 sStoreItems_Balls[] =
{
    ITEM_BEAST_BALL,
    ITEM_CHERISH_BALL,
    ITEM_DIVE_BALL,
    ITEM_DREAM_BALL,
    ITEM_DUSK_BALL,
    ITEM_FAST_BALL,
    ITEM_FRIEND_BALL,
    ITEM_GREAT_BALL,
    ITEM_HEAL_BALL,
    ITEM_HEAVY_BALL,
    ITEM_LEVEL_BALL,
    ITEM_LOVE_BALL,
    ITEM_LURE_BALL,
    ITEM_LUXURY_BALL,
    ITEM_MOON_BALL,
    ITEM_NEST_BALL,
    ITEM_NET_BALL,
    ITEM_PARK_BALL,
    ITEM_POKE_BALL,
    ITEM_PREMIER_BALL,
    ITEM_QUICK_BALL,
    ITEM_REPEAT_BALL,
    ITEM_SAFARI_BALL,
    ITEM_SPORT_BALL,
    ITEM_STRANGE_BALL,
    ITEM_TIMER_BALL,
    ITEM_ULTRA_BALL,
    
};

static const u16 sStoreItems_TmHm[] =
{
    ITEM_HM01,
    ITEM_HM02,
    ITEM_HM03,
    ITEM_HM04,
    ITEM_HM05,
    ITEM_HM06,
    ITEM_HM07,
    ITEM_HM08,
    ITEM_TM01,
    ITEM_TM02,
    ITEM_TM03,
    ITEM_TM04,
    ITEM_TM05,
    ITEM_TM06,
    ITEM_TM07,
    ITEM_TM08,
    ITEM_TM09,
    ITEM_TM10,
    ITEM_TM11,
    ITEM_TM12,
    ITEM_TM13,
    ITEM_TM14,
    ITEM_TM15,
    ITEM_TM16,
    ITEM_TM17,
    ITEM_TM18,
    ITEM_TM19,
    ITEM_TM20,
    ITEM_TM21,
    ITEM_TM22,
    ITEM_TM23,
    ITEM_TM24,
    ITEM_TM25,
    ITEM_TM26,
    ITEM_TM27,
    ITEM_TM28,
    ITEM_TM29,
    ITEM_TM30,
    ITEM_TM31,
    ITEM_TM32,
    ITEM_TM33,
    ITEM_TM34,
    ITEM_TM35,
    ITEM_TM36,
    ITEM_TM37,
    ITEM_TM38,
    ITEM_TM39,
    ITEM_TM40,
    ITEM_TM41,
    ITEM_TM42,
    ITEM_TM43,
    ITEM_TM44,
    ITEM_TM45,
    ITEM_TM46,
    ITEM_TM47,
    ITEM_TM48,
    ITEM_TM49,
    ITEM_TM50,
    ITEM_TM51,
    ITEM_TM52,
    ITEM_TM53,
    ITEM_TM54,
    ITEM_TM55,
    ITEM_TM56,
    ITEM_TM57,
    ITEM_TM58,
    ITEM_TM59,
    ITEM_TM60,
    ITEM_TM61,
    ITEM_TM62,
    ITEM_TM63,
    ITEM_TM64,
    ITEM_TM65,
    ITEM_TM66,
    ITEM_TM67,
    ITEM_TM68,
    ITEM_TM69,
    ITEM_TM70,
    ITEM_TM71,
    ITEM_TM72,
    ITEM_TM73,
    ITEM_TM74,
    ITEM_TM75,
    ITEM_TM76,
    ITEM_TM77,
    ITEM_TM78,
    ITEM_TM79,
    ITEM_TM80,
    ITEM_TM81,
    ITEM_TM82,
    ITEM_TM83,
    ITEM_TM84,
    ITEM_TM85,
    ITEM_TM86,
    ITEM_TM87,
    ITEM_TM88,
    ITEM_TM89,
    ITEM_TM90,
    ITEM_TM91,
    ITEM_TM92,
    ITEM_TM93,
    ITEM_TM94,
    ITEM_TM95,
    ITEM_TM96,
    ITEM_TM97,
    ITEM_TM98,
    ITEM_TM99,
    ITEM_TM100,
    
};

static const u16 sStoreItems_Berries[] =
{
    ITEM_AGUAV_BERRY,
    ITEM_APICOT_BERRY,
    ITEM_ASPEAR_BERRY,
    ITEM_BABIRI_BERRY,
    ITEM_BELUE_BERRY,
    ITEM_BERRY_JUICE,
    ITEM_BERRY_POUCH,
    ITEM_BERRY_SWEET,
    ITEM_BLUK_BERRY,
    ITEM_CHARTI_BERRY,
    ITEM_CHERI_BERRY,
    ITEM_CHESTO_BERRY,
    ITEM_CHILAN_BERRY,
    ITEM_CHOPLE_BERRY,
    ITEM_COBA_BERRY,
    ITEM_COLBUR_BERRY,
    ITEM_CORNN_BERRY,
    ITEM_CUSTAP_BERRY,
    ITEM_DURIN_BERRY,
    ITEM_ENIGMA_BERRY,
    ITEM_ENIGMA_BERRY_E_READER,
    ITEM_FIGY_BERRY,
    ITEM_GANLON_BERRY,
    ITEM_GREPA_BERRY,
    ITEM_HABAN_BERRY,
    ITEM_HONDEW_BERRY,
    ITEM_IAPAPA_BERRY,
    ITEM_JABOCA_BERRY,
    ITEM_KASIB_BERRY,
    ITEM_KEBIA_BERRY,
    ITEM_KEE_BERRY,
    ITEM_KELPSY_BERRY,
    ITEM_LANSAT_BERRY,
    ITEM_LEPPA_BERRY,
    ITEM_LIECHI_BERRY,
    ITEM_LUM_BERRY,
    ITEM_MAGOST_BERRY,
    ITEM_MAGO_BERRY,
    ITEM_MARANGA_BERRY,
    ITEM_MICLE_BERRY,
    ITEM_NANAB_BERRY,
    ITEM_NOMEL_BERRY,
    ITEM_OCCA_BERRY,
    ITEM_ORAN_BERRY,
    ITEM_PAMTRE_BERRY,
    ITEM_PASSHO_BERRY,
    ITEM_PAYAPA_BERRY,
    ITEM_PECHA_BERRY,
    ITEM_PERSIM_BERRY,
    ITEM_PETAYA_BERRY,
    ITEM_PINAP_BERRY,
    ITEM_POMEG_BERRY,
    ITEM_QUALOT_BERRY,
    ITEM_RABUTA_BERRY,
    ITEM_RAWST_BERRY,
    ITEM_RAZZ_BERRY,
    ITEM_RINDO_BERRY,
    ITEM_ROSELI_BERRY,
    ITEM_ROWAP_BERRY,
    ITEM_SALAC_BERRY,
    ITEM_SHUCA_BERRY,
    ITEM_SITRUS_BERRY,
    ITEM_SPELON_BERRY,
    ITEM_STARF_BERRY,
    ITEM_TAMATO_BERRY,
    ITEM_TANGA_BERRY,
    ITEM_WACAN_BERRY,
    ITEM_WATMEL_BERRY,
    ITEM_WEPEAR_BERRY,
    ITEM_WIKI_BERRY,
    ITEM_YACHE_BERRY,
    
};

static const u16 *const sStoreItemLists[] =
{
    sStoreItems_Items,
    sStoreItems_Medicine,
    sStoreItems_Battle,
    sStoreItems_Balls,
    sStoreItems_TmHm,
    sStoreItems_Berries,
};

enum {
    STORE_STATE_INIT,
    STORE_STATE_MAIN,
    STORE_STATE_EXIT_TO_FIELD,
    STORE_STATE_EXIT_TO_BUY,
};

#define tState     data[0]
#define tWindowId  data[1]
#define tSelectedCategory data[2]

static const struct WindowTemplate sStoreWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 13,
    .height = 10,
    .paletteNum = 15,
    .baseBlock = 1,
};

static void Task_StoreMenu(u8 taskId);
static void CB2_StoreMenu(void);
static void VBlankCB_StoreMenu(void);
static void Task_HandleStoreMenuSelection(u8 taskId);

static void CB2_StoreMenu(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_StoreMenu(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_OpenStoreFromStartMenu(void)
{
    // Populate menu texts from the pocket name table
    sStoreMenuActions[0].text = gPocketNamesStringsTable[POCKET_ITEMS];
    sStoreMenuActions[1].text = gPocketNamesStringsTable[POCKET_MEDICINE];
    sStoreMenuActions[2].text = gPocketNamesStringsTable[POCKET_BATTLE_ITEMS];
    sStoreMenuActions[3].text = gPocketNamesStringsTable[POCKET_POKE_BALLS];
    sStoreMenuActions[4].text = gPocketNamesStringsTable[POCKET_TM_HM];
    sStoreMenuActions[5].text = gPocketNamesStringsTable[POCKET_BERRIES];

    // Set function pointers (using a dummy function to avoid NULL pointers)
    sStoreMenuActions[0].func.void_u8 = Task_HandleStoreMenuSelection;
    sStoreMenuActions[1].func.void_u8 = Task_HandleStoreMenuSelection;
    sStoreMenuActions[2].func.void_u8 = Task_HandleStoreMenuSelection;
    sStoreMenuActions[3].func.void_u8 = Task_HandleStoreMenuSelection;
    sStoreMenuActions[4].func.void_u8 = Task_HandleStoreMenuSelection;
    sStoreMenuActions[5].func.void_u8 = Task_HandleStoreMenuSelection;

    // Initialize graphics system
    LoadMessageBoxAndBorderGfx();
    
    // Add fade transition to prevent flashing
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    
    // Set up graphics callbacks
    SetVBlankCallback(VBlankCB_StoreMenu);
    SetMainCallback2(CB2_StoreMenu);
    
    CreateTask(Task_StoreMenu, 0);
}

static void Task_StoreMenu(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (tState)
    {
    case STORE_STATE_INIT:
        // Wait for fade to complete before showing menu
        if (!gPaletteFade.active)
        {
            tWindowId = AddWindow(&sStoreWindowTemplate);
            SetStandardWindowBorderStyle(tWindowId, FALSE);
            PrintMenuTable(tWindowId, ARRAY_COUNT(sStoreMenuActions), sStoreMenuActions);
            InitMenuInUpperLeftCornerNormal(tWindowId, ARRAY_COUNT(sStoreMenuActions), 0);
            ScheduleBgCopyTilemapToVram(0);
            // Fade in the store menu
            BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
            tState = STORE_STATE_MAIN;
        }
        break;
    case STORE_STATE_MAIN:
    {
        s8 input = Menu_ProcessInput();
        if (input == MENU_NOTHING_CHOSEN)
            break;

        ClearStdWindowAndFrameToTransparent(tWindowId, FALSE);
        ClearWindowTilemap(tWindowId);
        RemoveWindow(tWindowId);

        if (input == MENU_B_PRESSED)
        {
            PlaySE(SE_SELECT);
            // Fade out before returning to field
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            tState = STORE_STATE_EXIT_TO_FIELD;
        }
        else
        {
            PlaySE(SE_SELECT);
            // Store the selected category and fade out
            tSelectedCategory = (u8)input;
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            tState = STORE_STATE_EXIT_TO_BUY;
        }
        break;
    }
    case STORE_STATE_EXIT_TO_FIELD:
        if (!gPaletteFade.active)
        {
            DestroyTask(taskId);
            SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
        }
        break;
    case STORE_STATE_EXIT_TO_BUY:
        if (!gPaletteFade.active)
        {
            CreateDirectBuyMenu(sStoreItemLists[tSelectedCategory]);
            DestroyTask(taskId);
        }
        break;
    }
}

static void Task_HandleStoreMenuSelection(u8 taskId)
{
    // This function will be called when a menu item is selected
    // The actual menu handling is done in Task_StoreMenu through Menu_ProcessInput()
    // So this can be empty or just play a sound effect
    PlaySE(SE_SELECT);
}
