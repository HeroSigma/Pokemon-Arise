PalletTown_PlayersHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_PlayersHouse_2F_OnTransition
	.byte 0

PalletTown_PlayersHouse_2F_OnTransition:
        call_if_eq VAR_INTRO_STATE, 4, PlayersHouse_2F_EventScript_BlockStairsUntilClockIsSet
        end

PalletTown_PlayersHouse_2F_Text_HowDoYouLikeYourRoom:
        .string "MOM: How do you like your room?\p"
        .string "Everything's put away neatly.\n"
        .string "They finished moving everything\n"
        .string "in downstairs, too!\p"
        .string "POKEMON movers are so convenient!$"
