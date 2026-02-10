// QoL Scientist helpers and script callnatives
#pragma once

#include "global.h"
#include "pokemon.h"

#define QOL_COST_PER_ACTION 1000  // ₽1000 per successful edit

enum QoLRegionId {
    QOL_REGION_HOENN  = 0,
    QOL_REGION_JOHTO  = 1,
    QOL_REGION_KANTO  = 2,
    QOL_REGION_SEVII  = 3,
    QOL_REGION_SINNOH = 4,
};

u8  QoL_GetCurrentRegionId(void);
bool8 QoL_TakeMoneyIfEnough(u32 cost);
bool8 QoL_IsMonShiny(struct Pokemon *mon);
bool8 QoL_IsMonLegendaryOrMythical(struct Pokemon *mon);
bool8 QoL_IsMonUltraBeast(struct Pokemon *mon);
bool8 QoL_BallIsLegalForMon(u16 item, struct Pokemon *mon);

// Numeric input spinner: 0x8000=min, 0x8001=max, 0x8002=initial; returns VAR_RESULT
void Script_QoL_PromptNumber(void);
void Script_QoL_MapStatSelection(void); // Map VAR_RESULT index to STAT_* constant

// Region-aware message fillers -> copy regional text into gStringVar4
void Script_QoL_Msg_Hello(void);
void Script_QoL_Msg_NotEnoughMoney(void);
void Script_QoL_Msg_IllegalBall(void);
void Script_QoL_Msg_Charged(void);
void Script_QoL_Msg_Canceled(void);
void Script_QoL_Msg_ConfirmNature(void);   // Uses VAR_0x8000 nature id -> gStringVar4
void Script_QoL_Msg_AbilityInfo(void);     // Uses VAR_0x8006 party slot -> gStringVar4
void Script_QoL_Msg_NatureInfo(void);      // Uses VAR_0x8006 party slot -> gStringVar4
void Script_QoL_Msg_EVsInfo(void);         // Uses VAR_0x8006 party slot -> gStringVar4
void Script_QoL_Msg_IVsInfo(void);         // Uses VAR_0x8006 party slot -> gStringVar4
void Script_QoL_Msg_BallInfo(void);        // Uses VAR_0x8006 party slot -> gStringVar4
void Script_QoL_Msg_TeraInfo(void);        // Uses VAR_0x8006 party slot -> gStringVar4
void Script_QoL_Msg_HPInfo(void);          // Uses VAR_0x8006 party slot -> gStringVar4
void Script_QoL_Msg_ConfirmPrice(void);    // Uses VAR_0x800A cost -> gStringVar4

// Populate VAR_0x8000..VAR_0x8005 with current EVs of selected mon
void Script_QoL_LoadCurrentEVs(void);

// Service callnatives (set VAR_RESULT = 1 success, 2 not enough money, 3 illegal)
// Uses chosen party mon; scripts store the selected slot in VAR_0x8006
// after calling ChoosePartyMon and waiting for completion.
void Script_QoL_SetNature(void);             // VAR_0x8000 = nature 0..24
void Script_QoL_EVs_PresetByNature(void);
void Script_QoL_EVs_QuickCustom(void);       // VAR_0x8000=a stat (0..5), VAR_0x8001=b stat (0..5)
void Script_QoL_EVs_Clear(void);
void Script_QoL_EVs_CustomFull(void);        // VAR_0x8000..0x8005 = HP,ATK,DEF,SPE,SPA,SPD (0..252 each, total ≤510)

void Script_QoL_IVs_Perfect31(void);
void Script_QoL_IVs_TrickRoom(void);
void Script_QoL_IVs_SetStat(void);           // VAR_0x8000 = stat (0..5), VAR_0x8001 = iv (0..31)

void Script_QoL_SetBall(void);               // VAR_0x8000 = itemId (ITEM_* Ball)
void Script_QoL_SetHiddenPowerType(void);    // VAR_0x8000 = TYPE_FIGHTING..TYPE_DARK indexable HP type

// Expose MonInvalidForEdit for use in other modules
#ifdef __cplusplus
extern "C" {
#endif
bool8 MonInvalidForEdit(struct Pokemon *mon);
#ifdef __cplusplus
}
#endif
// Ability services
void Script_QoL_Ability_SetNormal(void);     // VAR_0x8000 = 0 or 1
void Script_QoL_Ability_SetHidden(void);
void Script_QoL_Ability_Toggle(void);

// Dynamax / Gigantamax services
void Script_QoL_SetDynamaxLevelMax(void);    // Set selected mon's Dynamax Level to MAX_DYNAMAX_LEVEL
void Script_QoL_EnableGigantamaxFactor(void); // Enable G-Max Factor if applicable
