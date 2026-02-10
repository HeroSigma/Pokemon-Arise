Route101_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route101_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route101_OnFrame
	.byte 0

Route101_OnTransition:
	call ProfBirch_EventScript_UpdateLocation
	end

Route101_OnFrame:
	map_script_2 VAR_ROUTE101_STATE, 0, Route101_EventScript_HideMapNamePopup
	.2byte 0

Route101_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_ROUTE101_STATE, 1
	end

Route101_EventScript_StartBirchRescue::
    lockall
    playbgm MUS_HELP, TRUE
    @ Disable random wild encounters during the rescue scene
    setflag FLAG_TEMP_5
    msgbox Route101_Text_HelpMe, MSGBOX_DEFAULT
    closemessage
    setobjectxy LOCALID_ROUTE101_BIRCH, 0, 15
    setobjectxy LOCALID_ROUTE101_ZIGZAGOON, 0, 16
    applymovement LOCALID_PLAYER, Route101_Movement_EnterScene
    applymovement LOCALID_ROUTE101_BIRCH, Route101_Movement_BirchRunAway1
    applymovement LOCALID_ROUTE101_ZIGZAGOON, Route101_Movement_ZigzagoonChase1
    waitmovement 0
    applymovement LOCALID_ROUTE101_ZIGZAGOON, Route101_Movement_ZigzagoonChaseInCircles
    applymovement LOCALID_ROUTE101_BIRCH, Route101_Movement_BirchRunInCircles
    waitmovement 0
    applymovement LOCALID_ROUTE101_BIRCH, Common_Movement_WalkInPlaceFasterRight
    waitmovement 0
    applymovement LOCALID_ROUTE101_ZIGZAGOON, Route101_Movement_ZigzagoonFaceBirch
    applymovement LOCALID_ROUTE101_BIRCH, Route101_Movement_BirchFaceZigzagoon
    waitmovement 0
    msgbox Route101_Text_BirchUseOneQuick, MSGBOX_DEFAULT
    closemessage
    // Allow player to choose a starter from the bag as in vanilla
    setvar VAR_ROUTE101_STATE, 2
    releaseall
    end

Route101_EventScript_PreventExitSouth::
	lockall
	msgbox Route101_Text_DontLeaveMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Route101_Movement_PreventExitSouth
	waitmovement 0
	releaseall
	end

Route101_EventScript_PreventExitWest::
	lockall
	msgbox Route101_Text_DontLeaveMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Route101_Movement_PreventExitWest
	waitmovement 0
	releaseall
	end

Route101_EventScript_PreventExitNorth::
	lockall
	msgbox Route101_Text_DontLeaveMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Route101_Movement_PreventExitNorth
	waitmovement 0
	releaseall
	end

Route101_Movement_PreventExitSouth:
	walk_up
	step_end

Route101_Movement_PreventExitWest:
	walk_right
	step_end

Route101_Movement_PreventExitNorth:
	walk_down
	step_end

Route101_Movement_ZigzagoonChaseInCircles:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	step_end

Route101_Movement_ZigzagoonChase1:
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

@ Leftover data? This command is unused.
	step_end

Route101_Movement_ZigzagoonFaceBirch:
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	step_end

Route101_Movement_EnterScene:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_in_place_faster_left
	step_end

Route101_Movement_BirchRunInCircles:
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route101_Movement_BirchRunAway1:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	step_end

@ Leftover data? This command is unused.
	step_end

Route101_Movement_BirchFaceZigzagoon:
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	step_end

Route101_Movement_Unused1:
	walk_up
	walk_up
	step_end

Route101_Movement_Unused2:
	walk_up
	walk_left
	walk_up
	step_end

Route101_EventScript_Youngster::
	msgbox Route101_Text_TakeTiredPokemonToPokeCenter, MSGBOX_NPC
	end

Route101_EventScript_Boy::
	msgbox Route101_Text_WildPokemonInTallGrass, MSGBOX_NPC
	end

