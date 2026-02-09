InsideOfTruck_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, InsideOfTruck_OnLoad
	map_script MAP_SCRIPT_ON_RESUME, InsideOfTruck_OnResume
	.byte 0

InsideOfTruck_OnLoad:
	setmetatile 4, 1, METATILE_InsideOfTruck_ExitLight_Top, FALSE
	setmetatile 4, 2, METATILE_InsideOfTruck_ExitLight_Mid, FALSE
	setmetatile 4, 3, METATILE_InsideOfTruck_ExitLight_Bottom, FALSE
	end

InsideOfTruck_OnResume:
	setstepcallback STEP_CB_TRUCK
	end

InsideOfTruck_EventScript_SetIntroFlags::
	lockall
	setflag FLAG_HIDE_MAP_NAME_POPUP
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, InsideOfTruck_EventScript_SetIntroFlagsMale
	goto_if_eq VAR_RESULT, FEMALE, InsideOfTruck_EventScript_SetIntroFlagsFemale
	end

InsideOfTruck_EventScript_SetIntroFlagsMale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
	setvar VAR_LITTLEROOT_INTRO_STATE, 1
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_SIBLING
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 1
	setdynamicwarp MAP_LITTLEROOT_TOWN, 3, 10
	releaseall
	end

InsideOfTruck_EventScript_SetIntroFlagsFemale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F
	setvar VAR_LITTLEROOT_INTRO_STATE, 2
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_SIBLING
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 1
	setdynamicwarp MAP_LITTLEROOT_TOWN, 12, 10
	releaseall
	end

InsideOfTruck_EventScript_MovingBox::
	compare VAR_LITTLEROOT_INTRO_STATE, 3
	goto_if_eq VAR_RESULT, TRUE, InsideOfTruck_EventScript_ShowBoxMessage
	compare VAR_UNUSED_0x404E, 1
	goto_if_eq VAR_RESULT, TRUE, InsideOfTruck_EventScript_ShowBoxMessage
	call InsideOfTruck_EventScript_TruckScene
	setvar VAR_LITTLEROOT_INTRO_STATE, 3
	setvar VAR_UNUSED_0x404E, 1
	end

InsideOfTruck_EventScript_DriverStopExit::
	compare VAR_UNUSED_0x404E, 1
	goto_if_eq VAR_RESULT, TRUE, InsideOfTruck_EventScript_AllowExit
	lockall
	msgbox gText_Driver_StopPlayer, MSGBOX_DEFAULT
	call InsideOfTruck_EventScript_TruckScene
	setvar VAR_LITTLEROOT_INTRO_STATE, 3
	setvar VAR_UNUSED_0x404E, 1
	releaseall
	end

InsideOfTruck_EventScript_AllowExit::
	end

gText_Driver_StopPlayer::
	.string "DRIVER: Whoa there, kid!\n"
	.string "Not so fast.\n"
	.string "Got something for ya first.\p"
	.string "$"

InsideOfTruck_EventScript_ShowBoxMessage::
	msgbox InsideOfTruck_Text_BoxPrintedWithMonLogo, MSGBOX_SIGN
	end

InsideOfTruck_EventScript_Null::
	end

InsideOfTruck_Text_BoxPrintedWithMonLogo:
	.string "The box is printed with a POKéMON logo.\p"
	.string "It's a POKéMON brand moving\n"
	.string "and delivery service.$"

gText_Truck_Intro::
	.string "The truck rumbles on...\n"
	.string "You're inside with Mom and\n"
	.string "the driver.\p"
	.string "$"

gText_Driver_Welcome::
	.string "DRIVER: Hey, kid.\n"
	.string "Long trip, huh?\n"
	.string "Name's Mack.\n"
	.string "Back to Hoenn now?\p"
	.string "$"

gText_Player_Choice1::
	.string "What do you say?\p"
	.string "$"

gText_Driver_YeahResponse::
	.string "DRIVER: Heh, Hoenn's still\n"
	.string "the same.\n"
	.string "You'll settle in.\p"
	.string "$"

gText_Driver_NotResponse::
	.string "DRIVER: Tough start?\n"
	.string "Life throws those.\n"
	.string "Hoenn's got ya.\p"
	.string "$"

gText_Selene_Comment::
	.string "SELENE: Thanks, Mack.\n"
	.string "{PLAYER}, we're close...\p"
	.string "$"

gText_Driver_BoxNotice::
	.string "DRIVER: Almost forgot.\n"
	.string "Got a package for ya.\n"
	.string "Special delivery.\n"
	.string "From an 'old friend'.\p"
	.string "$"

gText_Player_Choice2::
	.string "Check the box?\p"
	.string "$"

gText_Driver_NoResponse::
	.string "DRIVER: Up to you.\p"
	.string "It ain't goin' anywhere.\p"
	.string "$"

gText_Driver_YesResponse::
	.string "DRIVER: Go on, open it.\p"
	.string "$"

gText_MegaRing_Receive::
	.string "{PLAYER} opened the box!\p"
	.string "MEGA RING obtained!\p"
	.string "$"

gText_Selene_MegaRing::
	.string "SELENE: A Mega Ring...?\n"
	.string "That's no toy.\n"
	.string "Be careful with it.\p"
	.string "$"

gText_Driver_Arrival::
	.string "DRIVER: Littleroot ahead!\n"
	.string "End of the line.\n"
	.string "Good luck, kid!\p"
	.string "$"

gText_Truck_Stop::
	.string "The truck stops.\p"
	.string "$"

InsideOfTruck_EventScript_TruckScene::
	lockall
	msgbox gText_Truck_Intro, MSGBOX_DEFAULT
	msgbox gText_Driver_Welcome, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_TRUCK_PLAYER_RESPONSE1, 0
	setvar VAR_RESULT, 0
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_PlayerSaidYeah
	compare VAR_RESULT, 1
	goto_if_eq InsideOfTruck_EventScript_PlayerSaidNot
	end

InsideOfTruck_EventScript_PlayerSaidYeah::
	msgbox gText_Driver_YeahResponse, MSGBOX_DEFAULT
	goto InsideOfTruck_EventScript_SeleneComment
	end

InsideOfTruck_EventScript_PlayerSaidNot::
	msgbox gText_Driver_NotResponse, MSGBOX_DEFAULT
	goto InsideOfTruck_EventScript_SeleneComment
	end

InsideOfTruck_EventScript_SeleneComment::
	msgbox gText_Selene_Comment, MSGBOX_DEFAULT
	msgbox gText_Driver_BoxNotice, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_TRUCK_PLAYER_RESPONSE2, 0
	setvar VAR_RESULT, 0
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_CheckBoxYes
	compare VAR_RESULT, 1
	goto_if_eq InsideOfTruck_EventScript_CheckBoxNo
	end

InsideOfTruck_EventScript_CheckBoxYes::
	msgbox gText_Driver_YesResponse, MSGBOX_DEFAULT
	goto InsideOfTruck_EventScript_GiveMegaRing
	end

InsideOfTruck_EventScript_CheckBoxNo::
	msgbox gText_Driver_NoResponse, MSGBOX_DEFAULT
	goto InsideOfTruck_EventScript_GiveMegaRing
	end

InsideOfTruck_EventScript_GiveMegaRing::
	msgbox gText_MegaRing_Receive, MSGBOX_DEFAULT
	giveitem ITEM_MEGA_RING
	msgbox gText_Selene_MegaRing, MSGBOX_DEFAULT
	msgbox gText_Driver_Arrival, MSGBOX_DEFAULT
	msgbox gText_Truck_Stop, MSGBOX_DEFAULT
	releaseall
	end

