Route103_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route103_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route103_OnLoad
	.byte 0

Route103_OnTransition:
    call Common_EventScript_SetupRivalGfxId
    call ProfBirch_EventScript_UpdateLocation
    end

Route103_OnLoad:
	call_if_set FLAG_SYS_GAME_CLEAR, Route103_EventScript_OpenAlteringCave
	end

Route103_EventScript_OpenAlteringCave::
	setmetatile 45, 5, METATILE_General_CaveEntrance_Top, TRUE
	setmetatile 45, 6, METATILE_General_CaveEntrance_Bottom, FALSE
	return

Route103_EventScript_Rival::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route103_EventScript_BothRivals_Male
	goto_if_eq VAR_RESULT, FEMALE, Route103_EventScript_BothRivals_Female
	end

Route103_EventScript_BothRivals_Male:: @ SE = Brendan, NE = May
    @ original single-rival object no longer present
	addobject LOCALID_ROUTE103_RIVAL_MAY
	addobject LOCALID_ROUTE103_RIVAL_BRENDAN
	applymovement LOCALID_ROUTE103_RIVAL_MAY, Common_Movement_FacePlayer
	applymovement LOCALID_ROUTE103_RIVAL_BRENDAN, Common_Movement_FacePlayer
	waitmovement 0
    msgbox Route103_Text_BothIntro_SE_Brendan, MSGBOX_DEFAULT
    msgbox Route103_Text_BothIntro_NE_May, MSGBOX_DEFAULT
	msgbox Route103_Text_BothIntro_PlayerGreetBoth, MSGBOX_DEFAULT
    msgbox Route103_Text_BothIntro_SE_TestPartner_BRENDAN, MSGBOX_DEFAULT
    msgbox Route103_Text_BothIntro_NE_WatchFirst_MAY, MSGBOX_DEFAULT
    msgbox Route103_Text_BothIntro_SE_BattleNow_BRENDAN, MSGBOX_DEFAULT
    @ SE (Brendan) should be super effective vs player's starter
    switch VAR_STARTER_MON
    case 0, Route103_EventScript_StartBrendanBattleTorchic  @ Player TREECKO -> SE TORCHIC
    case 1, Route103_EventScript_StartBrendanBattleMudkip   @ Player TORCHIC -> SE MUDKIP
    case 2, Route103_EventScript_StartBrendanBattleTreecko  @ Player MUDKIP  -> SE TREECKO
    end

Route103_EventScript_AfterMayBattle::
    @ This label now unused for male path SE; retained for completeness
    msgbox Route103_Text_SE_NiceStillGotIt_MAY, MSGBOX_DEFAULT
    msgbox Route103_Text_PlayerThanks, MSGBOX_DEFAULT
    msgbox Route103_Text_NE_HealUp_BRENDAN, MSGBOX_DEFAULT
    special HealPlayerParty
    msgbox Route103_Text_NE_MyTurn_BRENDAN, MSGBOX_DEFAULT
    switch VAR_STARTER_MON
    case 0, Route103_EventScript_StartBrendanBattleMudkip_2
    case 1, Route103_EventScript_StartBrendanBattleTreecko_2
    case 2, Route103_EventScript_StartBrendanBattleTorchic_2
    end