Route101_EventScript_RouteSign::
	msgbox Route101_Text_RouteSign, MSGBOX_SIGN
	end

Route101_EventScript_BirchsBag::
    lock
    faceplayer
    // If a starter was already taken, prevent re-use of the bag
    goto_if_set FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG, Route101_EventScript_BirchsBag_Empty
    setflag FLAG_SYS_POKEMON_GET
    // Stay in place; present simple starter choice without moving the player
    call Route101_EventScript_SelectStarter
    // Hide the bag; let the player confront the hostile Pokémon
    setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
    // Allow movement toward the hostile Pokémon by disabling the intro fences
    // (prevents Birch from stopping you with "Don't leave me like this!")
    setvar VAR_ROUTE101_STATE, 3
    releaseall
    end

Route101_EventScript_BirchsBag_Empty:
    msgbox Route101_Text_BirchsBagEmpty, MSGBOX_SIGN
    releaseall
    end

// Simple starter selection loop (TREECKO -> TORCHIC -> MUDKIP)
Route101_EventScript_SelectStarter::
    msgbox Route101_Text_ChooseTreecko, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, YES, Route101_EventScript_GiveTreecko
    msgbox Route101_Text_ChooseTorchic, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, YES, Route101_EventScript_GiveTorchic
    msgbox Route101_Text_ChooseMudkip, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, YES, Route101_EventScript_GiveMudkip
    // If declined all, ask again from the start
    goto Route101_EventScript_SelectStarter

Route101_EventScript_GiveTreecko:
    givemon SPECIES_TREECKO, 5
    setvar VAR_STARTER_MON, 0 @ Treecko
    bufferleadmonspeciesname STR_VAR_1
    playfanfare MUS_OBTAIN_ITEM
    message Route101_Text_PlayerReceivedStarter
    waitmessage
    waitfanfare
    closemessage
    return

Route101_EventScript_GiveTorchic:
    givemon SPECIES_TORCHIC, 5
    setvar VAR_STARTER_MON, 1 @ Torchic
    bufferleadmonspeciesname STR_VAR_1
    playfanfare MUS_OBTAIN_ITEM
    message Route101_Text_PlayerReceivedStarter
    waitmessage
    waitfanfare
    closemessage
    return

Route101_EventScript_GiveMudkip:
    givemon SPECIES_MUDKIP, 5
    setvar VAR_STARTER_MON, 2 @ Mudkip
    bufferleadmonspeciesname STR_VAR_1
    playfanfare MUS_OBTAIN_ITEM
    message Route101_Text_PlayerReceivedStarter
    waitmessage
    waitfanfare
    closemessage
    return

// Interact with the hostile Pokémon to trigger the overwhelming scene
Route101_EventScript_ZoroarkTrigger::
    lockall
    // Birch calls out as you approach
    msgbox Route101_Text_BirchStarterHint, MSGBOX_DEFAULT
    closemessage
    // Hisuian Zoroark cries out as you approach
    waitse
    playmoncry SPECIES_ZOROARK_HISUI, CRY_MODE_ENCOUNTER
    // Subtle jolt timed with the cry
    setvar VAR_0x8004, 1   @ vertical pan on
    setvar VAR_0x8005, 1   @ horizontal pan on
    setvar VAR_0x8006, 4   @ num shakes
    setvar VAR_0x8007, 2   @ delay per shake
    special ShakeCamera
    waitstate
    waitmoncry
    call Route101_EventScript_UnwinnableEncounter
    releaseall
    end

