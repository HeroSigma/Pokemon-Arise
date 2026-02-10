@ QoL Scientist event script (no Poryscript)

EventScript_QoLScientist::
	lock
	faceplayer
	callnative Script_QoL_Msg_Hello
	msgbox gStringVar4 MSGBOX_DEFAULT

.MainLoop:
    closemessage
    multichoice 15, 1, MULTI_QOL_MAIN_PG1, FALSE
    switch VAR_RESULT
        case 0, .DoNature
        case 1, .DoEVs
        case 2, .DoIVs
        case 3, .DoAbility
        case 4, .DoBall
        case 5, .DoHidden
        case 6, .DoTera
        case 7, .MainLoop2   @ NEXT >
        case 8, .End         @ Exit
        case MULTI_B_PRESSED, .MainLoop
        goto .MainLoop

.MainLoop2:
    closemessage
    multichoice 15, 1, MULTI_QOL_MAIN_PG2, FALSE
    switch VAR_RESULT
        case 0, .DoDmax
        case 1, .DoGmax
        case 2, .MainLoop    @ < BACK
        case 3, .End         @ Exit
        case MULTI_B_PRESSED, .MainLoop
        goto .MainLoop

.DoNature:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .MainLoop
    copyvar VAR_0x8006, VAR_0x8004
    callnative Script_QoL_Msg_NatureInfo
    msgbox gStringVar4, MSGBOX_DEFAULT
    msgbox gText_QoLChooseNature, MSGBOX_DEFAULT
    @ Build a scrollable 25-item menu using the debug nature strings (ordered 0..24)
    dynmultipush Debug_EventScript_ChangeNature_Text_Hardy,   0
    dynmultipush Debug_EventScript_ChangeNature_Text_Lonely,  1
    dynmultipush Debug_EventScript_ChangeNature_Text_Brave,   2
    dynmultipush Debug_EventScript_ChangeNature_Text_Adamant, 3
    dynmultipush Debug_EventScript_ChangeNature_Text_Naughty, 4
    dynmultipush Debug_EventScript_ChangeNature_Text_Bold,    5
    dynmultipush Debug_EventScript_ChangeNature_Text_Docile,  6
    dynmultipush Debug_EventScript_ChangeNature_Text_Relaxed, 7
    dynmultipush Debug_EventScript_ChangeNature_Text_Impish,  8
    dynmultipush Debug_EventScript_ChangeNature_Text_Lax,     9
    dynmultipush Debug_EventScript_ChangeNature_Text_Timid,   10
    dynmultipush Debug_EventScript_ChangeNature_Text_Hasty,   11
    dynmultipush Debug_EventScript_ChangeNature_Text_Serious, 12
    dynmultipush Debug_EventScript_ChangeNature_Text_Jolly,   13
    dynmultipush Debug_EventScript_ChangeNature_Text_Naive,   14
    dynmultipush Debug_EventScript_ChangeNature_Text_Modest,  15
    dynmultipush Debug_EventScript_ChangeNature_Text_Mild,    16
    dynmultipush Debug_EventScript_ChangeNature_Text_Quiet,   17
    dynmultipush Debug_EventScript_ChangeNature_Text_Bashful, 18
    dynmultipush Debug_EventScript_ChangeNature_Text_Rash,    19
    dynmultipush Debug_EventScript_ChangeNature_Text_Calm,    20
    dynmultipush Debug_EventScript_ChangeNature_Text_Gentle,  21
    dynmultipush Debug_EventScript_ChangeNature_Text_Sassy,   22
    dynmultipush Debug_EventScript_ChangeNature_Text_Careful, 23
    dynmultipush Debug_EventScript_ChangeNature_Text_Quirky,  24
    dynmultistack 15, 1, FALSE, 7, FALSE, 0, NULL
    compare VAR_RESULT, MULTI_B_PRESSED
    goto_if_eq .MainLoop
    copyvar VAR_0x8000, VAR_RESULT
    callnative Script_QoL_Msg_ConfirmNature
    msgbox gStringVar4, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, .MainLoop
    callnative Script_QoL_SetNature
    call .ResultMsg
    goto .MainLoop

