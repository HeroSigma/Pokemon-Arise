RustboroCity_DevonCorp_3F_MapScripts::
        map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_3F_OnTransition
        map_script MAP_SCRIPT_ON_RESUME, RustboroCity_DevonCorp_3F_OnResume
        map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, RustboroCity_DevonCorp_3F_OnWarp
        map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_DevonCorp_3F_OnFrame
	.byte 0

RustboroCity_DevonCorp_3F_OnTransition:
        call_if_eq VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos
        call_if_set FLAG_CAUGHT_TYPE_NULL, RustboroCity_DevonCorp_3F_HideTypeNull
        call_if_unset FLAG_CAUGHT_TYPE_NULL, RustboroCity_DevonCorp_3F_TryShowTypeNull
        setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_GREEN
        end

RustboroCity_DevonCorp_3F_OnResume:
        call_if_set FLAG_SYS_CTRL_OBJ_DELETE, RustboroCity_DevonCorp_3F_TryRemoveTypeNull
        end

RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos::
	setobjectxyperm LOCALID_DEVON_CORP_3F_EMPLOYEE, 3, 2
	setobjectmovementtype LOCALID_DEVON_CORP_3F_EMPLOYEE, MOVEMENT_TYPE_FACE_LEFT
	return

RustboroCity_DevonCorp_3F_OnWarp:
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast
	.2byte 0

RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast::
	turnobject LOCALID_PLAYER, DIR_EAST
	end

RustboroCity_DevonCorp_3F_OnFrame:
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_MeetPresident
	map_script_2 VAR_DEVON_CORP_3F_STATE, 2, RustboroCity_DevonCorp_3F_EventScript_RiftDataScene
	.2byte 0

RustboroCity_DevonCorp_3F_EventScript_MeetPresident::
	lockall
	msgbox RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen
	waitmovement 0
	delay 80
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_FOLLOW_ME, FALSE
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_PleaseGoAhead, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_PresidentAquaCloakedFigures, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_PresidentDevonSilph, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_PresidentForgiveMeAlertColleagues, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_PresidentAnotherFavor, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_3F_Text_ReceivedLetterAndGoods
	waitfanfare
	giveitem ITEM_LETTER
	giveitem ITEM_DEVON_PARTS
	msgbox RustboroCity_DevonCorp_3F_Text_PresidentRelyOnYouUnsettledSlateport, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_3F_Text_ReceivedPokenav
	waitfanfare
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_RECEIVED_POKENAV
	setflag FLAG_HIDE_RUSTBORO_CITY_POKEMON_SCHOOL_SCOTT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	clearflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_GREEN
	addobject LOCALID_DEVON_CORP_3F_GREEN
	applymovement LOCALID_DEVON_CORP_3F_GREEN, RustboroCity_DevonCorp_3F_Movement_GreenEnter
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_GreenImpressive, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_PlayerWhoAreYou, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_GreenNameIsGreen, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_GreenYouveSeenSomething, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_PlayerSawPortalBoy, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_PlayerRed, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_GreenRedYouSawHim, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_PlayerIDontKnowHim, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_GreenIfRedsHere, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_GreenLeaves, MSGBOX_DEFAULT
	applymovement LOCALID_DEVON_CORP_3F_GREEN, RustboroCity_DevonCorp_3F_Movement_GreenExit
	waitmovement 0
	removeobject LOCALID_DEVON_CORP_3F_GREEN
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_GREEN
	msgbox RustboroCity_DevonCorp_3F_Text_PlayerMonologueRedGreen, MSGBOX_DEFAULT
	setflag FLAG_HIDE_ROUTE_116_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDA
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_BRINEY_LOCATION, 1
	clearflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_DEVON_CORP_3F_STATE, 1
	setvar VAR_RUSTBORO_CITY_STATE, 6
	releaseall
	end

RustboroCity_DevonCorp_3F_Movement_Unused:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk:
	delay_16
	walk_in_place_faster_down
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

