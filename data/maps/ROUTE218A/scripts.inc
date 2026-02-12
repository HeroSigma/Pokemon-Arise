TimelessWood_MapScripts::
    .byte 0

TimelessWood_EventScript_EntryMonologue::
    lockall
    @ Slight darkening + ambient wind as the player enters
    setweather WEATHER_SHADE
    doweather
    playse SE_M_GUST
    msgbox TimelessWood_Text_PlayerLine1, MSGBOX_DEFAULT
    msgbox TimelessWood_Text_PlayerLine2, MSGBOX_DEFAULT
    msgbox TimelessWood_Text_PlayerLine3, MSGBOX_DEFAULT
    @ Pause to look around; leaves rustle, faint whispers
    delay 20
    playse SE_M_GUST2
    delay 15
    msgbox TimelessWood_Text_PlayerLine4, MSGBOX_DEFAULT
    msgbox TimelessWood_Text_PlayerLine5, MSGBOX_DEFAULT
    setvar VAR_UNUSED_0x40DB, 1
    releaseall
    end

@ Red encounter (triggered by coord event)
TimelessWood_EventScript_RedEncounter::
    goto_if_set FLAG_UNUSED_0x027, TimelessWood_EventScript_End
    lockall
    addobject LOCALID_TIMELESS_RED
    setobjectxy LOCALID_TIMELESS_RED, 24, 12
    turnobject LOCALID_TIMELESS_RED, DIR_SOUTH
    special SpawnCameraObject
    applymovement LOCALID_CAMERA, TimelessWood_Movement_CameraPanToRed
    waitmovement 0
    msgbox TimelessWood_Text_RedLine1, MSGBOX_DEFAULT
    msgbox TimelessWood_Text_RedLine2, MSGBOX_DEFAULT
    msgbox TimelessWood_Text_RedLine3, MSGBOX_DEFAULT
    msgbox TimelessWood_Text_RedStageDirection1, MSGBOX_DEFAULT
    msgbox TimelessWood_Text_RedLine4, MSGBOX_DEFAULT
    applymovement LOCALID_TIMELESS_RED, TimelessWood_Movement_RedRight6
    waitmovement 0
    removeobject LOCALID_TIMELESS_RED
    setflag FLAG_UNUSED_0x027
    applymovement LOCALID_CAMERA, TimelessWood_Movement_CameraPanToPlayer
    waitmovement 0
    special RemoveCameraObject
    msgbox TimelessWood_Text_PlayerWhoWasThat, MSGBOX_DEFAULT
    setvar VAR_UNUSED_0x40E5, 1
    releaseall
    end

TimelessWood_Movement_RedRight6:
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    step_end

TimelessWood_Movement_CameraPanToRed:
    walk_right
    walk_right
    walk_right
    step_end

TimelessWood_Movement_CameraPanToPlayer:
    walk_left
    walk_left
    walk_left
    step_end

TimelessWood_Text_RedLine1:
    .string "{COLOR LIGHT_RED}RED: ...This place...\n"
    .string "It feels wrong.$"

TimelessWood_Text_RedLine2:
    .string "{COLOR LIGHT_RED}RED: The air... it isn't\n"
    .string "moving. Almost like time stopped.$"

TimelessWood_Text_RedLine3:
    .string "{COLOR LIGHT_RED}RED: (Have I been pulled...\n"
    .string "outside the world I know?)$"

TimelessWood_Text_RedStageDirection1:
    .string "(He narrows his eyes, steady but\n"
    .string "uncertain.)$"

TimelessWood_Text_RedLine4:
    .string "{COLOR LIGHT_RED}RED: Whatever this place is...\n"
    .string "I need to move forward.$"

TimelessWood_Text_PlayerWhoWasThat:
    .string "{PLAYER}: Who was that?$"

TimelessWood_Text_PlayerLine1:
    .string "{COLOR GREEN}{PLAYER}: ...This place feels\n"
    .string "different.$"

TimelessWood_Text_PlayerLine2:
    .string "{COLOR GREEN}{PLAYER}: The air is heavy, yet\n"
    .string "still. Almost like time itself\n"
    .string "doesn't move here.$"

TimelessWood_Text_PlayerLine3:
    .string "{COLOR GREEN}{PLAYER}: (It feels... timeless.\n"
    .string "Like a place lost between worlds.)$"

TimelessWood_Text_PlayerLine4:
    .string "{COLOR GREEN}{PLAYER}: Strange... I can't shake\n"
    .string "the feeling this forest has seen\n"
    .string "everything... and forgotten nothing.$"

TimelessWood_Text_PlayerLine5:
    .string "{COLOR GREEN}{PLAYER}: (Whatever this place is,\n"
    .string "I should tread carefully.)$"

TimelessWood_Text_PlayerLine6:
	.string "" @ unused now

TimelessWood_EventScript_End::
	end
