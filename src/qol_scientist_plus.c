// QoL Scientist: money, region, ball legality, numeric spinner, regional messages
#include "global.h"
#include "qol_scientist.h"
#include "event_data.h"
#include "money.h"
#include "overworld.h"
#include "pokemon.h"
#include "main.h"
#include "script.h"
#include "task.h"
#include "window.h"
#include "text.h"
#include "menu.h"
#include "string_util.h"
#include "strings.h"
#include "item.h"
#include "pokeball.h"
#include "party_menu.h"
#include "pokemon.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/abilities.h"
#include "constants/battle.h"
#include "constants/pokemon.h"
#include "constants/party_menu.h"
#include "regions.h"
#include "data.h" // struct TypeInfo, gTypesInfo

// Forward declarations for static helpers used before definition
static u16 sQol_GetSlot(void);

// ---------- Region detection ----------
u8 QoL_GetCurrentRegionId(void)
{
    // Map from general Region -> QoL region id. Default Hoenn.
    switch (GetCurrentRegion())
    {
    case REGION_KANTO: return QOL_REGION_KANTO;
    case REGION_JOHTO: return QOL_REGION_JOHTO;
    case REGION_SINNOH: return QOL_REGION_SINNOH;
    // No dedicated Sevii region in constants; keep default Hoenn.
    default: return QOL_REGION_HOENN;
    }
}

// ---------- Money ----------
bool8 QoL_TakeMoneyIfEnough(u32 cost)
{
    if (GetMoney(&gSaveBlock1Ptr->money) < cost) return FALSE;
    RemoveMoney(&gSaveBlock1Ptr->money, cost);
    return TRUE;
}

// ---------- Mon checks ----------
bool8 QoL_IsMonShiny(struct Pokemon *mon) { return GetMonData(mon, MON_DATA_IS_SHINY, NULL); }

__attribute__((weak)) bool8 IsLegendarySpecies(u16 species) { return FALSE; }
__attribute__((weak)) bool8 IsMythicalSpecies(u16 species) { return FALSE; }
__attribute__((weak)) bool8 IsUltraBeastSpecies(u16 species){ return FALSE; }

bool8 QoL_IsMonLegendaryOrMythical(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    return IsLegendarySpecies(species) || IsMythicalSpecies(species);
}
bool8 QoL_IsMonUltraBeast(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    return IsUltraBeastSpecies(species);
}

// ---------- Ball legality ----------
static bool8 ItemIsBall_(u16 item)
{
    return ItemIdToBallId(item) != BALL_STRANGE;
}

bool8 QoL_BallIsLegalForMon(u16 item, struct Pokemon *mon)
{
    if (!ItemIsBall_(item)) return FALSE;
    if (GetMonData(mon, MON_DATA_IS_EGG, NULL)) return FALSE;

    if (item == ITEM_CHERISH_BALL)
        if (!QoL_IsMonShiny(mon) && !QoL_IsMonLegendaryOrMythical(mon))
            return FALSE;

    if (item == ITEM_BEAST_BALL)
        if (!QoL_IsMonUltraBeast(mon))
            return FALSE;

    return TRUE;
}

// ---------- Region strings (externs) ----------
extern const u8 gText_QoLHello_Hoenn[],  gText_QoLHello_Johto[],  gText_QoLHello_Kanto[],  gText_QoLHello_Sevii[],  gText_QoLHello_Sinnoh[];
extern const u8 gText_QoL_NotEnoughMoney_Hoenn[], gText_QoL_NotEnoughMoney_Johto[], gText_QoL_NotEnoughMoney_Kanto[], gText_QoL_NotEnoughMoney_Sevii[], gText_QoL_NotEnoughMoney_Sinnoh[];
extern const u8 gText_QoL_IllegalBall_Hoenn[],  gText_QoL_IllegalBall_Johto[],  gText_QoL_IllegalBall_Kanto[],  gText_QoL_IllegalBall_Sevii[],  gText_QoL_IllegalBall_Sinnoh[];
extern const u8 gText_QoL_Charged_Hoenn[], gText_QoL_Charged_Johto[], gText_QoL_Charged_Kanto[], gText_QoL_Charged_Sevii[], gText_QoL_Charged_Sinnoh[];
extern const u8 gText_QoL_Canceled_Hoenn[], gText_QoL_Canceled_Johto[], gText_QoL_Canceled_Kanto[], gText_QoL_Canceled_Sevii[], gText_QoL_Canceled_Sinnoh[];

