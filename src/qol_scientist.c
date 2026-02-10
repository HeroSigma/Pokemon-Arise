// QoL Scientist core services
#include "global.h"
#include "qol_scientist.h"
#include "event_data.h"
#include "pokemon.h"
#include "money.h"
#include "script.h"
#include "item.h"
#include "pokeball.h"
#include "battle_main.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/battle.h"
#include "constants/pokemon.h"
#include "constants/flags.h"

extern const struct SpeciesInfo gSpeciesInfo[];
extern u16 SanitizeSpeciesId(u16 species);
u32 GetGMaxTargetSpecies(u32 species);

static struct Pokemon *sQolMon(void)
{
    // Prefer a dedicated variable (VAR_0x8006) to hold the chosen
    // party slot, falling back to VAR_0x8004 for backward compatibility.
    u16 slot = VarGet(VAR_0x8006);
    if (slot >= PARTY_SIZE)
        slot = VarGet(VAR_0x8004);
    if (slot >= PARTY_SIZE)
        slot = 0;
    return &gPlayerParty[slot];
}

bool8 MonInvalidForEdit(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    if (species == SPECIES_NONE)
        return TRUE;
    if (GetMonData(mon, MON_DATA_IS_EGG, NULL))
        return TRUE;
    return FALSE;
}

/* ==================== NATURE ==================== */

void Script_QoL_SetNature(void)
{
    u16 nat = VarGet(VAR_0x8000); // 0..24
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    // Use the project's hidden nature system: keep the original personality
    // (and therefore displayed base nature), but apply stats using the
    // hidden nature stored in MON_DATA_HIDDEN_NATURE.
    if (nat >= NUM_NATURES) { VarSet(VAR_RESULT, 0); return; }
    SetMonData(mon, MON_DATA_HIDDEN_NATURE, &nat);
    CalculateMonStats(mon);
    VarSet(VAR_RESULT, 1);
}

/* ==================== EVs ==================== */

static void ZeroEVs(struct Pokemon *mon)
{
    u8 z = 0;
    SetMonData(mon, MON_DATA_HP_EV, &z);
    SetMonData(mon, MON_DATA_ATK_EV, &z);
    SetMonData(mon, MON_DATA_DEF_EV, &z);
    SetMonData(mon, MON_DATA_SPEED_EV, &z);
    SetMonData(mon, MON_DATA_SPATK_EV, &z);
    SetMonData(mon, MON_DATA_SPDEF_EV, &z);
}

static void PutEV(struct Pokemon *mon, u8 stat, u8 val)
{
    if (val > 252) val = 252;
    switch (stat) {
    case STAT_HP:    SetMonData(mon, MON_DATA_HP_EV, &val); break;
    case STAT_ATK:   SetMonData(mon, MON_DATA_ATK_EV, &val); break;
    case STAT_DEF:   SetMonData(mon, MON_DATA_DEF_EV, &val); break;
    case STAT_SPEED: SetMonData(mon, MON_DATA_SPEED_EV, &val); break;
    case STAT_SPATK: SetMonData(mon, MON_DATA_SPATK_EV, &val); break;
    case STAT_SPDEF: SetMonData(mon, MON_DATA_SPDEF_EV, &val); break;
    }
}

// from gNaturesInfo
extern const struct NatureInfo gNaturesInfo[];
static s8 NatureDelta(u8 nature, u8 stat)
{
    if (gNaturesInfo[nature].statUp == stat) return +1;
    if (gNaturesInfo[nature].statDown == stat) return -1;
    return 0;
}

void Script_QoL_EVs_PresetByNature(void)
{
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    // Use the hidden (minted) nature when determining which stat to boost.
    // The visible nature is tied to the personality, but the stat changes
    // come from MON_DATA_HIDDEN_NATURE.
    // Clamp the hidden nature to the supported range since the encoded value
    // may exceed NUM_NATURES if it was never initialised, which could crash
    // when indexing gNaturesInfo. If the stored value is invalid, fall back to
    // the mon's visible nature instead of wrapping it.
    u8 nature = GetMonData(mon, MON_DATA_HIDDEN_NATURE);
    if (nature >= NUM_NATURES)
        nature = GetNature(mon);
    u8 boosted = STAT_SPEED; // default to speed if neutral
    for (u8 s = STAT_ATK; s <= STAT_SPDEF; s++)
        if (NatureDelta(nature, s) > 0) { boosted = s; break; }

    ZeroEVs(mon);
    if (boosted == STAT_SPEED) {
        // If the nature lowers one offensive stat, invest in the other.
        u8 second;
        if (gNaturesInfo[nature].statDown == STAT_SPATK)
            second = STAT_ATK;   // Jolly, Adamant-like preference -> physical
        else if (gNaturesInfo[nature].statDown == STAT_ATK)
            second = STAT_SPATK; // Timid/Modest-like preference -> special
        else
            second = STAT_ATK;   // neutral natures: default to physical
        PutEV(mon, STAT_SPEED, 252);
        PutEV(mon, second,     252);
    } else {
        // If a non-Speed stat is boosted, pair it with Speed.
        PutEV(mon, boosted,    252);
        PutEV(mon, STAT_SPEED, 252);
    }
    PutEV(mon, STAT_HP, 6);
    CalculateMonStats(mon);
    VarSet(VAR_RESULT, 1);
}

