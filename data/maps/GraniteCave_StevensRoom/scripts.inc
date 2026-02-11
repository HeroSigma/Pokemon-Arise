GraniteCave_StevensRoom_MapScripts::
        map_script MAP_SCRIPT_ON_TRANSITION, GraniteCave_StevensRoom_OnTransition
        map_script MAP_SCRIPT_ON_RESUME, GraniteCave_StevensRoom_OnResume
        .byte 0

GraniteCave_StevensRoom_OnTransition:
        call_if_set FLAG_CAUGHT_YVELTAL, GraniteCave_StevensRoom_HideYveltal
        call_if_unset FLAG_CAUGHT_YVELTAL, GraniteCave_StevensRoom_TryShowYveltal
        return

GraniteCave_StevensRoom_OnResume:
        call_if_set FLAG_SYS_CTRL_OBJ_DELETE, GraniteCave_StevensRoom_TryRemoveYveltal
        end

GraniteCave_StevensRoom_EventScript_Steven::
	lockall
	faceplayer
	@ Ensure BLUE is present for the scene
	clearflag FLAG_HIDE_GRANITE_CAVE_BLUE
	@ BLUE speaks first
	msgbox GraniteCave_StevensRoom_Text_BlueSealedOff, MSGBOX_DEFAULT
	@ STEVEN responds calmly
	msgbox GraniteCave_StevensRoom_Text_StevenCaveNotThereBefore, MSGBOX_DEFAULT
	@ PLAYER internal thought
	msgbox GraniteCave_StevensRoom_Text_PlayerTimelessWoodsThought, MSGBOX_DEFAULT
	@ PLAYER hands over the letter
	msgbox GraniteCave_StevensRoom_Text_PlayerDeliverLine_New, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_LETTER
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_DELIVERED_STEVEN_LETTER
	@ STEVEN on DEVON/SILPH research
	msgbox GraniteCave_StevensRoom_Text_StevenDevonSilphStabilize, MSGBOX_DEFAULT
	@ BLUE skeptical
	msgbox GraniteCave_StevensRoom_Text_BlueSinkingShip, MSGBOX_DEFAULT
	@ STEVEN advises patience
	msgbox GraniteCave_StevensRoom_Text_StevenImpatience, MSGBOX_DEFAULT
	@ PLAYER internal comparison
	msgbox GraniteCave_StevensRoom_Text_PlayerBlueVsSteven, MSGBOX_DEFAULT
	@ STEVEN gives TM: STEEL WING
	giveitem ITEM_TM_STEEL_WING
	call_if_eq VAR_RESULT, FALSE, GraniteCave_StevensRoom_EventScript_BagFull
	msgbox GraniteCave_StevensRoom_Text_SteelWingGift_New, MSGBOX_DEFAULT
	@ Keep POKENAV registration behavior consistent
	setflag FLAG_REGISTERED_STEVEN_POKENAV
	@ BLUE exits confidently
	msgbox GraniteCave_StevensRoom_Text_BlueLeaves, MSGBOX_DEFAULT
	applymovement LOCALID_GRANITE_CAVE_BLUE, GraniteCave_StevensRoom_Movement_BlueExit
	waitmovement 0
	removeobject LOCALID_GRANITE_CAVE_BLUE
	setflag FLAG_HIDE_GRANITE_CAVE_BLUE
	@ STEVEN's final note to the player
	msgbox GraniteCave_StevensRoom_Text_StevenFinal, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, GraniteCave_StevensRoom_EventScript_StevenExitNorth
	call_if_eq VAR_FACING, DIR_SOUTH, GraniteCave_StevensRoom_EventScript_StevenExitSouth
	call_if_eq VAR_FACING, DIR_WEST, GraniteCave_StevensRoom_EventScript_StevenExitWestEast
	call_if_eq VAR_FACING, DIR_EAST, GraniteCave_StevensRoom_EventScript_StevenExitWestEast
	playse SE_EXIT
	removeobject LOCALID_GRANITE_CAVE_STEVEN
	releaseall
	end

GraniteCave_StevensRoom_EventScript_StevenExitNorth::
	applymovement LOCALID_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_StevenExitWestEast::
	applymovement LOCALID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
	applymovement LOCALID_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_StevenExitSouth::
        applymovement LOCALID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
        applymovement LOCALID_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_Movement_StevenExitSouth
        waitmovement 0
        return

GraniteCave_StevensRoom_EventScript_BagFull::
        msgbox GraniteCave_StevensRoom_Text_OhBagIsFull, MSGBOX_DEFAULT
        return

GraniteCave_StevensRoom_HideYveltal::
        setflag FLAG_HIDE_YVELTAL
        return

GraniteCave_StevensRoom_TryShowYveltal::
        goto_if_unset FLAG_BADGE06_GET, Common_EventScript_NopReturn
        goto_if_unset FLAG_CAUGHT_HOOPA, Common_EventScript_NopReturn
        clearflag FLAG_HIDE_YVELTAL
        return