RustboroCity_DevonCorp_3F_EventScript_MrStone::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EXP_SHARE, RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, RustboroCity_DevonCorp_3F_EventScript_GiveExpShare
	msgbox RustboroCity_DevonCorp_3F_Text_CountingOnYou, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_GiveExpShare::
	msgbox RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter, MSGBOX_DEFAULT
	giveitem ITEM_EXP_SHARE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EXP_SHARE
	msgbox RustboroCity_DevonCorp_3F_Text_ExplainExpShare, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor::
	msgbox RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REPEAT_BALL, RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls
	msgbox RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls::
	msgbox RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_RareRocksDisplay::
	msgbox RustboroCity_DevonCorp_3F_Text_RareRocksDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor:
	.string "I'm MR. STONE, the PRESIDENT of\n"
	.string "the DEVON CORPORATION.\p"
	.string "I'd just got word about you!\p"
	.string "You saved our staff not just once,\n"
	.string "but twice!\p"
	.string "I have a favor to ask of an amazing\n"
	.string "person like you.\p"
	.string "I understand that you're delivering\n"
	.string "a package to SLATEPORT's SHIPYARD.\p"
	.string "Well, on the way, could you stop off in\n"
	.string "DEWFORD TOWN?\p"
	.string "I was hoping that you'd deliver a\n"
	.string "LETTER to STEVEN in DEWFORD.$"

RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis:
	.string "MR. STONE: Now, you should know that\n"
	.string "I am a great PRESIDENT.\p"
	.string "So, I'd never be so cheap as to ask\n"
	.string "a favor for nothing in return.\p"
	.string "That's why I want you to have this!$"

RustboroCity_DevonCorp_3F_Text_ReceivedPokenav:
	.string "{PLAYER} received a POKéNAV.$"

// Replaced by custom scene and Green entrance

// Unused after custom scene

RustboroCity_DevonCorp_3F_Text_CountingOnYou:
	.string "MR. STONE: I'm counting on you!$"

RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter:
	.string "MR. STONE: You delivered my LETTER?\n"
	.string "Thank you kindly!\p"
	.string "This is my way of thanking you.\n"
	.string "It should help you, a TRAINER.$"

RustboroCity_DevonCorp_3F_Text_ExplainExpShare:
	.string "MR. STONE: A POKéMON holding that\n"
	.string "EXP. SHARE will be given some of the\l"
	.string "EXP Points from battle.\p"
	.string "It will get EXP Points even if it didn't\n"
	.string "actually battle.\p"
	.string "I would say EXP. SHARE is quite useful\n"
	.string "for raising weak POKéMON.$"

RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends:
	.string "MR. STONE: Since my youth, I've immersed\n"
	.string "myself in work.\p"
	.string "Consequently, I'm not familiar with\n"
	.string "trends and that sort of thing.\p"
	.string "But do young people all want to be\n"
	.string "TRAINERS in the POKéMON LEAGUE?$"

RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere:
	.string "This is the DEVON CORPORATION's\n"
	.string "third floor.\p"
	.string "Our PRESIDENT's OFFICE is on\n"
	.string "this floor.\p"
	.string "Anyway, I can't tell you how much I'm\n"
	.string "grateful for what you've done.\p"
	.string "Um… By the way, that parcel\n"
	.string "you got back for us…\p"
	.string "Could I get you to deliver that to\n"
	.string "the SHIPYARD in SLATEPORT?\p"
	.string "It would be awful if those robbers\n"
	.string "tried to take it again.\p"
	.string "Uh… Hehehe, so, uh, could I count\n"
	.string "on you to do that for me?\p"
	.string "Oh, that's right.\n"
	.string "Could you wait here a second?$"

RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe:
	.string "Our PRESIDENT would like to have\n"
	.string "a word with you.\p"
	.string "Please come with me.$"

RustboroCity_DevonCorp_3F_Text_PleaseGoAhead:
	.string "Please, go ahead.$"

RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard:
	.string "If you visit the SHIPYARD in SLATEPORT,\n"
	.string "you should go see CAPT. STERN.$"

RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular:
	.string "DEVON's new products, the REPEAT BALL\n"
	.string "and TIMER BALL, have become hugely\l"
	.string "popular among TRAINERS.$"

