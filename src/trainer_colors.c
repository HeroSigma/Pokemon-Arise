#include "global.h"
#include "constants/trainers.h"
#include "trainer_colors.h"
#include "text.h"

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

// Define some basic colors
#define BLACK  { 0,  0,  0}
#define WHITE  {31, 31, 31}
#define RED    {31,  0,  0}
#define GREEN  { 0, 31,  0}
#define BLUE   { 0,  0, 31}
#define YELLOW {31, 31,  0}
#define PURPLE {31,  0, 31}
#define CYAN   { 0, 31, 31}
#define ORANGE {31, 16,  0}
#define PINK   {31, 12, 16}
#define BROWN  {16,  8,  0}
#define GRAY   {16, 16, 16}
#define TEAM_AQUA_BLUE { 0, 16, 31}
#define TEAM_MAGMA_RED {31,  8,  0}

// Default color (white)
static const TrainerColor sDefaultColor = WHITE;

// Color definitions for each trainer class
static const TrainerColor sTrainerClassColors[] = {
    [TRAINER_CLASS_HIKER]           = BROWN,
    [TRAINER_CLASS_TEAM_AQUA]       = TEAM_AQUA_BLUE,
    [TRAINER_CLASS_PKMN_BREEDER]    = PINK,
    [TRAINER_CLASS_COOLTRAINER]     = PURPLE,
    [TRAINER_CLASS_BIRD_KEEPER]     = YELLOW,
    [TRAINER_CLASS_COLLECTOR]       = BROWN,
    [TRAINER_CLASS_SWIMMER_M]       = BLUE,
    [TRAINER_CLASS_TEAM_MAGMA]      = TEAM_MAGMA_RED,
    [TRAINER_CLASS_EXPERT]          = PURPLE,
    [TRAINER_CLASS_AQUA_ADMIN]      = TEAM_AQUA_BLUE,
    [TRAINER_CLASS_BLACK_BELT]      = BLACK,
    [TRAINER_CLASS_AQUA_LEADER]     = TEAM_AQUA_BLUE,
    [TRAINER_CLASS_HEX_MANIAC]      = PURPLE,
    [TRAINER_CLASS_AROMA_LADY]      = PINK,
    [TRAINER_CLASS_RUIN_MANIAC]     = BROWN,
    [TRAINER_CLASS_INTERVIEWER]     = YELLOW,
    [TRAINER_CLASS_TUBER_F]         = BLUE,
    [TRAINER_CLASS_TUBER_M]         = BLUE,
    [TRAINER_CLASS_LADY]            = PINK,
    [TRAINER_CLASS_BEAUTY]          = PINK,
    [TRAINER_CLASS_RICH_BOY]        = YELLOW,
    [TRAINER_CLASS_POKEMANIAC]      = PURPLE,
    [TRAINER_CLASS_GUITARIST]       = BLACK,
    [TRAINER_CLASS_KINDLER]         = ORANGE,
    [TRAINER_CLASS_CAMPER]          = GREEN,
    [TRAINER_CLASS_PICNICKER]       = GREEN,
    [TRAINER_CLASS_BUG_MANIAC]      = YELLOW,
    [TRAINER_CLASS_PSYCHIC]         = PURPLE,
    [TRAINER_CLASS_GENTLEMAN]       = GRAY,
    [TRAINER_CLASS_ELITE_FOUR]      = PURPLE,
    [TRAINER_CLASS_LEADER]          = RED,
    [TRAINER_CLASS_SCHOOL_KID]      = YELLOW,
    [TRAINER_CLASS_SR_AND_JR]       = PINK,
    [TRAINER_CLASS_WINSTRATE]       = WHITE,
    [TRAINER_CLASS_POKEFAN]         = PINK,
    [TRAINER_CLASS_YOUNGSTER]       = GREEN,
    [TRAINER_CLASS_CHAMPION]        = YELLOW,
    [TRAINER_CLASS_FISHERMAN]       = BLUE,
    [TRAINER_CLASS_TRIATHLETE]      = CYAN,
    [TRAINER_CLASS_DRAGON_TAMER]    = PURPLE,
    [TRAINER_CLASS_NINJA_BOY]       = BLACK,
    [TRAINER_CLASS_BATTLE_GIRL]     = RED,
    [TRAINER_CLASS_PARASOL_LADY]    = PINK,
    [TRAINER_CLASS_SWIMMER_F]       = BLUE,
    [TRAINER_CLASS_TWINS]           = PINK,
    [TRAINER_CLASS_SAILOR]          = BLUE,
    [TRAINER_CLASS_COOLTRAINER_2]   = PURPLE,
    [TRAINER_CLASS_MAGMA_ADMIN]     = TEAM_MAGMA_RED,
    [TRAINER_CLASS_RIVAL]           = GREEN,
    [TRAINER_CLASS_BUG_CATCHER]     = GREEN,
    [TRAINER_CLASS_PKMN_RANGER]     = GREEN,
    [TRAINER_CLASS_MAGMA_LEADER]    = TEAM_MAGMA_RED,
    [TRAINER_CLASS_LASS]            = PINK,
    [TRAINER_CLASS_YOUNG_COUPLE]    = PINK,
    [TRAINER_CLASS_OLD_COUPLE]      = GRAY,
    [TRAINER_CLASS_SIS_AND_BRO]     = BLUE,
    [TRAINER_CLASS_SALON_MAIDEN]    = PINK,
    [TRAINER_CLASS_DOME_ACE]        = YELLOW,
    [TRAINER_CLASS_PALACE_MAVEN]    = PURPLE,
    [TRAINER_CLASS_ARENA_TYCOON]    = YELLOW,
    [TRAINER_CLASS_FACTORY_HEAD]    = GRAY,
    [TRAINER_CLASS_PIKE_QUEEN]      = PINK,
    [TRAINER_CLASS_PYRAMID_KING]    = YELLOW,
    [TRAINER_CLASS_RS_PROTAG]       = BLUE,
};