GraniteCave_StevensRoom_TryRemoveYveltal::
        specialvar VAR_RESULT, GetBattleOutcome
        goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
        removeobject LOCALID_GRANITE_CAVE_YVELTAL
        return

GraniteCave_StevensRoom_Yveltal::
        lock
        faceplayer
        waitse
        playmoncry SPECIES_YVELTAL, CRY_MODE_ENCOUNTER
        waitmoncry
        seteventmon SPECIES_YVELTAL, 70
        setflag FLAG_SYS_CTRL_OBJ_DELETE
        special BattleSetup_StartLegendaryBattle
        waitstate
        clearflag FLAG_SYS_CTRL_OBJ_DELETE
        specialvar VAR_RESULT, GetBattleOutcome
        goto_if_eq VAR_RESULT, B_OUTCOME_WON, GraniteCave_StevensRoom_DefeatedYveltal
        goto_if_eq VAR_RESULT, B_OUTCOME_RAN, GraniteCave_StevensRoom_RanFromYveltal
        goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, GraniteCave_StevensRoom_RanFromYveltal
        setflag FLAG_CAUGHT_YVELTAL
        release
        end

GraniteCave_StevensRoom_DefeatedYveltal::
        setvar VAR_0x8004, SPECIES_YVELTAL
        goto Common_EventScript_LegendaryFlewAway
        end

GraniteCave_StevensRoom_RanFromYveltal::
        setvar VAR_0x8004, SPECIES_YVELTAL
        goto Common_EventScript_LegendaryFlewAway
        end

GraniteCave_StevensRoom_Movement_StevenExit:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Movement_BlueExit:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

GraniteCave_StevensRoom_Movement_StevenExitSouth:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Text_StevenCarvingsGreeting:
	.string "{COLOR BLUE}STEVEN:\n"
	.string "Remarkable... These carvings predate\n"
	.string "even Hoenn's first records.\p"
	.string "They speak of distortions--tears in\n"
	.string "the fabric of reality itself.\p"
	.string "Ah. You must be {PLAYER}.\p"
	.string "BIRCH mentioned you, but I didn't\n"
	.string "expect you so soon.$"

GraniteCave_StevensRoom_Text_PlayerDeliverLine:
	.string "{COLOR GREEN}{PLAYER}:\n"
	.string "Mr. STONE asked me to deliver this\n"
	.string "to you.$"

GraniteCave_StevensRoom_Text_StevenDevonSilphRifts:
	.string "{COLOR BLUE}STEVEN:\n"
	.string "So DEVON suspects as well...\n"
	.string "SILPH's research agrees.\p"
	.string "The balance of this region is\n"
	.string "shifting.\p"
	.string "Look closely--figures lost to rifts,\n"
	.string "POKEMON twisted into new forms.\p"
	.string "This is no myth. The ZOROARK you saw\n"
	.string "near LITTLEROOT was proof.$"

GraniteCave_StevensRoom_Text_SteelWingGift:
	.string "{COLOR BLUE}STEVEN:\n"
	.string "Take this. Steel endures.\p"
	.string "May it serve you when all else feels\n"
	.string "uncertain.\p"
	.string "{COLOR DARK_GRAY}You received TM47 (STEEL WING)!$"

GraniteCave_StevensRoom_Text_StevenJourneyForeshadow:
	.string "{COLOR BLUE}STEVEN:\n"
	.string "Your journey is crossing paths with\n"
	.string "powers greater than you know.\p"
	.string "Others are watching too... silent\n"
	.string "for now.\p"
	.string "When the time comes, we will meet\n"
	.string "again--and perhaps then, the truth\n"
	.string "will no longer hide itself.$"

GraniteCave_StevensRoom_Text_OhBagIsFull:
	.string "{COLOR DARK_GRAY}Oh, your BAG is full...\n"
	.string "That's too bad, then.$"

GraniteCave_StevensRoom_Text_PlayerThoughtFather:
	.string "{PLAYER}: (Vanished…? Could he be talking\n"
	.string "about Father?)$"

// New cutscene text for BLUE + STEVEN in Steven's Room
GraniteCave_StevensRoom_Text_BlueSealedOff:
	.string "{COLOR BLUE}BLUE: Tch. Finally caught up, huh?\p"
	.string "{COLOR BLUE}I pushed further earlier, but the path ahead was sealed off.\nLike the cave itself doesn't want me in there.\p"
	.string "{COLOR BLUE}Doesn't make sense.$"
	.string "{COLOR BLUE}BLUE:\n"
	.string "Tch. Finally caught up, huh?\p"
	.string "I pushed further earlier, but the path\n"
	.string "ahead was sealed off.\n"
	.string "Like the cave itself doesn't want me in there.\p"
	.string "Doesn't make sense.$"