.DoEVs:
        setvar VAR_0x8004, SCROLL_MULTI_QOL_EVS
        special ShowScrollableMultichoice
        waitstate
        switch VAR_RESULT
                case 0, .EV_Preset
                case 1, .EV_Quick
                case 2, .EV_Full
                case 3, .EV_Clear
                case 4, .MainLoop
                case MULTI_B_PRESSED, .MainLoop

.EV_Preset:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .DoEVs
    copyvar VAR_0x8006, VAR_0x8004
    callnative Script_QoL_Msg_EVsInfo
    msgbox gStringVar4, MSGBOX_DEFAULT
    callnative Script_QoL_EVs_PresetByNature
    call .ResultMsg
    goto .DoEVs

.EV_Quick:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .DoEVs
    copyvar VAR_0x8006, VAR_0x8004
    callnative Script_QoL_Msg_EVsInfo
    msgbox gStringVar4, MSGBOX_DEFAULT
    msgbox gText_QoLPickStat1, MSGBOX_DEFAULT
    setvar VAR_0x8004, SCROLL_MULTI_QOL_STATS
    special ShowScrollableMultichoice
    waitstate
    compare VAR_RESULT, 6
    goto_if_eq .DoEVs
    compare VAR_RESULT, MULTI_B_PRESSED
    goto_if_eq .DoEVs
    callnative Script_QoL_MapStatSelection
    copyvar VAR_0x8000, VAR_RESULT
        msgbox gText_QoLPickStat2, MSGBOX_DEFAULT
        setvar VAR_0x8004, SCROLL_MULTI_QOL_STATS
        special ShowScrollableMultichoice
        waitstate
        compare VAR_RESULT, 6
        goto_if_eq .DoEVs
        compare VAR_RESULT, MULTI_B_PRESSED
        goto_if_eq .DoEVs
        callnative Script_QoL_MapStatSelection
        copyvar VAR_0x8001, VAR_RESULT
        callnative Script_QoL_EVs_QuickCustom
        call .ResultMsg
        goto .DoEVs

.EV_Full:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .DoEVs
    copyvar VAR_0x8006, VAR_0x8004
    callnative Script_QoL_Msg_EVsInfo
    msgbox gStringVar4, MSGBOX_DEFAULT
    @ Seed spinners with current EVs
    callnative Script_QoL_LoadCurrentEVs

    @ Prompt HP
    copyvar VAR_0x8002, VAR_0x8000   @ initial = current HP
    setvar VAR_0x8000, 0             @ min
    setvar VAR_0x8001, 252           @ max
    callnative Script_QoL_PromptNumber
    copyvar VAR_0x8000, VAR_RESULT   @ store new HP

    @ Prompt ATK
    copyvar VAR_0x8002, VAR_0x8001   @ initial = current ATK
    setvar VAR_0x8000, 0
    setvar VAR_0x8001, 252
    callnative Script_QoL_PromptNumber
    copyvar VAR_0x8001, VAR_RESULT   @ store new ATK

    @ Prompt DEF
    copyvar VAR_0x8002, VAR_0x8002   @ initial = current DEF
    setvar VAR_0x8000, 0
    setvar VAR_0x8001, 252
    callnative Script_QoL_PromptNumber
    copyvar VAR_0x8002, VAR_RESULT   @ store new DEF

    @ Prompt SPE (Speed)
    copyvar VAR_0x8002, VAR_0x8003   @ initial = current SPE
    setvar VAR_0x8000, 0
    setvar VAR_0x8001, 252
    callnative Script_QoL_PromptNumber
    copyvar VAR_0x8003, VAR_RESULT   @ store new SPE

    @ Prompt SPA
    copyvar VAR_0x8002, VAR_0x8004   @ initial = current SPA
    setvar VAR_0x8000, 0
    setvar VAR_0x8001, 252
    callnative Script_QoL_PromptNumber
    copyvar VAR_0x8004, VAR_RESULT   @ store new SPA

    @ Prompt SPD
    copyvar VAR_0x8002, VAR_0x8005   @ initial = current SPD
    setvar VAR_0x8000, 0
    setvar VAR_0x8001, 252
    callnative Script_QoL_PromptNumber
    copyvar VAR_0x8005, VAR_RESULT   @ store new SPD

	callnative Script_QoL_EVs_CustomFull
	call .ResultMsg
	goto .DoEVs