static const u8 *Sel(const u8 *const tbl[5])
{
    u8 r = QoL_GetCurrentRegionId();
    if (r > QOL_REGION_SINNOH) r = QOL_REGION_HOENN;
    return tbl[r];
}

static void CopyRegional(const u8 *const tbl[5])
{
    StringCopy(gStringVar4, Sel(tbl));
}

void Script_QoL_Msg_Hello(void) {
    static const u8 *const t[5] = {gText_QoLHello_Hoenn,gText_QoLHello_Johto,gText_QoLHello_Kanto,gText_QoLHello_Sevii,gText_QoLHello_Sinnoh};
    CopyRegional(t);
}
void Script_QoL_Msg_NotEnoughMoney(void) {
    static const u8 *const t[5] = {gText_QoL_NotEnoughMoney_Hoenn,gText_QoL_NotEnoughMoney_Johto,gText_QoL_NotEnoughMoney_Kanto,gText_QoL_NotEnoughMoney_Sevii,gText_QoL_NotEnoughMoney_Sinnoh};
    CopyRegional(t);
}
void Script_QoL_Msg_IllegalBall(void) {
    static const u8 *const t[5] = {gText_QoL_IllegalBall_Hoenn,gText_QoL_IllegalBall_Johto,gText_QoL_IllegalBall_Kanto,gText_QoL_IllegalBall_Sevii,gText_QoL_IllegalBall_Sinnoh};
    CopyRegional(t);
}
void Script_QoL_Msg_Charged(void) {
    static const u8 *const t[5] = {gText_QoL_Charged_Hoenn,gText_QoL_Charged_Johto,gText_QoL_Charged_Kanto,gText_QoL_Charged_Sevii,gText_QoL_Charged_Sinnoh};
    CopyRegional(t);
}
void Script_QoL_Msg_Canceled(void) {
    static const u8 *const t[5] = {gText_QoL_Canceled_Hoenn,gText_QoL_Canceled_Johto,gText_QoL_Canceled_Kanto,gText_QoL_Canceled_Sevii,gText_QoL_Canceled_Sinnoh};
    CopyRegional(t);
}

// ---------- Confirmation helpers ----------
extern const struct NatureInfo gNaturesInfo[];
void Script_QoL_Msg_ConfirmNature(void)
{
    u16 nat = VarGet(VAR_0x8000);
    if (nat >= NUM_NATURES)
        nat = 0;
    StringCopy(gStringVar1, gNaturesInfo[nat].name);
    StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("Change nature to {STR_VAR_1}?\nCost: ¥1000."));
}

// Show current ability and the standard cost
void Script_QoL_Msg_AbilityInfo(void)
{
    u16 slot = sQol_GetSlot();
    struct Pokemon *mon = &gPlayerParty[slot];
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u8 abilityNum = GetMonData(mon, MON_DATA_ABILITY_NUM, NULL);
    u16 abilityId = GetSpeciesAbility(species, abilityNum);
    if (abilityId >= ABILITIES_COUNT)
        abilityId = 0;
    StringCopy(gStringVar1, gAbilitiesInfo[abilityId].name);
    StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("Current ability: {STR_VAR_1}\nCost: ¥1000."));
}

static u16 sQol_GetSlot(void)
{
    u16 slot = VarGet(VAR_0x8006);
    if (slot >= PARTY_SIZE)
        slot = VarGet(VAR_0x8004);
    if (slot >= PARTY_SIZE)
        slot = 0;
    return slot;
}

// Current minted (hidden) nature info
extern const struct NatureInfo gNaturesInfo[];
void Script_QoL_Msg_NatureInfo(void)
{
    u16 slot = sQol_GetSlot();
    struct Pokemon *mon = &gPlayerParty[slot];
    u8 minted = GetMonData(mon, MON_DATA_HIDDEN_NATURE);
    if (minted >= NUM_NATURES)
        minted = GetNature(mon);
    u8 visible = GetNature(mon);
    StringCopy(gStringVar1, gNaturesInfo[minted].name);
    StringCopy(gStringVar2, gNaturesInfo[visible].name);
    StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("Minted nature: {STR_VAR_1} (visible: {STR_VAR_2})\nCost: ¥1000."));
}

