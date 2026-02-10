PetalburgWoods_MapScripts::
        map_script MAP_SCRIPT_ON_TRANSITION, PetalburgWoods_OnTransition
        map_script MAP_SCRIPT_ON_RESUME, PetalburgWoods_OnResume
        .byte 0

PetalburgWoods_OnTransition:
        call_if_set FLAG_CAUGHT_CELEBI, PetalburgWoods_HideCelebi
        call_if_unset FLAG_CAUGHT_CELEBI, PetalburgWoods_TryShowCelebi
        call_if_set FLAG_CAUGHT_XERNEAS, PetalburgWoods_HideXerneas
        call_if_unset FLAG_CAUGHT_XERNEAS, PetalburgWoods_TryShowXerneas
        end

PetalburgWoods_OnResume:
        call_if_set FLAG_SYS_CTRL_OBJ_DELETE, PetalburgWoods_TryRemoveCelebi
        call_if_set FLAG_SYS_CTRL_OBJ_DELETE, PetalburgWoods_TryRemoveXerneas
        end

PetalburgWoods_HideCelebi::
        setflag FLAG_HIDE_CELEBI
        return

PetalburgWoods_TryShowCelebi::
        goto_if_unset FLAG_BADGE06_GET, Common_EventScript_NopReturn
        goto_if_unset FLAG_CAUGHT_HOOPA, Common_EventScript_NopReturn
        goto_if_unset FLAG_CAUGHT_MEW, Common_EventScript_NopReturn
        clearflag FLAG_HIDE_CELEBI
        return

PetalburgWoods_TryRemoveCelebi::
        specialvar VAR_RESULT, GetBattleOutcome
        goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
        removeobject LOCALID_PETALBURG_WOODS_CELEBI
        return

PetalburgWoods_Celebi::
        lock
        faceplayer
        waitse
        playmoncry SPECIES_CELEBI, CRY_MODE_ENCOUNTER
        waitmoncry
        seteventmon SPECIES_CELEBI, 30
        setflag FLAG_SYS_CTRL_OBJ_DELETE
        special BattleSetup_StartLegendaryBattle
        waitstate
        clearflag FLAG_SYS_CTRL_OBJ_DELETE
        specialvar VAR_RESULT, GetBattleOutcome
        goto_if_eq VAR_RESULT, B_OUTCOME_WON, PetalburgWoods_DefeatedCelebi
        goto_if_eq VAR_RESULT, B_OUTCOME_RAN, PetalburgWoods_RanFromCelebi
        goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, PetalburgWoods_RanFromCelebi
        setflag FLAG_CAUGHT_CELEBI
        release
        end

PetalburgWoods_DefeatedCelebi::
        setvar VAR_0x8004, SPECIES_CELEBI
        goto Common_EventScript_LegendaryFlewAway
        end

PetalburgWoods_RanFromCelebi::
        setvar VAR_0x8004, SPECIES_CELEBI
        goto Common_EventScript_LegendaryFlewAway
        end

PetalburgWoods_HideXerneas::
        setflag FLAG_HIDE_XERNEAS
        return

PetalburgWoods_TryShowXerneas::
        goto_if_unset FLAG_BADGE06_GET, Common_EventScript_NopReturn
        goto_if_unset FLAG_CAUGHT_HOOPA, Common_EventScript_NopReturn
        clearflag FLAG_HIDE_XERNEAS
        return

PetalburgWoods_TryRemoveXerneas::
        specialvar VAR_RESULT, GetBattleOutcome
        goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
        removeobject LOCALID_PETALBURG_WOODS_XERNEAS
        return

PetalburgWoods_Xerneas::
        lock
        faceplayer
        waitse
        playmoncry SPECIES_XERNEAS, CRY_MODE_ENCOUNTER
        waitmoncry
        seteventmon SPECIES_XERNEAS, 70
        setflag FLAG_SYS_CTRL_OBJ_DELETE
        special BattleSetup_StartLegendaryBattle
        waitstate
        clearflag FLAG_SYS_CTRL_OBJ_DELETE
        specialvar VAR_RESULT, GetBattleOutcome
        goto_if_eq VAR_RESULT, B_OUTCOME_WON, PetalburgWoods_DefeatedXerneas
        goto_if_eq VAR_RESULT, B_OUTCOME_RAN, PetalburgWoods_RanFromXerneas
        goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, PetalburgWoods_RanFromXerneas
        setflag FLAG_CAUGHT_XERNEAS
        release
        end

