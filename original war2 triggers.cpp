void v_human1(bool rep_init)
{
	if (rep_init)
	{
		//pathfind_fix(true);
		//ai_fix_plugin(true);
		//saveload_fixed = true;
		//your initialize
	}
	else
	{
		//your custom victory conditions
		byte local = *(byte*)LOCAL_PLAYER;
		if (!slot_alive(local))lose(true);
        if ((get_val(FARM,local)>=4)&&(get_val(BARRACKS,local)>=1))win(true);
	}
}

void v_human2(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_ARCHER);
        sort_stat(S_COLOR, P_WHITE, CMP_EQ);
        if (units == 0)lose(true);
        if ((get_val(CIRCLE_UNITS, local) >= 1))win(true);
    }
}

void v_human3(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        if ((get_val(OIL_PLATFORM, local) >= 4))win(true);
    }
}

void v_human4(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_human5(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_human6(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_human7(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        int r = 0;
        for (int i = 0; i < 8; i++)
        {
            if (i != local)
                r += get_val(REFINERY, i);
        }
        if ((r == 0))win(true);
    }
}

void v_human8(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
		find_all_alive_units(U_PEASANT);
		sort_stat(S_COLOR, P_ORANGE, CMP_EQ);
		set_stat_all(S_NEXT_ORDER, ORDER_STOP);
        unit_convert(P_ORANGE, U_PEASANT, U_ATTACK_PEASANT, 0);
        ally(local, P_ORANGE, 0);
        if (!slot_alive(local))lose(true);
        if (get_val(TH3, local) >= 1)
        {
            bool f = false;
            for (int i = 0; i < 8; i++)
            {
                if (i != local)
                {
                    if (slot_alive(i))f = true;
                }
            }
            if ((!f))win(true);
        }
    }
}

void v_human9(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_UTER);
        if (units == 0)lose(true);
        if ((get_val(CIRCLE_UNITS, local) >= 1))win(true);
    }
}

void v_human10(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
		//your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
		find_all_alive_units(U_PEASANT);
		sort_stat(S_COLOR, P_ORANGE, CMP_EQ);
		give_all(P_ORANGE);
		unit_convert(P_ORANGE, U_PEASANT, U_ATTACK_PEASANT, 1);
		find_all_alive_units(U_ATTACK_PEASANT);
		sort_stat(S_OWNER, P_ORANGE, CMP_EQ);
		give_all(local);
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_ATTACK_PEASANT);
        if (units < 4)lose(true);
        if ((get_val(CIRCLE_UNITS, local) >= 4))win(true);
    }
}

void v_human11(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_human12(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        int r = 0;
        for (int i = 0; i < 8; i++)
        {
            if (i != local)
            {
                r += get_val(OIL_PLATFORM, i);
                r += get_val(TRANSPORT, i);
                r += get_val(SHIPYARD, i);
            }
        }
        if ((r == 0))win(true);
    }
}

void v_human13(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        find_all_alive_units(U_LOTHAR);
        if (units != 0)
        {
            byte f = *((byte*)((uintptr_t)unit[0] + S_FLAGS2));
            f &= ~1;
            set_stat(unit[0], f, S_FLAGS2);
        }
        call_default_kill();
    }
}

void v_human14(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        if ((get_val(PORTAL, P_NEUTRAL) == 0))win(true);
    }
}

void v_xhuman1(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize 
    }
    else
    {
		allow_table(P_BLUE, 4, L_HEAL, 1);
        allow_table(P_BLUE, 4, L_EXORCISM, 1);
	
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_ALLERIA);
        if (units == 0)lose(true);
        find_all_alive_units(U_DANATH);
        if (units == 0)lose(true);
        find_all_alive_units(U_TYRALYON);
        if (units == 0)lose(true);
        if ((get_val(CIRCLE_UNITS, local) >= 3))win(true);
    }
}

void v_xhuman2(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        find_all_alive_units(U_DANATH);
        if (units == 0)lose(true);
        call_default_kill();
    }
}

void v_xhuman3(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
		allow_table(P_BLUE, 4, L_VISION, 1);
        allow_table(P_BLUE, 4, L_HEAL, 1);
        allow_table(P_BLUE, 4, L_EXORCISM, 1);
	
        //your custom victory conditions
		ua[0] = U_PORTAL;
		ut[0] = U_PORTAL;
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_TYRALYON);
        if (units == 0)lose(true);
        int r = 0;
        for (int i = 0; i < 8; i++)
        {
            if (i != local)
            {
                r += get_val(TH2, i);
                r += get_val(TH3, i);
            }
        }
        if ((r == 0))
        {
            if ((get_val(CIRCLE_UNITS, local) >= 1))win(true);
        }
    }
}