RustboroCity_DevonCorp_3F_Text_RareRocksDisplay:
        .string "It's a collection of rare rocks and\n"
        .string "stones assembled by the PRESIDENT.$"

// New custom dialogue for Mr. Stone and Green entrance

RustboroCity_DevonCorp_3F_Text_PresidentAquaCloakedFigures:
	.string "{COLOR BLUE}PRESIDENT:\n"
	.string "Ah, {PLAYER}! You stood up to\n"
	.string "TEAM AQUA. Impressive.\p"
	.string "But I heard... someone else was\n"
	.string "there too. Cloaked figures.\n"
	.string "Silent. Watching.$"

RustboroCity_DevonCorp_3F_Text_PresidentDevonSilph:
	.string "(The PRESIDENT frowns deeply.)\p"
	.string "{COLOR BLUE}PRESIDENT:\n"
	.string "You've done us a great service.\n"
	.string "These aren't just parts and metal.\n"
	.string "DEVON is working with SILPH CO.\n"
	.string "to connect our regions. If these\n"
	.string "fell into the wrong hands...$"

RustboroCity_DevonCorp_3F_Text_PresidentForgiveMeAlertColleagues:
	.string "(He shakes his head, unsettled.)\p"
	.string "{COLOR BLUE}PRESIDENT:\n"
	.string "Forgive me. Cloaked figures in\n"
	.string "Hoenn... This is troubling.\p"
	.string "I'll need to alert some colleagues.\p"
	.string "But that's not your burden to carry.$"

RustboroCity_DevonCorp_3F_Text_PresidentAnotherFavor:
	.string "(He brightens, offering a package\n"
	.string "and a letter.)\p"
	.string "{COLOR BLUE}PRESIDENT:\n"
	.string "Still, I must ask another favor.\n"
	.string "This letter goes to Granite Cave\n"
	.string "Steven. The goods go to the\n"
	.string "SHIPYARD CAPTAIN in SLATEPORT.\n"
	.string "Will you take them?$"

RustboroCity_DevonCorp_3F_Text_ReceivedLetterAndGoods:
	.string "{COLOR DARK_GRAY}{PLAYER} received the\n"
	.string "LETTER and the DEVON GOODS!$"

RustboroCity_DevonCorp_3F_Text_PresidentRelyOnYouUnsettledSlateport:
	.string "{COLOR BLUE}PRESIDENT:\n"
	.string "I knew I could rely on you. The\n"
	.string "CAPTAIN was last seen in SLATEPORT.\n"
	.string "Things there have been unsettled.$"

RustboroCity_DevonCorp_3F_Text_GreenImpressive:
	.string "{COLOR GREEN}GREEN:\n"
	.string "So you're the one who stopped AQUA\n"
	.string "and that guy in black. Not bad.$"

RustboroCity_DevonCorp_3F_Text_PlayerWhoAreYou:
	.string "{COLOR GREEN}{PLAYER}: Who... are you?$"

RustboroCity_DevonCorp_3F_Text_GreenNameIsGreen:
	.string "{COLOR GREEN}GREEN:\n"
	.string "Name's GREEN. I know my way around\n"
	.string "Hoenn, but... the strange thing is,\n"
	.string "I don't remember how I got here\n"
	.string "this time.$"

RustboroCity_DevonCorp_3F_Text_GreenYouveSeenSomething:
	.string "(She eyes you carefully.)\p"
	.string "{COLOR GREEN}GREEN:\n"
	.string "You've got that look. Like you've\n"
	.string "seen something strange yourself.$"

RustboroCity_DevonCorp_3F_Text_PlayerSawPortalBoy:
	.string "{COLOR GREEN}{PLAYER}:\n"
	.string "On ROUTE 102... I saw a boy step\n"
	.string "out of a portal. Didn't know his\n"
	.string "name then. But just now, seeing\n"
	.string "you... the name came back to me.$"

RustboroCity_DevonCorp_3F_Text_PlayerRed:
	.string "{COLOR GREEN}{PLAYER}: Red.$"