const TrainerColor* GetTrainerClassColor(u8 trainerClass)
{
    if (trainerClass >= ARRAY_COUNT(sTrainerClassColors) || 
        (sTrainerClassColors[trainerClass].r == 0 && 
         sTrainerClassColors[trainerClass].g == 0 && 
         sTrainerClassColors[trainerClass].b == 0))
    {
        return &sDefaultColor;
    }
    return &sTrainerClassColors[trainerClass];
}

// Returns a GBA color (0x7FFF format) based on the trainer's class
u16 GetTrainerClassTextColor(u8 trainerClass)
{
    // Get the RGB color for this trainer class
    const TrainerColor* color = GetTrainerClassColor(trainerClass);
    
    // Special case: For black text, we'll use a very dark gray instead
    // to ensure it's visible on dark backgrounds
    if (color->r == 0 && color->g == 0 && color->b == 0)
        return RGB2(5, 5, 5);  // Dark gray instead of pure black
        
    // For white text, use a slightly off-white to stand out from the background
    if (color->r >= 30 && color->g >= 30 && color->b >= 30)
        return RGB2(25, 25, 25);  // Off-white
        
    // For very light colors, darken them slightly for better contrast
    if (color->r + color->g + color->b > 60)  // If sum > 60 (very light)
    {
        u8 r = (color->r * 2) / 3;  // Reduce brightness by 1/3
        u8 g = (color->g * 2) / 3;
        u8 b = (color->b * 2) / 3;
        return RGB2(r, g, b);
    }
    
    // For dark colors, ensure minimum brightness for visibility
    if (color->r + color->g + color->b < 15)  // If sum < 15 (very dark)
    {
        u8 minBrightness = 5;
        u8 r = MAX(color->r, minBrightness);
        u8 g = MAX(color->g, minBrightness);
        u8 b = MAX(color->b, minBrightness);
        return RGB2(r, g, b);
    }
    
    // Default case: use the color as-is
    return RGB2(color->r, color->g, color->b);
}
