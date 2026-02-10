#ifndef GUARD_CONFIG_AI_H
#define GUARD_CONFIG_AI_H

// =============================================================================
// OP AI CONFIG - "GOD MODE" PRESET
// =============================================================================
// This preset makes AI nearly omniscient and hyper-aggressive:
// - Switches PERFECTLY out of ANY bad situation (100% on all "should switch")
// - Stays in ONLY if truly advantageous (0% "stay in" biases)
// - Considers almost ALL non-perfect moves "bad" (super high thresholds)
// - Predicts switches/moves flawlessly
// - Uses Tera aggressively (no conservation, always saves from KO)
// - Ignores recovery unless dying (<30%)
// - Enables omniscience cheats for perfect switching/knowledge
// - Setup sweepers are protected (stay after minimal boosts)
// - Status/PP stall is detected & punished 100%
// - Doubles: Avoids friendly fire religiously
// 
// WARNING: This will make AI unbeatable vs average players.
// Test in singles first. Tune down if too frustrating.
// =============================================================================

// CORE SWITCHING (always switch from doom)
#define SHOULD_SWITCH_WONDER_GUARD_PERCENTAGE                   100
#define SHOULD_SWITCH_TRUANT_PERCENTAGE                         100
#define SHOULD_SWITCH_ALL_MOVES_BAD_PERCENTAGE                  100
#define STAY_IN_STATS_RAISED                                    1   // Stay/protect after ANY setup (OP sweeper mode)

// SMART SWITCHING (perfect decisions)
#define SHOULD_SWITCH_ABSORBS_MOVE_PERCENTAGE                       100
#define SHOULD_SWITCH_ABSORBS_HIDDEN_POWER_PERCENTAGE               100
#define SHOULD_SWITCH_TRAPPER_PERCENTAGE                            100
#define SHOULD_SWITCH_FREE_TURN_PERCENTAGE                          100
#define STAY_IN_ABSORBING_PERCENTAGE                                0    // NEVER stay if better absorber available
#define SHOULD_SWITCH_HASBADODDS_PERCENTAGE                         100
#define SHOULD_SWITCH_ENCORE_STATUS_PERCENTAGE                      100
#define SHOULD_SWITCH_ENCORE_DAMAGE_PERCENTAGE                      100
#define SHOULD_SWITCH_CHOICE_LOCKED_PERCENTAGE                      100 // Only if locked into status move
#define SHOULD_SWITCH_ATTACKING_STAT_MINUS_TWO_PERCENTAGE           100
#define SHOULD_SWITCH_ATTACKING_STAT_MINUS_THREE_PLUS_PERCENTAGE    100
#define SHOULD_SWITCH_ALL_SCORES_BAD_PERCENTAGE                     100

// STATUS (flee ALL bad status instantly)
#define SHOULD_SWITCH_PERISH_SONG_PERCENTAGE                    100
#define SHOULD_SWITCH_YAWN_PERCENTAGE                           100
#define SHOULD_SWITCH_BADLY_POISONED_PERCENTAGE                 100
#define SHOULD_SWITCH_BADLY_POISONED_STATS_RAISED_PERCENTAGE    100
#define SHOULD_SWITCH_CURSED_PERCENTAGE                         100
#define SHOULD_SWITCH_CURSED_STATS_RAISED_PERCENTAGE            100
#define SHOULD_SWITCH_NIGHTMARE_PERCENTAGE                      100
#define SHOULD_SWITCH_NIGHTMARE_STATS_RAISED_PERCENTAGE         100
#define SHOULD_SWITCH_SEEDED_PERCENTAGE                         100
#define SHOULD_SWITCH_SEEDED_STATS_RAISED_PERCENTAGE            100
#define SHOULD_SWITCH_INFATUATION_PERCENTAGE                    100

// BENEFICIAL ABILITIES (still switch out aggressively unless desperate)
#define SHOULD_SWITCH_NATURAL_CURE_STRONG_PERCENTAGE                100
#define SHOULD_SWITCH_NATURAL_CURE_STRONG_STATS_RAISED_PERCENTAGE   50
#define SHOULD_SWITCH_NATURAL_CURE_WEAK_PERCENTAGE                  100
#define SHOULD_SWITCH_NATURAL_CURE_WEAK_STATS_RAISED_PERCENTAGE     50
#define SHOULD_SWITCH_REGENERATOR_PERCENTAGE                        100
#define SHOULD_SWITCH_REGENERATOR_STATS_RAISED_PERCENTAGE           50