Route103_EventScript_PostSecondBattle_Male::
    msgbox Route103_Text_NE_WhoaSharp_MAY, MSGBOX_DEFAULT
    msgbox Route103_Text_PlayerYouPushedMe, MSGBOX_DEFAULT
    msgbox Route103_Text_SE_HeadOutSearch_BRENDAN, MSGBOX_DEFAULT
    msgbox Route103_Text_NE_MeetAgain_MAY, MSGBOX_DEFAULT
    msgbox Route103_Text_SE_SomeThingsNeverChange_BRENDAN, MSGBOX_DEFAULT
    msgbox Route103_Text_NE_ReportBackLab_MAY, MSGBOX_DEFAULT
	msgbox Route103_Text_PlayerSeeYouThere, MSGBOX_DEFAULT
    @ Let both rivals walk down; first move player aside to avoid collision
    applymovement LOCALID_PLAYER, Common_Movement_WalkRight
    waitmovement 0
    applymovement LOCALID_ROUTE103_RIVAL_MAY, Route103_Movement_RivalExit2    @ upper rival goes first
    waitmovement 0
    applymovement LOCALID_ROUTE103_RIVAL_BRENDAN, Route103_Movement_RivalExit1 @ then lower rival follows
    waitmovement 0
	removeobject LOCALID_ROUTE103_RIVAL_BRENDAN
	removeobject LOCALID_ROUTE103_RIVAL_MAY
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_BothRivals_Female:: @ SE = Brendan, NE = May
    @ original single-rival object no longer present
	addobject LOCALID_ROUTE103_RIVAL_BRENDAN
	addobject LOCALID_ROUTE103_RIVAL_MAY
	applymovement LOCALID_ROUTE103_RIVAL_BRENDAN, Common_Movement_FacePlayer
	applymovement LOCALID_ROUTE103_RIVAL_MAY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Route103_Text_BothIntro_SE_Brendan, MSGBOX_DEFAULT
	msgbox Route103_Text_BothIntro_NE_May, MSGBOX_DEFAULT
	msgbox Route103_Text_BothIntro_PlayerGreetBoth, MSGBOX_DEFAULT
    msgbox Route103_Text_BothIntro_SE_TestPartner_BRENDAN, MSGBOX_DEFAULT
    msgbox Route103_Text_BothIntro_NE_WatchFirst_MAY, MSGBOX_DEFAULT
    msgbox Route103_Text_BothIntro_SE_BattleNow_BRENDAN, MSGBOX_DEFAULT
    @ SE (Brendan) should be super effective vs player's starter
    switch VAR_STARTER_MON
    case 0, Route103_EventScript_StartBrendanBattleTorchic  @ Player TREECKO -> SE TORCHIC
    case 1, Route103_EventScript_StartBrendanBattleMudkip   @ Player TORCHIC -> SE MUDKIP
    case 2, Route103_EventScript_StartBrendanBattleTreecko  @ Player MUDKIP  -> SE TREECKO
    end

Route103_EventScript_AfterBrendanBattle::
    msgbox Route103_Text_SE_NiceStillGotIt_BRENDAN, MSGBOX_DEFAULT
	msgbox Route103_Text_PlayerThanks, MSGBOX_DEFAULT
    msgbox Route103_Text_NE_HealUp_MAY, MSGBOX_DEFAULT
	special HealPlayerParty
    msgbox Route103_Text_NE_MyTurn_MAY, MSGBOX_DEFAULT
    @ NE (May) should be the remaining type (not SE), i.e., weak to player
    switch VAR_STARTER_MON
    case 0, Route103_EventScript_StartMayBattleMudkip_2    @ Player TREECKO -> NE MUDKIP
    case 1, Route103_EventScript_StartMayBattleTreecko_2   @ Player TORCHIC -> NE TREECKO
    case 2, Route103_EventScript_StartMayBattleTorchic_2   @ Player MUDKIP  -> NE TORCHIC
	end

Route103_EventScript_PostSecondBattle_Female::
    msgbox Route103_Text_NE_WhoaSharp_MAY, MSGBOX_DEFAULT
	msgbox Route103_Text_PlayerYouPushedMe, MSGBOX_DEFAULT
    msgbox Route103_Text_SE_HeadOutSearch_BRENDAN, MSGBOX_DEFAULT
    msgbox Route103_Text_NE_MeetAgain_MAY, MSGBOX_DEFAULT
    msgbox Route103_Text_SE_SomeThingsNeverChange_BRENDAN, MSGBOX_DEFAULT
    msgbox Route103_Text_NE_ReportBackLab_MAY, MSGBOX_DEFAULT
	msgbox Route103_Text_PlayerSeeYouThere, MSGBOX_DEFAULT
    @ Let both rivals walk down; first move player aside to avoid collision
    applymovement LOCALID_PLAYER, Common_Movement_WalkRight
    waitmovement 0
    applymovement LOCALID_ROUTE103_RIVAL_MAY, Route103_Movement_RivalExit2    @ upper rival goes first
    waitmovement 0
    applymovement LOCALID_ROUTE103_RIVAL_BRENDAN, Route103_Movement_RivalExit1 @ then lower rival follows
    waitmovement 0
	removeobject LOCALID_ROUTE103_RIVAL_MAY
	removeobject LOCALID_ROUTE103_RIVAL_BRENDAN
	goto Route103_EventScript_RivalEnd
	end


Route103_EventScript_StartMayBattleTreecko::
    trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TREECKO, Route103_Text_MayDefeated
    goto Route103_EventScript_AfterMayBattle
    end

Route103_EventScript_StartMayBattleTorchic::
    trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TORCHIC, Route103_Text_MayDefeated
    goto Route103_EventScript_AfterMayBattle
    end

