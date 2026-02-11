.set LOCALID_RIVAL, 1

LittlerootTown_PlayersHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_PlayersHouse_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_PlayersHouse_2F_OnWarp
	.byte 0

LittlerootTown_PlayersHouse_2F_OnTransition:
	call SecretBase_EventScript_SetDecorationFlags
	setvar VAR_SECRET_BASE_INITIALIZED, 0
	end

LittlerootTown_PlayersHouse_2F_OnWarp:
	map_script_2 VAR_SECRET_BASE_INITIALIZED, 0, LittlerootTown_PlayersHouse_2F_EventScript_CheckInitDecor
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 4, LittlerootTown_PlayersHouse_2F_EventScript_ShowTruckArrival
	.2byte 0

LittlerootTown_PlayersHouse_2F_EventScript_CheckInitDecor::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, SecretBase_EventScript_InitDecorations
	end

LittlerootTown_PlayersHouse_2F_EventScript_PC::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_PlayersHouse_2F_EventScript_CheckPlayersPC
	goto_if_eq VAR_RESULT, FEMALE, LittlerootTown_PlayersHouse_2F_EventScript_CheckRivalsPC
	end

LittlerootTown_PlayersHouse_2F_EventScript_CheckPlayersPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special BedroomPC
	waitstate
	releaseall
	end

LittlerootTown_PlayersHouse_2F_EventScript_TurnOffPlayerPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

LittlerootTown_PlayersHouse_2F_EventScript_CheckRivalsPC::
	msgbox gText_PokemonTrainerSchoolEmail, MSGBOX_DEFAULT
	releaseall
	end

PlayersHouse_2F_EventScript_Notebook::
	msgbox PlayersHouse_2F_Text_Notebook, MSGBOX_SIGN
	end

PlayersHouse_2F_EventScript_GameCube::
	msgbox PlayersHouse_2F_Text_ItsAGameCube, MSGBOX_SIGN
	end

// Brief flicker when arriving upstairs to hint at the Poké Ball
PlayersHouse_2F_EventScript_IntroFlicker::
	lockall
	msgbox PlayersHouse_2F_Text_FlickerThought, MSGBOX_DEFAULT
	releaseall
	return

// Wrapper to show the truck arrival scene after warp completes
LittlerootTown_PlayersHouse_2F_EventScript_ShowTruckArrival::
	lockall
	msgbox gText_Truck_Intro, MSGBOX_DEFAULT
	msgbox gText_Truck_PlayerReflection, MSGBOX_DEFAULT
	msgbox gText_Truck_ReadyToExit, MSGBOX_DEFAULT
	setvar VAR_LITTLEROOT_INTRO_STATE, 5
	releaseall
	return

// Poké Ball interaction: grant Z-Power Ring with flavor dialogue
PlayersHouse_2F_EventScript_ZRingBall::
    lockall
    checkitem ITEM_Z_POWER_RING, 1
    goto_if_eq VAR_RESULT, TRUE, PlayersHouse_2F_EventScript_ZRingBall_Empty
    msgbox PlayersHouse_2F_Text_PlayerBallSpot, MSGBOX_DEFAULT
    msgbox PlayersHouse_2F_Text_PlayerCallMom, MSGBOX_DEFAULT
    msgbox PlayersHouse_2F_Text_MomReply, MSGBOX_DEFAULT
    setvar VAR_0x8000, ITEM_Z_POWER_RING
    setvar VAR_0x8001, 1
    callstd STD_OBTAIN_ITEM
    setflag FLAG_HIDE_LITTLEROOT_TOWN_PLAYERS_HOUSE_2F_ZRING_BALL
    removeobject VAR_LAST_TALKED
    msgbox PlayersHouse_2F_Text_DistantVoice, MSGBOX_DEFAULT
    releaseall
    end

PlayersHouse_2F_EventScript_ZRingBall_Empty::
    msgbox PlayersHouse_2F_Text_EmptyBall, MSGBOX_SIGN
    releaseall
    end

PlayersHouse_2F_Text_ClockIsStopped:
	.string "The clock is stopped…\p"
	.string "Better set it and start it!$"

PlayersHouse_2F_Text_PlayerSafeEnough:
	.string "I guess this is safe enough.$"

PlayersHouse_2F_Text_Notebook:
	.string "{PLAYER} flipped open the notebook.\p"
	.string "ADVENTURE RULE NO. 1\n"
	.string "Open the MENU with START.\p"
	.string "ADVENTURE RULE NO. 2\n"
	.string "Record your progress with SAVE.\p"
	.string "The remaining pages are blank…$"

Common_Text_LookCloserAtMap:
	.string "{PLAYER} took a closer look at the\n"
	.string "HOENN region map.$"