// Simulated overwhelming encounter + rescue voice, then proceed to lab
Route101_EventScript_UnwinnableEncounter::
    // The strange Pokémon remains on the field during this sequence
    fadescreen FADE_TO_BLACK
    delay 20
    // Glitch pulse on the hostile Pokémon (palette + sound)
    playse SE_MUGSHOT
    delay 30
    fadescreen FADE_FROM_BLACK
    // Brief shake to sell the surge
    setvar VAR_0x8004, 1
    setvar VAR_0x8005, 1
    setvar VAR_0x8006, 5
    setvar VAR_0x8007, 3
    special ShakeCamera
    waitstate
    msgbox Route101_Text_PlayerOverwhelmed, MSGBOX_DEFAULT
    closemessage
    // Voice intervenes, repel the foe
    fadescreen FADE_TO_BLACK
    delay 15
    playse SE_THUNDER
    delay 20
    fadescreen FADE_FROM_BLACK
    // A low rumble just before the voice speaks
    setvar VAR_0x8004, 1
    setvar VAR_0x8005, 1
    setvar VAR_0x8006, 4
    setvar VAR_0x8007, 2
    special ShakeCamera
    waitstate
    msgbox Route101_Text_VoiceNotYet, MSGBOX_DEFAULT
    closemessage
    // Enemy flees under unseen force
    // A defiant cry, then the force repels it completely
    waitse
    playmoncry SPECIES_ZOROARK_HISUI, CRY_MODE_ENCOUNTER
    waitmoncry
    setvar VAR_0x8004, 1
    setvar VAR_0x8005, 1
    setvar VAR_0x8006, 5
    setvar VAR_0x8007, 3
    special ShakeCamera
    waitstate
    // Spin in place as if being twisted by the rift
    applymovement LOCALID_ROUTE101_ZIGZAGOON, Route101_Movement_ZoroarkSpin
    waitmovement 0
    playse SE_WARP_OUT
    removeobject LOCALID_ROUTE101_ZIGZAGOON
    delay 20
    // Aftermath dialogue
    msgbox Route101_Text_PlayerVoiceProtecting, MSGBOX_DEFAULT
    msgbox Route101_Text_PlayerUneasyFeeling, MSGBOX_DEFAULT
    msgbox Route101_Text_BirchWhatWasThat, MSGBOX_DEFAULT
    msgbox Route101_Text_BirchNoMatterToLab, MSGBOX_DEFAULT
    // Birch rushes to the player and insists you take the remaining starters
    call Route101_EventScript_BirchGivesRemainingStarters
    // Ensure no message box is active before transitioning
    closemessage
    // Prepare lab state similar to saved flow
    special HealPlayerParty
    clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
    setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
    setflag FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE
    setvar VAR_BIRCH_LAB_STATE, 2
    clearflag FLAG_HIDE_MAP_NAME_POPUP
    checkplayergender
    call_if_eq VAR_RESULT, MALE, Route101_EventScript_HideMayInBedroom
    call_if_eq VAR_RESULT, FEMALE, Route101_EventScript_HideBrendanInBedroom
    // Re-enable random wild encounters now that the scene is over
    clearflag FLAG_TEMP_5
    warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 6, 5
    waitstate
    return

// Birch approaches and gives the remaining two starters
Route101_EventScript_BirchGivesRemainingStarters::
    applymovement LOCALID_ROUTE101_BIRCH, Route101_Movement_BirchApproachPlayer
    waitmovement 0
    lock
    faceplayer
    bufferleadmonspeciesname STR_VAR_1
    msgbox Route101_Text_BirchChoseMon, MSGBOX_DEFAULT
    msgbox Route101_Text_BirchNotEnough, MSGBOX_DEFAULT
    msgbox Route101_Text_BirchTakeRemaining, MSGBOX_DEFAULT
    // Give the remaining two depending on VAR_STARTER_MON (0=Treecko, 1=Torchic, 2=Mudkip)
    switch VAR_STARTER_MON
    case 0, Route101_EventScript_GiveTorchicAndMudkip
    case 1, Route101_EventScript_GiveTreeckoAndMudkip
    case 2, Route101_EventScript_GiveTreeckoAndTorchic
    return

