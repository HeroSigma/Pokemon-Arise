.set LOCALID_MOM, 1

PalletTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PalletTown_OnFrame
	.byte 0

PalletTown_OnTransition:
	setflag FLAG_VISITED_PALLET_TOWN
	end

PalletTown_OnFrame:
	map_script_2 VAR_INTRO_STATE, 1, PalletTown_EventScript_StepOffTruck
	.2byte 0

PalletTown_EventScript_StepOffTruck::
	lockall
	setvar VAR_0x8004, 6
	setvar VAR_0x8005, 7
	call PalletTown_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_TRUCK
	warpsilent MAP_PALLET_TOWN_PLAYERS_HOUSE_1F, 3, 8
	waitstate
	releaseall
	end

PalletTown_EventScript_GoInsideWithMom::
	delay 15
	playse SE_LEDGE
	applymovement OBJ_EVENT_ID_PLAYER, PalletTown_Movement_PlayerStepOffTruck
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	addobject LOCALID_MOM
	applymovement LOCALID_MOM, PalletTown_Movement_MomExitHouse
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	delay 10
	applymovement LOCALID_MOM, PalletTown_Movement_MomApproachPlayerAtTruck
	waitmovement 0
	msgbox PalletTown_Text_YoureBack, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOM, PalletTown_Movement_MomApproachDoor
	applymovement OBJ_EVENT_ID_PLAYER, PalletTown_Movement_PlayerApproachDoor
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement LOCALID_MOM, PalletTown_Movement_MomEnterHouse
	applymovement OBJ_EVENT_ID_PLAYER, PalletTown_Movement_PlayerEnterHouse
	waitmovement 0
	setflag FLAG_HIDE_INTRO_MOM_OUTSIDE
	setvar VAR_INTRO_STATE, 3
	hideobjectat OBJ_EVENT_ID_PLAYER, 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return

PalletTown_Movement_MomExitHouse:
	walk_down
	step_end

PalletTown_Movement_MomApproachPlayerAtTruck:
	walk_down
	walk_in_place_faster_left
	step_end

PalletTown_Movement_MomApproachDoor:
	delay_16
	delay_8
	walk_up
	step_end

PalletTown_Movement_MomEnterHouse:
	walk_up
	set_invisible
	step_end

PalletTown_Movement_PlayerApproachDoor:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_up
	step_end

PalletTown_Movement_PlayerEnterHouse:
	walk_up
	walk_up
	step_end

PalletTown_Movement_PlayerStepOffTruck:
	jump_right
	delay_16
	delay_16
	delay_16
	step_end

PalletTown_EventScript_OaksLabSign::
	msgbox PalletTown_Text_OakPokemonResearchLab, MSGBOX_SIGN
	end

PalletTown_EventScript_PlayersHouseSign::
	msgbox PalletTown_Text_PlayersHouse, MSGBOX_SIGN
	end

PalletTown_EventScript_OaksHouseSign::
	msgbox PalletTown_Text_OaksHouse, MSGBOX_SIGN
	end

PalletTown_EventScript_TownSign::
        msgbox PalletTown_Text_TownSign, MSGBOX_SIGN
        end

PalletTown_EventScript_TeleportLittleroot::
        lockall
        msgbox PalletTown_Text_TeleportLittleroot, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, PalletTown_EventScript_TeleportEnd
        warpteleport MAP_LITTLEROOT_TOWN, 3, 10
        waitstate
PalletTown_EventScript_TeleportEnd::
        releaseall
        end

PalletTown_EventScript_TeleportNewBark::
        lockall
        msgbox PalletTown_Text_TeleportNewBark, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, PalletTown_EventScript_TeleportEnd
        warpteleport MAP_NEW_BARK_TOWN, 3, 10
        waitstate
        goto PalletTown_EventScript_TeleportEnd

PalletTown_Text_YoureBack:
	.string "MOM: {PLAYER}, you're back, honey!\p"
	.string "It must be tiring riding with your things\n"
	.string "in the moving truck.\p"
	.string "Come on, let's go inside.$"

PalletTown_Text_OakPokemonResearchLab::
    .string "OAK POKéMON RESEARCH LAB$"

PalletTown_Text_PlayersHouse::
    .string "{PLAYER}'S HOUSE$"

PalletTown_Text_OaksHouse::
    .string "PROFESSOR OAK'S HOUSE$"

PalletTown_Text_TownSign::
    .string "PALLET TOWN\n"
    .string "Shades of your journey await!$"

PalletTown_Text_TeleportLittleroot:
    .string "Warp to LITTLEROOT TOWN?$"

PalletTown_Text_TeleportNewBark:
    .string "Warp to NEW BARK TOWN?$"
