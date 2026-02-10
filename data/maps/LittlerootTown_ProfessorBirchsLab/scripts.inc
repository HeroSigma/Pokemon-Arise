LittlerootTown_ProfessorBirchsLab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_ProfessorBirchsLab_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_ProfessorBirchsLab_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_ProfessorBirchsLab_OnFrame
	.byte 0

	@ State descriptions for VAR_DEX_UPGRADE_JOHTO_STARTER_STATE
	@ 1: Beat Elite Four, Dex upgrade ready
	@ 2: Received National Dex
	@ 3: Left lab after receiving National Dex
	@ 4: Entered lab after catching all Hoenn mons
	@ 5: Birch told player to choose Johto starter
	@ 6: Chose Johto starter

	@ State descriptions for VAR_BIRCH_LAB_STATE
	@ 1: Never occurs
	@ 2: Chose starter
	@ 3: Received starter in lab
	@ 4: Defeated rival on Route 103
	@ 5: Received pokedex

LittlerootTown_ProfessorBirchsLab_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call ProfBirch_EventScript_UpdateLocation
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_SetAfterJohtoStarterLayout
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_CheckReadyForJohtoStarter
	end

LittlerootTown_ProfessorBirchsLab_EventScript_CheckReadyForJohtoStarter::
	specialvar VAR_RESULT, HasAllHoennMons
	goto_if_eq VAR_RESULT, TRUE, LittlerootTown_ProfessorBirchsLab_EventScript_SetReadyForJohtoStarter
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_SetRivalJohtoLayout_May
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_SetRivalJohtoLayout_Brendan
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SetRivalJohtoLayout_May::
	setobjectmovementtype LOCALID_BIRCHS_LAB_MAY, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
	setobjectxyperm LOCALID_BIRCHS_LAB_MAY, 5, 10
	return

LittlerootTown_ProfessorBirchsLab_EventScript_SetRivalJohtoLayout_Brendan::
	setobjectmovementtype LOCALID_BIRCHS_LAB_BRENDAN, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
	setobjectxyperm LOCALID_BIRCHS_LAB_BRENDAN, 5, 10
	return

LittlerootTown_ProfessorBirchsLab_EventScript_SetReadyForJohtoStarter::
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4
	goto LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout

LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout::
	setmaplayoutindex LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB_WITH_TABLE
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SetAfterJohtoStarterLayout::
	setmaplayoutindex LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB_WITH_TABLE
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_SetRivalJohtoLayout_May
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_SetRivalJohtoLayout_Brendan
	end

LittlerootTown_ProfessorBirchsLab_OnWarp:
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_SetPlayerPosForReceiveStarter
	@ After Route 103 rival battle, prepare Pokedex scene layout
	map_script_2 VAR_BIRCH_LAB_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectsForPost103
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_AddGenderedRivalObject
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AddGenderedRivalObject
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters
	.2byte 0

@ Ensure Birch and the rival are placed for the Pokedex-giving scene
LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectsForPost103::
    turnobject LOCALID_PLAYER, DIR_NORTH
    addobject LOCALID_BIRCHS_LAB_BIRCH
    addobject LOCALID_BIRCHS_LAB_BRENDAN
    addobject LOCALID_BIRCHS_LAB_MAY
    @ Birch at desk, facing player
    setobjectxy LOCALID_BIRCHS_LAB_BIRCH, 6, 4
    turnobject LOCALID_BIRCHS_LAB_BIRCH, DIR_SOUTH
    @ Brendan to Birch's left; May to Birch's right
    setobjectxy LOCALID_BIRCHS_LAB_BRENDAN, 5, 4
    turnobject LOCALID_BIRCHS_LAB_BRENDAN, DIR_SOUTH
    setobjectxy LOCALID_BIRCHS_LAB_MAY, 7, 4
    turnobject LOCALID_BIRCHS_LAB_MAY, DIR_SOUTH
    return

LittlerootTown_ProfessorBirchsLab_EventScript_SetPlayerPosForReceiveStarter::
	turnobject LOCALID_PLAYER, DIR_NORTH
	addobject LOCALID_BIRCHS_LAB_BIRCH
	addobject LOCALID_BIRCHS_LAB_SELENE
	addobject LOCALID_BIRCHS_LAB_MRS_BIRCH
	@ Place Birch at his desk and position Selene and Mrs. Birch beside him, all facing down
	setobjectxy LOCALID_BIRCHS_LAB_BIRCH, 6, 4
	setobjectxy LOCALID_BIRCHS_LAB_SELENE, 5, 4
	setobjectxy LOCALID_BIRCHS_LAB_MRS_BIRCH, 7, 4
	turnobject LOCALID_BIRCHS_LAB_BIRCH, DIR_SOUTH
	turnobject LOCALID_BIRCHS_LAB_SELENE, DIR_SOUTH
	turnobject LOCALID_BIRCHS_LAB_MRS_BIRCH, DIR_SOUTH
	@ Do not autoplay the debrief; let the player talk to Birch to begin
	return

// Post-rescue lab debrief with Selene and Mrs. Birch present
LittlerootTown_ProfessorBirchsLab_EventScript_PostRescueDebrief::
    lockall
    msgbox LittlerootTown_ProfessorBirchsLab_Text_ZoroarkUnseen, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_SeleneIntervene, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_MrsBirchTroubling, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_FieldworkStart, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_BondUnderFire, MSGBOX_DEFAULT
    // Offer nickname for the rescued starter
    msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_NicknameRescueStarter
    msgbox LittlerootTown_ProfessorBirchsLab_Text_HeadTo103, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_SeleneCare, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_MrsBirchDinner, MSGBOX_DEFAULT
	// Selene and Mrs. Birch walk off and leave (to the south door)
	applymovement LOCALID_BIRCHS_LAB_SELENE, LittlerootTown_ProfessorBirchsLab_Movement_SeleneLeave
	applymovement LOCALID_BIRCHS_LAB_MRS_BIRCH, LittlerootTown_ProfessorBirchsLab_Movement_MrsBirchLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_BIRCHS_LAB_SELENE
	removeobject LOCALID_BIRCHS_LAB_MRS_BIRCH
	msgbox LittlerootTown_ProfessorBirchsLab_Text_PlayerResolve, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_RightThen103, MSGBOX_DEFAULT
    // Send player to meet rival at Route 103
    setvar VAR_BIRCH_LAB_STATE, 3
    releaseall
    return

