#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "caps.h"
#include "pokemon.h"
#include "config/caps.h"


u32 GetCurrentLevelCap(void)
{
    static const u32 sLevelCapFlagMap[][2] =
    {
        // Gym badges (pre-gym caps)
        {FLAG_BADGE01_GET, 16}, // Roxanne (Rustboro)
        {FLAG_BADGE02_GET, 20}, // Brawly (Dewford)
        {FLAG_BADGE03_GET, 24}, // Wattson (Mauville)
        {FLAG_BADGE04_GET, 29}, // Flannery (Lavaridge)
        {FLAG_BADGE05_GET, 33}, // Norman (Petalburg)
        {FLAG_BADGE06_GET, 36}, // Winona (Fortree)
        {FLAG_BADGE07_GET, 42}, // Tate & Liza (Mossdeep)
        {FLAG_BADGE08_GET, 46}, // Wallace/Juan (Sootopolis)
        // Elite Four (pre-member caps)
        {FLAG_DEFEATED_ELITE_4_SIDNEY, 48},
        {FLAG_DEFEATED_ELITE_4_PHOEBE, 49},
        {FLAG_DEFEATED_ELITE_4_GLACIA, 50},
        {FLAG_DEFEATED_ELITE_4_DRAKE,  52},
        // Champion (pre-champion cap)
        {FLAG_IS_CHAMPION, 55}, // Wallace (Champion)
        // Post-game cap (always-unset placeholder flag)
        {FLAG_UNUSED_0x29F, 65}, // After defeating Wallace
    };

    u32 i;

    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
        {
            if (!FlagGet(sLevelCapFlagMap[i][0]))
                return sLevelCapFlagMap[i][1];
        }
    }
    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();

    if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP)
        {
            levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp) - 1)
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);
        }
        else
        {
            return expValue;
        }
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_HARD)
    {
        return 0;
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_SOFT)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown) - 1)
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}

u32 GetCurrentEVCap(void)
{
    static const u16 sEvCapFlagMap[][2] = {
        // Define EV caps for each milestone
        {FLAG_BADGE01_GET, MAX_TOTAL_EVS *  1 / 17},
        {FLAG_BADGE02_GET, MAX_TOTAL_EVS *  3 / 17},
        {FLAG_BADGE03_GET, MAX_TOTAL_EVS *  5 / 17},
        {FLAG_BADGE04_GET, MAX_TOTAL_EVS *  7 / 17},
        {FLAG_BADGE05_GET, MAX_TOTAL_EVS *  9 / 17},
        {FLAG_BADGE06_GET, MAX_TOTAL_EVS * 11 / 17},
        {FLAG_BADGE07_GET, MAX_TOTAL_EVS * 13 / 17},
        {FLAG_BADGE08_GET, MAX_TOTAL_EVS * 15 / 17},
        {FLAG_IS_CHAMPION, MAX_TOTAL_EVS},
    };

    if (B_EV_CAP_TYPE == EV_CAP_FLAG_LIST)
    {
        for (u32 evCap = 0; evCap < ARRAY_COUNT(sEvCapFlagMap); evCap++)
        {
            if (!FlagGet(sEvCapFlagMap[evCap][0]))
                return sEvCapFlagMap[evCap][1];
        }
    }
    else if (B_EV_CAP_TYPE == EV_CAP_VARIABLE)
    {
        return VarGet(B_EV_CAP_VARIABLE);
    }
    else if (B_EV_CAP_TYPE == EV_CAP_NO_GAIN)
    {
        return 0;
    }

    return MAX_TOTAL_EVS;
}

// Badge-based level cap enforcement functions

static u32 GetBadgeCount(void)
{
    u32 badgeCount = 0;
    
    if (FlagGet(FLAG_BADGE01_GET)) badgeCount++;
    if (FlagGet(FLAG_BADGE02_GET)) badgeCount++;
    if (FlagGet(FLAG_BADGE03_GET)) badgeCount++;
    if (FlagGet(FLAG_BADGE04_GET)) badgeCount++;
    if (FlagGet(FLAG_BADGE05_GET)) badgeCount++;
    if (FlagGet(FLAG_BADGE06_GET)) badgeCount++;
    if (FlagGet(FLAG_BADGE07_GET)) badgeCount++;
    if (FlagGet(FLAG_BADGE08_GET)) badgeCount++;
    
    return badgeCount;
}

static u16 FindPreEvolution(u16 species)
{
    u32 i, j;
    
    // Search through all species to find one that evolves into the given species
    for (i = 1; i < NUM_SPECIES; i++)
    {
        const struct Evolution *evolutions = GetSpeciesEvolutions(i);
        if (evolutions == NULL)
            continue;
            
        for (j = 0; evolutions[j].method != EVOLUTIONS_END; j++)
        {
            if (evolutions[j].targetSpecies == species)
                return i; // Found pre-evolution
        }
    }
    
    return SPECIES_NONE; // No pre-evolution found
}