Route101_EventScript_GiveTreeckoAndMudkip:
    givemon SPECIES_TREECKO, 5
    bufferspeciesname STR_VAR_1, SPECIES_TREECKO
    playfanfare MUS_OBTAIN_ITEM
    message Route101_Text_PlayerReceivedStarter
    waitmessage
    waitfanfare
    givemon SPECIES_MUDKIP, 5
    bufferspeciesname STR_VAR_1, SPECIES_MUDKIP
    playfanfare MUS_OBTAIN_ITEM
    message Route101_Text_PlayerReceivedStarter
    waitmessage
    waitfanfare
    goto Route101_EventScript_GiveRemainingStarters_End

Route101_EventScript_GiveTreeckoAndTorchic:
    givemon SPECIES_TREECKO, 5
    bufferspeciesname STR_VAR_1, SPECIES_TREECKO
    playfanfare MUS_OBTAIN_ITEM
    message Route101_Text_PlayerReceivedStarter
    waitmessage
    waitfanfare
    givemon SPECIES_TORCHIC, 5
    bufferspeciesname STR_VAR_1, SPECIES_TORCHIC
    playfanfare MUS_OBTAIN_ITEM
    message Route101_Text_PlayerReceivedStarter
    waitmessage
    waitfanfare
    goto Route101_EventScript_GiveRemainingStarters_End

Route101_EventScript_GiveTorchicAndMudkip:
    givemon SPECIES_TORCHIC, 5
    bufferspeciesname STR_VAR_1, SPECIES_TORCHIC
    playfanfare MUS_OBTAIN_ITEM
    message Route101_Text_PlayerReceivedStarter
    waitmessage
    waitfanfare
    givemon SPECIES_MUDKIP, 5
    bufferspeciesname STR_VAR_1, SPECIES_MUDKIP
    playfanfare MUS_OBTAIN_ITEM
    message Route101_Text_PlayerReceivedStarter
    waitmessage
    waitfanfare
    goto Route101_EventScript_GiveRemainingStarters_End

Route101_EventScript_GiveRemainingStarters_End:
    msgbox Route101_Text_PlayerAllThreeInner, MSGBOX_DEFAULT
    release
    return

Route101_EventScript_HideMayInBedroom::
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	return

Route101_EventScript_HideBrendanInBedroom::
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	return

Route101_Movement_BirchApproachPlayer:
    walk_right
    face_down
    step_end

// Simulated spin (rotate facing) for Zoroark before vanishing
Route101_Movement_ZoroarkSpin:
    // Start slow
    face_right
    delay_16
    face_down
    delay_16
    face_left
    delay_16
    face_up
    delay_16
    // Then pick up speed
    face_right
    delay_8
    face_down
    delay_8
    face_left
    delay_8
    face_up
    delay_8
    // Final rapid spin
    face_right
    delay_4
    face_down
    delay_4
    face_left
    delay_4
    face_up
    delay_4
    step_end

Route101_Text_HelpMe:
    .string "BIRCH: H-Help!\n"
    .string "Somebody- please!\p"
    .string "$"

Route101_Text_BirchUseOneQuick:
    .string "BIRCH: {PLAYER}! Quick-\n"
    .string "there’s no time!\p"
    .string "Use one of my\n"
    .string "POKéMON!$"

Route101_Text_PlayerOverwhelmed:
    .string "{COLOR GREEN}{PLAYER}: (This power… I can’t stop it…!){COLOR DARK_GRAY}$"

Route101_Text_VoiceNotYet:
    .string "{COLOR LIGHT_RED}??? : …Not yet. Your path is not ready.{COLOR DARK_GRAY}$"

Route101_Text_PlayerVoiceProtecting:
    .string "{COLOR GREEN}{PLAYER}: That voice… it was protecting me?{COLOR DARK_GRAY}$"

Route101_Text_PlayerUneasyFeeling:
    .string "{COLOR GREEN}{PLAYER}: (Is this the uneasy feeling I’ve had…\n"
    .string "or something else entirely?){COLOR DARK_GRAY}$"