// Small talk text
LittlerootTown_ProfessorBirchsLab_Text_SeleneAreYouOk:
    .string "SELENE: We heard what happened out there.\p"
    .string "Are you alright?$"

LittlerootTown_ProfessorBirchsLab_Text_MrsBirchHeard:
	.string "MRS. BIRCH: Dear, we heard about\n"
	.string "the incident.\p"
	.string "Are you holding up okay?$"

LittlerootTown_ProfessorBirchsLab_Text_PlayerImFine:
    .string "{COLOR GREEN}{PLAYER}: I’m fine. Just a bit shaken,\n"
    .string "but I’ll manage.{COLOR DARK_GRAY}$"

// Optional small-talk handlers if spoken to before Birch
LittlerootTown_ProfessorBirchsLab_EventScript_SeleneSmallTalk::
    lock
    faceplayer
    goto_if_eq VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_SeleneSmallTalk_Ok
    msgbox LittlerootTown_ProfessorBirchsLab_Text_SeleneCare, MSGBOX_DEFAULT
    release
    end

LittlerootTown_ProfessorBirchsLab_EventScript_SeleneSmallTalk_Ok:
    msgbox LittlerootTown_ProfessorBirchsLab_Text_SeleneAreYouOk, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_PlayerImFine, MSGBOX_DEFAULT
    release
    end

LittlerootTown_ProfessorBirchsLab_EventScript_MrsBirchSmallTalk::
    lock
    faceplayer
    goto_if_eq VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_MrsBirchSmallTalk_Ok
    msgbox LittlerootTown_ProfessorBirchsLab_Text_MrsBirchDinner, MSGBOX_DEFAULT
    release
    end

LittlerootTown_ProfessorBirchsLab_EventScript_MrsBirchSmallTalk_Ok:
    msgbox LittlerootTown_ProfessorBirchsLab_Text_MrsBirchHeard, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_PlayerImFine, MSGBOX_DEFAULT
    release
    end

// Nickname flow for the rescued starter (same as party nicknaming)
LittlerootTown_ProfessorBirchsLab_EventScript_NicknameRescueStarter::
    setvar VAR_0x8004, 0
    call Common_EventScript_NameReceivedPartyMon
    msgbox LittlerootTown_ProfessorBirchsLab_Text_HeadTo103, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_SeleneCare, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_MrsBirchDinner, MSGBOX_DEFAULT
    // Selene and Mrs. Birch walk off and leave (to the south door)
    applymovement LOCALID_BIRCHS_LAB_SELENE, LittlerootTown_ProfessorBirchsLab_Movement_SeleneLeave
    applymovement LOCALID_BIRCHS_LAB_MRS_BIRCH, LittlerootTown_ProfessorBirchsLab_Movement_MrsBirchLeave
    waitmovement 0
    playse SE_EXIT
    removeobject LOCALID_BIRCHS_LAB_SELENE
    removeobject LOCALID_BIRCHS_LAB_MRS_BIRCH
    msgbox LittlerootTown_ProfessorBirchsLab_Text_PlayerResolve, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_RightThen103, MSGBOX_DEFAULT
    setvar VAR_BIRCH_LAB_STATE, 3
    releaseall
    return
@ Exit movements toward the actual south door tiles (6,12) and (7,12)
LittlerootTown_ProfessorBirchsLab_Movement_SeleneLeave:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	set_invisible
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_MrsBirchLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	set_invisible
	step_end


LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade::
	turnobject LOCALID_PLAYER, DIR_NORTH
	addobject LOCALID_BIRCHS_LAB_BIRCH
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_AddMayAtFiveFiveFacingNorth
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_AddBrendanAtFiveFiveFacingNorth
	turnobject LOCALID_BIRCHS_LAB_BIRCH, DIR_SOUTH
	setobjectxy LOCALID_BIRCHS_LAB_BIRCH, 6, 4
	turnobject LOCALID_BIRCHS_LAB_AIDE, DIR_EAST
	setobjectxy LOCALID_BIRCHS_LAB_AIDE, 10, 10
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AddMayAtFiveFiveFacingNorth::
	addobject LOCALID_BIRCHS_LAB_MAY
	turnobject LOCALID_BIRCHS_LAB_MAY, DIR_NORTH
	setobjectxy LOCALID_BIRCHS_LAB_MAY, 5, 5
	return

LittlerootTown_ProfessorBirchsLab_EventScript_AddBrendanAtFiveFiveFacingNorth::
	addobject LOCALID_BIRCHS_LAB_BRENDAN
	turnobject LOCALID_BIRCHS_LAB_BRENDAN, DIR_NORTH
	setobjectxy LOCALID_BIRCHS_LAB_BRENDAN, 5, 5
	return

LittlerootTown_ProfessorBirchsLab_EventScript_AddGenderedRivalObject::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_AddMay
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_AddBrendan
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AddMay::
	addobject LOCALID_BIRCHS_LAB_MAY
	return

LittlerootTown_ProfessorBirchsLab_EventScript_AddBrendan::
	addobject LOCALID_BIRCHS_LAB_BRENDAN
	return

LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters::
	addobject LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL
	addobject LOCALID_BIRCHS_LAB_TOTODILE_BALL
	addobject LOCALID_BIRCHS_LAB_CHIKORITA_BALL
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_AddMayAtFiveFiveFacingEast
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_AddBrendanAtFiveFiveFacingEast
	turnobject LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL, DIR_SOUTH
	setobjectxy LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL, 8, 4
	turnobject LOCALID_BIRCHS_LAB_TOTODILE_BALL, DIR_SOUTH
	setobjectxy LOCALID_BIRCHS_LAB_TOTODILE_BALL, 9, 4
	turnobject LOCALID_BIRCHS_LAB_CHIKORITA_BALL, DIR_SOUTH
	setobjectxy LOCALID_BIRCHS_LAB_CHIKORITA_BALL, 10, 4
	turnobject LOCALID_BIRCHS_LAB_BIRCH, DIR_SOUTH
	setobjectxy LOCALID_BIRCHS_LAB_BIRCH, 6, 4
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AddMayAtFiveFiveFacingEast::
	addobject LOCALID_BIRCHS_LAB_MAY
	turnobject LOCALID_BIRCHS_LAB_MAY, DIR_EAST
	setobjectxy LOCALID_BIRCHS_LAB_MAY, 5, 5
	return