void Script_QoL_Msg_EVsInfo(void)
{
    u16 slot = sQol_GetSlot();
    struct Pokemon *mon = &gPlayerParty[slot];
    if (MonInvalidForEdit(mon)) {
        StringCopy(gStringVar4, COMPOUND_STRING("No valid Pokémon selected."));
        return;
    }
    u8 ev[6];
    ev[0] = GetMonData(mon, MON_DATA_HP_EV);
    ev[1] = GetMonData(mon, MON_DATA_ATK_EV);
    ev[2] = GetMonData(mon, MON_DATA_DEF_EV);
    ev[3] = GetMonData(mon, MON_DATA_SPEED_EV);
    ev[4] = GetMonData(mon, MON_DATA_SPATK_EV);
    ev[5] = GetMonData(mon, MON_DATA_SPDEF_EV);
    // Line 1
    ConvertIntToDecimalStringN(gStringVar1, ev[0], STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, ev[1], STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, ev[2], STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("EVs HP/Atk/Def: {STR_VAR_1}/{STR_VAR_2}/{STR_VAR_3}"));
    // Line 2 (avoid overflowing small temp buffers)
    StringAppend(gStringVar4, COMPOUND_STRING("\nSpe/SpA/SpD: "));
    ConvertIntToDecimalStringN(gStringVar1, ev[3], STR_CONV_MODE_LEFT_ALIGN, 3);
    StringAppend(gStringVar4, gStringVar1);
    StringAppend(gStringVar4, COMPOUND_STRING("/"));
    ConvertIntToDecimalStringN(gStringVar1, ev[4], STR_CONV_MODE_LEFT_ALIGN, 3);
    StringAppend(gStringVar4, gStringVar1);
    StringAppend(gStringVar4, COMPOUND_STRING("/"));
    ConvertIntToDecimalStringN(gStringVar1, ev[5], STR_CONV_MODE_LEFT_ALIGN, 3);
    StringAppend(gStringVar4, gStringVar1);
    // Cost
    StringAppend(gStringVar4, COMPOUND_STRING("\nCost: ¥1000."));
}

void Script_QoL_Msg_IVsInfo(void)
{
    u16 slot = sQol_GetSlot();
    struct Pokemon *mon = &gPlayerParty[slot];
    if (MonInvalidForEdit(mon)) {
        StringCopy(gStringVar4, COMPOUND_STRING("No valid Pokémon selected."));
        return;
    }
    u8 iv[6];
    iv[0] = GetMonData(mon, MON_DATA_HP_IV);
    iv[1] = GetMonData(mon, MON_DATA_ATK_IV);
    iv[2] = GetMonData(mon, MON_DATA_DEF_IV);
    iv[3] = GetMonData(mon, MON_DATA_SPEED_IV);
    iv[4] = GetMonData(mon, MON_DATA_SPATK_IV);
    iv[5] = GetMonData(mon, MON_DATA_SPDEF_IV);
    // Line 1
    ConvertIntToDecimalStringN(gStringVar1, iv[0], STR_CONV_MODE_LEFT_ALIGN, 2);
    ConvertIntToDecimalStringN(gStringVar2, iv[1], STR_CONV_MODE_LEFT_ALIGN, 2);
    ConvertIntToDecimalStringN(gStringVar3, iv[2], STR_CONV_MODE_LEFT_ALIGN, 2);
    StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("IVs HP/Atk/Def: {STR_VAR_1}/{STR_VAR_2}/{STR_VAR_3}"));
    // Line 2
    StringAppend(gStringVar4, COMPOUND_STRING("\nSpe/SpA/SpD: "));
    ConvertIntToDecimalStringN(gStringVar1, iv[3], STR_CONV_MODE_LEFT_ALIGN, 2);
    StringAppend(gStringVar4, gStringVar1);
    StringAppend(gStringVar4, COMPOUND_STRING("/"));
    ConvertIntToDecimalStringN(gStringVar1, iv[4], STR_CONV_MODE_LEFT_ALIGN, 2);
    StringAppend(gStringVar4, gStringVar1);
    StringAppend(gStringVar4, COMPOUND_STRING("/"));
    ConvertIntToDecimalStringN(gStringVar1, iv[5], STR_CONV_MODE_LEFT_ALIGN, 2);
    StringAppend(gStringVar4, gStringVar1);
    // Cost
    StringAppend(gStringVar4, COMPOUND_STRING("\nCost: ¥1000."));
}