static bool32 IsEvolutionLegalUnderLevelCap(u16 species, u32 levelCap, u32 badgeCount)
{
    u16 preEvo = FindPreEvolution(species);
    
    // If no pre-evolution exists, the species is always legal
    if (preEvo == SPECIES_NONE)
        return TRUE;
    
    // Find the evolution method from pre-evolution to this species
    const struct Evolution *evolutions = GetSpeciesEvolutions(preEvo);
    if (evolutions == NULL)
        return TRUE;
    
    u32 i;
    for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
    {
        if (evolutions[i].targetSpecies == species)
        {
            switch (evolutions[i].method)
            {
                case EVO_LEVEL:
                case EVO_LEVEL_BATTLE_ONLY:
                    // Level-based evolution: check if required level is within cap
                    return evolutions[i].param <= levelCap;
                    
                case EVO_TRADE:
                case EVO_ITEM:
                    // Non-level evolution: check badge-based policy
                    return badgeCount >= B_NON_LEVEL_EVO_BADGE_REQUIREMENT;
                    
                default:
                    // Other evolution methods: use same policy as trade/item
                    return badgeCount >= B_NON_LEVEL_EVO_BADGE_REQUIREMENT;
            }
        }
    }
    
    return TRUE; // Default to legal if evolution method not found
}

static u16 DowngradeToLegalSpecies(u16 species, u32 levelCap, u32 badgeCount)
{
    u16 currentSpecies = species;
    
    // Keep downgrading until we find a legal species or reach base form
    while (!IsEvolutionLegalUnderLevelCap(currentSpecies, levelCap, badgeCount))
    {
        u16 preEvo = FindPreEvolution(currentSpecies);
        if (preEvo == SPECIES_NONE)
            break; // Reached base form or no pre-evolution found
        currentSpecies = preEvo;
    }
    
    return currentSpecies;
}

bool32 IsTrainerExemptFromLevelCap(u16 trainerId)
{
    // Add special trainer IDs that should be exempt from level cap enforcement
    // This can be expanded to include gym leaders, elite four, champion, etc.
    // For now, return FALSE to apply level cap to all trainers
    return FALSE;
}