LittlerootTown_ProfessorBirchsLab_EventScript_AddBrendanAtFiveFiveFacingEast::
	addobject LOCALID_BIRCHS_LAB_BRENDAN
	turnobject LOCALID_BIRCHS_LAB_BRENDAN, DIR_EAST
	setobjectxy LOCALID_BIRCHS_LAB_BRENDAN, 5, 5
	return

LittlerootTown_ProfessorBirchsLab_OnFrame:
	map_script_2 VAR_BIRCH_LAB_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedexEvent
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_ProfessorBirchsLab_EventScript_UpgradeToNationalDex
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_ChooseJohtoStarter
	.2byte 0

@ The starter is technically given prior to this on Route 101 by special ChooseStarter
@ This is just where the game tells you its yours and lets you nickname it
LittlerootTown_ProfessorBirchsLab_EventScript_GiveStarterEvent::
	lockall
	bufferleadmonspeciesname STR_VAR_1
	message LittlerootTown_ProfessorBirchsLab_Text_LikeYouToHavePokemon
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
    msgbox LittlerootTown_ProfessorBirchsLab_Text_WhyNotGiveNicknameToMon, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_NicknameStarter
    goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival
    end

LittlerootTown_ProfessorBirchsLab_EventScript_NicknameStarter::
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MightBeGoodIdeaToGoSeeRival, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GetRivalToTeachYou, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_ROUTE_101_BOY
	setvar VAR_BIRCH_LAB_STATE, 3
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DontBeThatWay, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedexEvent::
    lockall
    applymovement LOCALID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForPokedex
    waitmovement 0
    goto LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedex
    end

LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForPokedex:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_UpgradeToNationalDex::
	lockall
	delay 30
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OtherRegionsUpgradeToNational, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCHS_LAB_BIRCH, LittlerootTown_ProfessorBirchsLab_Movement_BirchRetrievePokedexes
	waitmovement 0
	delay 20
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 20
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayShiftRight
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanShiftRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayUpgradeComment
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanUpgradeComment
	playse SE_PC_ON
	waitse
	delay 20
	applymovement LOCALID_BIRCHS_LAB_BIRCH, LittlerootTown_ProfessorBirchsLab_Movement_BirchReturnPokedex
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayShiftUp
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanShiftUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OkayAllDone, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_Text_PokedexUpgradedToNational
	waitmessage
	waitfanfare
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2
	setvar VAR_SCOTT_BF_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_BATTLE_FRONTIER
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayUpgradeComment::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayUpgradeSoCool, MSGBOX_DEFAULT
	closemessage
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanUpgradeComment::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanYouCanThankMe, MSGBOX_DEFAULT
	closemessage
	return

@ Small helpers to move the correct rival during National Dex upgrade
LittlerootTown_ProfessorBirchsLab_EventScript_MayShiftRight::
	applymovement LOCALID_BIRCHS_LAB_MAY, Common_Movement_WalkInPlaceFasterRight
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanShiftRight::
	applymovement LOCALID_BIRCHS_LAB_BRENDAN, Common_Movement_WalkInPlaceFasterRight
	return

LittlerootTown_ProfessorBirchsLab_EventScript_MayShiftUp::
	applymovement LOCALID_BIRCHS_LAB_MAY, Common_Movement_WalkInPlaceFasterUp
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanShiftUp::
	applymovement LOCALID_BIRCHS_LAB_BRENDAN, Common_Movement_WalkInPlaceFasterUp
	return

LittlerootTown_ProfessorBirchsLab_Movement_BirchRetrievePokedexes:
	walk_left
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_right
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_BirchReturnPokedex:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_in_place_faster_down
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_ChooseJohtoStarter::
	lockall
	applymovement LOCALID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForJohtoStarter
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CompletedDexChoosePokemon, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForJohtoStarter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_Aide::
	lock
	faceplayer
	goto_if_ge VAR_BIRCH_LAB_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_AideReceivedStarter
	goto_if_set FLAG_BIRCH_AIDE_MET, LittlerootTown_ProfessorBirchsLab_EventScript_AideAlreadyMet
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchAwayOnFieldwork, MSGBOX_DEFAULT
	setflag FLAG_BIRCH_AIDE_MET
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AideAlreadyMet::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchIsntOneForDeskWork, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AideReceivedStarter::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchEnjoysRivalsHelpToo, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Cyndaquil::
	release
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	showmonpic SPECIES_CYNDAQUIL, 10, 3
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeCyndaquil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveCyndaquil
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Totodile::
	release
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	showmonpic SPECIES_TOTODILE, 10, 3
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeTotodile, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveTotodile
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Chikorita::
	release
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	showmonpic SPECIES_CHIKORITA, 10, 3
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeChikorita, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveChikorita
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BetterLeaveOthersAlone, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime::
	hidemonpic
	msgbox LittlerootTown_ProfessorBirchsLab_Text_TakeYourTimeAllInvaluable, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GiveCyndaquil::
	bufferspeciesname STR_VAR_1, SPECIES_CYNDAQUIL
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CYNDAQUIL
	givemon SPECIES_CYNDAQUIL, 5
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToPC
	hidemonpic
	goto Common_EventScript_NoMoreRoomForPokemon
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToParty::
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToPC::
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC
	end

LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil::
	hidemonpic
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GiveTotodile::
	bufferspeciesname STR_VAR_1, SPECIES_TOTODILE
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TOTODILE
	givemon SPECIES_TOTODILE, 5
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToPC
	hidemonpic
	goto Common_EventScript_NoMoreRoomForPokemon
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToParty::
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BIRCHS_LAB_TOTODILE_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToPC::
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BIRCHS_LAB_TOTODILE_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC
	end

LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile::
	hidemonpic
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GiveChikorita::
	bufferspeciesname STR_VAR_1, SPECIES_CHIKORITA
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CHIKORITA
	givemon SPECIES_CHIKORITA, 5
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToPC
	hidemonpic
	goto Common_EventScript_NoMoreRoomForPokemon
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToParty::
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BIRCHS_LAB_CHIKORITA_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToPC::
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BIRCHS_LAB_CHIKORITA_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita::
	hidemonpic
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter::
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_Text_ReceivedJohtoStarter
	waitmessage
	waitfanfare
	return

LittlerootTown_ProfessorBirchsLab_EventScript_Birch::
	lock
	faceplayer
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_CanHaveAnyOneOfRarePokemon
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_GrassyPatchWaiting
	goto_if_eq VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_PostRescueDebrief
	goto_if_eq VAR_BIRCH_LAB_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_RemindRoute103
	goto_if_unset FLAG_HAS_MATCH_CALL, LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister
	goto_if_unset FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, EventScript_RegisterProfBirch
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister
	end

LittlerootTown_ProfessorBirchsLab_EventScript_RemindRoute103::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_RightThen103, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_CanHaveAnyOneOfRarePokemon::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CanHaveAnyOneOfRarePokemon, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GrassyPatchWaiting::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister::
	goto_if_unset FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380, ProfBirch_EventScript_RatePokedexOrRegister
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, ProfBirch_EventScript_RatePokedexOrRegister
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, ProfBirch_EventScript_RatePokedexOrRegister
	goto_if_eq VAR_BIRCH_LAB_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_PokemonAwait
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchRivalGoneHome, MSGBOX_DEFAULT
	release
	end

EventScript_RegisterProfBirch::
	msgbox MatchCall_Text_BirchRegisterCall, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MatchCall_Text_RegisteredBirch, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
	setvar VAR_REGISTER_BIRCH_STATE, 2
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedex::
    @ New post-Route 103 scene: Birch, Brendan, and May together
    msgbox LittlerootTown_ProfessorBirchsLab_Text_Post103_AllHere, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_Brendan_Sharper, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_May_PushedThrough, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_Birch_ImpressiveBond, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_Player_OldaleTwoMen, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_Birch_Thoughts1, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_Birch_Thoughts2, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_Birch_Threat, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_Birch_NatDex, MSGBOX_DEFAULT
    call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex
    closemessage
    @ May gives Poke Balls
    msgbox LittlerootTown_ProfessorBirchsLab_Text_May_GiveBalls, MSGBOX_DEFAULT
    giveitem ITEM_POKE_BALL, 5
    call_if_eq VAR_RESULT, FALSE, LittlerootTown_ProfessorBirchsLab_EventScript_MayNoRoomForPokeBalls
    @ Brendan gives EXP Share
    msgbox LittlerootTown_ProfessorBirchsLab_Text_Brendan_GiveExpShare, MSGBOX_DEFAULT
    giveitem ITEM_EXP_SHARE, 1
    call_if_eq VAR_RESULT, FALSE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanNoRoomForPokeBalls
    @ Rivals parting words and exit
    msgbox LittlerootTown_ProfessorBirchsLab_Text_Rivals_TryToKeepUp, MSGBOX_DEFAULT
    applymovement LOCALID_BIRCHS_LAB_MAY, LittlerootTown_ProfessorBirchsLab_Movement_MayLeave
    applymovement LOCALID_BIRCHS_LAB_BRENDAN, LittlerootTown_ProfessorBirchsLab_Movement_BrendanLeave
    waitmovement 0
    removeobject LOCALID_BIRCHS_LAB_MAY
    removeobject LOCALID_BIRCHS_LAB_BRENDAN
    msgbox LittlerootTown_ProfessorBirchsLab_Text_Birch_StaySharp, MSGBOX_DEFAULT
    msgbox LittlerootTown_ProfessorBirchsLab_Text_Player_IntroMonologue, MSGBOX_DEFAULT
    setvar VAR_BIRCH_LAB_STATE, 5
    setflag FLAG_ADVENTURE_STARTED
    setvar VAR_OLDALE_TOWN_STATE, 1
    @ Ensure the Oldale rival disappears after this scene
    setvar VAR_OLDALE_RIVAL_STATE, 2
    setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
    setvar VAR_LITTLEROOT_RIVAL_STATE, 4
    setvar VAR_LITTLEROOT_TOWN_STATE, 3
    @ Hide Brendan/May by flag so they won't auto-spawn
    setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
    releaseall
    end

LittlerootTown_ProfessorBirchsLab_EventScript_MayGivePokeBalls::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_RivalGiveBalls, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	call_if_eq VAR_RESULT, FALSE, LittlerootTown_ProfessorBirchsLab_EventScript_MayNoRoomForPokeBalls
	msgbox LittlerootTown_ProfessorBirchsLab_Text_PlayerThanksForBalls, MSGBOX_DEFAULT
	setvar VAR_RESULT, 0
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanGivePokeBalls::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_RivalGiveBalls, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	call_if_eq VAR_RESULT, FALSE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanNoRoomForPokeBalls
	msgbox LittlerootTown_ProfessorBirchsLab_Text_PlayerThanksForBalls, MSGBOX_DEFAULT
	setvar VAR_RESULT, 1
	return

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex::
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokedex
	waitfanfare
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	setflag FLAG_SYS_DEXNAV
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 1
	return

LittlerootTown_ProfessorBirchsLab_EventScript_PokemonAwait::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CountlessPokemonAwait, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayNoRoomForPokeBalls::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OhYourBagsFull, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanNoRoomForPokeBalls::
    msgbox LittlerootTown_ProfessorBirchsLab_Text_HeyYourBagsFull, MSGBOX_DEFAULT
    return

LittlerootTown_ProfessorBirchsLab_Movement_RivalApproachPlayer:
    walk_down
    walk_in_place_faster_right
    step_end