void Script_QoL_EVs_QuickCustom(void)
{
    u8 a = VarGet(VAR_0x8000); // 0..5
    u8 b = VarGet(VAR_0x8001); // 0..5
    if (a > 5) a = STAT_SPEED;
    if (b > 5 || b == a) b = STAT_SPEED;

    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    ZeroEVs(mon);
    PutEV(mon, a, 252);
    PutEV(mon, b, 252);
    PutEV(mon, STAT_HP, 6);
    CalculateMonStats(mon);
    VarSet(VAR_RESULT, 1);
}

void Script_QoL_EVs_Clear(void)
{
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    ZeroEVs(mon);
    CalculateMonStats(mon);
    VarSet(VAR_RESULT, 1);
}

void Script_QoL_EVs_CustomFull(void)
{
    u16 e[6];
    e[0] = VarGet(VAR_0x8000);
    e[1] = VarGet(VAR_0x8001);
    e[2] = VarGet(VAR_0x8002);
    e[3] = VarGet(VAR_0x8003);
    e[4] = VarGet(VAR_0x8004);
    e[5] = VarGet(VAR_0x8005);
    for (int i=0;i<6;i++) if (e[i] > 252) e[i] = 252;
    u32 sum = e[0]+e[1]+e[2]+e[3]+e[4]+e[5];
    if (sum > 510) { VarSet(VAR_RESULT, 0); return; } // invalid, no charge

    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    u8 v;
    v=e[0]; SetMonData(mon, MON_DATA_HP_EV,    &v);
    v=e[1]; SetMonData(mon, MON_DATA_ATK_EV,   &v);
    v=e[2]; SetMonData(mon, MON_DATA_DEF_EV,   &v);
    v=e[3]; SetMonData(mon, MON_DATA_SPEED_EV, &v);
    v=e[4]; SetMonData(mon, MON_DATA_SPATK_EV, &v);
    v=e[5]; SetMonData(mon, MON_DATA_SPDEF_EV, &v);
    CalculateMonStats(mon);
    VarSet(VAR_RESULT, 1);
}

/* ==================== IVs ==================== */

static void SetAllIVs(struct Pokemon *mon, u8 iv)
{
    SetMonData(mon, MON_DATA_HP_IV,    &iv);
    SetMonData(mon, MON_DATA_ATK_IV,   &iv);
    SetMonData(mon, MON_DATA_DEF_IV,   &iv);
    SetMonData(mon, MON_DATA_SPEED_IV, &iv);
    SetMonData(mon, MON_DATA_SPATK_IV, &iv);
    SetMonData(mon, MON_DATA_SPDEF_IV, &iv);
}

void Script_QoL_IVs_Perfect31(void)
{
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    SetAllIVs(mon, 31);
    CalculateMonStats(mon);
    VarSet(VAR_RESULT, 1);
}

void Script_QoL_IVs_TrickRoom(void)
{
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    SetAllIVs(mon, 31);
    u8 z = 0;
    SetMonData(mon, MON_DATA_SPEED_IV, &z);
    CalculateMonStats(mon);
    VarSet(VAR_RESULT, 1);
}

void Script_QoL_IVs_SetStat(void)
{
    u8 stat = VarGet(VAR_0x8000);
    u8 iv   = VarGet(VAR_0x8001);
    if (iv > 31) iv = 31;
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    switch (stat) {
    case STAT_HP:    SetMonData(mon, MON_DATA_HP_IV,    &iv); break;
    case STAT_ATK:   SetMonData(mon, MON_DATA_ATK_IV,   &iv); break;
    case STAT_DEF:   SetMonData(mon, MON_DATA_DEF_IV,   &iv); break;
    case STAT_SPEED: SetMonData(mon, MON_DATA_SPEED_IV, &iv); break;
    case STAT_SPATK: SetMonData(mon, MON_DATA_SPATK_IV, &iv); break;
    case STAT_SPDEF: SetMonData(mon, MON_DATA_SPDEF_IV, &iv); break;
    }
    CalculateMonStats(mon);
    VarSet(VAR_RESULT, 1);
}

/* ==================== Ball changer ==================== */

void Script_QoL_SetBall(void)
{
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    u16 item = VarGet(VAR_0x8000);
    if (!QoL_BallIsLegalForMon(item, mon)) { VarSet(VAR_RESULT, 3); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION))  { VarSet(VAR_RESULT, 2); return; }

    u8 ball = ItemIdToBallId(item);
    SetMonData(mon, MON_DATA_POKEBALL, &ball);
    VarSet(VAR_RESULT, 1);
}

/* ==================== Hidden Power ==================== */