.EV_Clear:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .DoEVs
    copyvar VAR_0x8006, VAR_0x8004
    callnative Script_QoL_EVs_Clear
    call .ResultMsg
    goto .DoEVs

.DoIVs:
        setvar VAR_0x8004, SCROLL_MULTI_QOL_IVS
        special ShowScrollableMultichoice
        waitstate
        switch VAR_RESULT
                case 0, .IV_31
                case 1, .IV_TR
                case 2, .IV_SetStat
                case 3, .MainLoop
                case MULTI_B_PRESSED, .MainLoop

.IV_31:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .DoIVs
    copyvar VAR_0x8006, VAR_0x8004
    callnative Script_QoL_Msg_IVsInfo
    msgbox gStringVar4, MSGBOX_DEFAULT
    callnative Script_QoL_IVs_Perfect31
    call .ResultMsg
    goto .DoIVs

.IV_TR:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .DoIVs
    copyvar VAR_0x8006, VAR_0x8004
    callnative Script_QoL_Msg_IVsInfo
    msgbox gStringVar4, MSGBOX_DEFAULT
    callnative Script_QoL_IVs_TrickRoom
    call .ResultMsg
    goto .DoIVs

.IV_SetStat:
    msgbox gText_QoLPickAStat, MSGBOX_DEFAULT
    setvar VAR_0x8004, SCROLL_MULTI_QOL_STATS
    special ShowScrollableMultichoice
    waitstate
    compare VAR_RESULT, 6
    goto_if_eq .DoIVs
    compare VAR_RESULT, MULTI_B_PRESSED
    goto_if_eq .DoIVs
    callnative Script_QoL_MapStatSelection
    copyvar VAR_0x8000, VAR_RESULT        @ store chosen stat
    copyvar VAR_0x8003, VAR_0x8000       @ preserve stat across number prompt
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .DoIVs
    copyvar VAR_0x8006, VAR_0x8004
    callnative Script_QoL_Msg_IVsInfo
    msgbox gStringVar4, MSGBOX_DEFAULT
    setvar VAR_0x8000, 0                 @ min
    setvar VAR_0x8001, 31                @ max
    setvar VAR_0x8002, 31                @ initial
    callnative Script_QoL_PromptNumber
    copyvar VAR_0x8001, VAR_RESULT       @ iv value
    copyvar VAR_0x8000, VAR_0x8003       @ restore stat for callnative
    callnative Script_QoL_IVs_SetStat
    call .ResultMsg
    goto .DoIVs

.DoBall:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .MainLoop
    copyvar VAR_0x8006, VAR_0x8004
        callnative Script_QoL_Msg_BallInfo
        msgbox gStringVar4, MSGBOX_DEFAULT
        msgbox gText_QoLPickBall, MSGBOX_DEFAULT
        setvar VAR_0x8004, SCROLL_MULTI_QOL_BALLS
        special ShowScrollableMultichoice
        waitstate
        compare VAR_RESULT, 10
        goto_if_eq .MainLoop
        compare VAR_RESULT, MULTI_B_PRESSED
        goto_if_eq .MainLoop
        switch VAR_RESULT
                case 0, .B0
                case 1, .B1
                case 2, .B2
                case 3, .B3
                case 4, .B4
                case 5, .B5
                case 6, .B6
                case 7, .B7
                case 8, .B8
                case 9, .B9
.B0: setvar VAR_0x8000, ITEM_POKE_BALL;    goto .BApply
.B1: setvar VAR_0x8000, ITEM_GREAT_BALL;   goto .BApply
.B2: setvar VAR_0x8000, ITEM_ULTRA_BALL;   goto .BApply
.B3: setvar VAR_0x8000, ITEM_PREMIER_BALL; goto .BApply
.B4: setvar VAR_0x8000, ITEM_DIVE_BALL;    goto .BApply
.B5: setvar VAR_0x8000, ITEM_DUSK_BALL;    goto .BApply
.B6: setvar VAR_0x8000, ITEM_TIMER_BALL;   goto .BApply
.B7: setvar VAR_0x8000, ITEM_QUICK_BALL;   goto .BApply
.B8: setvar VAR_0x8000, ITEM_CHERISH_BALL; goto .BApply
.B9: setvar VAR_0x8000, ITEM_BEAST_BALL;   goto .BApply
.BConfirm:
    setvar VAR_0x800A, 1000
    callnative Script_QoL_Msg_ConfirmPrice
    msgbox gStringVar4, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, .DoBall
    return