@ Rivals exit movements (toward south door, then disappear)
LittlerootTown_ProfessorBirchsLab_Movement_MayLeave:
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    set_invisible
    step_end

LittlerootTown_ProfessorBirchsLab_Movement_BrendanLeave:
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    set_invisible
    step_end

@ New dialogue for the post-103 group scene
LittlerootTown_ProfessorBirchsLab_Text_Post103_AllHere:
	.string "{COLOR BLUE}PROF. BIRCH: Good, you're all here.\n"
	.string "How did your battles go?{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_Brendan_Sharper:
	.string "{COLOR LIGHT_RED}BRENDAN: {PLAYER} is sharper than\n"
	.string "I expected.\p"
	.string "Whatever happened out there,\n"
	.string "they're not holding back.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_May_PushedThrough:
	.string "{COLOR LIGHT_RED}MAY: Yeah. Even with us both\n"
	.string "battling, they pushed through.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_Birch_ImpressiveBond:
	.string "{COLOR BLUE}PROF. BIRCH: Impressive. That bond\n"
	.string "with your partners is essential.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_Player_OldaleTwoMen:
	.string "{COLOR GREEN}{PLAYER}: There were two men…\n"
	.string "They talked about HOENN being off.\p"
	.string "It felt like something was wrong.\n"
	.string "They seemed familiar.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_Birch_Thoughts1:
	.string "{COLOR BLUE}PROF. BIRCH: (Those descriptions…\n"
	.string "they sound like…){COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_Birch_Thoughts2:
	.string "{COLOR BLUE}PROF. BIRCH: (No, it can't be…\n"
	.string "GIOVANNI and CYRUS?){COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_Birch_Threat:
	.string "{COLOR BLUE}PROF. BIRCH: For now, don't dwell on it.\p"
	.string "But if people like that are in\n"
	.string "HOENN, we face a grave threat.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_Birch_NatDex:
	.string "{COLOR BLUE}PROF. BIRCH: Here. The POKéDEX--now\n"
	.string "covers all regions.\p"
	.string "You three will need it.\n"
	.string "Consider it the NATIONAL DEX.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_May_GiveBalls:
	.string "{COLOR LIGHT_RED}MAY: Here, {PLAYER}.\n"
	.string "Take these too.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_Brendan_GiveExpShare:
	.string "{COLOR LIGHT_RED}BRENDAN: And this is from me.\p"
	.string "It'll help your team stay balanced.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_Rivals_TryToKeepUp:
	.string "{COLOR LIGHT_RED}MAY & BRENDAN: Try to keep up\n"
	.string "this time, will you?{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_Birch_StaySharp:
	.string "{COLOR BLUE}PROF. BIRCH: Excellent. You're ready\n"
	.string "for the road ahead.\p"
	.string "But we still don't understand\n"
	.string "that ZOROARK, or those men in OLDALE.\p"
	.string "Stay sharp.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_Player_IntroMonologue:
	.string "{COLOR GREEN}{PLAYER}: (All three starters, both\n"
	.string "rivals by my side, and threats\n"
	.string "already stirring in HOENN…\p"
	.string "This journey is only just beginning.){COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_EventScript_Machine::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Rival::
	lock
	faceplayer
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_RivalFuturePlans
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_RivalHaveYouGoneToBattleFrontier
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_RivalTakeBreakFromFieldwork
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayWhereShouldIGoNext
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanWhereShouldIGoNext
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayWhereShouldIGoNext::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayWhereShouldIGoNext, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanWhereShouldIGoNext::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanWhereShouldIGoNext, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_RivalFuturePlans::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayWhatNextImStayingHere
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanPreferCollectingSlowly
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayWhatNextImStayingHere::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayWhatNextImStayingHere, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanPreferCollectingSlowly:
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanPreferCollectingSlowly, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_RivalHaveYouGoneToBattleFrontier::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayHaveYouGoneToBattleFrontier
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanHaveYouGoneToBattleFrontier
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayHaveYouGoneToBattleFrontier::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayHaveYouGoneToBattleFrontier, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanHaveYouGoneToBattleFrontier::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanHaveYouGoneToBattleFrontier, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_RivalTakeBreakFromFieldwork::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayTakeBreakFromFieldwork
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanTakeBreakFromFieldwork
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayTakeBreakFromFieldwork::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayTakeBreakFromFieldwork, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanTakeBreakFromFieldwork::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanTakeBreakFromFieldwork, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_PC::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Bookshelf::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Book::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BookTooHardToRead, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ScottAboardSSTidalCall::
	lockall
	pokenavcall LittlerootTown_ProfessorBirchsLab_Text_ScottAboardSSTidalCall
	waitmessage
	clearflag FLAG_SCOTT_CALL_BATTLE_FRONTIER
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_Text_BirchAwayOnFieldwork:
	.string "Hunh? PROF. BIRCH?\p"
	.string "The PROF's away on\n"
	.string "fieldwork. Ergo, he\n"
	.string "isn't here.\p"
	.string "Let me explain what\n"
	.string "fieldwork is.\p"
	.string "It's to study things\n"
	.string "in the natural\n"
	.string "environment, like\n"
	.string "fields and mountains,\n"
	.string "instead of a lab.\p"
	.string "The PROF isn't one\n"
	.string "for desk work. He's\n"
	.string "the type who'd rather\n"
	.string "go outside and\n"
	.string "experience things\n"
	.string "than read about them\n"
	.string "here.$"

LittlerootTown_ProfessorBirchsLab_Text_BirchIsntOneForDeskWork:
	.string "The PROF isn't one for doing desk work.\n"
	.string "He's the type of person who would\l"
	.string "rather go outside and experience\l"
	.string "things than read about them here.$"

LittlerootTown_ProfessorBirchsLab_Text_BirchEnjoysRivalsHelpToo:
	.string "PROF. BIRCH is studying the habitats\n"
	.string "and distribution of POKéMON.\p"
	.string "The PROF enjoys {RIVAL}'s help, too.\n"
	.string "There's a lot of love there.$"