RustboroCity_DevonCorp_3F_Text_GreenRedYouSawHim:
	.string "(GREEN's eyes widen. She whispers\n"
	.string "the name back like it stings.)\p"
	.string "{COLOR GREEN}GREEN:\n"
	.string "Red...? You saw him?!$"

RustboroCity_DevonCorp_3F_Text_PlayerIDontKnowHim:
	.string "{COLOR GREEN}{PLAYER}:\n"
	.string "I don't know him. I can't remember.\n"
	.string "But when I saw you, the name was\n"
	.string "suddenly there. Like I'd forgotten\n"
	.string "it all this time.$"

RustboroCity_DevonCorp_3F_Text_GreenIfRedsHere:
	.string "(GREEN turns away, hiding her concern,\n"
	.string "then steadies her voice.)\p"
	.string "{COLOR GREEN}GREEN:\n"
	.string "If RED's really here, things are\n"
	.string "worse than I thought. I'll track\n"
	.string "him down. You--finish your delivery.\n"
	.string "The CAPTAIN's in trouble. Move fast.$"

RustboroCity_DevonCorp_3F_Text_GreenLeaves:
	.string "(She leaves through the elevator,\n"
	.string "disappearing from sight.)$"

RustboroCity_DevonCorp_3F_Text_PlayerMonologueRedGreen:
	.string "{COLOR GREEN}{PLAYER}: (Red... Green... Why do\n"
	.string "these names feel familiar when I can't\n"
	.string "even remember why?)$"

RustboroCity_DevonCorp_3F_HideTypeNull::
        setflag FLAG_HIDE_TYPE_NULL
        return

RustboroCity_DevonCorp_3F_TryShowTypeNull::
        goto_if_unset FLAG_BADGE06_GET, Common_EventScript_NopReturn
        goto_if_unset FLAG_CAUGHT_HOOPA, Common_EventScript_NopReturn
        clearflag FLAG_HIDE_TYPE_NULL
        return

RustboroCity_DevonCorp_3F_TryRemoveTypeNull::
        specialvar VAR_RESULT, GetBattleOutcome
        goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
        removeobject LOCALID_DEVON_CORP_3F_TYPE_NULL
        return

RustboroCity_DevonCorp_3F_TypeNull::
        lock
        faceplayer
        waitse
        playmoncry SPECIES_TYPE_NULL, CRY_MODE_ENCOUNTER
        waitmoncry
        seteventmon SPECIES_TYPE_NULL, 20
        setflag FLAG_SYS_CTRL_OBJ_DELETE
        special BattleSetup_StartLegendaryBattle
        waitstate
        clearflag FLAG_SYS_CTRL_OBJ_DELETE
        specialvar VAR_RESULT, GetBattleOutcome
        goto_if_eq VAR_RESULT, B_OUTCOME_WON, RustboroCity_DevonCorp_3F_DefeatedTypeNull
        goto_if_eq VAR_RESULT, B_OUTCOME_RAN, RustboroCity_DevonCorp_3F_RanFromTypeNull
        goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, RustboroCity_DevonCorp_3F_RanFromTypeNull
        setflag FLAG_CAUGHT_TYPE_NULL
        release
        end

RustboroCity_DevonCorp_3F_DefeatedTypeNull::
        setvar VAR_0x8004, SPECIES_TYPE_NULL
        goto Common_EventScript_LegendaryFlewAway
        end

RustboroCity_DevonCorp_3F_RanFromTypeNull::
        setvar VAR_0x8004, SPECIES_TYPE_NULL
        goto Common_EventScript_LegendaryFlewAway
        end