Route101_Text_BirchWhatWasThat:
    .string "BIRCH: What was that\n"
    .string "just now? That\n"
    .string "creature-\p"
    .string "I've never seen\n"
    .string "anything like it in\n"
    .string "HOENN.\p"
    .string "BIRCH: And that\n"
    .string "voice… Who was it\n"
    .string "speaking to?\n"
    .string "Who… are you,\n"
    .string "{PLAYER}?$"

Route101_Text_BirchNoMatterToLab:
    .string "BIRCH: No matter.\n"
    .string "Quick- let’s get\n"
    .string "to my lab before\n"
    .string "anything else\n"
    .string "happens!$"

Route101_Text_BirchStarterHint:
    .string "BIRCH: Steady now. Keep your partner close.$"

Route101_Text_ChooseTreecko:
    .string "BIRCH: TREECKO will\n"
    .string "stand with you.\n"
    .string "Will you take\n"
    .string "TREECKO?$"

Route101_Text_ChooseTorchic:
    .string "BIRCH: TORCHIC burns\n"
    .string "bright with courage.\n"
    .string "Will you take\n"
    .string "TORCHIC?$"

Route101_Text_ChooseMudkip:
    .string "BIRCH: MUDKIP is\n"
    .string "steady and strong.\n"
    .string "Will you take\n"
    .string "MUDKIP?$"

Route101_Text_PlayerReceivedStarter:
    .string "{PLAYER} received {STR_VAR_1}!$"

Route101_Text_DontLeaveMe:
	.string "Wh-Where are you going?!\n"
	.string "Don't leave me like this!$"

// Post-Zoroark gift scene
Route101_Text_BirchChoseMon:
    .string "BIRCH: {PLAYER}! You chose {STR_VAR_1}, didn’t you?$"

Route101_Text_BirchNotEnough:
    .string "BIRCH: But after what we just saw… I don’t\n"
    .string "think {STR_VAR_1} alone will be enough.$"

Route101_Text_BirchTakeRemaining:
    .string "BIRCH: Take the remaining two as well. If this\n"
    .string "happens again, you’ll need every safeguard possible.$"

Route101_Text_PlayerAllThreeInner:
    .string "{COLOR GREEN}{PLAYER}: (All three…? Birch must be truly shaken.\n"
    .string "This isn’t how it’s supposed to begin.){COLOR DARK_GRAY}$"

Route101_Text_YouSavedMe:
    .string "PROF. BIRCH: Whew! Nice work!\p"
    .string "PROF. BIRCH: {PLAYER}? From LITTLEROOT...\p"
    .string "is that you?\p"
    .string "PLAYER: It's me, Professor.\p"
    .string "PROF. BIRCH: After eight years...\p"
    .string "welcome back.\p"
    .string "PROF. BIRCH: This isn't safe. The wild\p"
    .string "POKéMON are on edge.\p"
    .string "PROF. BIRCH: Let's head to the\p"
    .string "POKéMON LAB and talk there.\p"
    .string "PLAYER: Okay.\p"
    .string "PROF. BIRCH: Right. This way.$"

Route101_Text_TakeTiredPokemonToPokeCenter:
	.string "If POKéMON get tired, take them to\n"
	.string "a POKéMON CENTER.\p"
	.string "There's a POKéMON CENTER in OLDALE\n"
	.string "TOWN right close by.$"

Route101_Text_WildPokemonInTallGrass:
	.string "Wild POKéMON will jump out at you in\n"
	.string "tall grass.\p"
	.string "If you want to catch POKéMON, you have\n"
	.string "to go into the tall grass and search.$"

Route101_Text_RouteSign:
    .string "ROUTE 101\n"
    .string "{UP_ARROW} OLDALE TOWN$"

Route101_Text_BirchsBagEmpty:
    .string "The bag is empty.$"