static const u8 sBallName_Poke[]    = _("POKé BALL");
static const u8 sBallName_Great[]   = _("GREAT BALL");
static const u8 sBallName_Ultra[]   = _("ULTRA BALL");
static const u8 sBallName_Premier[] = _("PREMIER BALL");
static const u8 sBallName_Dive[]    = _("DIVE BALL");
static const u8 sBallName_Dusk[]    = _("DUSK BALL");
static const u8 sBallName_Timer[]   = _("TIMER BALL");
static const u8 sBallName_Quick[]   = _("QUICK BALL");
static const u8 sBallName_Cherish[] = _("CHERISH BALL");
static const u8 sBallName_Beast[]   = _("BEAST BALL");
static const u8 sBallName_Unknown[] = _("UNKNOWN BALL");

static u16 FindItemIdByBallId(u8 ballId)
{
    // Find an item whose secondaryId matches the ballId
    for (u16 item = ITEM_POKE_BALL; item < ITEMS_COUNT; item++)
    {
        if (GetItemSecondaryId(item) == ballId)
            return item;
    }
    return ITEM_NONE;
}

void Script_QoL_Msg_BallInfo(void)
{
    u16 slot = sQol_GetSlot();
    struct Pokemon *mon = &gPlayerParty[slot];
    u8 ballId = GetMonData(mon, MON_DATA_POKEBALL);
    u16 itemId = FindItemIdByBallId(ballId);
    if (itemId != ITEM_NONE)
        CopyItemName(itemId, gStringVar1);
    else
        StringCopy(gStringVar1, sBallName_Unknown);
    StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("Ball: {STR_VAR_1}\nCost: ¥1000."));
}

extern const struct TypeInfo gTypesInfo[];
void Script_QoL_Msg_TeraInfo(void)
{
    u16 slot = sQol_GetSlot();
    struct Pokemon *mon = &gPlayerParty[slot];
    u8 type = GetMonData(mon, MON_DATA_TERA_TYPE);
    if (type >= NUMBER_OF_MON_TYPES)
        type = TYPE_NORMAL;
    StringCopy(gStringVar1, gTypesInfo[type].name);
    StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("Tera Type: {STR_VAR_1}\nCost: ¥1000."));
}

// Hidden Power info: derive current type from IV parity (Gen 3 formula)
void Script_QoL_Msg_HPInfo(void)
{
    static const u8 sHpTypeOrder[16] = {
        TYPE_FIGHTING, TYPE_FLYING, TYPE_POISON, TYPE_GROUND,
        TYPE_ROCK, TYPE_BUG, TYPE_GHOST, TYPE_STEEL,
        TYPE_FIRE, TYPE_WATER, TYPE_GRASS, TYPE_ELECTRIC,
        TYPE_PSYCHIC, TYPE_ICE, TYPE_DRAGON, TYPE_DARK
    };
    u16 slot = sQol_GetSlot();
    struct Pokemon *mon = &gPlayerParty[slot];
    u8 hp = GetMonData(mon, MON_DATA_HP_IV);
    u8 at = GetMonData(mon, MON_DATA_ATK_IV);
    u8 df = GetMonData(mon, MON_DATA_DEF_IV);
    u8 sp = GetMonData(mon, MON_DATA_SPEED_IV);
    u8 sa = GetMonData(mon, MON_DATA_SPATK_IV);
    u8 sd = GetMonData(mon, MON_DATA_SPDEF_IV);
    u8 S = (hp & 1) + 2 * (at & 1) + 4 * (df & 1) + 8 * (sp & 1) + 16 * (sa & 1) + 32 * (sd & 1);
    u8 idx = (S * 15) / 63; // 0..15
    u8 type = sHpTypeOrder[idx];
    if (type >= NUMBER_OF_MON_TYPES)
        type = TYPE_NORMAL;
    StringCopy(gStringVar1, gTypesInfo[type].name);
    StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("Hidden Power: {STR_VAR_1}\nCost: ¥1000."));
}

// Generic confirmation message that shows the current cost in VAR_0x800A
void Script_QoL_Msg_ConfirmPrice(void)
{
    u32 cost = VarGet(VAR_0x800A);
    ConvertIntToDecimalStringN(gStringVar1, cost, STR_CONV_MODE_LEFT_ALIGN, 7);
    StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("Proceed? Cost: ¥{STR_VAR_1}."));
}

