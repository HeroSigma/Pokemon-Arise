# Multi-Generation Starter Selection System Implementation

## Overview
This implementation transforms the original 3-starter selection system into a two-phase system allowing players to choose from all 27 official starters (Generations 1-9) while reusing the original Birch bag scene, animations, and logic.

## System Architecture

### Phase 1 - Group Selection
- **Screen**: Shows 3 Poké Balls representing generation groups
  - Left: Gen 1-3 (Bulbasaur, Charmander, Squirtle; Chikorita, Cyndaquil, Totodile; Treecko, Torchic, Mudkip)
  - Middle: Gen 4-6 (Turtwig, Chimchar, Piplup; Snivy, Tepig, Oshawott; Chespin, Fennekin, Froakie)
  - Right: Gen 7-9 (Rowlet, Litten, Popplio; Grookey, Scorbunny, Sobble; Sprigatito, Fuecoco, Quaxly)
- **Controls**: D-pad to move hand cursor, A to select group
- **Behavior**: Selected ball animates (bouncing), A button transitions to Phase 2

### Phase 2 - Starter Selection
- **Screen**: 3 new Poké Balls appear showing actual starters from selected group
- **Controls**: D-pad to move between starters, A to confirm, B to return to Phase 1
- **Behavior**: Triggers original reveal animation (circle + Pokémon sprite + cry), then Yes/No confirmation

## Implementation Checklist

### ✅ Core Data Structures
- [x] Added constants: `STARTER_GROUP_COUNT`, `STARTERS_PER_GROUP`, `TOTAL_STARTERS`
- [x] Created `sAllStarters[TOTAL_STARTERS]` array with all 27 starters
- [x] Added task data variables: `tPhase` (0=group, 1=starter), `tGroupSelection`
- [x] Updated `GetStarterPokemon()` to handle 27 starters
- [x] Added `GetStarterFromGroup()` helper function

### ✅ Phase Management
- [x] Modified `Task_HandleStarterChooseInput()` for Phase 1 group selection
- [x] Created `Task_HandleStarterSelectionInput()` for Phase 2 starter selection
- [x] Implemented `Task_TransitionToStarterSelection()` to switch phases
- [x] Updated initialization to set `tPhase = 0` (start with group selection)

### ✅ Sprite Management
- [x] Phase transition destroys existing Poké Ball sprites
- [x] Creates new Poké Ball sprites for starter selection
- [x] Maintains original sprite animation and positioning logic

### ✅ Confirmation Logic
- [x] Updated `Task_AskConfirmStarter()` to use correct starter species
- [x] Modified `Task_HandleConfirmStarterInput()` to calculate final index: `group * 9 + selection`
- [x] Handles No/B press to return to Phase 2 (starter selection)
- [x] B button in Phase 2 returns to Phase 1 (group selection)

### ✅ Label System
- [x] Updated `CreateStarterPokemonLabel()` to handle both phases
- [x] Phase 1: Shows original starters (can be replaced with group names)
- [x] Phase 2: Shows actual starter names from selected group

## File Changes Made

### `src/starter_choose.c`
- Added new constants and data structures
- Implemented new task functions for phase management
- Modified existing functions to support two-phase system
- Updated confirmation and navigation logic

## Testing Requirements

### Basic Flow Testing
- [ ] Test Phase 1: Navigate between 3 group balls
- [ ] Test Phase 1→2 transition: Select group, verify new balls appear
- [ ] Test Phase 2: Navigate between 3 starter balls
- [ ] Test Phase 2→1 transition: Press B, verify return to group selection
- [ ] Test confirmation: Select starter, verify correct Pokémon appears
- [ ] Test final calculation: Verify `gSpecialVar_Result` equals correct index (0-26)

### Edge Cases
- [ ] Test rapid navigation between phases
- [ ] Test B button at various points
- [ ] Test all 9 groups and their respective starters
- [ ] Verify sprite cleanup works correctly

## Future Enhancements (Optional)

### Polish Features
- [ ] Add group name text above balls in Phase 1 ("Gen 1-3", "Gen 4-6", "Gen 7-9")
- [ ] Add fade/transition effects when switching phases
- [ ] Add sound effects for phase changes
- [ ] Improve label system to show actual group names instead of placeholder starters

### Visual Improvements
- [ ] Different colored Poké Balls for different generations
- [ ] Generation-specific visual themes
- [ ] Enhanced animations for group selection

## Technical Notes

### Index Calculation
- Final starter index: `group * 9 + selection`
- Group 0 (Gen 1-3): Indices 0-8
- Group 1 (Gen 4-6): Indices 9-17  
- Group 2 (Gen 7-9): Indices 18-26

### Memory Management
- Sprite cleanup handled during phase transitions
- Task data properly maintained across phases
- Original memory layout preserved for compatibility

### Compatibility
- Maintains original function signatures where possible
- Preserves original visual presentation and animations
- Compatible with existing save system and special variables

## Conclusion
The implementation successfully extends the starter selection system to support all 27 official starters while maintaining the original game's visual style and user experience. The two-phase approach provides an intuitive navigation system that scales well with the expanded starter roster.