PetalburgWoods_DefeatedXerneas::
        setvar VAR_0x8004, SPECIES_XERNEAS
        goto Common_EventScript_LegendaryFlewAway
        end

PetalburgWoods_RanFromXerneas::
        setvar VAR_0x8004, SPECIES_XERNEAS
        goto Common_EventScript_LegendaryFlewAway
        end

PetalburgWoods_EventScript_DevonResearcherLeft::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_DevonResearcherContinue, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_AquaApproach, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherLeft
	waitmovement 0
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_DevonRefuse, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_PlayerDefend, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_DevonRequestHelp, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_PlayerAccept, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachPlayer
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement LOCALID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitLeft
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherRight::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_DevonResearcherContinue, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_AquaApproach, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherRight
	waitmovement 0
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_DevonRefuse, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_PlayerDefend, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_DevonRequestHelp, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_PlayerAccept, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement LOCALID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitRight
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherIntro::
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherLookAround
	waitmovement 0
	msgbox PetalburgWoods_Text_NotAOneToBeFound, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_DevonResearcherPostBattle::
	msgbox PetalburgWoods_Text_YouveGotSomeNerve, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaRunAway
	waitmovement 0
	removeobject LOCALID_PETALBURG_WOODS_GRUNT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox PetalburgWoods_Text_ThatWasAwfullyClose, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_DevonContinueConvo, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_DevonFine, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_PlayerGlad, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_DevonExplainRifts, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	msgbox PetalburgWoods_Text_ReceivedShinyCharm, MSGBOX_DEFAULT
	giveitem ITEM_SHINY_CHARM
	waitfanfare
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_BagFull
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_BagFull::
	msgbox PetalburgWoods_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_DevonResearcherFinish::
	msgbox PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro, MSGBOX_DEFAULT
	msgbox PetalburgWoods_Text_PlayerWillGo, MSGBOX_DEFAULT
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherStartExit
	waitmovement 0
	msgbox PetalburgWoods_Text_ICantBeWastingTime, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_RemoveDevonResearcher::
	removeobject LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE
	setvar VAR_PETALBURG_WOODS_STATE, 1
	releaseall
	end

PetalburgWoods_Movement_DevonResearcherLookAround:
	face_up
	delay_16
	delay_4
	face_right
	delay_16
	delay_8
	face_left
	delay_16
	delay_8
	face_down
	delay_16
	face_right
	delay_16
	delay_8
	face_up
	delay_16
	step_end

PetalburgWoods_Movement_DevonResearcherExitLeft:
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft:
	delay_16
	face_player
	walk_down
	walk_down
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerRight:
	delay_16
	face_player
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

PetalburgWoods_Movement_DevonResearcherExitRight:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_WatchResearcherLeave:
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight:
	walk_fast_down
	walk_fast_right
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherStartExit:
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_up
	step_end

PetalburgWoods_Movement_AquaApproachResearcherLeft:
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaBackOff:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

PetalburgWoods_Movement_AquaRunAway:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachResearcherRight:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaEntrance:
	walk_down
	walk_down
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachPlayer:
	walk_down
	step_end

PetalburgWoods_EventScript_Boy1::
	msgbox PetalburgWoods_Text_StayOutOfTallGrass, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Boy2::
	msgbox PetalburgWoods_Text_HiddenItemsExplanation, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MIRACLE_SEED, PetalburgWoods_EventScript_ExplainMiracleSeed
	msgbox PetalburgWoods_Text_TryUsingThisItem, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MIRACLE_SEED
	release
	end