Route103_EventScript_StartMayBattleMudkip::
    trainerbattle_no_intro TRAINER_MAY_ROUTE_103_MUDKIP, Route103_Text_MayDefeated
    goto Route103_EventScript_AfterMayBattle
    end

@ May second battle (used when Brendan was first)
Route103_EventScript_StartMayBattleTreecko_2::
    trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TREECKO, Route103_Text_MayDefeated
    goto Route103_EventScript_PostSecondBattle_Female
    end

Route103_EventScript_StartMayBattleTorchic_2::
    trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TORCHIC, Route103_Text_MayDefeated
    goto Route103_EventScript_PostSecondBattle_Female
    end

Route103_EventScript_StartMayBattleMudkip_2::
    trainerbattle_no_intro TRAINER_MAY_ROUTE_103_MUDKIP, Route103_Text_MayDefeated
    goto Route103_EventScript_PostSecondBattle_Female
    end

Route103_EventScript_StartBrendanBattleTreecko::
    trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TREECKO, Route103_Text_BrendanDefeated
    goto Route103_EventScript_AfterBrendanBattle
    end

Route103_EventScript_StartBrendanBattleTorchic::
    trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TORCHIC, Route103_Text_BrendanDefeated
    goto Route103_EventScript_AfterBrendanBattle
    end

Route103_EventScript_StartBrendanBattleMudkip::
    trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_MUDKIP, Route103_Text_BrendanDefeated
    goto Route103_EventScript_AfterBrendanBattle
    end

@ Brendan second battle (used when May was first)
Route103_EventScript_StartBrendanBattleTreecko_2::
    trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TREECKO, Route103_Text_BrendanDefeated
    goto Route103_EventScript_PostSecondBattle_Male
    end

Route103_EventScript_StartBrendanBattleTorchic_2::
    trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TORCHIC, Route103_Text_BrendanDefeated
    goto Route103_EventScript_PostSecondBattle_Male
    end

Route103_EventScript_StartBrendanBattleMudkip_2::
    trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_MUDKIP, Route103_Text_BrendanDefeated
    goto Route103_EventScript_PostSecondBattle_Male
    end

Route103_EventScript_RivalExit::
	closemessage
	goto Route103_EventScript_RivalEnd

@ (removed single-rival exit movements)
@ Route103_EventScript_RivalExitFacingNorth removed

Route103_EventScript_RivalEnd::
	setvar VAR_BIRCH_LAB_STATE, 4
	@ Keep Birch's Lab generic rival hidden; lab scene adds May/Brendan explicitly
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	setflag FLAG_DEFEATED_RIVAL_ROUTE103
	setvar VAR_OLDALE_RIVAL_STATE, 1
	clearflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Route103_Movement_RivalExitFacingNorth1:
	walk_left
	walk_down
	step_end

Route103_Movement_RivalExitFacingNorth2:
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route103_Movement_WatchRivalExitFacingNorth:
	delay_16
	delay_4
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

Route103_Movement_RivalExit1:
	@ Lower rival: walk down several steps
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route103_Movement_RivalExit2:
	@ Upper rival: jump past partner, then walk down
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route103_Movement_WatchRivalExitFacingEastOrWest:
	delay_16
	walk_in_place_faster_down
	step_end

Route103_EventScript_Boy::
	msgbox Route103_Text_ShouldHaveBroughtPotion, MSGBOX_NPC
	end

Route103_EventScript_Man::
	msgbox Route103_Text_ShortcutToOldale, MSGBOX_NPC
	end

Route103_EventScript_RouteSign::
	msgbox Route103_Text_RouteSign, MSGBOX_SIGN
	end

Route103_EventScript_Daisy::
	trainerbattle_single TRAINER_DAISY, Route103_Text_DaisyIntro, Route103_Text_DaisyDefeated
	msgbox Route103_Text_DaisyPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Amy::
	trainerbattle_double TRAINER_AMY_AND_LIV_1, Route103_Text_AmyIntro, Route103_Text_AmyDefeated, Route103_Text_AmyNotEnoughPokemon, Route102_EventScript_AmyRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_AmyRematch
	msgbox Route103_Text_AmyPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_AmyRegisterMatchCallAfterBattle::
	msgbox Route103_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

Route102_EventScript_AmyRematch::
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, Route103_Text_AmyRematchIntro, Route103_Text_AmyRematchDefeated, Route103_Text_AmyRematchNotEnoughPokemon
	msgbox Route103_Text_AmyRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Liv::
	trainerbattle_double TRAINER_AMY_AND_LIV_1, Route103_Text_LivIntro, Route103_Text_LivDefeated, Route103_Text_LivNotEnoughPokemon, Route102_EventScript_LivRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_LivRematch
	msgbox Route103_Text_LivPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_LivRegisterMatchCallAfterBattle::
	msgbox Route103_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