LittlerootTown_ProfessorBirchsLab_Text_LikeYouToHavePokemon:
	.string "PROF. BIRCH: Great work back there, {PLAYER}.\p"
	.string "PROF. BIRCH: Before we go on… how is\n"
	.string "your father?\p"
	.string "PLAYER: He's still at home on the\n"
	.string "ARCHIPELAGO.\p"
	.string "PROF. BIRCH: I see. I'm glad you're safe.\p"
	.string "PROF. BIRCH: My team was on ROUTE 102\n"
	.string "earlier.\p"
	.string "PROF. BIRCH: A new area opened up.\n"
	.string "It's strange.\p"
	.string "PROF. BIRCH: Feels like time is standing\n"
	.string "still there.\p"
	.string "PROF. BIRCH: There's a rift nearby, but\n"
	.string "we don't know the source.\p"
	.string "PROF. BIRCH: Now, about the POKéMON\n"
	.string "you used.\p"
	.string "PROF. BIRCH: You can keep it.\p"
	.string "{PLAYER} received the {STR_VAR_1}!$"

LittlerootTown_ProfessorBirchsLab_Text_WhyNotGiveNicknameToMon:
	.string "PROF. BIRCH: Want to give it a\n"
	.string "nickname?$"

LittlerootTown_ProfessorBirchsLab_Text_MightBeGoodIdeaToGoSeeRival:
	.string "PROF. BIRCH: Good. Next, head to ROUTE 103.\p"
	.string "PROF. BIRCH: {RIVAL} is there checking\n"
	.string "statics.\p"
	.string "PROF. BIRCH: Call them for me and bring\n"
	.string "back what they found.$"

LittlerootTown_ProfessorBirchsLab_Text_GetRivalToTeachYou:
	.string "PROF. BIRCH: Okay.$"

LittlerootTown_ProfessorBirchsLab_Text_DontBeThatWay:
	.string "PROF. BIRCH: Oh, don't be that way.\n"
	.string "You should go meet my kid.$"

LittlerootTown_ProfessorBirchsLab_Text_BirchRivalGoneHome:
	.string "PROF. BIRCH: {RIVAL}?\n"
	.string "Gone home, I think.\p"
	.string "Or maybe that kid's scrabbling around\n"
	.string "in tall grass again somewhere…\p"
	.string "If you or your POKéMON get tired,\n"
	.string "you should get some rest at home.$"

LittlerootTown_ProfessorBirchsLab_Text_Post103Intro:
	.string "BIRCH: Good, you're all here. Tell me-\n"
	.string "how did the battles go?\p"
	.string "BRENDAN: {PLAYER} is sharper than I expected.\n"
	.string "Whatever happened out there, they're not holding back.\p"
	.string "MAY: Yeah. Even with us fighting one after the other,\n"
	.string "they pushed through.\p"
	.string "BIRCH: Impressive. That bond with your partners\n"
	.string "will be essential.\p"
	.string "{PLAYER}: There were two men in OLDALE… talking about\n"
	.string "HOENN being off, like something was wrong.\n"
	.string "I couldn't shake it-they felt familiar.\p"
	.string "BIRCH: (Those descriptions… they sound like…\n"
	.string "no, it can't be… GIOVANNI and CYRUS?)\p"
	.string "BIRCH: (If true, this is dangerous. I need to alert\n"
	.string "the ARCANUM.)\p"
	.string "BIRCH: For now, don't dwell on it. But know this-\n"
	.string "if figures like that are in HOENN, we face a grave threat.$"

// New debrief scene text (post Route 101)
LittlerootTown_ProfessorBirchsLab_Text_ZoroarkUnseen:
	.string "{COLOR BLUE}BIRCH: That POKéMON we saw… it looked like a\n"
	.string "ZOROARK, but at the same time, it didn’t.\p"
	.string "BIRCH: ZOROARK isn’t even found in HOENN, and\n"
	.string "I’ve never seen a form like that in any record.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_SeleneIntervene:
	.string "{COLOR BLUE}SELENE: Whatever it was, it nearly overwhelmed\n"
	.string "you. If not for… whatever intervened, we\l"
	.string "wouldn’t be standing here.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_MrsBirchTroubling:
	.string "{COLOR BLUE}MRS. BIRCH: I've lived here my\n"
	.string "whole life, and I've never seen\p"
	.string "anything like that before.\n"
	.string "This is troubling, Professor.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_FieldworkStart:
	.string "{COLOR BLUE}BIRCH: Troubling, yes- but also important.\n"
	.string "We need to understand what’s happening.\p"
	.string "BIRCH: For that, {PLAYER}, I want you to begin\n"
	.string "fieldwork right away.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_BondUnderFire:
	.string "{COLOR BLUE}BIRCH: You already chose a partner out there,\n"
	.string "under fire. That bond is yours now.\p"
    .string "But theory won’t help us- we need practice.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_HeadTo103:
	.string "{COLOR BLUE}BIRCH: Head north to ROUTE 103. {RIVAL} should\n"
	.string "be waiting there.\p"
	.string "Battle them, explain what happened, and then\n"
	.string "come straight back here.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_SeleneCare:
    .string "{COLOR BLUE}SELENE: Be careful, {PLAYER}. Remember- you don’t\n"
 	.string "have to shoulder this alone.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_MrsBirchDinner:
	.string "{COLOR BLUE}MRS. BIRCH: And tell {RIVAL} I'll\n"
	.string "have dinner ready if they're late\n"
	.string "home again.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_PlayerResolve:
	.string "{COLOR GREEN}{PLAYER}: (That Zoroark… or whatever it was…\n"
	.string "I can still feel its presence.\p"
	.string "Maybe battling {RIVAL} will help me steady\n"
	.string "myself.){COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_RightThen103:
	.string "{COLOR BLUE}BIRCH: Right then. ROUTE 103. Don’t delay,\n"
	.string "{PLAYER}.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokedex:
	.string "{PLAYER} received the POKéDEX!$"