// SWITCH CONSIDERATIONS (ultra picky)
#define ALL_MOVES_BAD_STATUS_MOVES_BAD                          TRUE   // Ignore status moves entirely for "all bad" check
#define AI_BAD_SCORE_THRESHOLD                                  140    // ALMOST EVERYTHING below perfect is "bad" -> switch!
#define AI_GOOD_SCORE_THRESHOLD                                 90     // "Good" is lenient but rare with high bad thresh

// MOVE SCORING (perfect play)
#define LOW_ACCURACY_THRESHOLD                                  75
#define STATUS_MOVE_FOCUS_PUNCH_CHANCE                          0      // Never fall for Focus Punch
#define BOOST_INTO_HAZE_CHANCE                                  0      // Never boost into Haze
#define SHOULD_RECOVER_CHANCE                                   100    // Recover ONLY if low HP
#define ENABLE_RECOVERY_THRESHOLD                               30     // Desperate only
#define SUCKER_PUNCH_CHANCE                                     0      // NEVER whiff Sucker Punch
#define SUCKER_PUNCH_PREDICTION_CHANCE                          0
#define PRIORITIZE_LAST_CHANCE_CHANCE                           100    // Always prioritize revenge kills

// DAMAGE CALC (assumes crits often)
#define RISKY_AI_CRIT_STAGE_THRESHOLD                           1      // Crit assumption at +1 stage
#define RISKY_AI_CRIT_THRESHOLD_GEN_1                           64     // Very low crit threshold

// PREDICTION (psychic level)
#define PREDICT_SWITCH_CHANCE                                   100
#define PREDICT_MOVE_CHANCE                                     100

// TERA (always optimal)
#define AI_CONSERVE_TERA_CHANCE_PER_MON                         0      // Use Tera on mon 1, always
#define AI_TERA_PREDICT_CHANCE                                  100    // ALWAYS tera to dodge KO

// PP STALL (impossible to stall)
#define PP_STALL_DISREGARD_MOVE_PERCENTAGE                      100
#define PP_STALL_SCORE_REDUCTION                                100

// ASSUME STAB (full omniscience)
#define ASSUME_STAB_SEES_ABILITY                                TRUE

// ASSUME STATUS MOVES (knows all likely moves)
#define ASSUME_STATUS_MOVES_HAS_TUNING                  TRUE
#define ASSUME_STATUS_HIGH_ODDS                         100
#define ASSUME_STATUS_MEDIUM_ODDS                       100
#define ASSUME_STATUS_LOW_ODDS                          100
#define ASSUME_ALL_STATUS_ODDS                          100

// SMART SWITCHING (cheat mode ON)
#define SMART_SWITCHING_OMNISCIENT                              TRUE

// DOUBLES (godlike positioning)
#define FRIENDLY_FIRE_RISKY_THRESHOLD             0
#define FRIENDLY_FIRE_NORMAL_THRESHOLD            1
#define FRIENDLY_FIRE_CONSERVATIVE_THRESHOLD      0
#define DOUBLE_TRICK_ROOM_ON_LAST_TURN_CHANCE    100
#define TAILWIND_IN_TRICK_ROOM_CHANCE            100
#define AI_FLAG_ATTACKS_PARTNER_FOCUSES_PARTNER  TRUE

// SPLIT MOVES (always optimal)
#define GUARD_SPLIT_ALLY_PERCENTAGE     300
#define GUARD_SPLIT_ENEMY_PERCENTAGE    0
#define POWER_SPLIT_ALLY_PERCENTAGE     300
#define POWER_SPLIT_ENEMY_PERCENTAGE    0

// Z-MOVES (use aggressively on status)
#define Z_EFFECT_FOLLOW_ME_THRESHOLD    10
#define Z_EFFECT_RESTORE_HP_LOWER_THRESHOLD   20
#define Z_EFFECT_RESTORE_HP_HIGHER_THRESHOLD  50

#endif // GUARD_CONFIG_AI_H