Route102_EventScript_LivRematch::
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, Route103_Text_LivRematchIntro, Route103_Text_LivRematchDefeated, Route103_Text_LivRematchNotEnoughPokemon
	msgbox Route103_Text_LivRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Andrew::
	trainerbattle_single TRAINER_ANDREW, Route103_Text_AndrewIntro, Route103_Text_AndrewDefeated
	msgbox Route103_Text_AndrewPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Miguel::
	trainerbattle_single TRAINER_MIGUEL_1, Route103_Text_MiguelIntro, Route103_Text_MiguelDefeated, Route102_EventScript_MiguelRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route103_EventScript_MiguelRematch
	msgbox Route103_Text_MiguelPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_MiguelRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route103_Text_MiguelRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_MIGUEL_1
	release
	end

Route103_EventScript_MiguelRematch::
	trainerbattle_rematch TRAINER_MIGUEL_1, Route103_Text_MiguelRematchIntro, Route103_Text_MiguelRematchDefeated
	msgbox Route103_Text_MiguelRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Marcos::
	trainerbattle_single TRAINER_MARCOS, Route103_Text_MarcosIntro, Route103_Text_MarcosDefeated
	msgbox Route103_Text_MarcosPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Rhett::
	trainerbattle_single TRAINER_RHETT, Route103_Text_RhettIntro, Route103_Text_RhettDefeated
	msgbox Route103_Text_RhettPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Pete::
	trainerbattle_single TRAINER_PETE, Route103_Text_PeteIntro, Route103_Text_PeteDefeated
	msgbox Route103_Text_PetePostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Isabelle::
	trainerbattle_single TRAINER_ISABELLE, Route103_Text_IsabelleIntro, Route103_Text_IsabelleDefeated
	msgbox Route103_Text_IsabellePostBattle, MSGBOX_AUTOCLOSE
	end

Route103_Text_MayRoute103Pokemon:
	.string "MAY: {PLAYER}! You made it.\p"
	.string "MAY: We're logging statics for\n"
	.string "PROF. BIRCH.\p"
	.string "{PLAYER}: Good to see you.\p"
	.string "MAY: Let's test your partner.\p"
	.string "MAY: All right - battle me!$"

Route103_Text_MayLetsBattle:
	.string "MAY: Don't hold back.\p"
	.string "{PLAYER}: Wouldn't dream of it.$"

Route103_Text_MayDefeated:
	.string "MAY: Nice! You've still got it.$"

Route103_Text_MayTimeToHeadBack:
	.string "MAY: We'll head out and search all\n"
	.string "over HOENN.\p"
	.string "MAY: We'll meet again - count on it.\p"
	.string "MAY: Some things never change.\p"
	.string "MAY: Let's report back to the LAB.\p"
	.string "{PLAYER}: Right. See you there.$"

Route103_Text_BrendanRoute103Pokemon:
	.string "BRENDAN: {PLAYER}! You made it.\p"
	.string "BRENDAN: We're logging statics for\n"
	.string "PROF. BIRCH.\p"
	.string "{PLAYER}: Good to see you.\p"
	.string "BRENDAN: Let's test your partner.\p"
	.string "BRENDAN: All right - battle me!$"

Route103_Text_BrendanLetsBattle:
	.string "BRENDAN: Don't hold back.\p"
	.string "{PLAYER}: Wouldn't dream of it.$"

Route103_Text_BrendanDefeated:
	.string "BRENDAN: Nice! You've still got it.$"

Route103_Text_BrendanTimeToHeadBack:
	.string "BRENDAN: We'll head out and search all\n"
	.string "over HOENN.\p"
	.string "BRENDAN: We'll meet again - count on it.\p"
	.string "BRENDAN: Some things never change.\p"
	.string "BRENDAN: Let's report back to the LAB.\p"
	.string "{PLAYER}: Right. See you there.$"

Route103_Text_ShouldHaveBroughtPotion:
	.string "My POKéMON is staggeringly tired…\n"
	.string "I should have brought a POTION…$"

Route103_Text_ShortcutToOldale:
	.string "If you cross the sea from here,\n"
	.string "Shortcut to\n"
	.string "OLDALE TOWN.\p"
	.string "Fufufu, that's\n"
	.string "useful, isn't it?$"