void EnforceLevelCapOnTrainerParty(struct Pokemon *party, u32 partySize, u16 trainerId)
{
    // Skip enforcement if disabled in config
    if (!B_TRAINER_EVOLUTION_ENFORCEMENT)
        return;
        
    // Skip enforcement if trainer is exempt
    if (IsTrainerExemptFromLevelCap(trainerId))
        return;
    
    u32 levelCap = GetCurrentLevelCap();
    u32 badgeCount = GetBadgeCount();
    u32 i;
    
    for (i = 0; i < partySize; i++)
    {
        if (GetMonData(&party[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
            continue;
            
        u16 currentSpecies = GetMonData(&party[i], MON_DATA_SPECIES, NULL);
        u16 legalSpecies = DowngradeToLegalSpecies(currentSpecies, levelCap, badgeCount);
        
        // If species needs to be downgraded or level is above cap, adjust it while preserving everything else
        u32 level = GetMonData(&party[i], MON_DATA_LEVEL, NULL);
        if (legalSpecies != currentSpecies || level > levelCap)
        {
            // Store all the data we want to preserve
            level = (level > levelCap) ? levelCap : level; // Cap the level if needed
            u32 exp = GetMonData(&party[i], MON_DATA_EXP, NULL);
            u32 personality = GetMonData(&party[i], MON_DATA_PERSONALITY, NULL);
            u32 otId = GetMonData(&party[i], MON_DATA_OT_ID, NULL);
            u16 heldItem = GetMonData(&party[i], MON_DATA_HELD_ITEM, NULL);
            u8 friendship = GetMonData(&party[i], MON_DATA_FRIENDSHIP, NULL);
            u8 pokeball = GetMonData(&party[i], MON_DATA_POKEBALL, NULL);
            bool32 isShiny = GetMonData(&party[i], MON_DATA_IS_SHINY, NULL);
            u32 ivs = GetMonData(&party[i], MON_DATA_IVS, NULL);
            
            // Get EVs
            u8 evs[NUM_STATS];
            evs[STAT_HP] = GetMonData(&party[i], MON_DATA_HP_EV, NULL);
            evs[STAT_ATK] = GetMonData(&party[i], MON_DATA_ATK_EV, NULL);
            evs[STAT_DEF] = GetMonData(&party[i], MON_DATA_DEF_EV, NULL);
            evs[STAT_SPEED] = GetMonData(&party[i], MON_DATA_SPEED_EV, NULL);
            evs[STAT_SPATK] = GetMonData(&party[i], MON_DATA_SPATK_EV, NULL);
            evs[STAT_SPDEF] = GetMonData(&party[i], MON_DATA_SPDEF_EV, NULL);
            
            // Get moves
            u16 moves[MAX_MON_MOVES];
            u8 pp[MAX_MON_MOVES];
            u8 ppBonuses = GetMonData(&party[i], MON_DATA_PP_BONUSES, NULL);
            u32 j;
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                moves[j] = GetMonData(&party[i], MON_DATA_MOVE1 + j, NULL);
                pp[j] = GetMonData(&party[i], MON_DATA_PP1 + j, NULL);
            }
            
            // Get nickname
            u8 nickname[POKEMON_NAME_LENGTH + 1];
            GetMonData(&party[i], MON_DATA_NICKNAME, nickname);
            
            // Get OT name
            u8 otName[PLAYER_NAME_LENGTH + 1];
            GetMonData(&party[i], MON_DATA_OT_NAME, otName);
            
            // Get additional data
            u8 abilityNum = GetMonData(&party[i], MON_DATA_ABILITY_NUM, NULL);
            u32 dynamaxLevel = GetMonData(&party[i], MON_DATA_DYNAMAX_LEVEL, NULL);
            bool32 gigantamaxFactor = GetMonData(&party[i], MON_DATA_GIGANTAMAX_FACTOR, NULL);
            u8 teraType = GetMonData(&party[i], MON_DATA_TERA_TYPE, NULL);
            
            // Create new Pokemon with legal species
            CreateMon(&party[i], legalSpecies, level, 0, TRUE, personality, OT_ID_PRESET, otId);
            
            // Restore all preserved data
            SetMonData(&party[i], MON_DATA_EXP, &exp);
            SetMonData(&party[i], MON_DATA_HELD_ITEM, &heldItem);
            SetMonData(&party[i], MON_DATA_FRIENDSHIP, &friendship);
            SetMonData(&party[i], MON_DATA_POKEBALL, &pokeball);
            SetMonData(&party[i], MON_DATA_IS_SHINY, &isShiny);
            SetMonData(&party[i], MON_DATA_IVS, &ivs);
            
            // Restore EVs
            SetMonData(&party[i], MON_DATA_HP_EV, &evs[STAT_HP]);
            SetMonData(&party[i], MON_DATA_ATK_EV, &evs[STAT_ATK]);
            SetMonData(&party[i], MON_DATA_DEF_EV, &evs[STAT_DEF]);
            SetMonData(&party[i], MON_DATA_SPEED_EV, &evs[STAT_SPEED]);
            SetMonData(&party[i], MON_DATA_SPATK_EV, &evs[STAT_SPATK]);
            SetMonData(&party[i], MON_DATA_SPDEF_EV, &evs[STAT_SPDEF]);
            
            // Restore moves and PP
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                SetMonMoveSlot(&party[i], moves[j], j);
                SetMonData(&party[i], MON_DATA_PP1 + j, &pp[j]);
            }
            SetMonData(&party[i], MON_DATA_PP_BONUSES, &ppBonuses);
            
            // Restore names
            SetMonData(&party[i], MON_DATA_NICKNAME, nickname);
            SetMonData(&party[i], MON_DATA_OT_NAME, otName);
            
            // Restore additional data
            SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum);
            SetMonData(&party[i], MON_DATA_DYNAMAX_LEVEL, &dynamaxLevel);
            SetMonData(&party[i], MON_DATA_GIGANTAMAX_FACTOR, &gigantamaxFactor);
            SetMonData(&party[i], MON_DATA_TERA_TYPE, &teraType);
        }
    }
}