PetalburgWoods_EventScript_ExplainMiracleSeed::
	msgbox PetalburgWoods_Text_MiracleSeedExplanation, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_Sign1::
	msgbox PetalburgWoods_Text_TrainerTipsExperience, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Sign2::
	msgbox PetalburgWoods_Text_TrainerTipsPP, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Lyle::
	trainerbattle_single TRAINER_LYLE, PetalburgWoods_Text_GoBugPokemonTeam, PetalburgWoods_Text_ICouldntWin
	msgbox PetalburgWoods_Text_ImOutOfPokeBalls, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_EventScript_James::
	trainerbattle_single TRAINER_JAMES_1, PetalburgWoods_Text_InstantlyPopularWithBugPokemon, PetalburgWoods_Text_CantBePopularIfILose, PetalburgWoods_EventScript_TryRegisterJames
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, PetalburgWoods_EventScript_JamesRematch
	setvar VAR_0x8004, TRAINER_JAMES_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_TryRegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_TryRegisterJames::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames
	release
	end

PetalburgWoods_EventScript_RegisterJames::
	msgbox PetalburgWoods_Text_IWantRematch1, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_TryRegisterJames2::
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_RegisterJames2::
	msgbox PetalburgWoods_Text_IWantRematch2, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_JamesRematch::
	trainerbattle_rematch TRAINER_JAMES_1, PetalburgWoods_Text_MyPokemonHaveGrown, PetalburgWoods_Text_CantBePopularIfLose
	msgbox PetalburgWoods_Text_IveBeenTrainingHard, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_Text_NotAOneToBeFound:
	.string "Hmmm…\n"
	.string "Not a one to be found…$"

PetalburgWoods_Text_HaveYouSeenShroomish:
	.string "Let's see... the readings say it's\n"
	.string "around here.\p"
	.string "Rift statics are unstable.\p"
	.string "If the meter spikes, we mark the spot.\p"
	.string "Oh--hey! You there!\p"
	.string "Wait... you're {PLAYER}, right?\p"
	.string "Professor Birch radioed Devon that\n"
	.string "you'd be assisting.$"

PetalburgWoods_Text_IWasGoingToAmbushYou:
	.string "Yeah. I'm working with Professor\n"
	.string "Birch.$"

PetalburgWoods_Text_DevonResearcherContinue:
	.string "Good to have you, {PLAYER}.\p"
	.string "Still, it's dangerous near an active\n"
	.string "rift.\p"
	.string "Keep a little distance while I scan.$"

PetalburgWoods_Text_AquaApproach:
	.string "There you are, Devon tech.$"

PetalburgWoods_Text_HandOverThosePapers:
	.string "Hand over the rift data.$"

PetalburgWoods_Text_DevonRefuse:
	.string "These field logs are classified.$"

PetalburgWoods_Text_PlayerDefend:
	.string "He said no. Back off.$"

PetalburgWoods_Text_YouHaveToHelpMe:
	.string "Rifts are opening. Your logs show\n"
	.string "where and when.\p"
	.string "Give me the device... or I take it.$"

PetalburgWoods_Text_DevonRequestHelp:
	.string "{PLAYER}, you're with Birch--can you\n"
	.string "cover me?$"

PetalburgWoods_Text_PlayerAccept:
	.string "I've got you.$"

PetalburgWoods_Text_NoOneCrossesTeamAqua:
	.string "Fine. I'll go through you first.$"

PetalburgWoods_Text_YoureKiddingMe:
	.string "Tch... not bad.$"

PetalburgWoods_Text_YouveGotSomeNerve:
	.string "Keep the logs... for now.\p"
	.string "We'll take the rift data in\n"
	.string "Rustboro.\p"
	.string "Count on it.$"

PetalburgWoods_Text_ThatWasAwfullyClose:
	.string "{PLAYER}, thank you.$"

PetalburgWoods_Text_DevonContinueConvo:
	.string "Are you okay?$"

PetalburgWoods_Text_DevonFine:
	.string "I'm fine. You covered me.\p"
	.string "Professor Birch said you'd help.\n"
	.string "He was right.$"

PetalburgWoods_Text_PlayerGlad:
	.string "Glad I was here.$"

PetalburgWoods_Text_DevonExplainRifts:
	.string "These are rift field logs.\p"
	.string "From spots where time feels still.\p"
	.string "Take this. It helps with rare finds.$"

PetalburgWoods_Text_ReceivedShinyCharm:
	.string "{PLAYER} received the SHINY CHARM!$"

PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro:
	.string "Please come to Devon in Rustboro.\p"
	.string "Team Aqua will try again.$"

PetalburgWoods_Text_PlayerWillGo:
	.string "I'll head there next.$"

PetalburgWoods_Text_ICantBeWastingTime:
	.string "Be careful out here.$"

PetalburgWoods_Text_YoureLoadedWithItems:
	.string "You're loaded with items.\n"
	.string "I can't give you this SHINY CHARM.$"

PetalburgWoods_Text_GoBugPokemonTeam:
	.string "I caught a whole bunch of POKéMON!\p"
	.string "Go, go, go!\n"
	.string "My BUG POKéMON team!$"

PetalburgWoods_Text_ICouldntWin:
	.string "I have all these POKéMON,\n"
	.string "but I couldn't win…$"

PetalburgWoods_Text_ImOutOfPokeBalls:
	.string "I caught a bunch of POKéMON.\n"
	.string "Now I'm out of POKé BALLS.$"

PetalburgWoods_Text_InstantlyPopularWithBugPokemon:
	.string "If you take BUG POKéMON to school,\n"
	.string "you get to be instantly popular!$"

PetalburgWoods_Text_CantBePopularIfILose:
	.string "I can't be popular if I lose.$"

PetalburgWoods_Text_PeopleRespectYou:
	.string "If you have a big BUG POKéMON,\n"
	.string "people respect you for it.$"

PetalburgWoods_Text_IWantRematch1:
	.string "I want a rematch when my BUG\n"
	.string "POKéMON grow up!\p"
	.string "I'm registering you in my POKéNAV!$"

PetalburgWoods_Text_IWantRematch2:
	.string "I want a rematch when my BUG \n"
	.string "POKéMON grow up!\p"
	.string "I'm registering you in my POKéNAV!$"

PetalburgWoods_Text_MyPokemonHaveGrown:
	.string "My BUG POKéMON have grown.\n"
	.string "I'll be popular again.$"

PetalburgWoods_Text_CantBePopularIfLose:
	.string "I can't be popular if I lose.$"

PetalburgWoods_Text_IveBeenTrainingHard:
	.string "You get to be popular if you have\n"
	.string "strong POKéMON, right?\l"
	.string "So, I've been training hard.$"

PetalburgWoods_Text_StayOutOfTallGrass:
	.string "Yo, there!\n"
	.string "Your POKéMON doing okay?\p"
	.string "If your POKéMON are weak and you want\n"
	.string "to avoid battles, you should stay out\l"
	.string "of tall grass.$"

PetalburgWoods_Text_HiddenItemsExplanation:
	.string "Sometimes, there are things on the\n"
	.string "ground even if you can't see them.\p"
	.string "That's why I always check where I'm\n"
	.string "walking.$"

PetalburgWoods_Text_TryUsingThisItem:
	.string "Oh, neat!\n"
	.string "That's the BADGE from RUSTBORO GYM!\p"
	.string "You must be a TRAINER.\n"
	.string "You should try using this item.$"

PetalburgWoods_Text_MiracleSeedExplanation:
	.string "It's a MIRACLE SEED.\n"
	.string "If a POKéMON holds that item, its\l"
	.string "GRASS-type moves become stronger.\p"
	.string "Besides MIRACLE SEED, I think there are\n"
	.string "other convenient items for POKéMON\l"
	.string "to hold.$"

PetalburgWoods_Text_TrainerTipsExperience:
	.string "TRAINER TIPS\p"
	.string "Any POKéMON that appears even once\n"
	.string "in a battle is awarded EXP Points.\p"
	.string "To raise a weak POKéMON, put it at the\n"
	.string "left of the team list.\p"
	.string "As soon as a battle starts, switch it\n"
	.string "out. It will earn EXP Points without\l"
	.string "being exposed to any harm.$"

PetalburgWoods_Text_TrainerTipsPP:
	.string "TRAINER TIPS\p"
	.string "In addition to Hit Points (HP), POKéMON\n"
	.string "have Power Points (PP) that are used to\l"
	.string "make moves during battle.\p"
	.string "If a POKéMON runs out of PP, it must be\n"
	.string "taken to a POKéMON CENTER.$"