LittlerootTown_ProfessorBirchsLab_Text_ExplainPokedex:
	.string "{COLOR BLUE}PROF. BIRCH: This is the POKéDEX.\p"
	.string "It records data on POKéMON you meet.{COLOR DARK_GRAY}\p"
	.string "{COLOR GREEN}PLAYER: I'll make good use of it.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_CountlessPokemonAwait:
	.string "{COLOR BLUE}PROF. BIRCH: Countless POKéMON\n"
	.string "await you!\p"
	.string "Argh, I'm getting the itch to get out\n"
	.string "and do fieldwork again!{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_RivalGiveBalls:
	.string "{COLOR LIGHT_RED}{RIVAL}: Here - take these POKé BALLS.\p"
	.string "{RIVAL}: They said to pass them along.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_PlayerThanksForBalls:
	.string "{COLOR GREEN}PLAYER: Thanks. I'll put them to work.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_OhYourBagsFull:
	.string "Oh? Your BAG's full.$"

LittlerootTown_ProfessorBirchsLab_Text_MayWhereShouldIGoNext:
	.string "{COLOR LIGHT_RED}MAY: I wonder where I should go look\n"
	.string "for POKéMON next?{COLOR DARK_GRAY}$"

@ (unused - replaced by LittlerootTown_ProfessorBirchsLab_Text_RivalGiveBalls)
LittlerootTown_ProfessorBirchsLab_Text_BrendanGotPokedexTooTakeThese:
	.string "$"

@ (unused - replaced by LittlerootTown_ProfessorBirchsLab_Text_PlayerThanksForBalls)
LittlerootTown_ProfessorBirchsLab_Text_CatchCoolPokemonWithPokeBalls:
	.string "$"

@ New post-Route103 briefing
LittlerootTown_ProfessorBirchsLab_Text_Route102Briefing:
	.string "PROF. BIRCH: About that new area on\n"
	.string "ROUTE 102.\p"
	.string "PROF. BIRCH: It's odd. Time feels still\n"
	.string "there.\p"
	.string "PROF. BIRCH: There's a rift nearby.\n"
	.string "Source unknown.\p"
	.string "PLAYER: ...\p"
	.string "PROF. BIRCH: If you're going to scout it,\n"
	.string "be careful.\p"
	.string "PROF. BIRCH: I added a statics profile\n"
	.string "to your DEXNAV.\p"
	.string "PROF. BIRCH: Keep it on while you travel.\p"
	.string "PLAYER: Got it. I'll be careful.$"


LittlerootTown_ProfessorBirchsLab_Text_RivalLeave:
	.string "{RIVAL}: I'm heading after them.\p"
	.string "{RIVAL}: We'll meet again - count on it.\p"
	.string "PLAYER: See you out there.$"

LittlerootTown_ProfessorBirchsLab_Text_NextSteps:
	.string "{COLOR BLUE}PROF. BIRCH: Next, check ROUTE 102.{COLOR DARK_GRAY}\p"
	.string "{COLOR BLUE}PROF. BIRCH: Push past OLDALE when\n"
	.string "you're ready.{COLOR DARK_GRAY}\p"
	.string "{COLOR BLUE}PROF. BIRCH: Tell your mother before\n"
	.string "you go.{COLOR DARK_GRAY}\p"
	.string "{COLOR GREEN}PLAYER: I will. Thanks, Professor.{COLOR DARK_GRAY}\p"
	.string "{COLOR BLUE}PROF. BIRCH: Be careful out there.{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_HeyYourBagsFull:
	.string "Hey, your BAG's full.$"

LittlerootTown_ProfessorBirchsLab_Text_BrendanWhereShouldIGoNext:
	.string "{COLOR LIGHT_RED}BRENDAN: Where should I look for\n"
	.string "POKéMON next…{COLOR DARK_GRAY}$"

LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine:
	.string "It's a serious-looking machine.\n"
	.string "The PROF must use this for research.$"

LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch:
	.string "It's a PC used for research.\n"
	.string "Better not mess around with it.$"

LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon:
	.string "It's crammed with books on POKéMON.$"

LittlerootTown_ProfessorBirchsLab_Text_BookTooHardToRead:
	.string "It's a book that's too hard to read.$"

LittlerootTown_ProfessorBirchsLab_Text_OtherRegionsUpgradeToNational:
	.string "PROF. BIRCH: Now…\p"
	.string "{PLAYER}{KUN} and {RIVAL}, I've had the two\n"
	.string "of you help me study POKéMON.\p"
	.string "Thanks to your help, new facts\n"
	.string "are coming to light.\p"
	.string "It appears that in the HOENN region,\n"
	.string "there are also POKéMON from other\l"
	.string "regions.\p"
	.string "It goes to show how rich and varied\n"
	.string "the natural environments of HOENN\l"
	.string "happen to be.\p"
	.string "That's why I think it's necessary for\n"
	.string "me to upgrade your POKéDEX to\l"
	.string "the NATIONAL Mode.\p"
	.string "Here, let me see your POKéDEX units.$"

LittlerootTown_ProfessorBirchsLab_Text_MayUpgradeSoCool:
	.string "MAY: Eheheh!\p"
	.string "It's so cool that even my POKéDEX\n"
	.string "is getting updated!\p"
	.string "It's because you went out and caught\n"
	.string "so many POKéMON, {PLAYER}{KUN}!$"

LittlerootTown_ProfessorBirchsLab_Text_BrendanYouCanThankMe:
	.string "BRENDAN: I went out all over HOENN\n"
	.string "and checked out POKéMON.\p"
	.string "You can thank me for getting\n"
	.string "the NATIONAL Mode POKéDEX.\p"
	.string "Yep, you're lucky, {PLAYER}!$"

LittlerootTown_ProfessorBirchsLab_Text_OkayAllDone:
	.string "PROF. BIRCH: Okay, all done!$"

LittlerootTown_ProfessorBirchsLab_Text_PokedexUpgradedToNational:
	.string "{PLAYER}'s POKéDEX was upgraded\n"
	.string "to the NATIONAL Mode!$"

LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2:
	.string "PROF. BIRCH: But listen.\n"
	.string "You've become the CHAMPION,\l"
	.string "but your POKéMON journey isn't over.\p"
	.string "There is no end to the road\n"
	.string "that is POKéMON.\p"
	.string "Somewhere, there is a grassy patch\n"
	.string "that's waiting for you!$"