void v_xhuman4(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
		ua[0] = U_PORTAL;
		ut[0] = U_PORTAL;
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        if (get_val(TH3, local) >= 1)
        {
            bool f = false;
            for (int i = 0; i < 8; i++)
            {
                if ((i != local) && (i != P_YELLOW))
                {
                    if (slot_alive(i))f = true;
                }
            }
            if ((!f))win(true);
        }
    }
}

void v_xhuman5(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        if (get_val(SHIPYARD, local) >= 3)
        {
            int r = 0;
            for (int i = 0; i < 8; i++)
            {
                if (i != local)
                    r += get_val(SHIPYARD, i);
            }
            if ((r == 0))win(true);
        }
    }
}

void v_xhuman6(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_DANATH);
        if (units == 0)lose(true);
        find_all_alive_units(U_TYRALYON);
        if (units == 0)lose(true);
        if (!slot_alive(P_ORANGE))
        {
            find_all_alive_units(U_CIRCLE);
            if (units != 0)
            {
                byte x = *((byte*)((uintptr_t)unit[0] + S_X));
                byte y = *((byte*)((uintptr_t)unit[0] + S_Y));
                set_region(x, y, x + 1, y + 1);
                find_all_alive_units(U_DANATH);
                sort_in_region();
                if (units != 0)
                {
                    find_all_alive_units(U_TYRALYON);
                    sort_in_region();
                    if (units != 0)
                    {
                        win(true);
                    }
                }
            }
        }
    }
}

void v_xhuman7(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
		allow_table(P_BLUE, 4, L_VISION, 0);
        allow_table(P_BLUE, 4, L_HEAL, 1);
        allow_table(P_BLUE, 4, L_EXORCISM, 1);
        allow_table(P_BLUE, 4, L_FLAME_SHIELD, 1);
        allow_table(P_BLUE, 4, L_FIREBALL, 1);
        allow_table(P_BLUE, 4, L_SLOW, 1);
        allow_table(P_BLUE, 4, L_INVIS, 1);
        allow_table(P_BLUE, 4, L_POLYMORF, 0);
        allow_table(P_BLUE, 4, L_BLIZZARD, 1);
	
        //your custom victory conditions
		unit_convert(P_BLUE, U_KNIGHT, U_PALADIN, 1);
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_ALLERIA);
        if (units == 0)lose(true);
        find_all_alive_units(U_HADGAR);
        if (units == 0)lose(true);
        find_all_alive_units(U_KURDRAN);
        if (units == 0)lose(true);
        if ((get_val(AVIARY, P_BLACK) == 0))
        {
            find_all_alive_units(U_DEATHWING);
            if (units == 0)win(true);
        }
    }
}

void v_xhuman8(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_xhuman9(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        find_all_alive_units(U_RUNESTONE);
        sort_stat(S_HP, 5000, CMP_EQ);
        set_stat_all(S_HP, 400);
        if (!slot_alive(local))lose(true);
        if ((get_val(RUNESTONE, P_ORANGE) == 0))
        {
            if ((get_val(TH3, P_BLACK) == 0))win(true);
        }
    }
}

void v_xhuman10(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
		allow_table(P_BLUE, 4, L_VISION, 1);
        allow_table(P_BLUE, 4, L_HEAL, 1);
        allow_table(P_BLUE, 4, L_EXORCISM, 1);
        allow_table(P_BLUE, 4, L_FLAME_SHIELD, 1);
        allow_table(P_BLUE, 4, L_FIREBALL, 1);
        allow_table(P_BLUE, 4, L_SLOW, 1);
        allow_table(P_BLUE, 4, L_INVIS, 1);
        allow_table(P_BLUE, 4, L_POLYMORF, 1);
        allow_table(P_BLUE, 4, L_BLIZZARD, 1);
	
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        find_all_alive_units(U_ALLERIA);
        if (units == 0)lose(true);
        find_all_alive_units(U_DANATH);
        if (units == 0)lose(true);
        find_all_alive_units(U_TYRALYON);
        if (units == 0)lose(true);
        find_all_alive_units(U_HADGAR);
        if (units == 0)lose(true);
        find_all_alive_units(U_KURDRAN);
        if (units == 0)lose(true);
        call_default_kill();
        for (int i = 0; i < 8; i++)
        {
            if (!slot_alive(i))set_res(i, 0, 0, 0, 0, 0);
        }
        bool f = false;
        for (int i = 0; i < 8; i++)
        {
            if (i != local)
            {
                if (cmp_res(i, 0, 0x90, 0x1, 0, 0, CMP_BIGGER_EQ))f = true;
            }
        }
        if ((!f))win(true);
    }
}