static const u8 sHpTypeOrder[16] = { // mapping index 0..15 -> TYPE_*
    TYPE_FIGHTING, TYPE_FLYING, TYPE_POISON, TYPE_GROUND,
    TYPE_ROCK, TYPE_BUG, TYPE_GHOST, TYPE_STEEL,
    TYPE_FIRE, TYPE_WATER, TYPE_GRASS, TYPE_ELECTRIC,
    TYPE_PSYCHIC, TYPE_ICE, TYPE_DRAGON, TYPE_DARK
};

static bool8 HiddenPowerTypeToIndex(u8 type, u8 *outIdx)
{
    for (u8 i = 0; i < 16; i++)
        if (sHpTypeOrder[i] == type) { *outIdx = i; return TRUE; }
    return FALSE;
}

void Script_QoL_SetHiddenPowerType(void)
{
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    u8 idx;
    if (!HiddenPowerTypeToIndex(VarGet(VAR_0x8000), &idx)) { VarSet(VAR_RESULT, 0); return; }

    u8 bestS = 0;
    for (u8 S = 63; ; S--) {
        if (((S * 15) / 63) == idx) { bestS = S; break; }
        if (S == 0) break;
    }
    u8 odd[6] = {
        (bestS & 1) ? 1 : 0, (bestS & 2) ? 1 : 0, (bestS & 4) ? 1 : 0,
        (bestS & 8) ? 1 : 0, (bestS & 16)? 1 : 0, (bestS & 32)? 1 : 0,
    };
    u8 v;

    v = odd[0] ? 31 : 30; SetMonData(mon, MON_DATA_HP_IV,    &v);
    v = odd[1] ? 31 : 30; SetMonData(mon, MON_DATA_ATK_IV,   &v);
    v = odd[2] ? 31 : 30; SetMonData(mon, MON_DATA_DEF_IV,   &v);
    v = odd[3] ? 31 : 30; SetMonData(mon, MON_DATA_SPEED_IV, &v);
    v = odd[4] ? 31 : 30; SetMonData(mon, MON_DATA_SPATK_IV, &v);
    v = odd[5] ? 31 : 30; SetMonData(mon, MON_DATA_SPDEF_IV, &v);

    CalculateMonStats(mon);
    VarSet(VAR_RESULT, 1);
}

/* ==================== Ability changer ==================== */

static bool8 SpeciesHasAbilitySlot(u16 species, u8 slot)
{
    return GetSpeciesAbility(species, slot) != 0;
}

void Script_QoL_Ability_Toggle(void)
{
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u8 cur = GetMonData(mon, MON_DATA_ABILITY_NUM, NULL);
    // Only toggle between normal slots 0 and 1 if both exist and current is normal.
    if (!SpeciesHasAbilitySlot(species, 0) || !SpeciesHasAbilitySlot(species, 1) || cur > 1)
    { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    u8 newNum = cur ^ 1;
    SetMonData(mon, MON_DATA_ABILITY_NUM, &newNum);
    VarSet(VAR_RESULT, 1);
}

void Script_QoL_Ability_SetNormal(void)
{
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    u8 slot = VarGet(VAR_0x8000) & 1; // 0 or 1
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    if (!SpeciesHasAbilitySlot(species, slot)) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    SetMonData(mon, MON_DATA_ABILITY_NUM, &slot);
    VarSet(VAR_RESULT, 1);
}

void Script_QoL_Ability_SetHidden(void)
{
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    if (!SpeciesHasAbilitySlot(species, 2)) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    u8 num = 2;
    SetMonData(mon, MON_DATA_ABILITY_NUM, &num);
    VarSet(VAR_RESULT, 1);
}

/* ==================== Dynamax / Gigantamax ==================== */

void Script_QoL_SetDynamaxLevelMax(void)
{
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }
    u8 cur = GetMonData(mon, MON_DATA_DYNAMAX_LEVEL, NULL);
    if (cur >= MAX_DYNAMAX_LEVEL) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    u8 lvl = MAX_DYNAMAX_LEVEL;
    SetMonData(mon, MON_DATA_DYNAMAX_LEVEL, &lvl);
    VarSet(VAR_RESULT, 1);
}

void Script_QoL_EnableGigantamaxFactor(void)
{
    struct Pokemon *mon = sQolMon();
    if (MonInvalidForEdit(mon)) { VarSet(VAR_RESULT, 0); return; }

    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    // Vanilla behavior blocks Mythical mons (e.g., Melmetal).
    if (gSpeciesInfo[SanitizeSpeciesId(species)].isMythical) { VarSet(VAR_RESULT, 0); return; }

    // Only charge/apply if it actually changes something and the mon can G-Max.
    if (GetGMaxTargetSpecies(species) == species) { VarSet(VAR_RESULT, 0); return; }

    bool32 has = GetMonData(mon, MON_DATA_GIGANTAMAX_FACTOR, NULL);
    if (has) { VarSet(VAR_RESULT, 0); return; }
    if (!QoL_TakeMoneyIfEnough(QOL_COST_PER_ACTION)) { VarSet(VAR_RESULT, 2); return; }
    has = TRUE;
    SetMonData(mon, MON_DATA_GIGANTAMAX_FACTOR, &has);
    VarSet(VAR_RESULT, 1);
}
