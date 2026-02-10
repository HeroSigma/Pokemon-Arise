#include "global.h"
#include "data.h"
#include "event_data.h"
#include "script.h"
#include "constants/battle.h"

enum DifficultyLevel GetCurrentDifficultyLevel(void)
{
    if (!VAR_UNUSED_0x4091)
        return DIFFICULTY_NORMAL;

    return VarGet(VAR_UNUSED_0x4091);
}

void SetCurrentDifficultyLevel(enum DifficultyLevel desiredDifficulty)
{
    if (!VAR_UNUSED_0x4091)
        return;

    if (desiredDifficulty > DIFFICULTY_MAX)
        desiredDifficulty = DIFFICULTY_MAX;

    VarSet(VAR_UNUSED_0x4091, desiredDifficulty);
}

enum DifficultyLevel GetBattlePartnerDifficultyLevel(u16 partnerId)
{
    enum DifficultyLevel difficulty = GetCurrentDifficultyLevel();

    if (partnerId > TRAINER_PARTNER(PARTNER_NONE))
        partnerId -= TRAINER_PARTNER(PARTNER_NONE);

    if (difficulty == DIFFICULTY_NORMAL)
        return DIFFICULTY_NORMAL;

    if (gBattlePartners[difficulty][partnerId].party == NULL)
        return DIFFICULTY_NORMAL;

    return difficulty;
}

enum DifficultyLevel GetTrainerDifficultyLevel(u16 trainerId)
{
    enum DifficultyLevel difficulty = GetCurrentDifficultyLevel();

    if (difficulty == DIFFICULTY_NORMAL)
        return DIFFICULTY_NORMAL;

    if (gTrainers[difficulty][trainerId].party == NULL)
        return DIFFICULTY_NORMAL;

    return difficulty;
}

void Script_IncreaseDifficulty(void)
{
    enum DifficultyLevel currentDifficulty;

    if (!VAR_UNUSED_0x4091)
        return;

    currentDifficulty = GetCurrentDifficultyLevel();

    if (currentDifficulty++ > DIFFICULTY_MAX)
        return;

    Script_RequestEffects(SCREFF_V1);
    Script_RequestWriteVar(VAR_UNUSED_0x4091);

    SetCurrentDifficultyLevel(currentDifficulty);
}

void Script_DecreaseDifficulty(void)
{
    enum DifficultyLevel currentDifficulty;

    if (!VAR_UNUSED_0x4091)
        return;

    currentDifficulty = GetCurrentDifficultyLevel();

    if (!currentDifficulty)
        return;

    Script_RequestEffects(SCREFF_V1);
    Script_RequestWriteVar(VAR_UNUSED_0x4091);

    SetCurrentDifficultyLevel(--currentDifficulty);
}

void Script_GetDifficulty(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = GetCurrentDifficultyLevel();
}

void Script_SetDifficulty(struct ScriptContext *ctx)
{
    enum DifficultyLevel desiredDifficulty = ScriptReadByte(ctx);

    Script_RequestEffects(SCREFF_V1);
    Script_RequestWriteVar(VAR_UNUSED_0x4091);

    SetCurrentDifficultyLevel(desiredDifficulty);
}