void v_xhuman11(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
		allow_table(P_BLUE, 4, L_VISION, 1);
        allow_table(P_BLUE, 4, L_HEAL, 1);
        allow_table(P_BLUE, 4, L_EXORCISM, 1);
        allow_table(P_BLUE, 4, L_FLAME_SHIELD, 1);
        allow_table(P_BLUE, 4, L_FIREBALL, 1);
        allow_table(P_BLUE, 4, L_SLOW, 1);
        allow_table(P_BLUE, 4, L_INVIS, 1);
        allow_table(P_BLUE, 4, L_POLYMORF, 1);
        allow_table(P_BLUE, 4, L_BLIZZARD, 1);
		unit_convert(P_BLUE, U_KNIGHT, U_PALADIN, 1);
	
        //your custom victory conditions
        find_all_alive_units(U_ALLERIA);
        if (units == 0)lose(true);
        find_all_alive_units(U_HADGAR);
        if (units == 0)lose(true);
        find_all_alive_units(U_TYRALYON);
        if (units == 0)lose(true);
        call_default_kill();
    }
}

void v_xhuman12(bool rep_init)
{
	if (rep_init)
	{
	    //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
		//your initialize
	}
	else
	{
		allow_table(P_BLUE, 4, L_VISION, 1);
        allow_table(P_BLUE, 4, L_HEAL, 1);
        allow_table(P_BLUE, 4, L_EXORCISM, 1);
        allow_table(P_BLUE, 4, L_FLAME_SHIELD, 1);
        allow_table(P_BLUE, 4, L_FIREBALL, 1);
        allow_table(P_BLUE, 4, L_SLOW, 1);
        allow_table(P_BLUE, 4, L_INVIS, 1);
        allow_table(P_BLUE, 4, L_POLYMORF, 1);
        allow_table(P_BLUE, 4, L_BLIZZARD, 1);
	
		//your custom victory conditions
        ua[0] = U_HADGAR;
        ut[0] = U_PORTAL;
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_HADGAR);
        if (units == 0)lose(true);
        if ((get_val(PORTAL, P_NEUTRAL) == 0))win(true);
	}
}

void v_orc1(bool rep_init)
{
    if (rep_init)
    {
	    //pathfind_fix(true);
        //ai_fix_plugin(true);
		saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        if ((get_val(FARM, local) >= 4) && (get_val(BARRACKS, local) >= 1))win(true);
    }
}

void v_orc2(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_ZULJIN);
        if (units == 0)lose(true);
        find_all_alive_units(U_TROLL);
        sort_stat(S_OWNER, local, CMP_EQ);
        if (units != 0)
        {
            for (int i = 0; i < units; i++)
            {
                byte f = *((byte*)((uintptr_t)unit[i] + S_FLAGS2));
                f &= ~1;
                set_stat(unit[i], f, S_FLAGS2);
            }
        }
        if ((get_val(CIRCLE_UNITS, local) >= 1))win(true);
    }
}

void v_orc3(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        if ((get_val(OIL_PLATFORM, local) >= 4))win(true);
    }
}

void v_orc4(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_orc5(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_orc6(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_CHOGAL);
        if (units == 0)lose(true);
        if ((get_val(CIRCLE_UNITS, local) >= 1))win(true);
    }
}

void v_orc7(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_orc8(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_RUNESTONE);
        if (units == 0)lose(true);
        if ((get_val(TH3, P_BLUE) == 0))
        {
            if ((get_val(RUNESTONE, local) != 0))win(true);
        }
    }
}

void v_orc9(bool rep_init)
{
	if (rep_init)
	{
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
		//your initialize
	}
	else
	{
		//your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        bool fw = false, ff = false;
        find_all_alive_units(U_WHARF);
        for (int i = 0; i < units; i++)
        {
            int a = ((int (*)(int*, WORD))F_MTX_UNIT_ON_REGION)(unit[0], *(WORD*)0x004ABFA0);
            if (a)fw = true;
        }
        find_all_alive_units(U_FORTRESS);
        for (int i = 0; i < units; i++)
        {
            int a = ((int (*)(int*, WORD))F_MTX_UNIT_ON_REGION)(unit[0], *(WORD*)0x004ABFA0);
            if (a)ff = true;
        }
        if (fw && ff)win(true);
	}
}