Common_Text_LookCloserAtMapKanto:
	.string "{PLAYER} took a closer look at the\n"
	.string "KANTO region map.$"

Common_Text_LookCloserAtMapJohto:
	.string "{PLAYER} took a closer look at the\n"
	.string "JOHTO region map.$"

Common_Text_LookCloserAtMapSevii:
	.string "{PLAYER} took a closer look at the\n"
	.string "SEVII ISLES map.$"

PlayersHouse_2F_Text_ItsAGameCube:
        .string "It's a Nintendo GameCube.\p"
        .string "A Game Boy Advance is connected to\n"
        .string "serve as the Controller.$"

PlayersHouse_2F_Text_FlickerThought:
	.string "{COLOR GREEN}(Did the light just flicker?\n"
	.string "Weird…){COLOR DARK_GRAY}$"

PlayersHouse_2F_Text_PlayerBallSpot:
	.string "{COLOR GREEN}{PLAYER}: Huh? There's a Poké Ball here…{COLOR DARK_GRAY}$"

PlayersHouse_2F_Text_PlayerCallMom:
	.string "{COLOR GREEN}{PLAYER}: Mom, did you put a Poké Ball\n"
	.string "in my room?{COLOR DARK_GRAY}$"

PlayersHouse_2F_Text_MomReply:
	.string "MOM: No, dear! Maybe the movers left it?\p"
	.string "Or maybe it's a welcome gift!$"

PlayersHouse_2F_Text_DistantVoice:
    	.string "A distant voice: Your destiny awaits…$"

PlayersHouse_2F_Text_EmptyBall:
	.string "The Poké Ball is empty.$"

LittlerootTown_PlayersHouse_2F_Text_HowDoYouLikeYourRoom:
	.string "MOM: All set? The room looks nice.\p"
	.string "Good. Caelum will be glad you're safe.\p"
	.string "He said to take it easy for now.\p"
	.string "When things calm down, he'll catch up.\p"
	.string "Come downstairs when you're ready.\p"
	.string "$"
        .equ PlayersHouse_2F_Text_HowDoYouLikeYourRoom, LittlerootTown_PlayersHouse_2F_Text_HowDoYouLikeYourRoom
// Upstairs intro monologue (gender-specific)
PlayersHouse_2F_Text_UpstairsIntro_Male_1:
	.string "{COLOR GREEN}{PLAYER}: So this is my room again…\p"
	.string "feels smaller than the one back home.{COLOR DARK_GRAY}$"

PlayersHouse_2F_Text_UpstairsIntro_Male_2:
	.string "{COLOR GREEN}{PLAYER}: Still, it’s mine.\p"
	.string "A fresh start in HOENN.{COLOR DARK_GRAY}$"

PlayersHouse_2F_Text_UpstairsIntro_Male_3:
	.string "{COLOR GREEN}{PLAYER}: …Back at the Archipelago, Father’s\p"
	.string "study was always full of notes and machines.\p"
	.string "This room feels… quiet in comparison.{COLOR DARK_GRAY}$"

PlayersHouse_2F_Text_UpstairsIntro_Female_1:
	.string "{COLOR GREEN}{PLAYER}: So this is my room again…\p"
	.string "it’s cozier than what I remember.{COLOR DARK_GRAY}$"

PlayersHouse_2F_Text_UpstairsIntro_Female_2:
	.string "{COLOR GREEN}{PLAYER}: Guess I’ll have to make it mine\p"
	.string "all over again.{COLOR DARK_GRAY}$"

PlayersHouse_2F_Text_UpstairsIntro_Female_3:
	.string "{COLOR GREEN}{PLAYER}: …At the Archipelago, Father’s study\p"
	.string "always echoed with machines and scribbled notes.\p"
	.string "This room feels… still.{COLOR DARK_GRAY}$"

// Mom enters after setting the clock
PlayersHouse_2F_Text_MomDidYouSetClock:
	.string "MOM: {PLAYER}! Did you set the clock yet?$"

PlayersHouse_2F_Text_MomMakeSureSchedule:
	.string "MOM: Make sure it’s right- we’ll need to\n"
	.string " keep a proper schedule here in LITTLEROOT.$"

PlayersHouse_2F_Text_PlayerClockLine_Male:
	.string "{COLOR GREEN}{PLAYER}: Yeah, I’ll set it. Something about\n"
	.string "seeing the hands move… feels grounding.{COLOR DARK_GRAY}$"

PlayersHouse_2F_Text_PlayerClockLine_Female:
	.string "{COLOR GREEN}{PLAYER}: Mm. I’ll set it. Something about the\n"
	.string "ticking… feels steady.{COLOR DARK_GRAY}$"