RustboroCity_DevonCorp_3F_EventScript_RiftDataScene::
	lockall
	msgbox RustboroCity_DevonCorp_3F_Text_StoneThanksForProtectingData, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_RiftReadingsImportant, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_StoneHasTwoRequests, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_DeliverLetterToSteven, MSGBOX_DEFAULT
	giveitem ITEM_LETTER
	msgbox RustboroCity_DevonCorp_3F_Text_PlayerAcceptsLetter, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_TakeDevonPartsToStern, MSGBOX_DEFAULT
	giveitem ITEM_DEVON_PARTS
	msgbox RustboroCity_DevonCorp_3F_Text_PlayerUnderstandsParts, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_StoneCountingOnYou, MSGBOX_DEFAULT
	closemessage
	delay 30
	clearflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_GREEN
	addobject LOCALID_DEVON_CORP_3F_GREEN
	applymovement LOCALID_DEVON_CORP_3F_GREEN, RustboroCity_DevonCorp_3F_Movement_GreenEnter
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_GreenBadNews, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_GreenWhoAreYou, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_PlayerIntroducesThemself, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_GreenNeverMindHelpStern, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_StoneYouHeardThat, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_StoneDeliverLetterThenSlateport, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_GreenIllRememberYou, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_GreenGoingToDocks, MSGBOX_DEFAULT
	applymovement LOCALID_DEVON_CORP_3F_GREEN, RustboroCity_DevonCorp_3F_Movement_GreenExit
	waitmovement 0
	removeobject LOCALID_DEVON_CORP_3F_GREEN
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_GREEN
	setvar VAR_DEVON_CORP_3F_STATE, 3
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	clearflag FLAG_HIDE_ROUTE_116_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDA
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_BRINEY_LOCATION, 1
	releaseall
	end

RustboroCity_DevonCorp_3F_Movement_GreenEnter:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

RustboroCity_DevonCorp_3F_Movement_GreenExit:
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_DevonCorp_3F_Text_StoneThanksForProtectingData:
	.string "STONE: {PLAYER}, thank you for protecting\n"
	.string "our data.$"

RustboroCity_DevonCorp_3F_Text_RiftReadingsImportant:
	.string "STONE: Those rift readings are important\n"
	.string "to HOENN.$"

RustboroCity_DevonCorp_3F_Text_StoneHasTwoRequests:
	.string "STONE: I have two requests.$"

RustboroCity_DevonCorp_3F_Text_DeliverLetterToSteven:
	.string "STONE: First, deliver this letter to my\n"
	.string "son, STEVEN.\p"
	.string "He's in GRANITE CAVE on DEWFORD.$"

RustboroCity_DevonCorp_3F_Text_PlayerAcceptsLetter:
	.string "PLAYER: I'll take it to him.$"

RustboroCity_DevonCorp_3F_Text_TakeDevonPartsToStern:
	.string "STONE: Second, take these DEVON PARTS\n"
	.string "to CAPTAIN STERN.\p"
	.string "You'll find him in SLATEPORT, at the\n"
	.string "OCEANIC MUSEUM.$"

RustboroCity_DevonCorp_3F_Text_PlayerUnderstandsParts:
	.string "PLAYER: Understood.$"

RustboroCity_DevonCorp_3F_Text_StoneCountingOnYou:
	.string "STONE: Thank you, {PLAYER}. I'm counting\n"
	.string "on you.$"

RustboroCity_DevonCorp_3F_Text_GreenBadNews:
	.string "GREEN: Mr. STONE! Bad news--the MUSEUM\n"
	.string "in SLATEPORT.\p"
	.string "AQUA grunts are gathering out front.$"

RustboroCity_DevonCorp_3F_Text_GreenWhoAreYou:
	.string "GREEN: …And you are?$"

RustboroCity_DevonCorp_3F_Text_PlayerIntroducesThemself:
	.string "PLAYER: I'm {PLAYER}.$"

RustboroCity_DevonCorp_3F_Text_GreenNeverMindHelpStern:
	.string "GREEN: Never mind. If you've got\n"
	.string "POKéMON, help STERN.$"

RustboroCity_DevonCorp_3F_Text_StoneYouHeardThat:
	.string "STONE: You heard that, {PLAYER}.$"

RustboroCity_DevonCorp_3F_Text_StoneDeliverLetterThenSlateport:
	.string "STONE: Deliver the letter to STEVEN,\n"
	.string "then head to SLATEPORT.$"

RustboroCity_DevonCorp_3F_Text_GreenIllRememberYou:
	.string "GREEN: {PLAYER}, huh? I'll remember that.$"

RustboroCity_DevonCorp_3F_Text_GreenGoingToDocks:
	.string "GREEN: I'm going to the docks. Move fast.$"