.BApply:
	call .BConfirm
	callnative Script_QoL_SetBall
	call .ResultMsg
	goto .MainLoop

.DoTera:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    copyvar VAR_0x8004, VAR_RESULT
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .MainLoop
    copyvar VAR_0x8006, VAR_0x8004 @ store chosen slot for setteratype macro
    callnative Script_QoL_Msg_TeraInfo
    msgbox gStringVar4, MSGBOX_DEFAULT
    @ Page 1 of Tera types
.TeraPage1:
	setvar VAR_0x8004, SCROLL_MULTI_TERA_TYPES_PAGE1
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
		case 0, .TeraSetNormal
		case 1, .TeraSetFighting
		case 2, .TeraSetFlying
		case 3, .TeraSetPoison
		case 4, .TeraSetGround
		case 5, .TeraSetRock
		case 6, .TeraSetBug
		case 7, .TeraSetGhost
		case 8, .TeraSetSteel
		case 9, .TeraPage2
		case 10, .MainLoop
		case MULTI_B_PRESSED, .MainLoop
	end

.TeraPage2:
	setvar VAR_0x8004, SCROLL_MULTI_TERA_TYPES_PAGE2
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
		case 0, .TeraSetFire
		case 1, .TeraSetWater
		case 2, .TeraSetGrass
		case 3, .TeraSetElectric
		case 4, .TeraSetPsychic
		case 5, .TeraSetIce
		case 6, .TeraSetDragon
		case 7, .TeraSetDark
		case 8, .TeraSetFairy
		case 9, .TeraSetStellar
		case 10, .TeraPage1
		case 11, .MainLoop
		case MULTI_B_PRESSED, .MainLoop
	end

.TeraPay:
	showmoneybox 0, 0
	checkmoney VAR_0x800A
	goto_if_eq VAR_RESULT, FALSE, .TeraNoMoney
	removemoney VAR_0x800A
	updatemoneybox
	callnative Script_QoL_Msg_Charged
	msgbox gStringVar4 MSGBOX_DEFAULT
	hidemoneybox
	return
.TeraNoMoney:
	callnative Script_QoL_Msg_NotEnoughMoney
	msgbox gStringVar4 MSGBOX_DEFAULT
	hidemoneybox
	goto .MainLoop

.TeraConfirmFrom1:
    callnative Script_QoL_Msg_ConfirmPrice
    msgbox gStringVar4, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, .TeraPage1
    return
.TeraConfirmFrom2:
    callnative Script_QoL_Msg_ConfirmPrice
    msgbox gStringVar4, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, .TeraPage2
    return

.TeraSetNormal:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom1
    call .TeraPay
    setteratype TYPE_NORMAL,   VAR_0x8006
    goto .MainLoop
.TeraSetFighting:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom1
    call .TeraPay
    setteratype TYPE_FIGHTING, VAR_0x8006
    goto .MainLoop
.TeraSetFlying:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom1
    call .TeraPay
    setteratype TYPE_FLYING,   VAR_0x8006
    goto .MainLoop
.TeraSetPoison:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom1
    call .TeraPay
    setteratype TYPE_POISON,   VAR_0x8006
    goto .MainLoop
.TeraSetGround:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom1
    call .TeraPay
    setteratype TYPE_GROUND,   VAR_0x8006
    goto .MainLoop
.TeraSetRock:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom1
    call .TeraPay
    setteratype TYPE_ROCK,     VAR_0x8006
    goto .MainLoop
.TeraSetBug:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom1
    call .TeraPay
    setteratype TYPE_BUG,      VAR_0x8006
    goto .MainLoop
.TeraSetGhost:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom1
    call .TeraPay
    setteratype TYPE_GHOST,    VAR_0x8006
    goto .MainLoop
.TeraSetSteel:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom1
    call .TeraPay
    setteratype TYPE_STEEL,    VAR_0x8006
    goto .MainLoop
.TeraSetFire:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom2
    call .TeraPay
    setteratype TYPE_FIRE,     VAR_0x8006
    goto .MainLoop