void Script_QoL_LoadCurrentEVs(void)
{
    u16 slot = sQol_GetSlot();
    struct Pokemon *mon = &gPlayerParty[slot];
    VarSet(VAR_0x8000, GetMonData(mon, MON_DATA_HP_EV));
    VarSet(VAR_0x8001, GetMonData(mon, MON_DATA_ATK_EV));
    VarSet(VAR_0x8002, GetMonData(mon, MON_DATA_DEF_EV));
    VarSet(VAR_0x8003, GetMonData(mon, MON_DATA_SPEED_EV));
    VarSet(VAR_0x8004, GetMonData(mon, MON_DATA_SPATK_EV));
    VarSet(VAR_0x8005, GetMonData(mon, MON_DATA_SPDEF_EV));
}

// ---------- Numeric Input UI ----------
enum {
    QT_WIN=0, QT_VAL, QT_MIN, QT_MAX, QT_CANCEL, QT_WAIT_KEYS
};

static const struct WindowTemplate sNumWinTemplate = {
    .bg=0, .tilemapLeft=10, .tilemapTop=7, .width=10, .height=4, .paletteNum=15, .baseBlock=0x1
};

static void PrintNumber(u8 windowId, u16 val, const u8 *label)
{
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    DrawStdWindowFrame(windowId, FALSE);
    if (label) AddTextPrinterParameterized(windowId, FONT_NORMAL, label, 8, 4, 0, NULL);
    ConvertIntToDecimalStringN(gStringVar1, val, STR_CONV_MODE_LEFT_ALIGN, 3);
    AddTextPrinterParameterized(windowId, FONT_NORMAL, gStringVar1, 8, 20, 0, NULL);
    CopyWindowToVram(windowId, COPYWIN_GFX);
}

static void Task_QoL_NumberInput(u8 taskId)
{
    s16 *d = gTasks[taskId].data;
    u8 win = d[QT_WIN];

    if (!d[QT_WAIT_KEYS])
    {
        if (gMain.heldKeys == 0)
            d[QT_WAIT_KEYS] = TRUE;
        return;
    }

    if (JOY_NEW(B_BUTTON)) {
        d[QT_CANCEL] = TRUE;
        ClearStdWindowAndFrameToTransparent(win, TRUE);
        RemoveWindow(win);
        ScriptContext_Enable();
        DestroyTask(taskId);
        return;
    }
    if (JOY_NEW(A_BUTTON)) {
        VarSet(VAR_RESULT, d[QT_VAL]);
        ClearStdWindowAndFrameToTransparent(win, TRUE);
        RemoveWindow(win);
        ScriptContext_Enable();
        DestroyTask(taskId);
        return;
    }
    if (JOY_REPEAT(DPAD_RIGHT) && d[QT_VAL] < d[QT_MAX]) d[QT_VAL]++;
    if (JOY_REPEAT(DPAD_LEFT)  && d[QT_VAL] > d[QT_MIN]) d[QT_VAL]--;
    if (JOY_REPEAT(DPAD_UP))   d[QT_VAL] = (d[QT_VAL] + 10 <= d[QT_MAX]) ? d[QT_VAL] + 10 : d[QT_MAX];
    if (JOY_REPEAT(DPAD_DOWN)) d[QT_VAL] = (d[QT_VAL] >= d[QT_MIN] + 10) ? d[QT_VAL] - 10 : d[QT_MIN];

    PrintNumber(win, d[QT_VAL], gText_ThreeDashes);
}

void Script_QoL_PromptNumber(void)
{
    u16 min  = VarGet(VAR_0x8000);
    u16 max  = VarGet(VAR_0x8001);
    u16 init = VarGet(VAR_0x8002);
    if (init < min) init = min;
    if (init > max) init = max;

    ScriptContext_Stop();
    u8 win = AddWindow(&sNumWinTemplate);
    DrawStdWindowFrame(win, FALSE);
    PrintNumber(win, init, gText_EmptyString2);

    u8 taskId = CreateTask(Task_QoL_NumberInput, 0);
    s16 *d = gTasks[taskId].data;
    d[QT_WIN]   = win;
    d[QT_VAL]   = init;
    d[QT_MIN]   = min;
    d[QT_MAX]   = max;
    d[QT_CANCEL]= FALSE;
    d[QT_WAIT_KEYS] = FALSE;
}

// Map a QoL stat menu selection in VAR_RESULT to the corresponding STAT_* constant.
void Script_QoL_MapStatSelection(void)
{
    static const u8 sMap[6] = {STAT_HP, STAT_ATK, STAT_DEF, STAT_SPATK, STAT_SPDEF, STAT_SPEED};
    u16 sel = VarGet(VAR_RESULT);
    if (sel < ARRAY_COUNT(sMap))
        VarSet(VAR_RESULT, sMap[sel]);
}