LittlerootTown_ProfessorBirchsLab_Text_MayTakeBreakFromFieldwork:
	.string "MAY: I think I'll take a short break\n"
	.string "from fieldwork.\p"
	.string "I think I'll help the PROF here for\n"
	.string "a while.$"

LittlerootTown_ProfessorBirchsLab_Text_BrendanTakeBreakFromFieldwork:
	.string "BRENDAN: For the time being,\n"
	.string "I'm taking a break from fieldwork.\p"
	.string "I'll be helping out the PROF here\n"
	.string "for a while.$"

LittlerootTown_ProfessorBirchsLab_Text_CompletedDexChoosePokemon:
	.string "PROF. BIRCH: Oh, {PLAYER}{KUN}!\n"
	.string "Let's have a look at your POKéDEX.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Yes, there's no doubt about it.\p"
	.string "You really have completed the HOENN\n"
	.string "region's POKéDEX.\p"
	.string "That's more than just impressive.\p"
	.string "I have a gift for you.\p"
	.string "Consider it my show of appreciation\n"
	.string "for the fantastic work you've done.\p"
	.string "My gift is a rare POKéMON only found\n"
	.string "in another region!\p"
	.string "You can have any one of these\n"
	.string "three POKéMON!$"

LittlerootTown_ProfessorBirchsLab_Text_CanHaveAnyOneOfRarePokemon:
	.string "PROF. BIRCH: These are rare POKéMON\n"
	.string "only found in another region!\p"
	.string "You can have any one of these\n"
	.string "three POKéMON!$"

LittlerootTown_ProfessorBirchsLab_Text_YoullTakeCyndaquil:
	.string "PROF. BIRCH: The FIRE POKéMON\n"
	.string "CYNDAQUIL caught your eye!\p"
	.string "You're as sharp as ever!\p"
	.string "So the CYNDAQUIL is your choice?$"

LittlerootTown_ProfessorBirchsLab_Text_YoullTakeTotodile:
	.string "PROF. BIRCH: The WATER POKéMON\n"
	.string "TOTODILE is your choice!\p"
	.string "You know how to pick a good one.\p"
	.string "So, you'll take the TOTODILE?$"

LittlerootTown_ProfessorBirchsLab_Text_YoullTakeChikorita:
	.string "PROF. BIRCH: The GRASS POKéMON\n"
	.string "CHIKORITA is your choice!\p"
	.string "You sure know what you're doing.\p"
	.string "So, you'll take the CHIKORITA?$"

LittlerootTown_ProfessorBirchsLab_Text_TakeYourTimeAllInvaluable:
	.string "PROF. BIRCH: Take your time before\n"
	.string "you decide.\p"
	.string "They're all invaluable POKéMON.$"

@ Unused
LittlerootTown_ProfessorBirchsLab_Text_PickedFinePokemon:
	.string "PROF. BIRCH: I see!\n"
	.string "You picked a fine POKéMON!$"

LittlerootTown_ProfessorBirchsLab_Text_ReceivedJohtoStarter:
	.string "{PLAYER} received the {STR_VAR_1}\n"
	.string "from PROF. BIRCH!$"

@ Unused
LittlerootTown_ProfessorBirchsLab_Text_NicknameJohtoStarter:
	.string "Want to give a nickname to\n"
	.string "the {STR_VAR_1} you received?$"

LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting:
	.string "PROF. BIRCH: Listen, {PLAYER}{KUN}.\n"
	.string "You've completed the HOENN POKéDEX,\l"
	.string "but your POKéMON journey isn't over.\p"
	.string "There is no end to the road\n"
	.string "that is POKéMON.\p"
	.string "Somewhere, there is a grassy patch\n"
	.string "that's waiting for you!$"

LittlerootTown_ProfessorBirchsLab_Text_BetterLeaveOthersAlone:
	.string "You received the promised POKéMON.\n"
	.string "Better leave the others alone.$"

@ Unused
LittlerootTown_ProfessorBirchsLab_Text_DontHaveAnyRoomForPokemon:
	.string "Oh, you don't have any room for\n"
	.string "this POKéMON.$"

LittlerootTown_ProfessorBirchsLab_Text_MayWhatNextImStayingHere:
	.string "MAY: {PLAYER}{KUN}, after this…\n"
	.string "What are you going to do?\p"
	.string "Are you going to keep battling\n"
	.string "and sharpening your skills?\p"
	.string "Or are you going to try filling\n"
	.string "the NATIONAL POKéDEX?\p"
	.string "I'm staying here to help the PROF.$"

LittlerootTown_ProfessorBirchsLab_Text_BrendanPreferCollectingSlowly:
	.string "BRENDAN: Rather than collecting\n"
	.string "POKéMON, I prefer slowly and \l"
	.string "steadily raising the one I chose.$"

LittlerootTown_ProfessorBirchsLab_Text_MayHaveYouGoneToBattleFrontier:
	.string "MAY: Oh, hi, {PLAYER}{KUN}!\n"
	.string "Have you gone to that place,\l"
	.string "the BATTLE FRONTIER?$"

LittlerootTown_ProfessorBirchsLab_Text_BrendanHaveYouGoneToBattleFrontier:
	.string "BRENDAN: Hey, {PLAYER}!\n"
	.string "Have you gone out to that place,\l"
	.string "the BATTLE FRONTIER?$"

LittlerootTown_ProfessorBirchsLab_Text_ScottAboardSSTidalCall:
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "SCOTT: Hi, hi, {PLAYER}!\n"
	.string "It's me, SCOTT.\p"
	.string "I'm aboard the S.S. TIDAL now.\n"
	.string "It feels great to be on the sea!\p"
	.string "By the way…\p"
	.string "There's this place that I'd like to\n"
	.string "invite you to for a visit.\p"
	.string "If you're interested, board a ferry\n"
	.string "at either SLATEPORT or LILYCOVE.\p"
	.string "I'll fill you in on the details when\n"
	.string "we meet. I'll be waiting!\p"
	.string "… … … … … …\n"
	.string "… … … … … Click!$"