.TeraSetWater:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom2
    call .TeraPay
    setteratype TYPE_WATER,    VAR_0x8006
    goto .MainLoop
.TeraSetGrass:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom2
    call .TeraPay
    setteratype TYPE_GRASS,    VAR_0x8006
    goto .MainLoop
.TeraSetElectric:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom2
    call .TeraPay
    setteratype TYPE_ELECTRIC, VAR_0x8006
    goto .MainLoop
.TeraSetPsychic:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom2
    call .TeraPay
    setteratype TYPE_PSYCHIC,  VAR_0x8006
    goto .MainLoop
.TeraSetIce:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom2
    call .TeraPay
    setteratype TYPE_ICE,      VAR_0x8006
    goto .MainLoop
.TeraSetDragon:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom2
    call .TeraPay
    setteratype TYPE_DRAGON,   VAR_0x8006
    goto .MainLoop
.TeraSetDark:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom2
    call .TeraPay
    setteratype TYPE_DARK,     VAR_0x8006
    goto .MainLoop
.TeraSetFairy:
    setvar VAR_0x800A, 1000
    call .TeraConfirmFrom2
    call .TeraPay
    setteratype TYPE_FAIRY,    VAR_0x8006
    goto .MainLoop
.TeraSetStellar:
    setvar VAR_0x800A, 5000
    call .TeraConfirmFrom2
    call .TeraPay
    setteratype TYPE_STELLAR,  VAR_0x8006
    goto .MainLoop

.DoHidden:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .MainLoop
    copyvar VAR_0x8006, VAR_0x8004
    callnative Script_QoL_Msg_HPInfo
    msgbox gStringVar4, MSGBOX_DEFAULT
    msgbox gText_QoLPickHPType, MSGBOX_DEFAULT

.HPPage1:
    setvar VAR_0x8004, SCROLL_MULTI_QOL_HP_TYPES_PAGE1
    special ShowScrollableMultichoice
    waitstate
    switch VAR_RESULT
        case 0, .HPSetFighting
        case 1, .HPSetFlying
        case 2, .HPSetPoison
        case 3, .HPSetGround
        case 4, .HPSetRock
        case 5, .HPSetBug
        case 6, .HPSetGhost
        case 7, .HPSetSteel
        case 8, .HPPage2     @ Next
        case 9, .MainLoop
        case MULTI_B_PRESSED, .MainLoop
    end

.HPPage2:
    setvar VAR_0x8004, SCROLL_MULTI_QOL_HP_TYPES_PAGE2
    special ShowScrollableMultichoice
    waitstate
    switch VAR_RESULT
        case 0, .HPSetFire
        case 1, .HPSetWater
        case 2, .HPSetGrass
        case 3, .HPSetElectric
        case 4, .HPSetPsychic
        case 5, .HPSetIce
        case 6, .HPSetDragon
        case 7, .HPSetDark
        case 8, .HPPage1     @ Back
        case 9, .MainLoop
        case MULTI_B_PRESSED, .MainLoop
    end

.HPConfirmFrom1:
    setvar VAR_0x800A, 1000
    callnative Script_QoL_Msg_ConfirmPrice
    msgbox gStringVar4, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, .HPPage1
    return

.HPConfirmFrom2:
    setvar VAR_0x800A, 1000
    callnative Script_QoL_Msg_ConfirmPrice
    msgbox gStringVar4, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, .HPPage2
    return