void ReduceTrainerPartyLevelsToCap(struct Pokemon *party, u32 partySize, u16 trainerId)
{
    // Skip level reduction if disabled in config
    if (!B_TRAINER_LEVEL_REDUCTION)
        return;

    // Skip level reduction if trainer is exempt
    if (IsTrainerExemptFromLevelCap(trainerId))
        return;

    u32 levelCap = GetCurrentLevelCap();
    u32 i;

    for (i = 0; i < partySize; i++)
    {
        if (GetMonData(&party[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
            continue;

        u32 currentLevel = GetMonData(&party[i], MON_DATA_LEVEL, NULL);

        // If Pokémon level exceeds level cap, reduce it to the cap
        if (currentLevel > levelCap)
        {
            // Store all the data we want to preserve
            u32 exp = GetMonData(&party[i], MON_DATA_EXP, NULL);
            u32 personality = GetMonData(&party[i], MON_DATA_PERSONALITY, NULL);
            u32 otId = GetMonData(&party[i], MON_DATA_OT_ID, NULL);
            u16 heldItem = GetMonData(&party[i], MON_DATA_HELD_ITEM, NULL);
            u8 friendship = GetMonData(&party[i], MON_DATA_FRIENDSHIP, NULL);
            u8 pokeball = GetMonData(&party[i], MON_DATA_POKEBALL, NULL);
            bool32 isShiny = GetMonData(&party[i], MON_DATA_IS_SHINY, NULL);
            u32 ivs = GetMonData(&party[i], MON_DATA_IVS, NULL);

            // Get EVs
            u8 evs[NUM_STATS];
            evs[STAT_HP] = GetMonData(&party[i], MON_DATA_HP_EV, NULL);
            evs[STAT_ATK] = GetMonData(&party[i], MON_DATA_ATK_EV, NULL);
            evs[STAT_DEF] = GetMonData(&party[i], MON_DATA_DEF_EV, NULL);
            evs[STAT_SPEED] = GetMonData(&party[i], MON_DATA_SPEED_EV, NULL);
            evs[STAT_SPATK] = GetMonData(&party[i], MON_DATA_SPATK_EV, NULL);
            evs[STAT_SPDEF] = GetMonData(&party[i], MON_DATA_SPDEF_EV, NULL);

            // Get moves
            u16 moves[MAX_MON_MOVES];
            u8 pp[MAX_MON_MOVES];
            u8 ppBonuses = GetMonData(&party[i], MON_DATA_PP_BONUSES, NULL);
            u32 j;
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                moves[j] = GetMonData(&party[i], MON_DATA_MOVE1 + j, NULL);
                pp[j] = GetMonData(&party[i], MON_DATA_PP1 + j, NULL);
            }

            // Get nickname
            u8 nickname[POKEMON_NAME_LENGTH + 1];
            GetMonData(&party[i], MON_DATA_NICKNAME, nickname);

            // Get OT name
            u8 otName[PLAYER_NAME_LENGTH + 1];
            GetMonData(&party[i], MON_DATA_OT_NAME, otName);

            // Get additional data
            u8 abilityNum = GetMonData(&party[i], MON_DATA_ABILITY_NUM, NULL);
            u32 dynamaxLevel = GetMonData(&party[i], MON_DATA_DYNAMAX_LEVEL, NULL);
            bool32 gigantamaxFactor = GetMonData(&party[i], MON_DATA_GIGANTAMAX_FACTOR, NULL);
            u8 teraType = GetMonData(&party[i], MON_DATA_TERA_TYPE, NULL);

            u16 species = GetMonData(&party[i], MON_DATA_SPECIES, NULL);

            // Create new Pokemon with reduced level
            CreateMon(&party[i], species, levelCap, 0, TRUE, personality, OT_ID_PRESET, otId);

            // Restore all preserved data
            SetMonData(&party[i], MON_DATA_EXP, &exp);
            SetMonData(&party[i], MON_DATA_HELD_ITEM, &heldItem);
            SetMonData(&party[i], MON_DATA_FRIENDSHIP, &friendship);
            SetMonData(&party[i], MON_DATA_POKEBALL, &pokeball);
            SetMonData(&party[i], MON_DATA_IS_SHINY, &isShiny);
            SetMonData(&party[i], MON_DATA_IVS, &ivs);

            // Restore EVs
            SetMonData(&party[i], MON_DATA_HP_EV, &evs[STAT_HP]);
            SetMonData(&party[i], MON_DATA_ATK_EV, &evs[STAT_ATK]);
            SetMonData(&party[i], MON_DATA_DEF_EV, &evs[STAT_DEF]);
            SetMonData(&party[i], MON_DATA_SPEED_EV, &evs[STAT_SPEED]);
            SetMonData(&party[i], MON_DATA_SPATK_EV, &evs[STAT_SPATK]);
            SetMonData(&party[i], MON_DATA_SPDEF_EV, &evs[STAT_SPDEF]);

            // Restore moves and PP
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                SetMonMoveSlot(&party[i], moves[j], j);
                SetMonData(&party[i], MON_DATA_PP1 + j, &pp[j]);
            }
            SetMonData(&party[i], MON_DATA_PP_BONUSES, &ppBonuses);

            // Restore names
            SetMonData(&party[i], MON_DATA_NICKNAME, nickname);
            SetMonData(&party[i], MON_DATA_OT_NAME, otName);

            // Restore additional data
            SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum);
            SetMonData(&party[i], MON_DATA_DYNAMAX_LEVEL, &dynamaxLevel);
            SetMonData(&party[i], MON_DATA_GIGANTAMAX_FACTOR, &gigantamaxFactor);
            SetMonData(&party[i], MON_DATA_TERA_TYPE, &teraType);

            // Recalculate stats with new level
            CalculateMonStats(&party[i]);
        }
    }
}
