# Badge-Based Level Cap Enforcement

This system automatically enforces badge-based level caps on trainer battles by downgrading illegal Pokémon forms to their legal pre-evolutions while preserving all other data.

## How It Works

1. **Level Cap Detection**: Uses the existing `GetCurrentLevelCap()` function to determine the current level cap based on the player's badge count.

2. **Evolution Legality Check**: For each Pokémon in a trainer's party, the system checks if its evolution is legal under the current level cap:
   - **Level-based evolutions** (e.g., Charmander → Charmeleon at level 16): Only allowed if the required level is within the current level cap
   - **Non-level evolutions** (trade, item, friendship, etc.): Allowed based on badge count policy (configurable)

3. **Automatic Downgrading**: If a Pokémon's evolution is illegal, it's automatically downgraded to the most recent legal pre-evolution while preserving:
   - Level, experience, and stats
   - Moveset and PP
   - IVs, EVs, and nature
   - Ability, held item, and Poké Ball
   - Nickname and OT information
   - Shiny status, Tera type, and Dynamax level

## Configuration Options

Located in `include/config/caps.h`:

### B_TRAINER_EVOLUTION_ENFORCEMENT
- **TRUE**: Enable badge-based evolution enforcement (default)
- **FALSE**: Disable the system entirely

### B_NON_LEVEL_EVO_BADGE_REQUIREMENT
- **0**: Allow all non-level evolutions regardless of badge count
- **1-8**: Require this many badges before allowing non-level evolutions
- **5**: Default setting (allows trade/item evolutions after 5th badge)

## Examples

### Early Game (0-1 badges, level cap 16-20)
- Charmeleon (evolves at 16) → Downgraded to Charmander if level cap is below 16
- Alakazam (trade evolution) → Downgraded to Kadabra (or Abra if badges < 5)
- Golem (trade evolution) → Downgraded to Graveler (or Geodude if badges < 5)

### Mid Game (5+ badges, level cap 33+)
- Non-level evolutions like Alakazam, Golem, Steelix are now allowed
- Level-based evolutions still respect the level cap

### Late Game (8 badges, level cap 46+)
- Most evolutions are legal
- Only very high-level evolutions might still be restricted

## Trainer Exemptions

The `IsTrainerExemptFromLevelCap()` function can be customized to exempt specific trainers:

```c
bool32 IsTrainerExemptFromLevelCap(u16 trainerId)
{
    // Example: Exempt gym leaders, Elite Four, and Champion
    if (trainerId >= TRAINER_ROXANNE && trainerId <= TRAINER_WALLACE)
        return TRUE;
    
    // Exempt specific important battles
    if (trainerId == TRAINER_RIVAL_FINAL || trainerId == TRAINER_CHAMPION)
        return TRUE;
    
    return FALSE; // Apply level cap to all other trainers
}
```

## Technical Details

### Key Functions

- `FindPreEvolution(u16 species)`: Finds the immediate pre-evolution of a species
- `IsEvolutionLegalUnderLevelCap()`: Checks if an evolution is legal under current restrictions
- `DowngradeToLegalSpecies()`: Recursively downgrades a species to its legal form
- `EnforceLevelCapOnTrainerParty()`: Main enforcement function called during trainer party creation

### Integration Points

The system integrates into the existing trainer battle flow:
1. `CreateNPCTrainerParty()` creates the trainer's party normally
2. `EnforceLevelCapOnTrainerParty()` is called to enforce level caps
3. Battle proceeds with the adjusted party

### Performance Considerations

- Evolution checking is done once per trainer battle, not during battle
- Pre-evolution lookup uses a simple linear search (acceptable for the number of species)
- All data preservation is done in-place to minimize memory usage

## Customization

### Adding New Evolution Methods

To support new evolution methods, update `IsEvolutionLegalUnderLevelCap()`:

```c
case EVO_NEW_METHOD:
    // Add your logic here
    return someCondition;
```

### Changing Badge Requirements

Modify `B_NON_LEVEL_EVO_BADGE_REQUIREMENT` or add more granular control:

```c
// Example: Different requirements for different evolution types
case EVO_TRADE:
    return badgeCount >= 3;  // Trade evolutions after 3 badges
case EVO_ITEM:
    return badgeCount >= 5;  // Item evolutions after 5 badges
```

### Adding Trainer-Specific Rules

Expand `IsTrainerExemptFromLevelCap()` with custom logic:

```c
// Example: Allow higher evolutions for gym leaders
if (IsGymLeader(trainerId))
    return TRUE;

// Example: Progressive difficulty - later trainers get more leeway
if (GetTrainerDifficultyRating(trainerId) > DIFFICULTY_HARD)
    return TRUE;
```

## Compatibility

This system is designed to work alongside existing pokeemerald features:
- Compatible with existing level cap systems
- Works with custom trainer data formats
- Preserves all modern Pokémon features (Tera types, Dynamax, etc.)
- Does not modify trainer files - all changes are runtime only

## Troubleshooting

### Common Issues

1. **Evolutions not being downgraded**: Check that `B_TRAINER_EVOLUTION_ENFORCEMENT` is TRUE
2. **Wrong badge requirements**: Verify `B_NON_LEVEL_EVO_BADGE_REQUIREMENT` setting
3. **Specific trainers not affected**: Check if they're exempted in `IsTrainerExemptFromLevelCap()`

### Debug Information

Add debug prints to see what's happening:

```c
// In EnforceLevelCapOnTrainerParty()
if (legalSpecies != currentSpecies)
{
    // Debug: Print downgrade information
    printf("Downgraded species %d to %d for trainer %d\n", 
           currentSpecies, legalSpecies, trainerId);
}
```