.HPSetFighting: setvar VAR_0x8000, TYPE_FIGHTING; call .HPConfirmFrom1; goto .HPApply
.HPSetFlying:   setvar VAR_0x8000, TYPE_FLYING;   call .HPConfirmFrom1; goto .HPApply
.HPSetPoison:   setvar VAR_0x8000, TYPE_POISON;   call .HPConfirmFrom1; goto .HPApply
.HPSetGround:   setvar VAR_0x8000, TYPE_GROUND;   call .HPConfirmFrom1; goto .HPApply
.HPSetRock:     setvar VAR_0x8000, TYPE_ROCK;     call .HPConfirmFrom1; goto .HPApply
.HPSetBug:      setvar VAR_0x8000, TYPE_BUG;      call .HPConfirmFrom1; goto .HPApply
.HPSetGhost:    setvar VAR_0x8000, TYPE_GHOST;    call .HPConfirmFrom1; goto .HPApply
.HPSetSteel:    setvar VAR_0x8000, TYPE_STEEL;    call .HPConfirmFrom1; goto .HPApply
.HPSetFire:     setvar VAR_0x8000, TYPE_FIRE;     call .HPConfirmFrom2; goto .HPApply
.HPSetWater:    setvar VAR_0x8000, TYPE_WATER;    call .HPConfirmFrom2; goto .HPApply
.HPSetGrass:    setvar VAR_0x8000, TYPE_GRASS;    call .HPConfirmFrom2; goto .HPApply
.HPSetElectric: setvar VAR_0x8000, TYPE_ELECTRIC; call .HPConfirmFrom2; goto .HPApply
.HPSetPsychic:  setvar VAR_0x8000, TYPE_PSYCHIC;  call .HPConfirmFrom2; goto .HPApply
.HPSetIce:      setvar VAR_0x8000, TYPE_ICE;      call .HPConfirmFrom2; goto .HPApply
.HPSetDragon:   setvar VAR_0x8000, TYPE_DRAGON;   call .HPConfirmFrom2; goto .HPApply
.HPSetDark:     setvar VAR_0x8000, TYPE_DARK;     call .HPConfirmFrom2; goto .HPApply

.HPApply:
    callnative Script_QoL_SetHiddenPowerType
    call .ResultMsg
    goto .MainLoop

.ResultMsg:
	compare VAR_RESULT, 1
	goto_if_eq .MsgCharged
	compare VAR_RESULT, 2
	goto_if_eq .MsgNoMoney
	compare VAR_RESULT, 3
	goto_if_eq .MsgIllegal
	goto .MsgCanceled

.MsgCharged:
	callnative Script_QoL_Msg_Charged
	msgbox gStringVar4 MSGBOX_DEFAULT
	return
.MsgNoMoney:
	callnative Script_QoL_Msg_NotEnoughMoney
	msgbox gStringVar4 MSGBOX_DEFAULT
	return
.MsgIllegal:
	callnative Script_QoL_Msg_IllegalBall
	msgbox gStringVar4 MSGBOX_DEFAULT
	return
.MsgCanceled:
	callnative Script_QoL_Msg_Canceled
	msgbox gStringVar4 MSGBOX_DEFAULT
	return

.End:
	release
	end
.DoDmax:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .MainLoop
    copyvar VAR_0x8006, VAR_0x8004
    callnative Script_QoL_SetDynamaxLevelMax
    call .ResultMsg
    goto .MainLoop

.DoGmax:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .MainLoop
    copyvar VAR_0x8006, VAR_0x8004
    callnative Script_QoL_EnableGigantamaxFactor
    call .ResultMsg
    goto .MainLoop
.DoAbility:
    msgbox gText_QoLChooseMon, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, .MainLoop
    copyvar VAR_0x8006, VAR_0x8004
    callnative Script_QoL_Msg_AbilityInfo
    msgbox gStringVar4, MSGBOX_DEFAULT
    setvar VAR_0x8004, SCROLL_MULTI_QOL_ABILITIES
    special ShowScrollableMultichoice
    waitstate
    switch VAR_RESULT
        case 0, .AB_Toggle
        case 1, .AB_SetNorm1
        case 2, .AB_SetNorm2
        case 3, .AB_SetHidden
        case 4, .MainLoop
        case MULTI_B_PRESSED, .MainLoop
    end
.AB_Toggle:
    call .ABConfirm
    callnative Script_QoL_Ability_Toggle
    call .ResultMsg
    goto .MainLoop
.AB_SetNorm1:
    setvar VAR_0x8000, 0
    call .ABConfirm
    callnative Script_QoL_Ability_SetNormal
    call .ResultMsg
    goto .MainLoop
.AB_SetNorm2:
    setvar VAR_0x8000, 1
    call .ABConfirm
    callnative Script_QoL_Ability_SetNormal
    call .ResultMsg
    goto .MainLoop
.AB_SetHidden:
    call .ABConfirm
    callnative Script_QoL_Ability_SetHidden
    call .ResultMsg
    goto .MainLoop

.ABConfirm:
    setvar VAR_0x800A, 1000
    callnative Script_QoL_Msg_ConfirmPrice
    msgbox gStringVar4, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, .DoAbility
    return