GraniteCave_StevensRoom_Text_StevenCaveNotThereBefore:
	.string "{COLOR BLUE}STEVEN: You're not mistaken. That cave to the left of DEWFORD was not here before.\p"
	.string "{COLOR BLUE}I've explored HOENN many times… yet what I see now is new. As if the earth itself rewrote the stone.$"
	.string "{COLOR BLUE}STEVEN:\n"
	.string "You're not mistaken.\n"
	.string "That cave to the left of DEWFORD\n"
	.string "was not here before.\p"
	.string "I've explored HOENN many times…\n"
	.string "yet what I see now is new.\n"
	.string "As if the earth itself rewrote the stone.$"

GraniteCave_StevensRoom_Text_PlayerTimelessWoodsThought:
	.string "{COLOR GREEN}{PLAYER}:\n"
	.string "(Just like the TIMELESS WOODS… HOENN is\n"
	.string "changing right in front of us.)$"
	.string "{COLOR DARK_GRAY}({PLAYER}): Just like the TIMELESS WOODS… HOENN is changing right in front of us.$"

GraniteCave_StevensRoom_Text_PlayerDeliverLine_New:
	.string "{COLOR GREEN}{PLAYER}: I was asked to deliver this to you. From Mr. STONE of DEVON CORP.$"
	.string "{COLOR GREEN}{PLAYER}:\n"
	.string "I was asked to deliver this to you.\n"
	.string "From Mr. STONE of DEVON CORP.$"

GraniteCave_StevensRoom_Text_StevenDevonSilphStabilize:
	.string "{COLOR BLUE}STEVEN: …Ah. From Dad. Thank you, {PLAYER}.\pThese notes matter. DEVON and SILPH are investigating ways to stabilize interregional connections--timely, given what we've witnessed here.$"
	.string "{COLOR BLUE}STEVEN:\n"
	.string "…Ah. From Dad. Thank you, {PLAYER}.\p"
	.string "These notes matter.\n"
	.string "DEVON and SILPH are investigating ways\n"
	.string "to stabilize interregional connections--\n"
	.string "timely, given what we've witnessed here.$"

GraniteCave_StevensRoom_Text_BlueSinkingShip:
	.string "{COLOR BLUE}BLUE:\n"
	.string "SILPH, huh? More like patching a\n"
	.string "sinking ship. Whatever's in that cave\n"
	.string "isn't normal--and I don't like being\n"
	.string "shut out.$"
	.string "{COLOR BLUE}BLUE: SILPH, huh? More like patching a sinking ship. Whatever's in that cave isn't normal--and I don't like being shut out.$"

GraniteCave_StevensRoom_Text_StevenImpatience:
	.string "{COLOR BLUE}STEVEN:\n"
	.string "Impatience won't open the door, BLUE.\p"
	.string "Some things reveal themselves only\n"
	.string "in their own time.$"
	.string "{COLOR BLUE}STEVEN: Impatience won't open the door, BLUE.\pSome things reveal themselves only in their own time.$"

GraniteCave_StevensRoom_Text_PlayerBlueVsSteven:
	.string "{COLOR GREEN}{PLAYER}:\n"
	.string "(BLUE again… always pushing for answers.\n"
	.string "STEVEN watches--and understands.)$"
	.string "{COLOR DARK_GRAY}({PLAYER}): BLUE again… always pushing for answers. STEVEN watches--and understands.$"

GraniteCave_StevensRoom_Text_SteelWingGift_New:
	.string "{COLOR BLUE}STEVEN:\n"
	.string "Still, you both have potential.\p"
	.string "Take this TM as thanks…and as\n"
	.string "preparation for what's ahead.\p"
	.string "{COLOR DARK_GRAY}You received TM47 (STEEL WING)!\p"
	.string "{COLOR BLUE}Use it wisely. STEEL WING requires\n"
	.string "precision and resolve--qualities you have.$"
	.string "{COLOR BLUE}STEVEN: Still, you both have potential.\pTake this TM as thanks… and as preparation for what's ahead.\pUse it wisely. STEEL WING requires precision and resolve--qualities you have.$"
	.string "{COLOR DARK_GRAY}You received TM47 (STEEL WING)!$"

GraniteCave_StevensRoom_Text_BlueLeaves:
	.string "{COLOR BLUE}BLUE:\n"
	.string "Hmph. Guess I'll wait for the cave\n"
	.string "to open itself. But next time, I'll\n"
	.string "be ahead of you. Don't get comfy.$"
	.string "{COLOR BLUE}BLUE: Hmph. Guess I'll wait for the cave to open itself. But next time, I'll be ahead of you. Don't get comfy.$"

GraniteCave_StevensRoom_Text_StevenFinal:
	.string "{COLOR BLUE}STEVEN:\n"
	.string "He has strength--and pride. But strength\n"
	.string "without patience can be dangerous.\p"
	.string "Keep your eyes open, {PLAYER}. HOENN is\n"
	.string "shifting--and you're at the center of it.$"
	.string "{COLOR BLUE}STEVEN: He has strength--and pride. But strength without patience can be dangerous.\pKeep your eyes open, {PLAYER}. HOENN is shifting--and you're at the center of it.$"