void v_orc10(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_orc11(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_orc12(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_orc13(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_orc14(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_xorc1(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_GROM);
        if (units == 0)lose(true);
        if ((get_val(MAGUS, P_WHITE) == 0))
        {
            find_all_alive_units(U_TEMPLE);
            sort_stat(S_OWNER, P_WHITE, CMP_EQ);
            if (units == 0)win(true);
        }
    }
}

void v_xorc2(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
		allow_table(P_BLACK, 4, L_EYE, 1);
        allow_table(P_BLACK, 4, L_BLOOD, 1);
	
        //your custom victory conditions
        find_all_alive_units(U_KARGATH);
        if (units == 0)lose(true);
        find_all_alive_units(U_DENTARG);
        if (units == 0)lose(true);
        call_default_kill();
    }
}

void v_xorc3(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_xorc4(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        find_all_alive_units(U_TERON);
        if (units == 0)lose(true);
        call_default_kill();
    }
}

void v_xorc5(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_DRAGONROOST);
        if (units == 0)lose(true);
        if (get_val(AVIARY, P_GREEN) == 0)
        {
            if (get_val(DRAGON, P_GREEN) == 0)win(true);
        }
    }
}

void v_xorc6(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        find_all_alive_units(U_TERON);
        if (units == 0)lose(true);
        call_default_kill();
    }
}

void v_xorc7(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        if (get_val(SHIPYARD, local) >= 5)
        {
            int r = 0;
            for (int i = 0; i < 8; i++)
            {
                if (i != local)
                {
                    r += get_val(DESTROYER, i);
                    r += get_val(BATTLESHIP, i);
                    r += get_val(SUBMARINE, i);
                }
            }
            if ((r == 0))win(true);
        }
    }
}

void v_xorc8(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}

void v_xorc9(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
		allow_table(P_BLUE, 4, L_HEAL, 1);
        allow_table(P_BLUE, 4, L_EXORCISM, 1);
		unit_convert(P_BLUE, U_KNIGHT, U_PALADIN, 1);
	
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_DEMON);
        if (units == 0)win(true);
    }
}

void v_xorc10(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_MAGE);
        sort_stat(S_COLOR, P_ORANGE, CMP_EQ);
        if (units == 0)lose(true);
        else
        {
            byte f = *((byte*)((uintptr_t)unit[0] + S_FLAGS2));
            if (!(f & 1))
            {
                bool f = false;
                for (int i = 0; i < 8; i++)
                {
                    if ((i != local) && (i != P_ORANGE))
                    {
                        if (slot_alive(i))f = true;
                    }
                }
                if ((!f))win(true);
            }
        }
    }
}

void v_xorc11(bool rep_init)
{
	if (rep_init)
	{
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
		//your initialize
	}
	else
	{
		//your custom victory conditions
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        if (!slot_alive(P_VIOLET))win(true);
	}
}

void v_xorc12(bool rep_init)
{
	if (rep_init)
	{
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
		//your initialize
	}
	else
	{
		//your custom victory conditions
		allow_table(P_BLACK, 4, L_EYE, 1);
        allow_table(P_BLACK, 4, L_BLOOD, 1);
        allow_table(P_BLACK, 4, L_RUNES, 1);
        allow_table(P_BLACK, 4, L_COIL, 1);
        allow_table(P_BLACK, 4, L_RAISE, 1);
        allow_table(P_BLACK, 4, L_WIND, 1);
        allow_table(P_BLACK, 4, L_HASTE, 1);
        allow_table(P_BLACK, 4, L_UNHOLY, 1);
        allow_table(P_BLACK, 4, L_DD, 1);
		
        byte local = *(byte*)LOCAL_PLAYER;
        if (!slot_alive(local))lose(true);
        find_all_alive_units(U_PORTAL);
        if (units == 0)lose(true);
        else
        {
            byte f = *((byte*)((uintptr_t)unit[0] + S_FLAGS2));
            f |= 1;
            set_stat(unit[0], f, S_FLAGS2);
        }
        if (get_val(PORTAL, local) >= 1)
        {
            bool f = false;
            for (int i = 0; i < 8; i++)
            {
                if ((i != local))
                {
                    if (slot_alive(i))f = true;
                }
            }
            if ((!f))win(true);
        }
	}
}

void v_custom(bool rep_init)
{
    if (rep_init)
    {
        //pathfind_fix(true);
        //ai_fix_plugin(true);
		//saveload_fixed = true;
        //your initialize
    }
    else
    {
        //your custom victory conditions
        call_default_kill();
    }
}