Route103_Text_RouteSign:
	.string "ROUTE 103\n"
	.string "{DOWN_ARROW} OLDALE TOWN$"

@ Additional text for dual-rival flow
Route103_Text_BothIntro_SE_May:
	.string "MAY: {PLAYER}! You made it.$"

Route103_Text_BothIntro_NE_Brendan:
	.string "BRENDAN: We're logging statics for\n"
	.string "PROF. BIRCH.$"

Route103_Text_BothIntro_SE_Brendan:
	.string "BRENDAN: {PLAYER}! You made it.$"

Route103_Text_BothIntro_NE_May:
	.string "MAY: We're logging statics for\n"
	.string "PROF. BIRCH.$"

Route103_Text_BothIntro_PlayerGreetBoth:
	.string "{PLAYER}: Good to see you both.\p"
	.string "{PLAYER}: Surprised?\n"
	.string "PROF. BIRCH gave me all three\n"
	.string "starters after that attack.$"

Route103_Text_BothIntro_SE_TestPartner_MAY:
	.string "MAY: All three? Wow... Birch never\n"
	.string "does that. He must've trusted you.\p"
	.string "Let's see how you handle them.$"

Route103_Text_BothIntro_SE_TestPartner_BRENDAN:
	.string "BRENDAN: All three? That's crazy!\n"
	.string "Birch must've been really shaken.\p"
	.string "Let's see how you handle them.$"

Route103_Text_BothIntro_NE_WatchFirst_MAY:
	.string "MAY: I'll watch first. I'm still\n"
	.string "running numbers.$"

Route103_Text_BothIntro_NE_WatchFirst_BRENDAN:
	.string "BRENDAN: I'll watch first. I'm still\n"
	.string "running numbers.$"

Route103_Text_BothIntro_SE_BattleNow_MAY:
	.string "MAY: All right - battle me!$"

Route103_Text_BothIntro_SE_BattleNow_BRENDAN:
	.string "BRENDAN: All right - battle me!$"

Route103_Text_SE_NiceStillGotIt_MAY:
	.string "MAY: Nice! You've still got it.$"

Route103_Text_SE_NiceStillGotIt_BRENDAN:
	.string "BRENDAN: Nice! You've still got it.$"

Route103_Text_PlayerThanks:
	.string "{PLAYER}: Thanks.$"

Route103_Text_NE_HealUp_MAY:
	.string "MAY: Here, heal up before round two.\n"
	.string "Birch said your safety comes first.$"

Route103_Text_NE_HealUp_BRENDAN:
	.string "BRENDAN: Heal up first.\n"
	.string "Birch was right - you'll need it.$"

Route103_Text_NE_MyTurn_BRENDAN:
    .string "BRENDAN: My turn.$"

Route103_Text_NE_MyTurn_MAY:
    .string "MAY: My turn.$"

Route103_Text_NE_WhoaSharp_MAY:
	.string "MAY: Whoa...\n"
	.string "You handled all of us with ease.$"

Route103_Text_NE_WhoaSharp_BRENDAN:
	.string "BRENDAN: Whoa. You're sharp as ever.$"

Route103_Text_PlayerYouPushedMe:
	.string "{PLAYER}: You two pushed me... but I\n"
	.string "needed that.$"

Route103_Text_SE_HeadOutSearch_MAY:
	.string "MAY: We'll head out and search\n"
	.string "all over HOENN.$"

Route103_Text_SE_HeadOutSearch_BRENDAN:
	.string "BRENDAN: Whatever that thing was\n"
	.string "on Route 101 - it wasn't normal.$"

Route103_Text_NE_MeetAgain_MAY:
	.string "MAY: Right. We should tell Birch\n"
	.string "exactly what happened.$"

Route103_Text_NE_MeetAgain_BRENDAN:
	.string "BRENDAN: We'll meet again - count on it.$"

Route103_Text_SE_SomeThingsNeverChange_MAY:
	.string "MAY: Some things never change.$"

Route103_Text_SE_SomeThingsNeverChange_BRENDAN:
	.string "BRENDAN: Some things never change.\n"
	.string "Let's regroup at the lab.$"

Route103_Text_NE_ReportBackLab_MAY:
	.string "MAY: Let's report back to the LAB.$"

Route103_Text_NE_ReportBackLab_BRENDAN:
	.string "BRENDAN: Let's report back to the LAB.$"

Route103_Text_PlayerSeeYouThere:
	.string "{PLAYER}: Right. See you there.$"
