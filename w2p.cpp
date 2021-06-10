#include <windows.h>
#include <stdint.h>
#include "patch.h"//stole that file from Fois plugins sources because why not
#include "defs.h"//some addresses and constants
#include "names.h"//some constants

byte a_custom = 0;//custom game
byte reg[4] = { 0 };//region
int* unit[1610];//array for units
int* unitt[1610];//temp array for units
int* capt[1610];//array for captured units
int units = 0;//number of units in array
int captk = 0;//number of units in captured array
byte ua[255] = { 255 };//attackers array
byte ut[255] = { 255 };//targets array     only unit ua[i] can deal damage to unit ut[i]
byte runes[9] = { 0 };//runestone special abilities flags
bool agr = false;//allied comps aggro if attacked
bool cpt = false;//can buildings be captured on low hp
bool pcpt = false;//only peons can capture low hp build
bool thcpt = false;//if th captured on low hp, capture all units of that player
bool steal = false;//if can steal resources
bool aport = false;//only allies can teleport in portal
bool mport = false;//portal can teleport only if have mage(or dk) nearby
bool b3rune = false;//can build runestone
bool b3port = false;//can build portal
bool b3cirl = false;//can build circle of power
bool b3mine = false;//can build gold mine
bool b3forest = false;//can build forest
bool apn = false;//can build attack peons
bool manaburn = false;//if demons have manaburn
byte heros[16] = { 0 };//heroes ids
bool herosb[16] = { false };//heroes buildable ids
char hhero[180] = { 0 };//buttons for build human heroes array
char ohero[180] = { 0 };//buttons for build orc heroes array
bool A_runestone = false;//runestone activated
bool A_portal = false;//portals activated
bool A_transport = false;//transport activated
bool A_autoheal = false;//paladins autoheal activated
bool blood_f = false;//blood fixed
bool more_res = false;//can get more resources
byte m_slow_aura[255] = { 255 };//units that have slow aura
byte m_death_aura[255] = { 255 };//units that have death aura
byte m_sneak[255] = { 255 };//units that have hide ability
byte m_devotion[255] = { 255 };//units that have defence aura
byte m_vampire[255] = { 255 };//units that have vampire aura
byte m_prvnt[255] = { 255 };//units that have prevent loss

char sheep_build[] = "\x0\x0\x73\x0\xf0\x40\x44\x0\xd0\xe6\x40\x0\x1\x39\x28\x1\x0\x0\x0\x0";
char demon_build[] = "\x0\x0\x25\x0\xf0\x40\x44\x0\xd0\xe6\x40\x0\x1\x38\x18\x1\x0\x0\x0\x0";
char build_3[] = "\x0\x0\x52\x0\xf0\x40\x44\x0\x80\x6b\x43\x0\x0\x66\x31\x1\x0\x0\x0\x0\x1\x0\x50\x0\xf0\x40\x44\x0\x80\x6b\x43\x0\x0\x65\x3e\x1\x0\x0\x0\x0\x2\x0\x51\x0\xf0\x40\x44\x0\x80\x6b\x43\x0\x0\x64\x46\x1\x0\x0\x0\x0\x3\x0\x4A\x0\xf0\x40\x44\x0\x80\x6b\x43\x0\x0\x5c\x38\x1\x0\x0\x0\x0\x4\x0\x67\x0\xf0\x40\x44\x0\x80\x6b\x43\x0\x0\x5c\x91\x1\x0\x0\x0\x0\x8\x0\x5b\x0\xf0\x40\x44\x0\x70\xa6\x44\x0\x0\x6e\x97\x1\x0\x0\x0\x0";
char peon_build3[] = "\x0\x0\x54\x0\xf0\x40\x44\x0\x90\x66\x43\x0\x0\x0\x88\x1\x2\x0\x0\x0\x1\x0\xa7\x0\xf0\x40\x44\x0\xf0\x61\x43\x0\x0\x0\x89\x1\x1\x0\x0\x0\x2\x0\x77\x0\xf0\x40\x44\x0\x40\x69\x43\x0\x0\x0\x8a\x1\x8\x0\x0\x0\x3\x0\x55\x0\xf0\x40\x44\x0\x70\x6a\x43\x0\x0\x0\x8b\x1\x0\x1\x0\x0\x4\x0\x56\x0\x60\x51\x44\x0\x10\x6a\x43\x0\x0\x0\x8c\x1\x40\x0\x0\x0\x5\x0\x5a\x0\xa0\x51\x44\x0\x30\x6b\x43\x0\x0\x0\x91\x1\x80\x0\x0\x0\x6\x0\x57\x0\xe0\x4d\x44\x0\x70\xa6\x44\x0\x0\x71\x8e\x1\x0\x0\x0\x0\x7\x0\x58\x0\x50\x50\x44\x0\x70\xa6\x44\x0\x0\x72\x8f\x1\x0\x0\x0\x0\x8\x0\x6d\x0\xf0\x40\x44\x0\x70\xa6\x44\x0\x0\x6d\x38\x1\x0\x0\x0\x0";
char oth_build[] = "\x0\x0\x1\x0\xa0\x44\x44\x0\xd0\xe6\x40\x0\x1\x3\xd\x1\x0\x0\x0\x0\x1\x0\x43\x0\xb0\x42\x44\x0\x10\xe7\x40\x0\x0\x59\x3e\x1\x0\x0\x0\x0\x1\x0\x45\x0\xb0\x42\x44\x0\x10\xe7\x40\x0\x1\x5b\x3c\x1\x0\x0\x0\x0\x2\x0\x4f\x0\xf0\x40\x44\x0\x70\xa6\x44\x0\x0\x6c\x90\x1\x0\x0\x0\x0\x3\x0\xb5\x0\xf0\x40\x44\x0\xd0\xe6\x40\x0\x1\x11\x8a\x1\x0\x0\x0\x0";
char hth_build[] = "\x2\x0\x4f\x0\xf0\x40\x44\x0\x70\xa6\x44\x0\x0\x6b\x90\x1\x0\x0\x0\x0\x3\x0\xb4\x0\xf0\x40\x44\x0\xd0\xe6\x40\x0\x1\x10\x8a\x1\x0\x0\x0\x0";
char churc[] = "\x0\x0\xa\x0\xc0\x43\x44\x0\x90\xe6\x40\x0\x14\x21\x72\x1\x0\x0\x0\x0\x0\x0\x6b\x0\x10\x44\x44\x0\x90\xe6\x40\x0\x1\x23\x81\x1\x0\x0\x0\x0\x1\x0\x6e\x0\x10\x44\x44\x0\x90\xe6\x40\x0\x3\x24\x83\x1\x0\x0\x0\x0\x3\x0\x6d\x0\xf0\x40\x44\x0\xf0\x40\x44\x0\x0\x0\x6c\x1\x0\x0\x0\x0";

void show_message(byte time, char* text)
{
    ((void (*)(char*, int, int))F_MAP_MSG)(text, 15, time * 10);//original war2 show msg func
}

void clear_chat()
{
    for (int i = 0; i < 12; i++)
    {
        int* p = (int*)CHAT_POINTER;
        p = (int*)(*((int*)((uintptr_t)p)));
        p -= 100 / 4 * i;
        char buf[] = "\x0";//just set 0 in all messages to empty
        PATCH_SET((char*)p, buf);
    }
}

int get_val(int adress, int player)
{
    return (int)(*(WORD*)(adress + player * 2));//player*2 cause all vals is WORD
}

bool cmp_args(byte m, byte v, byte c)
{//compare bytes
    bool f = false;
    switch (m)
    {
    case CMP_EQ:f = (v == c); break;
    case CMP_NEQ:f = (v != c); break;
    case CMP_BIGGER_EQ:f = (v >= c); break;
    case CMP_SMALLER_EQ:f = (v <= c); break;
    case CMP_BIGGER:f = (v > c); break;
    case CMP_SMALLER:f = (v < c); break;
    default: f = false; break;
    }
    return f;
}

bool cmp_args2(byte m, WORD v, WORD c)
{//compare words
    bool f = false;
    switch (m)
    {
    case CMP_EQ:f = (v == c); break;
    case CMP_NEQ:f = (v != c); break;
    case CMP_BIGGER_EQ:f = (v >= c); break;
    case CMP_SMALLER_EQ:f = (v <= c); break;
    case CMP_BIGGER:f = (v > c); break;
    case CMP_SMALLER:f = (v < c); break;
    default: f = false; break;
    }
    return f;
}

bool cmp_args4(byte m, int v, int c)
{//compare 4 bytes (for resources)
    bool f = false;
    switch (m)
    {
    case CMP_EQ:f = (v == c); break;
    case CMP_NEQ:f = (v != c); break;
    case CMP_BIGGER_EQ:f = (v >= c); break;
    case CMP_SMALLER_EQ:f = (v <= c); break;
    case CMP_BIGGER:f = (v > c); break;
    case CMP_SMALLER:f = (v < c); break;
    default: f = false; break;
    }
    return f;
}

void lose(bool t)
{
    if (t == true)
    {
        char buf[] = "\x0";//if need to show table
        PATCH_SET((char*)LOSE_SHOW_TABLE, buf);
    }
    else
    {
        char buf[] = "\x3b";
        PATCH_SET((char*)LOSE_SHOW_TABLE, buf);
    }
    char l[] = "\x2\x0\x0\x0";
    PATCH_SET((char*)(ENDGAME_STATE + (4 * (*(byte*)LOCAL_PLAYER))), l);
    ((void (*)())F_LOSE)();//original lose func
}

void win(bool t)
{
    if (t == true)
    {
        char buf[] = "\xEB";//if need to show table
        PATCH_SET((char*)WIN_SHOW_TABLE, buf);
    }
    else
    {
        char buf[] = "\x74";
        PATCH_SET((char*)WIN_SHOW_TABLE, buf);
    }
    char l[] = "\x3\x0\x0\x0";
    PATCH_SET((char*)(ENDGAME_STATE + (4 * (*(byte*)LOCAL_PLAYER))), l);
    ((void (*)())F_WIN)();//original win func
}

void lose2(bool t, byte vid)
{
    lose(t);
    ((void (*)(int, byte))F_VIDEO)(vid, 1);//original war2 func that show video by id
}

void win2(bool t, byte vid)
{
    win(t);
    ((void (*)(int, byte))F_VIDEO)(vid, 1);//original war2 func that show video by id
}

void tile_remove_trees(int x, int y)
{
    ((void (*)(int, int))F_TILE_REMOVE_TREES)(x, y);
}

void tile_remove_rocks(int x, int y)
{
    ((void (*)(int, int))F_TILE_REMOVE_ROCKS)(x, y);
}

bool stat_byte(byte s)
{//chech if unit stat is 1 or 2 byte
    bool f = (s == S_DRAW_X) || (s == S_DRAW_Y) || (s == S_X) || (s == S_Y) || (s == S_HP)
        || (s == S_INVIZ) || (s == S_SHIELD) || (s == S_BLOOD) || (s == S_HASTE)
        || (s == S_AI_SPELLS) || (s == S_NEXT_FIRE)
        || (s == S_LAST_HARVEST_X) || (s == S_LAST_HARVEST_Y)
        || (s == S_BUILD_PROGRES) || (s == S_BUILD_PROGRES_TOTAL)
        || (s == S_RESOURCES) || (s == S_ORDER_X) || (s == S_ORDER_Y)
        || (s == S_RETARGET_X1) || (s == S_RETARGET_Y1) || (s == S_RETARGET_X2) || (s == S_RETARGET_Y2);
    return !f;
}

bool cmp_stat(int* p, int v, byte pr, byte cmp)
{
    //p - unit
    //v - value
    //pr - property
    //cmp - compare method
    bool f = false;
    if (stat_byte(pr))
    {
        byte ob = v % 256;
        char buf[3] = { 0 };
        buf[0] = ob;
        buf[1] = *((byte*)((uintptr_t)p + pr));
        if (cmp_args(cmp, buf[1], buf[0]))
        {
            f = true;
        }
    }
    else
    {
        if (cmp_args2(cmp, *((WORD*)((uintptr_t)p + pr)), (WORD)v))
        {
            f = true;
        }
    }
    return f;
}

void set_stat(int* p, int v, byte pr)
{
    if (stat_byte(pr))
    {
        char buf[] = "\x0";
        buf[0] = v % 256;
        PATCH_SET((char*)((uintptr_t)p + pr), buf);
    }
    else
    {
        char buf[] = "\x0\x0";
        buf[0] = v % 256;
        buf[1] = (v / 256) % 256;
        PATCH_SET((char*)((uintptr_t)p + pr), buf);
    }
}

void unit_convert(byte player, int who, int tounit, int a)
{
    //original war2 func converts units
    ((void (*)(byte, int, int, int))F_UNIT_CONVERT)(player, who, tounit, a);
}

void unit_create(int x, int y, int id, byte owner, byte n)
{
    while (n > 0)
    {
        n -= 1;
        int* p = (int*)(UNIT_SIZE_TABLE + 4 * id);//unit sizes table
        ((void (*)(int, int, int, byte, int*))F_UNIT_CREATE)(x, y, id, owner, p);//original war2 func creates unit
        //just call n times to create n units
    }
}

void unit_kill(int* u)
{
    ((void (*)(int*))F_UNIT_KILL)(u);//original war2 func kills unit
}

void unit_remove(int* u)
{
    byte f = *((byte*)((uintptr_t)u + S_FLAGS3));
    f |= SF_HIDDEN;
    set_stat(u, f, S_FLAGS3);
    unit_kill(u);//hide unit then kill
}

void unit_cast(int* u)//unit autocast
{
    ((void (*)(int*))F_AI_CAST)(u);//original war2 ai cast spells
}

void set_region(int x1, int y1, int x2, int y2)
{
    if (x1 < 0)x1 = 0;
    if (x1 > 127)x1 = 127;
    if (y1 < 0)y1 = 0;
    if (y1 > 127)y1 = 127;
    if (x2 < 0)x2 = 0;
    if (x2 > 127)x2 = 127;
    if (y2 < 0)y2 = 0;
    if (y2 > 127)y2 = 127;
    reg[0] = x1 % 256;
    reg[1] = y1 % 256;
    reg[2] = x2 % 256;
    reg[3] = y2 % 256;
}

bool in_region(byte x, byte y, byte x1, byte y1, byte x2, byte y2)
{
    //dnt know why but without this big monstrous ussless code gam crash 
    byte tmp;
    tmp = x % 256;
    x = tmp;
    tmp = y % 256;
    y = tmp;
    tmp = x1 % 256;
    x1 = tmp;
    tmp = y1 % 256;
    y1 = tmp;
    tmp = x2 % 256;
    x2 = tmp;
    tmp = y2 % 256;
    y2 = tmp;
    if (x < 0)x = 0;
    if (x > 127)x = 127;
    if (y < 0)y = 0;
    if (y > 127)y = 127;
    if (x1 < 0)x1 = 0;
    if (x1 > 127)x1 = 127;
    if (y1 < 0)y1 = 0;
    if (y1 > 127)y1 = 127;
    if (x2 < 0)x2 = 0;
    if (x2 > 127)x2 = 127;
    if (y2 < 0)y2 = 0;
    if (y2 > 127)y2 = 127;
    if (x2 < x1)
    {
        tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    if (y2 < y1)
    {
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
    //just check if coords inside region
    return ((x >= x1) && (y >= y1) && (x <= x2) && (y <= y2));
}

bool check_unit_dead(int* p)
{
    bool dead = false;
    if (p)
    {
        if ((*((byte*)((uintptr_t)p + S_FLAGS3))
            & (SF_DEAD | SF_DIEING | SF_UNIT_FREE)) != 0)
            dead = true;
    }
    else
        dead = true;
    return dead;
}

bool check_unit_complete(int* p)//for buildings
{
    bool f = false;
    if (p)
    {
        if ((*((byte*)((uintptr_t)p + S_FLAGS3)) & SF_COMPLETED) != 0)//flags3 last bit
            f = true;
    }
    else
        f = false;
    return f;
}

bool check_unit_hidden(int* p)
{
    bool f = false;
    if (p)
    {
        if ((*((byte*)((uintptr_t)p + S_FLAGS3)) & SF_HIDDEN) != 0)//flags3 4 bit
            f = true;
    }
    else
        f = true;
    return f;
}

bool check_unit_preplaced(int* p)
{
    bool f = false;
    if (p)
    {
        if ((*((byte*)((uintptr_t)p + S_FLAGS3)) & SF_PREPLACED) != 0)//flags3
            f = true;
    }
    else
        f = false;
    return f;
}

bool check_unit_near_death(int* p)
{
    bool dead = false;
    if (p)
    {
        if (((*((byte*)((uintptr_t)p + S_FLAGS3)) & SF_DIEING) != 0)
            && ((*((byte*)((uintptr_t)p + S_FLAGS3)) & (SF_DEAD | SF_UNIT_FREE)) == 0))
            dead = true;
    }
    else
        dead = true;
    return dead;
}

void find_all_units(byte id)
{
    //CAREFUL with this function - ALL units get into massive 
    //even if their memory was cleared already
    //all units by id will go in array
    units = 0;
    int* p = (int*)UNITS_MASSIVE;//pointer to units
    p = (int*)(*p);
    int k = *(int*)UNITS_NUMBER;
    while (k > 0)
    {
        bool f = *((byte*)((uintptr_t)p + S_ID)) == (byte)id;
        if (id == ANY_BUILDING)
            f = *((byte*)((uintptr_t)p + S_ID)) >= U_FARM;//buildings
        if (id == ANY_MEN)
            f = *((byte*)((uintptr_t)p + S_ID)) < U_FARM;//all nonbuildings
        if (id == ANY_UNITS)
            f = true;//all ALL units
        if (id == ANY_BUILDING_2x2)//small buildings
        {
            byte sz = *((byte*)UNIT_SIZE_TABLE + *((byte*)((uintptr_t)p + S_ID)) * 4);
            f = sz == 2;
        }
        if (id == ANY_BUILDING_3x3)//med buildings
        {
            byte sz = *((byte*)UNIT_SIZE_TABLE + *((byte*)((uintptr_t)p + S_ID)) * 4);
            f = sz == 3;
        }
        if (id == ANY_BUILDING_4x4)//big buildings
        {
            byte sz = *((byte*)UNIT_SIZE_TABLE + *((byte*)((uintptr_t)p + S_ID)) * 4);
            f = sz == 4;
        }
        if (f)
        {
            unit[units] = p;
            units++;
        }
        p = (int*)((int)p + 0x98);
        k--;
    }
}

void find_all_alive_units(byte id)
{
    //all units by id will go in array
    units = 0;
    for (int i = 0; i < 16; i++)
    {
        int* p = (int*)(UNITS_LISTS + 4 * i);//pointer to units list for each player
        if (p)
        {
            p = (int*)(*p);
            while (p)
            {
                bool f = *((byte*)((uintptr_t)p + S_ID)) == (byte)id;
                if (id == ANY_BUILDING)
                    f = *((byte*)((uintptr_t)p + S_ID)) >= U_FARM;//buildings
                if (id == ANY_MEN)
                    f = *((byte*)((uintptr_t)p + S_ID)) < U_FARM;//all nonbuildings
                if (id == ANY_UNITS)
                    f = true;//all ALL units
                if (id == ANY_BUILDING_2x2)//small buildings
                {
                    byte sz = *((byte*)UNIT_SIZE_TABLE + *((byte*)((uintptr_t)p + S_ID)) * 4);
                    f = sz == 2;
                }
                if (id == ANY_BUILDING_3x3)//med buildings
                {
                    byte sz = *((byte*)UNIT_SIZE_TABLE + *((byte*)((uintptr_t)p + S_ID)) * 4);
                    f = sz == 3;
                }
                if (id == ANY_BUILDING_4x4)//big buildings
                {
                    byte sz = *((byte*)UNIT_SIZE_TABLE + *((byte*)((uintptr_t)p + S_ID)) * 4);
                    f = sz == 4;
                }
                if (f)
                {
                    if (!check_unit_dead(p))
                    {
                        unit[units] = p;
                        units++;
                    }
                }
                p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
            }
        }
    }
}

void sort_complete()
{
    //only completed units stay in array
    int k = 0;
    for (int i = 0; i < units; i++)
    {
        if (check_unit_complete(unit[i]))
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void sort_in_region()
{
    //only units in region stay in array
    int k = 0;
    WORD x = 0, y = 0;
    for (int i = 0; i < units; i++)
    {
        x = *((WORD*)((uintptr_t)unit[i] + S_DRAW_X)) / 32;
        y = *((WORD*)((uintptr_t)unit[i] + S_DRAW_Y)) / 32;
        if (in_region((byte)x, (byte)y, reg[0], reg[1], reg[2], reg[3]))
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void sort_not_in_region()
{
    //only units not in region stay in array
    int k = 0;
    WORD x = 0, y = 0;
    for (int i = 0; i < units; i++)
    {
        x = *((WORD*)((uintptr_t)unit[i] + S_DRAW_X)) / 32;
        y = *((WORD*)((uintptr_t)unit[i] + S_DRAW_Y)) / 32;
        if (!in_region((byte)x, (byte)y, reg[0], reg[1], reg[2], reg[3]))
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void sort_target_in_region()
{
    //only units that have order coords in region stay in array
    int k = 0;
    byte x = 0, y = 0;
    for (int i = 0; i < units; i++)
    {
        x = *((byte*)((uintptr_t)unit[i] + S_ORDER_X));
        y = *((byte*)((uintptr_t)unit[i] + S_ORDER_Y));
        if (in_region(x, y, reg[0], reg[1], reg[2], reg[3]))
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void sort_stat(byte pr, int v, byte cmp)
{
    //only units stay in array if have property compared to value is true
    int k = 0;
    for (int i = 0; i < units; i++)
    {
        if (cmp_stat(unit[i], v, pr, cmp))
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void sort_tp_flag()
{
    //if not teleported by portal
    int k = 0;
    for (int i = 0; i < units; i++)
    {
        if ((*((byte*)((uintptr_t)unit[i] + S_FLAGS3)) & SF_TELEPORT) == 0)//unused in actual game flag
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void sort_hidden()
{
    //only not hidden units stay in array
    int k = 0;
    for (int i = 0; i < units; i++)
    {
        if (!check_unit_hidden(unit[i]))
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void sort_self(int* u)
{
    //unit remove self from array
    int k = 0;
    for (int i = 0; i < units; i++)
    {
        if (!(unit[i] == u))
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void sort_full_hp()
{
    //if hp not full
    int k = 0;
    for (int i = 0; i < units; i++)
    {
        byte id = *((byte*)((uintptr_t)unit[i] + S_ID));//unit id
        WORD mhp = *(WORD*)(UNIT_HP_TABLE + 2 * id);//max hp
        WORD hp = *((WORD*)((uintptr_t)unit[i] + S_HP));//unit hp
        if (hp < mhp)//hp not full
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void sort_fleshy()
{
    //only fleshy units stay in array
    int k = 0;
    for (int i = 0; i < units; i++)
    {
        byte id = *((byte*)((uintptr_t)unit[i] + S_ID));//unit id
        if ((*(int*)(UNIT_GLOBAL_FLAGS + id * 4) & IS_FLESHY) != 0)//fleshy global flag
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void sort_order_hp()
{
    //order array by hp from low to high
    for (int i = 0; i < units; i++)
    {
        int sm = i;
        for (int j = i + 1; j < units; j++)
        {
            WORD hpsm = *((WORD*)((uintptr_t)unit[sm] + S_HP));//unit hp
            WORD hpj = *((WORD*)((uintptr_t)unit[j] + S_HP));//unit hp
            if (hpj < hpsm)
            {
                sm = j;
            }
        }
        int* tmp = unit[i];
        unit[i] = unit[sm];
        unit[sm] = tmp;
    }
}

void sort_preplaced()
{
    int k = 0;
    for (int i = 0; i < units; i++)
    {
        if (!check_unit_preplaced(unit[i]))
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void sort_near_death()
{
    int k = 0;
    for (int i = 0; i < units; i++)
    {
        if (check_unit_near_death(unit[i]))
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void sort_attack_can_hit(int* p)
{
    //only units stay in array that *p can attack them
    int k = 0;
    for (int i = 0; i < units; i++)
    {
        int a = 0;
        a = ((int(*)(int*, int*))F_ATTACK_CAN_HIT)(p, unit[i]);//attack can hit original war2 function
        if (a != 0)
        {
            unitt[k] = unit[i];
            k++;
        }
    }
    units = k;
    for (int i = 0; i < units; i++)
    {
        unit[i] = unitt[i];
    }
}

void set_stat_all(byte pr, int v)
{
    for (int i = 0; i < units; i++)
    {
        set_stat(unit[i], v, pr);//set stat to all units in array
    }
}

void set_tp_flag(bool f)
{
    for (int i = 0; i < units; i++)
    {
        //set if unit can be teleported by portal (that flag unused in actual game)
        if (f)
            *((byte*)((uintptr_t)unit[i] + S_FLAGS3)) |= SF_TELEPORT;
        else
            *((byte*)((uintptr_t)unit[i] + S_FLAGS3)) &= ~SF_TELEPORT;
    }
}

void kill_all()
{
    for (int i = 0; i < units; i++)
    {
        unit_kill(unit[i]);//just kill all in array
    }
    units = 0;
}

void remove_all()
{
    for (int i = 0; i < units; i++)
    {
        unit_remove(unit[i]);//just kill all in array
    }
    units = 0;
}

void cast_all()
{
    for (int i = 0; i < units; i++)
    {
        unit_cast(unit[i]);//casting spells
    }
    units = 0;
}

void flame(int* p)
{
    //p - unit
    //original war2 func creates 1 flame with selected animation frame
    //flameshield have 5 flames
    ((void (*)(int*, int, int))F_CREATE_FLAME)(p, 0, 0);
    ((void (*)(int*, int, int))F_CREATE_FLAME)(p, 10, 4);
    ((void (*)(int*, int, int))F_CREATE_FLAME)(p, 20, 2);
    ((void (*)(int*, int, int))F_CREATE_FLAME)(p, 30, 3);
    ((void (*)(int*, int, int))F_CREATE_FLAME)(p, 40, 5);
}

void flame_all()
{
    for (int i = 0; i < units; i++)
    {
        flame(unit[i]);
    }
}

void damag(int* p, byte n)
{
    //dealt X damage to unit
    WORD hp = *((WORD*)((uintptr_t)p + S_HP));//unit hp
    if (hp > n)
    {
        hp -= n;
        set_stat(p, hp, S_HP);
    }
    else
    {
        set_stat(p, 0, S_HP);
        unit_kill(p);
    }
}

void damag_all(byte n)
{
    for (int i = 0; i < units; i++)
    {
        damag(unit[i], n);
    }
}

void heal(int* p, byte n)
{
    byte id = *((byte*)((uintptr_t)p + S_ID));//unit id
    WORD mhp = *(WORD*)(UNIT_HP_TABLE + 2 * id);//max hp
    WORD hp = *((WORD*)((uintptr_t)p + S_HP));//unit hp
    if (hp < mhp)
    {
        hp += n;
        if (hp > mhp)
            hp = mhp;//canot heal more than max hp
        set_stat(p, hp, S_HP);
    }
}

void heal_all(byte n)
{
    for (int i = 0; i < units; i++)
    {
        heal(unit[i], n);
    }
}

void mana_regen(int* p, byte n)
{
    byte tid = *((byte*)((uintptr_t)p + S_ID));
    bool f = (tid == U_MAGE) || (tid == U_DK) || (tid == U_PALADIN) || (tid == U_OGREMAGE) ||
        (tid == U_HADGAR) || (tid == U_TERON) || (tid == U_GULDAN) ||
        (tid == U_UTER) || (tid == U_TYRALYON) || (tid == U_CHOGAL) || (tid == U_DENTARG);
    if (f)
    {
        byte mp = *((byte*)((uintptr_t)p + S_MANA));//unit mana
        if (((int)mp + n) > 255)mp = 255;
        else mp += n;
        set_stat(p, mp, S_MANA);
    }
}

void mana_regen_all(byte n)
{
    for (int i = 0; i < units; i++)
    {
        mana_regen(unit[i], n);
    }
}

void give(int* p, byte owner)
{
    ((void (*)(int*, byte, byte))F_CAPTURE)(p, owner, 1);//original capture unit war2 func
    *(byte*)(RESCUED_UNITS + 2 * owner) -= 1;//reset number of captured units
}

void give_all(byte o)
{
    for (int i = 0; i < units; i++)
    {
        give(unit[i], o);
    }
}

bool unit_move(byte x, byte y, int* unit)
{
    if (x < 0)return false;
    if (y < 0)return false;//canot go negative
    byte mxs = *(byte*)MAP_SIZE;//map size
    if (x >= mxs)return false;
    if (y >= mxs)return false;//canot go outside map
    if (check_unit_hidden(unit))return false;//if unit not hidden
    byte cl = *((byte*)((uintptr_t)unit + S_MOVEMENT_TYPE));//movement type
    WORD mt = *(WORD*)(GLOBAL_MOVEMENT_TERRAIN_FLAGS + 2 * cl);//movement terrain flags

    int aa = 1;
    if ((cl == 0) || (cl == 3))//land and docked transport
    {
        aa = ((int (*)(int, int, int))F_XY_PASSABLE)(x, y, (int)mt);//original war2 func if terrain passable with that movement type
    }
    if ((x % 2 == 0) && (y % 2 == 0))//air and water
    {
        if ((cl == 1) || (cl == 2))
        {
            aa = ((int (*)(int, int, int))F_XY_PASSABLE)(x, y, (int)mt);
        }
    }
    if (aa == 0)
    {
        ((void (*)(int*))F_UNIT_UNPLACE)(unit);//unplace
        set_stat(unit, x, S_X);
        set_stat(unit, y, S_Y);//change real coords
        set_stat(unit, x * 32, S_DRAW_X);
        set_stat(unit, y * 32, S_DRAW_Y);//change draw sprite coords
        ((void (*)(int*))F_UNIT_PLACE)(unit);//place
        return true;
    }
    return false;
}

void move_all(byte x, byte y)
{
    sort_stat(S_ID, U_FARM, CMP_SMALLER);//non buildings
    sort_stat(S_ANIMATION, 2, CMP_EQ);//only if animation stop
    for (int i = 0; i < units; i++)
    {
        int xx = 0, yy = 0, k = 1;
        bool f = unit_move(x, y, unit[i]);
        xx--;
        while ((!f) & (k < 5))//goes in spiral like original war2 (size 5)
        {
            while ((!f) & (yy < k))
            {
                f = unit_move(x + xx, y + yy, unit[i]);
                yy++;
            }
            while ((!f) & (xx < k))
            {
                f = unit_move(x + xx, y + yy, unit[i]);
                xx++;
            }
            while ((!f) & (yy > -k))
            {
                f = unit_move(x + xx, y + yy, unit[i]);
                yy--;
            }
            while ((!f) & (xx >= -k))
            {
                f = unit_move(x + xx, y + yy, unit[i]);
                xx--;
            }
            k++;
        }
    }
}

void give_order(int* u, byte x, byte y, byte o)
{
    byte id = *((byte*)((uintptr_t)u + S_ID));
    if (id < U_FARM)
    {
        char buf[] = "\x0";
        bool f = ((o >= ORDER_SPELL_VISION) && (o <= ORDER_SPELL_ROT));
        if (f)
        {
            buf[0] = o;
            PATCH_SET((char*)GW_ACTION_TYPE, buf);
        }
        int* tr = NULL;
        for (int i = 0; i < 16; i++)
        {
            int* p = (int*)(UNITS_LISTS + 4 * i);//pointer to units list for each player
            if (p)
            {
                p = (int*)(*p);
                while (p)
                {
                    if (!check_unit_dead(p))
                    {
                        byte xx = *(byte*)((uintptr_t)p + S_X);
                        byte yy = *(byte*)((uintptr_t)p + S_Y);
                        if ((abs(x - xx) <= 2) && (abs(y - yy) <= 2))
                        {
                            if (f)
                            {
                                byte idd = *(byte*)((uintptr_t)p + S_ID);
                                if (idd < U_FARM)
                                    tr = p;
                            }
                            else
                                tr = p;
                        }
                    }
                    p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
                }
            }
        }
        bool aoe = (o == ORDER_SPELL_VISION) || (o == ORDER_SPELL_EXORCISM) || (o == ORDER_SPELL_FIREBALL) ||
            (o == ORDER_SPELL_BLIZZARD) || (o == ORDER_SPELL_EYE) || (o == ORDER_SPELL_RAISEDEAD) ||
            (o == ORDER_SPELL_DRAINLIFE) || (o == ORDER_SPELL_WHIRLWIND) || (o == ORDER_SPELL_RUNES) ||
            (o == ORDER_SPELL_ROT) || (o == ORDER_MOVE) || (o == ORDER_PATROL) ||
            (o == ORDER_ATTACK_AREA) || (o == ORDER_ATTACK_WALL) || (o == ORDER_STAND) ||
            (o == ORDER_ATTACK_GROUND) || (o == ORDER_ATTACK_GROUND_MOVE) || (o == ORDER_DEMOLISH) ||
            (o == ORDER_HARVEST) || (o == ORDER_RETURN) || (o == ORDER_UNLOAD_ALL);

        if (o != ORDER_ATTACK_WALL)
        {
            int ord = *(int*)(ORDER_FUNCTIONS + 4 * o);//orders functions
            if (!aoe && (tr != NULL) && (tr != u))
                ((void (*)(int*, int, int, int*, int))F_GIVE_ORDER)(u, 0, 0, tr, ord);//original war2 order
            if (aoe)
                ((void (*)(int*, int, int, int*, int))F_GIVE_ORDER)(u, x, y, NULL, ord);//original war2 order
        }
        else
        {
            byte oru = *(byte*)((uintptr_t)u + S_ORDER);
            if (oru!=ORDER_ATTACK_WALL)
            {
                int ord = *(int*)(ORDER_FUNCTIONS + 4 * ORDER_STOP);//orders functions
                ((void (*)(int*, int, int, int*, int))F_GIVE_ORDER)(u, 0, 0, NULL, ord);//original war2 order
            }
            set_stat(u, ORDER_ATTACK_WALL, S_NEXT_ORDER);
            set_stat(u, x, S_ORDER_X);
            set_stat(u, y, S_ORDER_Y);
        }

        if (f)
        {
            buf[0] = 0;
            PATCH_SET((char*)GW_ACTION_TYPE, buf);
        }
    }
}

void order_all(byte x, byte y, byte o)
{
    for (int i = 0; i < units; i++)
    {
        give_order(unit[i], x, y, o);
    }
}

bool check_ally(byte p1, byte p2)
{
    //check allied table
    return ((*(byte*)(ALLY + p1 + 16 * p2) != 0) & (*(byte*)(ALLY + p2 + 16 * p1) != 0));
}

void runestone()
{
    for (int i = 0; i < 16; i++)
    {
        int* p = (int*)(UNITS_LISTS + 4 * i);
        if (p)
        {
            p = (int*)(*p);
            while (p)
            {
                bool f = *((byte*)((uintptr_t)p + S_ID)) == U_RUNESTONE;
                if (f)
                {
                    if (!check_unit_dead(p) && check_unit_complete(p))
                    {//alive and completed runestone
                        byte x = *((byte*)((uintptr_t)p + S_X));
                        byte y = *((byte*)((uintptr_t)p + S_Y));
                        set_region((int)x - 4, (int)y - 4, (int)x + 5, (int)y + 5);//set region around myself
                        find_all_alive_units(ANY_MEN);
                        sort_in_region();
                        if (runes[8] == 1)//only allied units can can recieve bufs
                        {
                            byte o = *((byte*)((uintptr_t)p + S_OWNER));
                            for (int ui = 0; ui < 16; ui++)
                            {
                                if (!check_ally(o, ui))// tp
                                    sort_stat(S_OWNER, ui, CMP_NEQ);
                            }
                        }
                        if (runes[0] == 1)set_stat_all(S_INVIZ, (int)(*(WORD*)INVIZ_TIME));//inviz
                        if (runes[1] == 1)set_stat_all(S_SHIELD, (int)(*(WORD*)SHIELD_TIME));//shield
                        if (runes[2] == 1)set_stat_all(S_BLOOD, (int)(*(WORD*)BLOOD_TIME));//blood
                        if (runes[3] == 1)set_stat_all(S_HASTE, (int)(*(WORD*)HASTE_TIME1));//haste
                        if (runes[4] == 1)flame_all();
                        //5 mana
                        //6 heal
                        if (runes[7] == 1)//kill all not my owner units
                        {
                            byte o = *((byte*)((uintptr_t)p + S_OWNER));
                            sort_stat(S_OWNER, o, CMP_NEQ);
                            kill_all();
                        }
                        sort_stat(S_KILLS + 1, 0, CMP_EQ);
                        set_stat_all(S_KILLS + 1, 100);
                        if (runes[5] != 0)mana_regen_all(runes[5]);
                        if (runes[6] != 0)heal_all(runes[6]);
                    }
                }
                p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
            }
        }
    }
}

void portal()
{
    bool mp = true;
    for (int i = 0; i < 16; i++)
    {
        units = 0;
        int* p = (int*)(UNITS_LISTS + 4 * i);
        if (p)
        {
            p = (int*)(*p);
            int* fp = NULL;
            while (p)
            {
                bool f = *((byte*)((uintptr_t)p + S_ID)) == U_PORTAL;
                if (f)
                {
                    if (!check_unit_dead(p) && check_unit_complete(p))
                    {//alive and completed portal
                        if (!fp)fp = p;//remember first portal
                        byte tx = *((byte*)((uintptr_t)p + S_X)) + 1;
                        byte ty = *((byte*)((uintptr_t)p + S_Y)) + 1;//exit point is in center of portal
                        move_all(tx, ty);//teleport from previous portal
                        set_tp_flag(true);
                        set_stat_all(S_NEXT_ORDER, ORDER_STOP);
                        set_stat_all(S_ORDER_X, 128);
                        set_stat_all(S_ORDER_Y, 128);
                        byte x = *((byte*)((uintptr_t)p + S_X));
                        byte y = *((byte*)((uintptr_t)p + S_Y));
                        set_region((int)x - 1, (int)y - 1, (int)x + 4, (int)y + 4);//set region around myself
                        find_all_alive_units(ANY_MEN);
                        sort_in_region();
                        if (aport)
                        {
                            byte o = *((byte*)((uintptr_t)p + S_OWNER));
                            for (int ui = 0; ui < 16; ui++)
                            {
                                if (!check_ally(o, ui))//only allied units can tp
                                    sort_stat(S_OWNER, ui, CMP_NEQ);
                            }
                        }
                        sort_tp_flag();//flag show if unit was not teleported
                        mp = true;
                        if (mport)//only teleport if some caster near
                        {
                            mp = false;
                            for (int ui = 0; ui < units; ui++)
                            {
                                byte uid = *((byte*)((uintptr_t)unit[ui] + S_ID));
                                if ((uid == U_MAGE) || (uid == U_DK) || (uid == U_TERON) || (uid == U_HADGAR) || (uid == U_GULDAN))
                                    mp = true;//can tp only if mage nearby (teron hadgar and guldan too)
                            }
                        }
                        if (!mp)units = 0;
                        else
                        {
                            sort_stat(S_ORDER, ORDER_STOP, CMP_EQ);
                            sort_stat(S_ORDER_UNIT_POINTER, 0, CMP_EQ);
                            sort_stat(S_ORDER_UNIT_POINTER + 1, 0, CMP_EQ);
                            sort_stat(S_ORDER_UNIT_POINTER + 2, 0, CMP_EQ);
                            sort_stat(S_ORDER_UNIT_POINTER + 3, 0, CMP_EQ);
                            set_region((int)x, (int)y, (int)x + 3, (int)y + 3);//set region inside myself
                            sort_target_in_region();
                        }
                    }
                }
                p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
            }
            if (fp)//first portal teleports from last
            {
                byte tx = *((byte*)((uintptr_t)fp + S_X)) + 1;
                byte ty = *((byte*)((uintptr_t)fp + S_Y)) + 1;
                move_all(tx, ty);
                set_tp_flag(true);
                set_stat_all(S_NEXT_ORDER, ORDER_STOP);
                set_stat_all(S_ORDER_X, 128);
                set_stat_all(S_ORDER_Y, 128);
            }
        }
    }
    find_all_alive_units(ANY_MEN);
    set_tp_flag(false);//reset tp flags to all
}

void wharf()
{
    for (int i = 0; i < 16; i++)
    {
        int* p = (int*)(UNITS_LISTS + 4 * i);
        if (p)
        {
            p = (int*)(*p);
            while (p)
            {
                bool f = (*((byte*)((uintptr_t)p + S_ID)) == U_SHIPYARD) || (*((byte*)((uintptr_t)p + S_ID)) == U_WHARF);
                if (f)
                {
                    if (!check_unit_dead(p) && check_unit_complete(p))
                    {
                        byte x = *((byte*)((uintptr_t)p + S_X));
                        byte y = *((byte*)((uintptr_t)p + S_Y));
                        set_region((int)x - 2, (int)y - 2, (int)x + 4, (int)y + 4);//set region around myself
                        find_all_alive_units(ANY_MEN);
                        sort_in_region();
                        sort_hidden();
                        sort_stat(S_MOVEMENT_TYPE, MOV_WATER, CMP_BIGGER_EQ);//find ships - movement type >= water (2 or 3 actually(ships=2 transport=3))
                        byte o = *((byte*)((uintptr_t)p + S_OWNER));
                        for (int ui = 0; ui < 16; ui++)
                        {
                            if (!check_ally(o, ui))//only allied ships
                                sort_stat(S_OWNER, ui, CMP_NEQ);
                        }
                        heal_all(4);
                    }
                }
                p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
            }
        }
    }
}

void paladin()
{
    for (int ii = 0; ii < 16; ii++)
    {
        int* p = (int*)(UNITS_LISTS + 4 * ii);
        if (p)
        {
            p = (int*)(*p);
            while (p)
            {
                bool f = ((*((byte*)((uintptr_t)p + S_ID)) == U_PALADIN) ||
                    (*((byte*)((uintptr_t)p + S_ID)) == U_UTER) ||
                    (*((byte*)((uintptr_t)p + S_ID)) == U_TYRALYON));
                if (f)
                {
                    if (!check_unit_dead(p) && !check_unit_hidden(p))
                    {
                        byte o = *((byte*)((uintptr_t)p + S_OWNER));
                        if (((*(byte*)(SPELLS_LEARNED + 4 * o) & (1 << L_HEAL)) != 0) &&
                            ((*(byte*)(SPELLS_LEARNED + 4 * o) & (1 << L_GREATER_HEAL)) != 0))
                            //if player learned heal and autoheal
                        {
                            byte x = *((byte*)((uintptr_t)p + S_X));
                            byte y = *((byte*)((uintptr_t)p + S_Y));
                            set_region((int)x - 5, (int)y - 5, (int)x + 5, (int)y + 5);//set region around myself
                            find_all_alive_units(ANY_MEN);
                            sort_in_region();
                            sort_hidden();
                            sort_fleshy();//fleshy units (not heal cata and ships)
                            sort_full_hp();//if unit hp not full
                            sort_self(p);//not heal self
                            sort_order_hp();//heal lovest hp first
                            for (int ui = 0; ui < 16; ui++)
                            {
                                if (!check_ally(o, ui))//only allied units
                                    sort_stat(S_OWNER, ui, 1);
                            }
                            byte cost = *(byte*)(MANACOST + 2 * GREATER_HEAL);//2* cause manacost is WORD
                            for (int i = 0; i < units; i++)
                            {
                                byte mp = *((byte*)((uintptr_t)p + S_MANA));//paladin mp
                                if (mp >= cost)
                                {
                                    byte id = *((byte*)((uintptr_t)unit[i] + S_ID));//unit id
                                    WORD mhp = *(WORD*)(UNIT_HP_TABLE + 2 * id);//max hp
                                    WORD hp = *((WORD*)((uintptr_t)unit[i] + S_HP));//unit hp
                                    WORD shp = mhp - hp;//shortage of hp
                                    while (!(mp >= (shp * cost)) && (shp > 0))shp -= 1;
                                    if (shp > 0)//if can heal at least 1 hp
                                    {
                                        heal(unit[i], (byte)shp);
                                        mp -= shp * cost;
                                        *((byte*)((uintptr_t)p + S_MANA)) = mp;
                                        WORD xx = *((WORD*)((uintptr_t)unit[i] + S_DRAW_X));
                                        WORD yy = *((WORD*)((uintptr_t)unit[i] + S_DRAW_Y));
                                        ((void (*)(WORD, WORD, byte))F_BULLET_CREATE)(xx + 16, yy + 16, B_HEAL);//create heal effect
                                        ((void (*)(WORD, WORD, byte))F_SPELL_SOUND_XY)(xx + 16, yy + 16, SS_HEAL);//heal sound
                                    }
                                }
                                else i = units;
                            }
                        }
                    }
                }
                p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
            }
        }
    }
}

void transport()
{
    for (int i = 0; i < 16; i++)
    {
        int* p = (int*)(UNITS_LISTS + 4 * i);
        if (p)
        {
            p = (int*)(*p);
            while (p)
            {
                bool f = (*((byte*)((uintptr_t)p + S_ID)) == U_HTRANSPORT) || (*((byte*)((uintptr_t)p + S_ID)) == U_OTRANSPORT);
                if (f)
                {
                    if (!check_unit_dead(p) && (cmp_stat(p, ANIM_STOP, S_ANIMATION, CMP_EQ)))//if transport stop
                    {
                        byte x = *((byte*)((uintptr_t)p + S_X));
                        byte y = *((byte*)((uintptr_t)p + S_Y));
                        byte o = *((byte*)((uintptr_t)p + S_OWNER));
                        for (byte ui = 0; ui < 16; ui++)
                        {
                            set_region((int)x - 1, (int)y - 1, (int)x + 1, (int)y + 1);//set region around myself
                            find_all_alive_units(ANY_MEN);
                            sort_in_region();
                            sort_hidden();
                            sort_stat(S_MOVEMENT_TYPE, MOV_LAND, CMP_EQ);
                            sort_stat(S_ORDER, ORDER_STOP, CMP_EQ);
                            sort_stat(S_ANIMATION, ANIM_STOP, CMP_EQ);
                            sort_stat(S_OWNER, ui, CMP_EQ);
                            bool f = false;
                            if ((*(byte*)(CONTROLER_TYPE + o) == C_PLAYER))
                            {
                                f = true;
                                if ((*(byte*)(CONTROLER_TYPE + ui) == C_COMP))
                                {
                                    if (!check_ally(o, ui))//only allied comps
                                        sort_stat(S_OWNER, ui, CMP_NEQ);
                                }
                            }
                            if ((*(byte*)(CONTROLER_TYPE + o) == C_COMP))
                            {
                                f = true;
                                if ((*(byte*)(CONTROLER_TYPE + ui) == C_COMP))
                                {
                                    if (!check_ally(o, ui) || (ui == o))//only allied comps
                                        sort_stat(S_OWNER, ui, CMP_NEQ);
                                }
                                if ((*(byte*)(CONTROLER_TYPE + ui) == C_PLAYER))
                                {
                                    if (!check_ally(o, ui))//only allied players
                                    {
                                        sort_stat(S_OWNER, ui, CMP_NEQ);
                                    }
                                    sort_stat(S_ORDER_UNIT_POINTER, 0, CMP_EQ);
                                    sort_stat(S_ORDER_UNIT_POINTER + 1, 0, CMP_EQ);
                                    sort_stat(S_ORDER_UNIT_POINTER + 2, 0, CMP_EQ);
                                    sort_stat(S_ORDER_UNIT_POINTER + 3, 0, CMP_EQ);
                                    set_region((int)x, (int)y, (int)x, (int)y);//set region inside myself
                                    sort_target_in_region();
                                }
                            }
                            if (f)
                            {
                                sort_stat(S_KILLS + 1, 0, CMP_EQ);
                                set_stat_all(S_KILLS + 1, 100);
                                set_stat_all(S_NEXT_ORDER, ORDER_ENTER_TRANSPORT);
                                set_stat_all(S_ORDER_UNIT_POINTER, ((int)p) % 256);
                                set_stat_all(S_ORDER_UNIT_POINTER + 1, (((int)p) / 256) % 256);
                                set_stat_all(S_ORDER_UNIT_POINTER + 2, ((((int)p) / 256) / 256) % 256);
                                set_stat_all(S_ORDER_UNIT_POINTER + 3, (((((int)p) / 256) / 256) / 256) % 256);
                            }
                        }
                    }
                }
                p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
            }
        }
    }
}

void slow_aura(byte id)
{
    for (int i = 0; i < 16; i++)
    {
        int* p = (int*)(UNITS_LISTS + 4 * i);
        if (p)
        {
            p = (int*)(*p);
            while (p)
            {
                bool f = (*((byte*)((uintptr_t)p + S_ID)) == id);
                if (f)
                {
                    if (!check_unit_dead(p))
                    {
                        byte x = *((byte*)((uintptr_t)p + S_X));
                        byte y = *((byte*)((uintptr_t)p + S_Y));
                        set_region((int)x - 5, (int)y - 5, (int)x + 5, (int)y + 5);//set region around myself
                        find_all_alive_units(ANY_MEN);
                        sort_in_region();
                        byte o = *((byte*)((uintptr_t)p + S_OWNER));
                        for (int ui = 0; ui < 16; ui++)
                        {
                            if (check_ally(o, ui))//only enemies
                                sort_stat(S_OWNER, ui, CMP_NEQ);
                        }
                        set_stat_all(S_HASTE, 0xfcdf);//-800
                    }
                }
                p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
            }
        }
    }
}

void death_aura(byte id)
{
    for (int i = 0; i < 16; i++)
    {
        int* p = (int*)(UNITS_LISTS + 4 * i);
        if (p)
        {
            p = (int*)(*p);
            while (p)
            {
                bool f = (*((byte*)((uintptr_t)p + S_ID)) == id);
                if (f)
                {
                    if (!check_unit_dead(p))
                    {
                        byte mp = *((byte*)((uintptr_t)p + S_MANA));
                        byte x = *((byte*)((uintptr_t)p + S_X));
                        byte y = *((byte*)((uintptr_t)p + S_Y));
                        byte xx = *((byte*)((uintptr_t)p + S_ORDER_X));
                        byte yy = *((byte*)((uintptr_t)p + S_ORDER_Y));
                        set_stat(p, 255, S_MANA);
                        set_stat(p, x, S_ORDER_X);
                        set_stat(p, y, S_ORDER_Y);
                        char buf[] = "\x90\x90\x90\x90\x90\x90\x90\x90";
                        PATCH_SET((char*)RAISE_DEAD_DOING_SPELL1, buf);
                        char buf3[] = "\x90\x90\x90";
                        PATCH_SET((char*)RAISE_DEAD_DOING_SPELL2, buf3);
                        ((void (*)(int*))F_RAISE_DEAD)(p);
                        char buf2[] = "\x6a\x2\x53\xe8\x9f\x3\x1\x0";
                        PATCH_SET((char*)RAISE_DEAD_DOING_SPELL1, buf2);
                        char buf4[] = "\x83\xc4\x8";
                        PATCH_SET((char*)RAISE_DEAD_DOING_SPELL2, buf4);
                        set_stat(p, mp, S_MANA);
                        set_stat(p, xx, S_ORDER_X);
                        set_stat(p, yy, S_ORDER_Y);
                    }
                }
                p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
            }
        }
    }
}

void sneak(byte id)
{
    for (int i = 0; i < 16; i++)
    {
        int* p = (int*)(UNITS_LISTS + 4 * i);
        if (p)
        {
            p = (int*)(*p);
            while (p)
            {
                bool f = (*((byte*)((uintptr_t)p + S_ID)) == id);
                if (f)
                {
                    if (!check_unit_dead(p))
                    {
                        byte o = *((byte*)((uintptr_t)p + S_ORDER));
                        WORD n = *((WORD*)((uintptr_t)p + S_INVIZ));
                        if (o == ORDER_STAND)
                        {
                            if (n <= 10)set_stat(p, 10, S_INVIZ);
                        }
                    }
                }
                p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
            }
        }
    }
}

bool slot_alive(byte p)
{
    return (get_val(ALL_BUILDINGS, p) + get_val(ALL_UNITS, p)) != 0;//no units and buildings
}

void ally(byte p1, byte p2, byte a)
{
    //set ally bytes in table
    *(byte*)(ALLY + p1 + 16 * p2) = a;
    *(byte*)(ALLY + p2 + 16 * p1) = a;
    ((void (*)())F_RESET_COLORS)();//orig war2 func reset colors of sqares around units
}

void ally_one_sided(byte p1, byte p2, byte a)
{
    //set ally bytes in table
    *(byte*)(ALLY + p1 + 16 * p2) = a;
    ((void (*)())F_RESET_COLORS)();//orig war2 func reset colors of sqares around units
}

bool check_opponents(byte player)
{
    //check if player have opponents
    bool f = false;
    byte o = C_NOBODY;
    for (byte i = 0; i < 8; i++)
    {
        if (player != i)
        {
            if (slot_alive(i) && !check_ally(player, i))//if enemy and not dead
                f = true;
        }
    }
    return f;
}

void viz(int p1, int p2, byte a)
{
    //set vision bits
    byte v = *(byte*)(VIZ + p1);
    if (a == 0)
        v = v & (~(1 << p2));
    else
        v = v | (1 << p2);
    *(byte*)(VIZ + p1) = v;

    v = *(byte*)(VIZ + p2);
    if (a == 0)
        v = v & (~(1 << p1));
    else
        v = v | (1 << p1);
    *(byte*)(VIZ + p2) = v;
}

void viz_one_sided(int p1, int p2, byte a)
{
    //set vision bits
    byte v = *(byte*)(VIZ + p1);
    if (a == 0)
        v = v & (~(1 << p2));
    else
        v = v | (1 << p2);
    *(byte*)(VIZ + p1) = v;
}

void comps_vision(bool v)
{
    //allow comps give vision too
    if (v)
    {
        char o[] = "\x00";
        PATCH_SET((char*)COMPS_VIZION, o);
    }
    else
    {
        char o[] = "\xAA";
        PATCH_SET((char*)COMPS_VIZION, o);
    }
}

void change_res(byte p, byte r, byte k, int m)
{
    int a = GOLD;
    int* rs = (int*)a;
    DWORD res = 0;
    bool s = false;
    if (p >= 0 && p <= 8)//player id
    {
        switch (r)//select resource and add or substract it
        {
        case 0:
            a = GOLD + 4 * p;
            s = false;
            break;
        case 1:
            a = LUMBER + 4 * p;
            s = false;
            break;
        case 2:
            a = OIL + 4 * p;
            s = false;
            break;
        case 3:
            a = GOLD + 4 * p;
            s = true;
            break;
        case 4:
            a = LUMBER + 4 * p;
            s = true;
            break;
        case 5:
            a = OIL + 4 * p;
            s = true;
            break;
        default:break;
        }
        if (r >= 0 && r <= 5)
        {
            rs = (int*)a;//resourse pointer
            if (s)
            {
                if (*rs > (int)(k * m))
                    res = *rs - (k * m);
                else
                    res = 0;//canot go smaller than 0
            }
            else
            {
                if (*rs <= (256 * 256 * 256 * 32))
                    res = *rs + (k * m);
            }
            patch_setdword((DWORD*)a, res);
        }
    }
}

void add_total_res(byte p, byte r, byte k, int m)
{
    int a = GOLD_TOTAL;
    int* rs = (int*)a;
    DWORD res = 0;
    if (p >= 0 && p <= 8)//player id
    {
        switch (r)//select resource and add or substract it
        {
        case 0:
            a = GOLD_TOTAL + 4 * p;
            break;
        case 1:
            a = LUMBER_TOTAL + 4 * p;
            break;
        case 2:
            a = OIL_TOTAL + 4 * p;
            break;
        default:break;
        }
        if (r >= 0 && r <= 2)
        {
            rs = (int*)a;//resourse pointer
            if (*rs <= (256 * 256 * 256 * 32))
                res = *rs + (k * m);
            patch_setdword((DWORD*)a, res);
        }
    }
}

void set_res(byte p, byte r, byte k1, byte k2, byte k3, byte k4)
{
    //as before but dnt add or sub res, just set given value
    char buf[4] = { 0 };
    int a = 0;
    if (p >= 0 && p <= 8)
    {
        switch (r)
        {
        case 0:
            a = GOLD + 4 * p;
            break;
        case 1:
            a = LUMBER + 4 * p;
            break;
        case 2:
            a = OIL + 4 * p;
            break;
        default:break;
        }
        if (r >= 0 && r <= 2)
        {
            buf[0] = k1;
            buf[1] = k2;
            buf[2] = k3;
            buf[3] = k4;
            PATCH_SET((char*)a, buf);
        }
    }
}

bool cmp_res(byte p, byte r, byte k1, byte k2, byte k3, byte k4, byte cmp)
{
    //compare resource to value
    int a = GOLD;
    int* rs = (int*)a;
    if (p >= 0 && p <= 8)
    {
        switch (r)
        {
        case 0:
            a = GOLD + 4 * p;
            break;
        case 1:
            a = LUMBER + 4 * p;
            break;
        case 2:
            a = OIL + 4 * p;
            break;
        default:break;
        }
        if (r >= 0 && r <= 2)
        {
            rs = (int*)a;
            return cmp_args4(cmp, *rs, k1 + 256 * k2 + 256 * 256 * k3 + 256 * 256 * 256 * k4);
        }
    }
    return false;
}

int empty_false(byte) { return 0; }//always return false function
int empty_true(byte) { return 1; }//always return true function
void empty_build(int id)
{
    ((void (*)(int))F_TRAIN_UNIT)(id);//original build unit func
}

void build_forest(int)
{
    int* p = NULL;
    byte local = *(byte*)LOCAL_PLAYER;
    p = (int*)(UNITS_SELECTED + 9 * 4 * local);
    if (p)
    {
        p = (int*)(*p);
        if (p)
        {
            byte id = *((byte*)((uintptr_t)p + S_ID));
            byte o = *((byte*)((uintptr_t)p + S_OWNER));
            if (o == local)
            {
                if (id == U_PEASANT)
                {
                    ((void (*)(int))F_BUILD_BUILDING)(U_PIGFARM);//original build func
                }
                if (id == U_PEON)
                {
                    ((void (*)(int))F_BUILD_BUILDING)(U_FARM);//original build func
                }
            }
        }
    }
}

int _2tir() 
{ 
    if ((get_val(TH2, *(byte*)LOCAL_PLAYER) != 0) || (get_val(TH3, *(byte*)LOCAL_PLAYER) != 0))
        return 1;
    else
        return 0;
}

int check_hero(byte id)
{
    byte local = *(byte*)LOCAL_PLAYER;
    for (int i = 0; i < 16; i++)
    {
        if (heros[i] == id)
        {
            if (herosb[i])
            {
                //return false if player already builds that unit
                return 0;
            }
        }
    }
    //substitute for original war2 func that check if player have that unit
    for (int i = 0; i < 16; i++)
    {
        int* p = (int*)(UNITS_LISTS + 4 * i);
        if (p)
        {
            p = (int*)(*p);
            while (p)
            {
                byte o = *((byte*)((uintptr_t)p + S_OWNER));
                if (o == *(byte*)LOCAL_PLAYER)
                {
                    byte idd = *((byte*)((uintptr_t)p + S_ID));
                    bool f = idd == id;
                    if (f)
                    {
                        if (!check_unit_dead(p))
                        {
                           //return false if player already have that unit
                            return 0;
                        }
                    }
                    f = (idd == U_TOWN_HALL) || (idd == U_GREAT_HALL) ||
                        (idd == U_STRONGHOLD) || (idd == U_KEEP) ||
                        (idd == U_CASTLE) || (idd == U_FORTRESS);
                    if (f)
                    {
                        if (!check_unit_dead(p) && check_unit_complete(p))
                        {
                            if (*((byte*)((uintptr_t)p + S_BUILD_ORDER)) == 0)
                            {
                                if (*((byte*)((uintptr_t)p + S_BUILD_TYPE)) == id)
                                {
                                    if (*((WORD*)((uintptr_t)p + S_BUILD_PROGRES)) != 0)
                                    {
                                        //return false if player already building that unit
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
                p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
            }
        }
    }
    return 1;
}

void build3(bool b)
{
    //third build button for peons
    if (b)
    {
        char psnt[] = "\x9";
        PATCH_SET((char*)PEASANT_BUTTONS, psnt);
        char peon[] = "\x9\x0\x0\x0\x20\xf7\x48\x0";
        patch_setdword((DWORD*)(peon + 4), (DWORD)peon_build3);
        PATCH_SET((char*)PEON_BUTTONS, peon);

        char p1[] = "\x8\x0\x6d\x0\xf0\x40\x44\x0\x70\xa6\x44\x0\x0\x6d\x38\x1\x0\x0\x0\x0";
        PATCH_SET((char*)PEASANT_RE_BUTTONS, p1);

        if (b3rune)
        {
            patch_setdword((DWORD*)(build_3 + 4), (DWORD)F_ALWAYS_TRUE);
        }
        else
        {
            int (*r) (byte) = empty_false;
            patch_setdword((DWORD*)(build_3 + 4), (DWORD)r);
        }

        if (b3port)
        {
            patch_setdword((DWORD*)(build_3 + 24), (DWORD)F_ALWAYS_TRUE);
        }
        else
        {
            int (*r) (byte) = empty_false;
            patch_setdword((DWORD*)(build_3 + 24), (DWORD)r);
        }

        if (b3cirl)
        {
            patch_setdword((DWORD*)(build_3 + 44), (DWORD)F_ALWAYS_TRUE);
        }
        else
        {
            int (*r) (byte) = empty_false;
            patch_setdword((DWORD*)(build_3 + 44), (DWORD)r);
        }

        if (b3mine)
        {
            patch_setdword((DWORD*)(build_3 + 64), (DWORD)F_ALWAYS_TRUE);
        }
        else
        {
            int (*r) (byte) = empty_false;
            patch_setdword((DWORD*)(build_3 + 64), (DWORD)r);
        }

        if (b3forest)
        {
            patch_setdword((DWORD*)(build_3 + 84), (DWORD)F_ALWAYS_TRUE);
        }
        else
        {
            int (*r) (byte) = empty_false;
            patch_setdword((DWORD*)(build_3 + 84), (DWORD)r);
        }

        void (*r) (int) = build_forest;
        patch_setdword((DWORD*)(build_3 + 88), (DWORD)r);

        char b3[] = "\x6\x0\x0\x0\x0\xf8\x48\x0";
        patch_setdword((DWORD*)(b3 + 4), (DWORD)build_3);
        PATCH_SET((char*)DEAD_BLDG_BUTTONS, b3);
    }
    else
    {
        char psnt[] = "\x8";
        PATCH_SET((char*)PEASANT_BUTTONS, psnt);
        char peon[] = "\x8\x0\x0\x0\x28\x22\x4a\x0";
        PATCH_SET((char*)PEON_BUTTONS, peon);
        char p1[] = "\x0\x0\x54\x0\xf0\x40\x44\x0\x90\x66\x43\x0\x0\x0\x88\x1\x2\x0\x0\x0";
        PATCH_SET((char*)PEASANT_RE_BUTTONS, p1);
        char b3[] = "\x0\x0\x0\x0\x0\x0\x0";
        PATCH_SET((char*)DEAD_BLDG_BUTTONS, b3);
    }
}

void sheep(bool b)
{
    //sheeps from farms
    if (b)
    {
        char farm[] = "\x1\x0\x0\x0\x0\xf7\x48\x0\x1\x0\x0\x0\x0\xf7\x48\x0";
        patch_setdword((DWORD*)(farm + 4), (DWORD)sheep_build);
        patch_setdword((DWORD*)(farm + 12), (DWORD)sheep_build);
        PATCH_SET((char*)FARM_BUTTONS, farm);

        int (*r) (byte) = empty_true;//sheep check function
        void (*r1) (int) = empty_build;//sheep build function

        patch_setdword((DWORD*)(sheep_build + 4), (DWORD)r);
        patch_setdword((DWORD*)(sheep_build + 8), (DWORD)r1);
    }
    else
    {
        char farm[] = "\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0";
        PATCH_SET((char*)FARM_BUTTONS, farm);
    }
}

void demon(bool b)
{
    if (b)
    {
        char d[] = "\x1\x0\x0\x0\x0\xf7\x48\x0";
        patch_setdword((DWORD*)(d+4), (DWORD)demon_build);
        PATCH_SET((char*)CIRCLE_BUTTONS, d);

        int (*r) () = _2tir;//need 2 tier TH to build demon
        patch_setdword((DWORD*)(demon_build + 4), (DWORD)r);
    }
    else
    {
        char d[] = "\x0\x0\x0\x0\x0\x0\x0\x0";
        PATCH_SET((char*)CIRCLE_BUTTONS, d);
    }
}

byte get_icon(byte id)
{
    switch (id)
    {
    case U_ALLERIA:return 187; break;//alleria
    case U_TERON:return 189; break;//teron
    case U_KURDRAN:return 191; break;//kurdran
    case U_DENTARG:return 194; break;//dentarg
    case U_HADGAR:return 193; break;//hadgar
    case U_GROM:return 190; break;//grom
    case U_DEATHWING:return 192; break;//deathwing
    case U_TYRALYON:return 195; break;//tyralyon
    case U_DANATH:return 188; break;//danat
    case U_KARGATH:return 186; break;//kargat
    case U_CHOGAL:return 36; break;//chogal
    case U_LOTHAR:return 32; break;//lotar
    case U_GULDAN:return 33; break;//guldan
    case U_UTER:return 34; break;//uter
    case U_ZULJIN:return 35; break;//zuljin
    default:break;
    }
    return 113;
}

byte get_tbl(byte id)
{
    switch (id)
    {
    case U_ALLERIA:return '\x10'; break;//alleria
    case U_TERON:return '\x17'; break;//teron
    case U_KURDRAN:return '\x27'; break;//kurdran
    case U_DENTARG:return '\x14'; break;//dentarg
    case U_HADGAR:return '\x19'; break;//hadgar
    case U_GROM:return '\x1a'; break;//grom
    case U_DEATHWING:return '\x28'; break;//deathwing
    case U_TYRALYON:return '\x13'; break;//tyralyon
    case U_DANATH:return '\x1b'; break;//danat
    case U_KARGATH:return '\x22'; break;//kargat
    case U_CHOGAL:return '\x16'; break;//chogal
    case U_LOTHAR:return '\x21'; break;//lotar
    case U_GULDAN:return '\x1f'; break;//guldan
    case U_UTER:return '\x15'; break;//uter
    case U_ZULJIN:return '\xf'; break;//zuljin
    default:break;
    }
    return '\xdf';
}

DWORD CALLBACK hero_thread(LPVOID lpParam)
{
    Sleep(2000);
    for (int i = 0; i < 16; i++)
    {
        herosb[i] = false;
    }
    ExitThread(0);
}

void build_hero(int id)
{
    for (int i = 0; i < 16; i++)
    {
        if ((!herosb[i]) && (heros[i] == (id % 256)))
        {
            herosb[i] = true;
            DWORD dw = 0;
            CreateThread(NULL, 0, hero_thread, &dw, 0, NULL);
        }
    }
    ((void (*)(int))F_TRAIN_UNIT)(id);//original build func
    ((void (*)(int))F_CHANGE_STATUS)(0x6e);//change status
    ((void (*)())F_STATUS_REDRAW)();//status redraw
}

void heroes(bool b)
{
    if (b)
    {
        for (int i = 1; i < 20; i++)
        {
            hhero[i] = build_3[100 + i];
            ohero[i] = build_3[100 + i];
        }
        byte local = *(byte*)LOCAL_PLAYER;
        int l = 0;
        l += local;
        byte mx = 2;
        if (get_val(TH2, l) != 0)mx = 5;
        if (get_val(TH3, l) != 0)mx = 8;
        byte k = 1;
        for (byte i = 1; i < 9; i++)
        {
            byte id = heros[i - 1];
            if (id == 0) id = U_CRITTER;
            if (id != 0)
            {
                k++;
                byte ico = get_icon(id);
                hhero[20 * i + 0] = i;//button id
                hhero[20 * i + 1] = '\x0';//button id?
                hhero[20 * i + 2] = ico;//icon
                hhero[20 * i + 3] = '\x0';//icon

                int (*r) (byte) = check_hero;//hero check function
                if ((i > mx) || (id == U_CRITTER))r = empty_false;
                patch_setdword((DWORD*)(hhero + (20 * i + 4)), (DWORD)r);

                void (*r1) (int) = build_hero;//hero build function
                patch_setdword((DWORD*)(hhero + (20 * i + 8)), (DWORD)r1);

                hhero[20 * i + 12] = id;//arg
                hhero[20 * i + 13] = id;//unit id
                hhero[20 * i + 14] = get_tbl(id);//string from tbl
                hhero[20 * i + 15] = '\x1';//string from tbl
                hhero[20 * i + 16] = '\x0';//flags?
                hhero[20 * i + 17] = '\x0';//flags?
                hhero[20 * i + 18] = '\x0';//flags?
                hhero[20 * i + 19] = '\x0';//flags?
            }
            else i = 10;
        }
        char b1[] = "\x0\x0\x0\x0\x0\xf8\x48\x0";
        b1[0] = k;
        patch_setdword((DWORD*)(b1+4), (DWORD)hhero);
        PATCH_SET((char*)DEAD_BLDG2_BUTTONS, b1);
        k = 1;
        for (byte i = 1; i < 9; i++)
        {
            byte id = heros[i + 8 - 1];
            if (id == 0) id = U_CRITTER;
            if (id != 0)
            {
                k++;
                byte ico = get_icon(id);
                ohero[20 * i + 0] = i;//button id
                ohero[20 * i + 1] = '\x0';//button id?
                ohero[20 * i + 2] = ico;//icon
                ohero[20 * i + 3] = '\x0';//icon

                int (*r) (byte) = check_hero;//hero check function
                if ((i > mx) || (id == U_CRITTER))r = empty_false;
                patch_setdword((DWORD*)(ohero + (20 * i + 4)), (DWORD)r);

                void (*r1) (int) = build_hero;//hero build function
                patch_setdword((DWORD*)(ohero + (20 * i + 8)), (DWORD)r1);

                ohero[20 * i + 12] = id;//arg
                ohero[20 * i + 13] = id;//unit id
                ohero[20 * i + 14] = get_tbl(id);//string from tbl
                ohero[20 * i + 15] = '\x1';//string from tbl
                ohero[20 * i + 16] = '\x0';//flags?
                ohero[20 * i + 17] = '\x0';//flags?
                ohero[20 * i + 18] = '\x0';//flags?
                ohero[20 * i + 19] = '\x0';//flags?
            }
            else i = 10;
        }
        char b2[] = "\x0\x0\x0\x0\x0\xf8\x48\x0";
        b2[0] = k;
        patch_setdword((DWORD*)(b2 + 4), (DWORD)ohero);
        PATCH_SET((char*)DEAD_BLDG3_BUTTONS, b2);
    }
    else
    {
        char buf[] = "\x0\x0\x0\x0\x0\x0\x0";
        PATCH_SET((char*)DEAD_BLDG2_BUTTONS, buf);
        PATCH_SET((char*)DEAD_BLDG3_BUTTONS, buf);
    }
}

void repair_all(bool b)
{
    //peon can repair all units
    if (b)
    {
        char bau[] = "\xeb";//0x75
        PATCH_SET((char*)REPAIR_FLAG_CHECK, bau);
    }
    else
    {
        char bau[] = "\x75";
        PATCH_SET((char*)REPAIR_FLAG_CHECK, bau);
    }
}

void repair_cat(bool b)
{
    //peon can repair unit if it have transport flag OR catapult flag
    if (b)
    {
        char r1[] = "\xeb\x75\x90\x90\x90";//f6 c4 04 74 14
        PATCH_SET((char*)REPAIR_FLAG_CHECK2, r1);
        char r2[] = "\x66\xa9\x04\x04\x74\x9c\xeb\x86";
        PATCH_SET((char*)REPAIR_CODE_CAVE, r2);
    }
    else
    {
        char r1[] = "\xf6\xc4\x4\x74\x14";
        PATCH_SET((char*)REPAIR_FLAG_CHECK2, r1);
    }
}

void call_default_kill()//default kill all victory
{
    byte l = *(byte*)LOCAL_PLAYER;
    if (!slot_alive(l))lose(true);
    else
    {
        if (!check_opponents(l))win(true);
    }
}

void fireball_dmg(byte dmg)
{
    char fb[] = "\x28";//40 default
    fb[0] = dmg;
    PATCH_SET((char*)FIREBALL_DMG, fb);
}

void buff_time(byte bf, byte t1, byte t2)
{
    char tm[] = "\x0\x0";
    switch (bf)
    {
    case 0:
        tm[0] = t1;
        tm[1] = t2;
        PATCH_SET((char*)INVIZ_TIME, tm);//2000 default
        break;
    case 1:
        tm[0] = t1;
        tm[1] = t2;
        PATCH_SET((char*)BLOOD_TIME, tm);//1000 default
        break;
    case 2:
        tm[0] = t1;
        tm[1] = t2;
        PATCH_SET((char*)SHIELD_TIME, tm);//500 default
        break;
    case 3:
        tm[0] = t1;
        tm[1] = t2;
        PATCH_SET((char*)HASTE_TIME1, tm);//1000 default
        PATCH_SET((char*)HASTE_TIME2, tm);
        break;
    case 4:
        int tt = 0xffff - (t1 + 256 * t2);
        tm[0] = tt % 256;
        tm[1] = tt / 256;
        PATCH_SET((char*)SLOW_TIME1, tm);//1000 default
        PATCH_SET((char*)SLOW_TIME2, tm);
        break;
    }
}

void fireshield_flyers(bool b)
{
    //allow cast fireshield on flyers
    if (b)
    {
        char bau[] = "\x90\x90";//75 51
        PATCH_SET((char*)FIRESHIELD_FLYERS, bau);
    }
    else
    {
        char bau[] = "\x75\x51";
        PATCH_SET((char*)FIRESHIELD_FLYERS, bau);
    }
}

void trigger_time(byte tm)
{
    //war2 will call victory check function every 200 game ticks
    char ttime[] = "\xc8";//200 default
    ttime[0] = tm;
    PATCH_SET((char*)TRIG_TIME, ttime);
}

void manacost(byte id, byte c)
{
    //spells cost of mana
    char mana[] = "\x1";
    mana[0] = c;
    PATCH_SET((char*)(MANACOST + 2 * id), mana);
}

void upgr(byte id, byte c)
{
    //upgrades power
    char up[] = "\x1";
    up[0] = c;
    PATCH_SET((char*)(UPGRD + id), up);
}

void no_random_dmg(bool b)
{
    //always max damage instead of random (SC1-style)
    if (b)
    {
        char b1[] = "\x1a";
        PATCH_SET((char*)DAMAGE_AREA1, b1);
        char b2[] = "\x19";
        PATCH_SET((char*)DAMAGE_AREA2, b2);
        char b3[] = "\x90\x90";
        PATCH_SET((char*)DAMAGE_AREA3, b3);
        PATCH_SET((char*)DAMAGE_AREA4, b3);
        char b4[] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
        PATCH_SET((char*)DAMAGE_UNIT_VS_UNIT, b4);
    }
    else
    {
        char b1[] = "\x6";
        PATCH_SET((char*)DAMAGE_AREA1, b1);
        char b2[] = "\x5";
        PATCH_SET((char*)DAMAGE_AREA2, b2);
        char b3[] = "\xf7\xf1";
        PATCH_SET((char*)DAMAGE_AREA3, b3);
        PATCH_SET((char*)DAMAGE_AREA4, b3);
        char b4[] = "\x8d\x47\x1\x99\x2b\xc2\x8b\xf8\xd1\xff\xe8\x8d\x91\x6\x0\x8d\x4f\x1\x33\xd2\xf7\xf1\x3\xfa";
        PATCH_SET((char*)DAMAGE_UNIT_VS_UNIT, b4);
    }
}

void blood_fix(bool b)
{
    //remove bloodlust from game (and will make X2 in damage() function manually)
    if (b)
    {
        blood_f = true;//to make X2 in damage() function manually
        char b1[] = "\x90\x90";
        PATCH_SET((char*)BLOOD_CALC1, b1);
        char b2[] = "\x90\x90";
        PATCH_SET((char*)BLOOD_CALC2, b2);
    }
    else
    {
        blood_f = false;
        char b1[] = "\x3\xf6";
        PATCH_SET((char*)BLOOD_CALC1, b1);
        char b2[] = "\x3\xc0";
        PATCH_SET((char*)BLOOD_CALC2, b2);
    }
}

void center_view(byte x, byte y)
{
    ((void (*)(byte, byte))F_MINIMAP_CLICK)(x, y);//original war2 func that called when player click on minimap
}

void comp_aggro(int* trg, int* atk)
{
    byte own1 = *((byte*)((uintptr_t)trg + S_OWNER));
    byte own2 = *((byte*)((uintptr_t)atk + S_OWNER));
    if (own1 != own2)
    {
        if (check_ally(own1, own2))//if we allies
        {
            byte o1 = *(byte*)(CONTROLER_TYPE + own1);
            byte o2 = *(byte*)(CONTROLER_TYPE + own2);
            if ((o1 == C_COMP) && (o2 == C_PLAYER))//if target unit is comp and attacker is real player
            {
                ally(own1, own2, 0);
                viz(own1, own2, 0);
                //turn off ally and viz
            }
        }
    }
}

void capture(int* trg, int* atk)
{
    byte own1 = *((byte*)((uintptr_t)trg + S_OWNER));
    byte own2 = *((byte*)((uintptr_t)atk + S_OWNER));
    if (own1 != own2)
    {
        if (!pcpt || ((*((byte*)((uintptr_t)atk + S_ID)) == U_PEASANT) || (*((byte*)((uintptr_t)atk + S_ID)) == U_PEON)))
        {//if only peons can capture and attacker is peon(or peasant)
            if (cmp_stat(trg, U_FARM, S_ID, CMP_BIGGER_EQ))//only buildings (id >= farm)
            {
                if (check_unit_complete(trg))//completed buildings
                {
                    byte tid = *((byte*)((uintptr_t)trg + S_ID));//unit id
                    WORD mhp = *(WORD*)(UNIT_HP_TABLE + 2 * tid);//max hp
                    WORD hp = *((WORD*)((uintptr_t)trg + S_HP));//unit hp
                    if ((float)hp <= (((float)mhp / 100.0 * 5) + 1))//if hp<=5%
                    {
                        heal(trg, (byte)(((float)mhp / 100.0 * 5) + 1));//heal 5% hp so that it will not die suddenly
                        if (thcpt)//if th captured, capture all
                        {
                            bool mf = (tid == U_TOWN_HALL) || (tid == U_GREAT_HALL);
                            if (get_val(TH2, (int)own1) != 0)mf = (tid == U_KEEP) || (tid == U_STRONGHOLD);
                            if (get_val(TH3, (int)own1) != 0)mf = (tid == U_CASTLE) || (tid == U_FORTRESS);
                            if (mf)
                            {//THs of 1 2 and 3 tier
                                captk = 0;
                                for (int i = 0; i < 16; i++)
                                {
                                    int* p = (int*)(UNITS_LISTS + 4 * i);
                                    if (p)
                                    {
                                        p = (int*)(*p);
                                        while (p)
                                        {
                                            if (!check_unit_dead(p))
                                            {
                                                if (cmp_stat(p, (int)own1, S_OWNER, CMP_EQ))//capture all units of that player
                                                {
                                                    capt[captk] = p;
                                                    captk++;
                                                }
                                            }
                                            p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
                                        }
                                    }
                                }
                                for (int i = 0; i < captk; i++)
                                    give(capt[i], own2);
                            }
                        }
                        give(trg, own2);
                    }
                }
            }
        }
    }
}

void steal_res(int* trg, int* atk)
{
    byte own1 = *((byte*)((uintptr_t)trg + S_OWNER));
    byte own2 = *((byte*)((uintptr_t)atk + S_OWNER));
    if ((own1 != own2) && !check_ally(own1, own2))
    {
        if (cmp_stat(trg, U_FARM, S_ID, CMP_BIGGER_EQ))//only buildings (id >= farm)
        {
            if (check_unit_complete(trg))//completed buildings
            {
                if (cmp_stat(atk, U_FARM, S_ID, CMP_SMALLER))//only units (not towers)
                {
                    byte aid = *((byte*)((uintptr_t)atk + S_ID));
                    byte ar = *(byte*)(UNIT_RANGE_TABLE + aid);
                    if (ar < 2)
                    {
                        if (cmp_res(own1, 0, 2, 0, 0, 0, CMP_BIGGER_EQ))//2 gold
                        {
                            change_res(own1, 3, 2, 1);
                            change_res(own2, 0, 2, 1);
                        }
                        if (cmp_res(own1, 1, 1, 0, 0, 0, CMP_BIGGER_EQ))//1 lumber
                        {
                            change_res(own1, 4, 1, 1);
                            change_res(own2, 1, 1, 1);
                        }
                    }
                }
            }
        }
    }
}

void mana_burn(int* trg, int* atk)
{
    byte aid = *((byte*)((uintptr_t)atk + S_ID));
    if (aid == U_DEMON)//only demon have manaburn (you can put any other unit id here)
    {
        byte tid = *((byte*)((uintptr_t)trg + S_ID));
        bool f = (tid == U_MAGE) || (tid == U_DK) || (tid == U_PALADIN) || (tid == U_OGREMAGE) ||
            (tid == U_HADGAR) || (tid == U_TERON) || (tid == U_GULDAN) ||
            (tid == U_UTER) || (tid == U_TYRALYON) || (tid == U_CHOGAL) || (tid == U_DENTARG);
        if (f)
        {
            byte mp = *((byte*)((uintptr_t)trg + S_MANA));
            byte dmp = mp;
            if (dmp > 30)dmp = 30;
            mp -= dmp;
            set_stat(trg, mp, S_MANA);
            WORD hp = *((WORD*)((uintptr_t)trg + S_HP));
            if (hp != 0)
            {
                if (hp > dmp)hp -= dmp;
                else hp = 1;
            }
            set_stat(trg, hp, S_HP);
        }
    }
}

bool vamp_aura(int* trg, int* atk, byte id)
{
    byte tid = *((byte*)((uintptr_t)trg + S_ID));//unit id
    if ((*(int*)(UNIT_GLOBAL_FLAGS + tid * 4) & IS_FLESHY) != 0)//fleshy global flag
    {
        byte aid = *((byte*)((uintptr_t)atk + S_ID));//unit id
        if ((*(int*)(UNIT_GLOBAL_FLAGS + aid * 4) & IS_FLESHY) != 0)//fleshy global flag
        {
            byte x = *((byte*)((uintptr_t)atk + S_X));
            byte y = *((byte*)((uintptr_t)atk + S_Y));
            set_region((int)x - 5, (int)y - 5, (int)x + 5, (int)y + 5);//set region around myself
            find_all_alive_units(ANY_MEN);
            sort_in_region();
            sort_stat(S_ID, id, CMP_EQ);
            byte o = *((byte*)((uintptr_t)atk + S_OWNER));
            for (int ui = 0; ui < 16; ui++)
            {
                if (!check_ally(o, ui))
                    sort_stat(S_OWNER, ui, CMP_NEQ);
            }
            return units != 0;
        }
    }
    return false;
}

bool devotion_aura(int* trg, byte id)
{
    byte tid = *((byte*)((uintptr_t)trg + S_ID));//unit id
    if (tid < U_FARM)//not buildings
    {
        byte x = *((byte*)((uintptr_t)trg + S_X));
        byte y = *((byte*)((uintptr_t)trg + S_Y));
        set_region((int)x - 5, (int)y - 5, (int)x + 5, (int)y + 5);//set region around myself
        find_all_alive_units(id);
        sort_in_region();
        byte o = *((byte*)((uintptr_t)trg + S_OWNER));
        for (int ui = 0; ui < 16; ui++)
        {
            if (!check_ally(o, ui))
                sort_stat(S_OWNER, ui, CMP_NEQ);
        }
        return units != 0;
    }
    else
        return false;
}

void unit_timer()
{
    //timer for transport and runestone heal
    find_all_alive_units(ANY_MEN);
    sort_hidden();
    sort_stat(S_ID, U_HTRANSPORT, CMP_NEQ);
    sort_stat(S_ID, U_OTRANSPORT, CMP_NEQ);
    for (int i = 0; i < units; i++)
    {
        byte r = *(byte*)((uintptr_t)unit[i] + S_KILLS + 1);
        if (r > 0)r -= 1;
        set_stat(unit[i], r, S_KILLS + 1);
    }
}

PROC g_proc_0045271B;
void update_spells()
{
    ((void (*)())g_proc_0045271B)();//original
    // this function called every game tick
    // you can place your self-writed functions here in the end if need
    unit_timer();
    if (A_portal)portal();
    if (A_transport)transport();
    if (A_autoheal)paladin();
    if (A_runestone)runestone();
    for (int i = 0; i < 255; i++)
    {
        if (m_slow_aura[i] != 255)
            slow_aura(m_slow_aura[i]);
        else
            i = 256;
    }
    for (int i = 0; i < 255; i++)
    {
        if (m_death_aura[i] != 255)
            death_aura(m_death_aura[i]);
        else
            i = 256;
    }
    for (int i = 0; i < 255; i++)
    {
        if (m_sneak[i] != 255)
            sneak(m_sneak[i]);
        else
            i = 256;
    }
    //PLACE your new functions here
    
    //PLACE your new functions here
}

void seq_change(int* u, byte tt)
{
    //change animation speeds
    //USE this function CAREFULLY
    byte t = tt;
    /*
    if (FALSE)//remove this and USE this function CAREFULLY
    {
        if (t == 1)
        {
            byte t = *((byte*)((uintptr_t)u + S_ANIMATION_TIMER));
            byte id = *((byte*)((uintptr_t)u + S_ID));
            if (id == U_ARCHER)
            {
                byte a = *((byte*)((uintptr_t)u + S_ANIMATION));
                byte f = *((byte*)((uintptr_t)u + S_FRAME));
                if (a == ANIM_MOVE)
                    if (t > 1)t -= 1;//all archer movement timers will be 1 frame faster
                //but cannot be less than 1 !!!!!!!!!!
                if (a == ANIM_ATTACK)
                {
                    if (f != 0)
                    {
                        if (t > 5)t -= 5;
                        else t = 1;//ultra fast shooting for archer
                    }
                    else
                    {
                        if (t > 25)t -= 25;
                        else t = 1;//ultra fast shooting for archer
                    }
                    set_stat(u, 1, S_ATTACK_COUNTER);//ultra fast shooting for archer
                }
                set_stat(u, t, S_ANIMATION_TIMER);
            }
        }
    }
    */
}

PROC g_proc_004522B9;
int seq_run(int* u)
{
    byte t = *((byte*)((uintptr_t)u + S_ANIMATION_TIMER));
    int original = ((int (*)(int*))g_proc_004522B9)(u);//original
    seq_change(u, t);
    return original;
}

PROC g_proc_00409F3B, //action
g_proc_0040AF70, g_proc_0040AF99, //demolish
g_proc_0041038E, g_proc_00410762, //bullet
g_proc_004428AD;//spell
char fdmg = 0;//final damage
void damage(int* atk, int* trg, char dmg)
{
    fdmg = dmg;
    if ((trg != NULL) && (atk != NULL))
    {
        byte aid = *((byte*)((uintptr_t)atk + S_ID));//attacker id
        byte tid = *((byte*)((uintptr_t)trg + S_ID));//target id
        byte dmg2 = dmg;//can deal damage by default
        int i = 0;
        while (i < 255)
        {
            if ((tid == ut[i]) && (aid != ua[i]))
            {
                dmg2 = 0;//canot deal damage
            }
            if ((tid == ut[i]) && (aid == ua[i]))//check if only some certain units can attack that unit
            {
                dmg2 = dmg;//can deal damage
                i = 255;
            }
            i++;
            if (ua[i] == 255)//pairs must go in a row
            {
                i = 255;
            }
        }
        if (*((WORD*)((uintptr_t)trg + S_SHIELD)) != 0)dmg2 = 0;
        if (blood_f)//bloodlust fix to manually add x2 dmg
        {
            int bdmg = dmg2;
            if (*((WORD*)((uintptr_t)atk + S_BLOOD)) != 0)bdmg *= 2;
            if (bdmg > 255)bdmg = 255;
            if (bdmg != 0)dmg2 = bdmg % 256;
        }
        /*
        if (FALSE)//more damage to air units example
        {
            if (aid == U_DEMON)
            {
                byte tmov = *((byte*)((uintptr_t)trg + S_MOVEMENT_TYPE));//target mov
                if (tmov == MOV_AIR)
                {
                    if (dmg2 != 0)
                    {
                        int bdmg = dmg2 * 7;
                        if (bdmg > 255)bdmg = 255;
                        if (bdmg != 0)dmg2 = bdmg % 256;
                    }
                }
            }
        }
        */
        fdmg = dmg2;
        if (agr)comp_aggro(trg, atk);//check if allied comps go agro
        if (fdmg != 0)
        {
            if (cpt)capture(trg, atk);//check if buildings captured on low hp
            if (steal)steal_res(trg, atk);
            if (manaburn)mana_burn(trg, atk);
            bool f = false;
            for (int i = 0; i < 255; i++)
            {
                if ((m_devotion[i] != 255) && (!f))
                    f = devotion_aura(trg, m_devotion[i]);
                else
                    i = 256;
            }
            if (f)//defence
            {
                dmg2 = fdmg;
                if (dmg2 > 3)dmg2 -= 3;
                else dmg2 = 0;
                fdmg = dmg2;
            }
            f = false;
            for (int i = 0; i < 255; i++)
            {
                if ((m_prvnt[i] != 255) && (!f))
                    f = m_prvnt[i] == tid;
                else
                    i = 256;
            }
            if (f)//prevent
            {
                WORD hp = *((WORD*)((uintptr_t)trg + S_HP));
                if (hp > 0)
                {
                    if (hp <= fdmg)
                    {
                        fdmg = 0;
                        set_stat(trg, 300, S_SHIELD);
                        set_stat(trg, 0, S_HP);
                        flame(trg);
                    }
                }
            }
            f = false;
            for (int i = 0; i < 255; i++)
            {
                if ((m_vampire[i] != 255) && (!f))
                    f = vamp_aura(trg, atk, m_vampire[i]);
                else
                    i = 256;
            }
            if (f)//vampire
            {
                WORD hp = *((WORD*)((uintptr_t)trg + S_HP));
                byte mult = 2;//2=50% 4=25%
                if (hp > (fdmg / mult + 1))heal(atk, (fdmg / mult + 1));//steal 50% of damage +1 of target HP
                else heal(atk, hp % 256);//or steall all if damage is too big
                WORD xx = *((WORD*)((uintptr_t)atk + S_DRAW_X));
                WORD yy = *((WORD*)((uintptr_t)atk + S_DRAW_Y));
                ((void (*)(WORD, WORD, byte))F_BULLET_CREATE)(xx + 16, yy + 16, B_SHOT_FIRE);//create effect
            }
        }
        WORD hp = *((WORD*)((uintptr_t)trg + S_HP));//unit hp
        if ((tid < U_FARM) && (fdmg >= hp))//if damage more than hp = unit will die = add kill
        {
            if ((aid != U_HTRANSPORT) || (aid != U_OTRANSPORT))//no KILLS for transpots (or crash)
            {
                byte k = *((byte*)((uintptr_t)atk + S_KILLS));
                if (k < 255)k += 1;
                set_stat(atk, (int)k, S_KILLS);
            }
        }
    }
}

void damage1(int* atk, int* trg, char dmg)
{
    damage(atk, trg, dmg);
    ((void (*)(int*, int*, char))g_proc_00409F3B)(atk, trg, fdmg);
}

void damage2(int* atk, int* trg, char dmg)
{
    damage(atk, trg, dmg);
    ((void (*)(int*, int*, char))g_proc_0041038E)(atk, trg, fdmg);
}

void damage3(int* atk, int* trg, char dmg)
{
    damage(atk, trg, dmg);
    ((void (*)(int*, int*, char))g_proc_0040AF70)(atk, trg, fdmg);
}

void damage4(int* atk, int* trg, char dmg)
{
    damage(atk, trg, dmg);
    ((void (*)(int*, int*, char))g_proc_0040AF99)(atk, trg, fdmg);
}

void damage5(int* atk, int* trg, char dmg)
{
    damage(atk, trg, dmg);
    ((void (*)(int*, int*, char))g_proc_00410762)(atk, trg, fdmg);
}

void damage6(int* atk, int* trg, char dmg)
{
    damage(atk, trg, dmg);
    ((void (*)(int*, int*, char))g_proc_004428AD)(atk, trg, fdmg);
}

void tower_set_target(int* p, int x, int y)
{
    //set target manually
    //i think there should be better way to do this
    //cause this still possible cause some uncertain bugs
    set_stat(p, 0, S_RETARGET_X1);
    set_stat(p, 0, S_RETARGET_X1 + 1);
    set_stat(p, 0, S_RETARGET_X1 + 2);
    set_stat(p, 0, S_RETARGET_X1 + 3);
    int* u = NULL;
    set_region(x - 3, y - 3, x, y);
    find_all_alive_units(ANY_BUILDING_4x4);
    sort_in_region();
    sort_hidden();
    sort_attack_can_hit(p);
    if (units != 0)u = unit[0];
    set_region(x - 2, y - 2, x, y);
    find_all_alive_units(ANY_BUILDING_3x3);
    sort_in_region();
    sort_hidden();
    sort_attack_can_hit(p);
    if (units != 0)u = unit[0];
    set_region(x - 1, y - 1, x, y);
    find_all_alive_units(ANY_BUILDING_2x2);
    sort_in_region();
    sort_hidden();
    sort_attack_can_hit(p);
    if (units != 0)u = unit[0];
    set_region(x, y, x, y);
    find_all_alive_units(ANY_UNITS);
    sort_in_region();
    sort_hidden();
    sort_attack_can_hit(p);
    if (units != 0)u = unit[0];
    if (u)
    {
        set_stat(p, (int)u % 256, S_RETARGET_X1);
        set_stat(p, (int)u / 256, S_RETARGET_X1 + 1);
        set_stat(p, ((int)u / 256) / 256, S_RETARGET_X1 + 2);
        set_stat(p, (((int)u / 256) / 256) / 256, S_RETARGET_X1 + 3);
    }
}

void brclik(bool b)
{
    if (b)
    {
        char r[] = "\x90\x90\x90\x90\x90\x90";
        PATCH_SET((char*)RIGHT_CLICK_ALLOW_BUILDINGS, r);
    }
    else
    {
        char r[] = "\xf\x84\x26\x01\x0\x0";
        PATCH_SET((char*)RIGHT_CLICK_ALLOW_BUILDINGS, r);
    }
}

PROC g_proc_0043BAE1;
void rc_snd(int* p)
{
    //acknowlegement sound
    //(game crash cause buildings not have this sounds so this hooked function fix it)
    if (*((byte*)((uintptr_t)p + S_ID)) < U_FARM)
        ((void (*)(int*))g_proc_0043BAE1)(p);
}

PROC g_proc_0043B943;
void rc_build_click(int* p,int x,int y,int* t,int a)
{
    //when player clicked with right click
    byte id = *(byte*)((uintptr_t)p + S_ID);
    if (id >= U_FARM)//for buildings
    {
        set_stat(p, x, S_RETARGET_X1);
        set_stat(p, y, S_RETARGET_Y1);
        set_stat(p, 1, S_RETARGET_X1 + 1);
        if ((id == U_HARROWTOWER) || (id == U_OARROWTOWER) 
            || (id == U_HCANONTOWER) || (id == U_OCANONTOWER)
            || (id == U_HTOWER) || (id == U_OTOWER))
        {
            tower_set_target(p, x, y);
        }
    }
    else//for normal units
        ((void (*)(int*, int, int, int*, int))g_proc_0043B943)(p, x, y, t, a);//original
}

void rc_jmp(bool b)
{
    if (b)
    {
        char r[] = "\xf\x84\xa2\x0\x0\x0";
        PATCH_SET((char*)RIGHT_CLICK_1, r);
        patch_ljmp((char*)RIGHT_CLICK_CODE_CAVE, (char*)RIGHT_CLICK_2);
    }
    else
    {
        char r[] = "\xf\x84\x8b\x0\x0\x0";
        PATCH_SET((char*)RIGHT_CLICK_1, r);
    }
}

PROC g_proc_0040DF71;
int* bld_unit_create(int a1, int a2, int a3, byte a4, int* a5)
{
    //this function called when building finished training unit
    //and new unit should be created
    int* b = (int*)*(int*)UNIT_RUN_UNIT_POINTER;//building that processed right now
    int* u = ((int* (*)(int, int, int, byte, int*))g_proc_0040DF71)(a1, a2, a3, a4, a5);
    if (b)//building
    {
        if (u)//unit that was created (will be NULL if was not created (ex: no place))
        {
            byte bp = *((byte*)((uintptr_t)b + S_RETARGET_X1 + 1));
            if (bp == 1)
            {
                byte x = *((byte*)((uintptr_t)b + S_RETARGET_X1));
                byte y = *((byte*)((uintptr_t)b + S_RETARGET_Y1));
                byte uid = *((byte*)((uintptr_t)u + S_ID));
                byte o = ORDER_ATTACK_AREA;
                if ((uid == U_PEON) || (uid == U_PEASANT) || (uid == U_HTANKER) || (uid == U_OTANKER))
                    o = ORDER_HARVEST;
                give_order(u, x, y, o);
                set_stat(u, x, S_RETARGET_X1);
                set_stat(u, y, S_RETARGET_Y1);
                set_stat(u, o, S_RETARGET_ORDER);
            }
        }
    }
    return u;
}

PROC g_proc_0040AFBF;
int* tower_find_attacker(int* p)
{
    int* tr = NULL;
    byte id = *((byte*)((uintptr_t)p + S_ID));
    if ((id == U_HARROWTOWER) || (id == U_OARROWTOWER) || (id == U_HCANONTOWER) || (id == U_OCANONTOWER))
    {
        byte a1 = *((byte*)((uintptr_t)p + S_RETARGET_X1));
        byte a2 = *((byte*)((uintptr_t)p + S_RETARGET_X1 + 1));
        byte a3 = *((byte*)((uintptr_t)p + S_RETARGET_X1 + 2));
        byte a4 = *((byte*)((uintptr_t)p + S_RETARGET_X1 + 3));
        tr = (int*)(a1 + 256 * a2 + 256 * 256 * a3 + 256 * 256 * 256 * a4);
        if (tr)
        {
            if (!check_unit_near_death(tr) && !check_unit_dead(tr) && !check_unit_hidden(tr))
            {
                int a = ((int(*)(int*, int*))F_ATTACK_CAN_HIT)(p, tr);
                if (a != 0)
                {
                    byte id = *((byte*)((uintptr_t)tr + S_ID));
                    byte szx = *(byte*)(UNIT_SIZE_TABLE + 4 * id);
                    byte szy = *(byte*)(UNIT_SIZE_TABLE + 4 * id + 2);
                    byte idd = *((byte*)((uintptr_t)p + S_ID));
                    byte rng = *(byte*)(UNIT_RANGE_TABLE + idd);
                    byte ms = *(byte*)MAP_SIZE;
                    byte xx = *((byte*)((uintptr_t)tr + S_X));
                    byte yy = *((byte*)((uintptr_t)tr + S_Y));
                    byte x1 = *((byte*)((uintptr_t)p + S_X));
                    byte y1 = *((byte*)((uintptr_t)p + S_Y));
                    byte x2 = x1;
                    byte y2 = y1;
                    if (x1 < rng)x1 = 0;
                    else x1 -= rng;
                    if (y1 < rng)y1 = 0;
                    else y1 -= rng;
                    if ((x2 + rng + 1) > ms)x2 = ms;
                    else x2 += rng + 1;
                    if ((y2 + rng + 1) > ms)y2 = ms;
                    else y2 += rng + 1;
                    if (!((xx >= x1) && (xx <= x2) && (yy >= y1) && (yy <= y2)))
                        tr = NULL;
                }
            }
            else
                tr = NULL;
        }
    }
    if (!tr)
        return ((int* (*)(int*))g_proc_0040AFBF)(p);//original
    else
    {
        return tr;
    }
}

PROC g_proc_00451728;
void unit_kill_deselect(int* u)
{
    //hooked function that make tower forgot target that died
    //cause if not forgot then will be many bugs
    int* ud = u;
    ((void (*)(int*))g_proc_00451728)(u);//original
    for (int i = 0; i < 16; i++)
    {
        int* p = (int*)(UNITS_LISTS + 4 * i);
        if (p)
        {
            p = (int*)(*p);
            while (p)
            {
                byte id = *((byte*)((uintptr_t)p + S_ID));
                bool f = ((id == U_HARROWTOWER) || (id == U_OARROWTOWER)
                    || (id == U_HCANONTOWER) || (id == U_OCANONTOWER));
                if (f)
                {
                    if (!check_unit_dead(p) && check_unit_complete(p))
                    {
                        byte a1 = *((byte*)((uintptr_t)p + S_RETARGET_X1));
                        byte a2 = *((byte*)((uintptr_t)p + S_RETARGET_X1 + 1));
                        byte a3 = *((byte*)((uintptr_t)p + S_RETARGET_X1 + 2));
                        byte a4 = *((byte*)((uintptr_t)p + S_RETARGET_X1 + 3));
                        int* tr = (int*)(a1 + 256 * a2 + 256 * 256 * a3 + 256 * 256 * 256 * a4);
                        if (tr == ud)
                        {
                            set_stat(p, 0, S_RETARGET_X1);
                            set_stat(p, 0, S_RETARGET_X1 + 1);
                            set_stat(p, 0, S_RETARGET_X1 + 2);
                            set_stat(p, 0, S_RETARGET_X1 + 3);
                        }
                    }
                }
                p = (int*)(*((int*)((uintptr_t)p + S_NEXT_UNIT_POINTER)));
            }
        }
    }
}

void allow_table(byte p, int t, byte n, byte a)
{
    if (t == 0)t = ALLOWED_UNITS + (4 * p) + (n / 8);
    else if (t == 1)t = ALLOWED_UPGRADES + (4 * p) + (n / 8);
    else if (t == 2)t = ALLOWED_SPELLS + (4 * p) + (n / 8);
    else t = SPELLS_LEARNED + (4 * p) + (n / 8);
    byte b = *(byte*)t;
    if (a == 1)b |= (1 << (n % 8));
    else b &= (~(1 << (n % 8)));
    char buf[] = "\xff";
    buf[0] = b;
    PATCH_SET((char*)t, buf);
}

void draw_stats_fix(bool b)
{
    if (b)
    {
        char buf[] = "\xa0\x5b";
        PATCH_SET((char*)DEMON_STATS_DRAW, buf);//demon
        PATCH_SET((char*)CRITTER_STATS_DRAW, buf);//critter
    }
    else
    {
        char buf[] = "\xf0\x57";
        PATCH_SET((char*)DEMON_STATS_DRAW, buf);//demon
        PATCH_SET((char*)CRITTER_STATS_DRAW, buf);//critter
    }
}

void send_cheat(byte c)
{
    int b = *(int*)CHEATBITS;
    if ((b & (1 << c)) != 0)
        b &= ~(1 << c);
    else
        b |= 1 << c;
    ((void (*)(int))F_SEND_CHEAT_PACKET)(b);
}

void rec_autoheal()
{
    byte p = *(byte*)LOCAL_PLAYER;//player
    byte b = *(byte*)(SPELLS_LEARNED + 4 * p);
    byte sp = GREATER_HEAL;
    if ((b & (1 << sp)) != 0)
        b &= ~(1 << sp);
    else
        b |= 1 << sp;
    char buf[] = "\x0";
    buf[0] = b;
    PATCH_SET((char*)(SPELLS_LEARNED + 4 * p), buf);

    if ((*(byte*)(SPELLS_LEARNED + 4 * (p)) & (1 << L_GREATER_HEAL)) != 0)
    {
        churc[20 * 3 + 2] = '\x5b';//icon
        char msg[] = "autoheal\x5 enabled";
        show_message(10, msg);
    }
    else
    {
        churc[20 * 3 + 2] = '\x6d';//icon
        char msg[] = "autoheal\x3 disabled";
        show_message(10, msg);
    }
    ((void (*)())F_STATUS_REDRAW)();
}

void rec_peons()
{
    int* p = NULL;
    byte l = *(byte*)LOCAL_PLAYER;//player
    p = (int*)(UNITS_SELECTED + 9 * 4 * l);
    if (p)
    {
        p = (int*)(*p);
        if (p)
        {
            byte id = *((byte*)((uintptr_t)p + S_ID));
            bool fid = (id == U_TOWN_HALL) || (id == U_GREAT_HALL) ||
                (id == U_KEEP) || (id == U_STRONGHOLD) ||
                (id == U_CASTLE) || (id == U_FORTRESS);
            if (fid)
            {
                byte o = *((byte*)((uintptr_t)p + S_OWNER));
                if (o == l)
                {
                    byte x = *((byte*)((uintptr_t)p + S_X));
                    byte y = *((byte*)((uintptr_t)p + S_Y));
                    set_region((int)x - 5, (int)y - 5, (int)x + 8, (int)y + 8);//set region around myself rad 5
                    find_all_alive_units(ANY_MEN);
                    sort_in_region();
                    sort_hidden();
                    sort_stat(S_OWNER, o, CMP_EQ);//my owner
                    sort_stat(S_ID, U_ATTACK_PEASANT, CMP_BIGGER_EQ);
                    sort_stat(S_ID, U_ATTACK_PEON, CMP_SMALLER_EQ);
                    if (units != 0)
                    {
                        for (int i = 0; i < units; i++)
                        {
                            byte id = *((byte*)((uintptr_t)unit[i] + S_ID));//unit id
                            WORD mhp = *(WORD*)(UNIT_HP_TABLE + 2 * id);//max hp
                            WORD hp = *((WORD*)((uintptr_t)unit[i] + S_HP));//unit hp
                            byte idd = id % 2;
                            WORD mhp2 = *(WORD*)(UNIT_HP_TABLE + 2 * (U_PEASANT + idd));//max hp
                            int thp = hp + (mhp2 - mhp);
                            if (thp < 1)thp = 1;
                            hp = thp % (256 * 256);
                            set_stat(unit[i], hp, S_HP);
                            set_stat(unit[i], (U_PEASANT + idd), S_ID);
                            set_stat(unit[i], (U_PEASANT + idd), S_COMMANDS);
                            set_stat(unit[i], (U_PEASANT + idd), S_SPRITE);
                            set_stat(unit[i], ORDER_STOP, S_NEXT_ORDER);
                        }
                        char msg[] = "workers attack mode\x3 disabled";
                        show_message(10, msg);
                    }
                    else
                    {
                        find_all_alive_units(ANY_MEN);
                        sort_in_region();
                        sort_hidden();
                        sort_stat(S_OWNER, o, CMP_EQ);//my owner
                        sort_stat(S_ID, U_PEASANT, CMP_BIGGER_EQ);
                        sort_stat(S_ID, U_PEON, CMP_SMALLER_EQ);
                        if (units != 0)
                        {
                            for (int i = 0; i < units; i++)
                            {
                                byte id = *((byte*)((uintptr_t)unit[i] + S_ID));//unit id
                                WORD mhp = *(WORD*)(UNIT_HP_TABLE + 2 * id);//max hp
                                WORD hp = *((WORD*)((uintptr_t)unit[i] + S_HP));//unit hp
                                byte idd = id % 2;
                                WORD mhp2 = *(WORD*)(UNIT_HP_TABLE + 2 * (U_ATTACK_PEASANT + idd));//max hp
                                int thp = hp + (mhp2 - mhp);
                                if (thp < 1)thp = 1;
                                hp = thp % (256 * 256);
                                set_stat(unit[i], hp, S_HP);
                                set_stat(unit[i], (U_ATTACK_PEASANT + idd), S_ID);
                                set_stat(unit[i], (U_ATTACK_PEASANT + idd), S_COMMANDS);
                                set_stat(unit[i], (U_PEASANT + idd), S_SPRITE);
                                set_stat(unit[i], ORDER_STOP, S_NEXT_ORDER);
                            }
                            char msg[] = "workers attack mode\x5 enabled";
                            show_message(10, msg);
                        }
                    }
                }
            }
        }
    }
    ((void (*)())F_STATUS_REDRAW)();
}

PROC g_proc_0045614E;
void receive_cheat(int c, int a1)
{
    //received cheat packet
    bool f = true;
    if ((c & (1 << 8)) != 0)//8 - autoheal
    {
        rec_autoheal();
        f = false;
    }
    if ((c & (1 << 9)) != 0)//9 - attack peons
    {
        rec_peons();
        f = false;
    }
    if (f)
    {
        ((void (*)(int, int))g_proc_0045614E)(c, a1);//orig
    }
    else
    {
        char buf[] = "\x0";
        PATCH_SET((char*)PLAYER_CHEATED, buf);
    }
}

void button_autoheal(int)
{
    send_cheat(8);
    if ((*(byte*)(SPELLS_LEARNED + 4 * (*(byte*)LOCAL_PLAYER)) & (1 << L_GREATER_HEAL)) != 0)
        churc[20 * 3 + 2] = '\x5b';//icon
    else
        churc[20 * 3 + 2] = '\x6d';//icon
    ((void (*)())F_STATUS_REDRAW)();
}

void autoheal(bool b)
{
    if (b)
    {
        if ((*(byte*)(SPELLS_LEARNED + 4 * (*(byte*)LOCAL_PLAYER)) & (1 << L_GREATER_HEAL)) != 0)
            churc[20 * 3 + 2] = '\x5b';//icon
        else
            churc[20 * 3 + 2] = '\x6d';//icon

        void (*r1) (int) = button_autoheal;
        patch_setdword((DWORD*)(churc + (20 * 3 + 8)), (DWORD)r1);

        char b1[] = "\04\x0\x0\x0\x68\x37\x4a\x0";
        char* repf = churc;
        patch_setdword((DWORD*)(b1 + 4), (DWORD)repf);
        PATCH_SET((char*)CHURCH_BUTTONS, b1);
        A_autoheal = true;
    }
    else
    {
        char b1[] = "\03\x0\x0\x0\x68\x37\x4a\x0";
        PATCH_SET((char*)CHURCH_BUTTONS, b1);
        A_autoheal = false;
    }
}

void button_peons(int)
{
    send_cheat(9);
    ((void (*)())F_STATUS_REDRAW)();
}

void th_change(bool b)
{
    //add new buttons to TH
    if (b)
    {
        heroes(true);
        char hth[] = "\x5";
        PATCH_SET((char*)HUMAN_TH1_BUTTONS, hth);
        PATCH_SET((char*)HUMAN_TH2_BUTTONS, hth);
        PATCH_SET((char*)HUMAN_TH3_BUTTONS, hth);
        char oth[] = "\x5\x0\x0\x0\x20\xf7\x48\x0";
        char* repf = oth_build;
        patch_setdword((DWORD*)(oth + 4), (DWORD)repf);
        PATCH_SET((char*)ORC_TH1_BUTTONS, oth);
        PATCH_SET((char*)ORC_TH2_BUTTONS, oth);
        PATCH_SET((char*)ORC_TH3_BUTTONS, oth);

        bool af = false;
        for (int i = 0; i < 8; i++)
        {
            if (heros[i] != 0)af = true;
        }
        if (af)
        {
            patch_setdword((DWORD*)(hth_build + 4), (DWORD)F_ALWAYS_TRUE);
        }
        else
        {
            int (*repf) (byte) = empty_false;
            patch_setdword((DWORD*)(hth_build + 4), (DWORD)repf);
        }
        af = false;
        for (int i = 8; i < 16; i++)
        {
            if (heros[i] != 0)af = true;
        }
        if (af)
        {
            patch_setdword((DWORD*)(oth_build + 64), (DWORD)F_ALWAYS_TRUE);
        }
        else
        {
            int (*repf) (byte) = empty_false;
            patch_setdword((DWORD*)(oth_build + 64), (DWORD)repf);
        }

        if (apn)//if can build attack peons
        {
            patch_setdword((DWORD*)(hth_build + 24), (DWORD)F_ALWAYS_TRUE);
            patch_setdword((DWORD*)(oth_build + 84), (DWORD)F_ALWAYS_TRUE);

            void (*repf) (int) = button_peons;
            patch_setdword((DWORD*)(hth_build + 28), (DWORD)repf);
            patch_setdword((DWORD*)(oth_build + 88), (DWORD)repf);

            char bufb[] = "\xa\x0\x0\x0\x38\x1e\x4a\x0\xa\x0\x0\x0\x0\x1f\x4a\x0";
            PATCH_SET((char*)HUMAN_TH_ONE_BUTTON, bufb);
        }
        else
        {
            int (*repf) (byte) = empty_false;
            patch_setdword((DWORD*)(hth_build + 24), (DWORD)repf);
            patch_setdword((DWORD*)(oth_build + 84), (DWORD)repf);

            char bufb[] = "\x2\x0\x0\x0\xc8\x1f\x4a\x0\x2\x0\x0\x0\xf0\x1f\x4a\x0";
            PATCH_SET((char*)HUMAN_TH_ONE_BUTTON, bufb);
        }

        PATCH_SET((char*)HUMAN_TH_COMMON, hth_build);
    }
    else
    {
        heroes(false);
        char hth[] = "\x3";
        PATCH_SET((char*)HUMAN_TH1_BUTTONS, hth);
        PATCH_SET((char*)HUMAN_TH2_BUTTONS, hth);
        PATCH_SET((char*)HUMAN_TH3_BUTTONS, hth);
        char oth[] = "\x3\x0\x0\x0\x78\x34\x4a\x0";
        PATCH_SET((char*)ORC_TH1_BUTTONS, oth);
        PATCH_SET((char*)ORC_TH2_BUTTONS, oth);
        PATCH_SET((char*)ORC_TH3_BUTTONS, oth);
        char p1[] = "\x0\x0\x0\x0\x0\x0\x1\x0\xa0\x44\x44\x0\xd0\xe6\x40\x0\x1\x3\xd\x1\x0\x0\x0\x0\x1\x0\x43\x0\xb0\x42\x44\x0\x10\xe7\x40\x0\x0\x59\x3e\x1\x0\x0\x0\x0";
        PATCH_SET((char*)HUMAN_TH_COMMON, p1);
        char bufb[] = "\x2\x0\x0\x0\xc8\x1f\x4a\x0\x2\x0\x0\x0\xf0\x1f\x4a\x0";
        PATCH_SET((char*)HUMAN_TH_ONE_BUTTON, bufb);
    }
}

void def_stat(byte u, WORD hp, byte str, byte prc, byte arm, byte rng, byte gold, byte lum, byte oil, byte time)
{
    //change some unit stats (changes for ALL units of this type)

    /*
    to change vision and multiselectable you can use this construction
    char buf[] = "\x0\x0\x0\x0";//fix vision
    patch_setdword((DWORD*)buf, (DWORD)F_VISION6);
    PATCH_SET((char*)(UNIT_VISION_FUNCTIONS_TABLE + 4 * U_DEMON), buf);
    char buf2[] = "\x1";
    PATCH_SET((char*)(UNIT_MULTISELECTABLE + U_DEMON), buf2);
    */

    char buf2[] = "\x0\x0";
    buf2[0] = hp % 256;
    buf2[1] = hp / 256;
    PATCH_SET((char*)(UNIT_HP_TABLE + 2 * u), buf2);
    char buf[] = "\x0";
    buf[0] = str;
    PATCH_SET((char*)(UNIT_STRENGTH_TABLE + u), buf);
    buf[0] = prc;
    PATCH_SET((char*)(UNIT_PIERCE_TABLE + u), buf);
    buf[0] = arm;
    PATCH_SET((char*)(UNIT_ARMOR_TABLE + u), buf);
    buf[0] = rng;
    PATCH_SET((char*)(UNIT_RANGE_TABLE + u), buf);
    buf[0] = gold;
    PATCH_SET((char*)(UNIT_GOLD_TABLE + u), buf);
    buf[0] = lum;
    PATCH_SET((char*)(UNIT_LUMBER_TABLE + u), buf);
    buf[0] = oil;
    PATCH_SET((char*)(UNIT_OIL_TABLE + u), buf);
    buf[0] = time;
    PATCH_SET((char*)(UNIT_TIME_TABLE + u), buf);
}

PROC g_proc_004526FE;
void grow_structure(int* p)
{
    ((void (*)(int*))g_proc_004526FE)(p);//original
    if (p)
    {
        byte id = (*(byte*)((uintptr_t)p + S_ID));
        if ((id == U_FARM) || (id == U_PIGFARM))
        {
            if (check_unit_complete(p))
            {
                byte cid = (*(byte*)((uintptr_t)p + S_RESOURCES));
                if (((id == U_FARM) && (cid == U_PEON)) || ((id == U_PIGFARM) && (cid == U_PEASANT)))
                {//if peon created human farm OR peasant created orc farm - its not normal so its considered to grow forest
                    byte pg = *(byte*)(UNIT_GOLD_TABLE + id);//gold
                    byte pl = *(byte*)(UNIT_LUMBER_TABLE + id);//lumber
                    byte po = *(byte*)(UNIT_OIL_TABLE + id);//oil
                    byte o = (*(byte*)((uintptr_t)p + S_OWNER));
                    change_res(o, 0, pg, 10);//return gold
                    change_res(o, 1, pl, 10);//return lumber
                    change_res(o, 2, po, 10);//return oil

                    int price = 500;
                    if (cmp_res(o, 0, price % 256, price / 256, 0, 0, CMP_BIGGER_EQ))
                    {
                        change_res(o, 3, 1, price);//get 1000 gold
                        byte x = (*(byte*)((uintptr_t)p + S_X));
                        byte y = (*(byte*)((uintptr_t)p + S_Y));
                        byte mxs = *(byte*)MAP_SIZE;//map size
                        byte era = *(byte*)MAP_ERA;//map era
                        char* cel = (char*)*(int*)(MAP_CELLS_POINTER);//map cells
                        char* sq = (char*)*(int*)(MAP_SQ_POINTER);//map cells
                        char* reg = (char*)*(int*)(MAP_REG_POINTER);//map reg
                        char bufte[] = "\x88\x84\x82\x81\x81\x83\x7F\x85\x81\x83\x7F\x86\x81\x83\x7F\x85";//4 era tiles
                        char buft[] = "\x7E\x0";
                        for (int xx = x; (xx < x + 2) && (xx < mxs); xx++)
                        {
                            for (int yy = y; (yy < y + 2) && (yy < mxs); yy++)
                            {
                                if ((xx == x) && (yy == y))
                                    buft[0] = bufte[era * 4];
                                if ((xx == x + 1) && (yy == y))
                                    buft[0] = bufte[era * 4 + 1];
                                if ((xx == x) && (yy == y + 1))
                                    buft[0] = bufte[era * 4 + 2];
                                if ((xx == x + 1) && (yy == y + 1))
                                    buft[0] = bufte[era * 4 + 3];
                                PATCH_SET((char*)(cel + 2 * xx + 2 * yy * mxs), buft);
                                char buf[] = "\x81\x0";//unpassable land
                                PATCH_SET((char*)(sq + 2 * xx + 2 * yy * mxs), buf);
                                buf[0] = '\xFE';//tree
                                buf[1] = '\xFF';//tree
                                PATCH_SET((char*)(reg + 2 * xx + 2 * yy * mxs), buf);
                            }
                        }
                    }
                    byte flg = (*(byte*)((uintptr_t)p + S_FLAGS3));
                    flg |= SF_HIDDEN;//hide
                    set_stat(p, flg, S_FLAGS3);
                    ((void (*)(int*))F_DEAD_BUILDING_REDRAW)(p);//unitdraw insert dead bldg
                    unit_kill(p);
                }
            }
        }
        if (id == U_MINE)
        {
            if (check_unit_complete(p))
            {
                give(p, P_NEUTRAL);
                set_stat(p, P_NEUTRAL, S_COLOR);
                WORD mhp = *(WORD*)(UNIT_HP_TABLE + 2 * id);//max hp
                if (mhp > 300)
                {
                    set_stat(p, 300, S_HP);
                }
                //int r = ((int (*)())F_NET_RANDOM)();
                //r %= 50;
                //r += 1;
                int r = 50;
                set_stat(p, r, S_RESOURCES);

                byte x = (*(byte*)((uintptr_t)p + S_X));
                byte y = (*(byte*)((uintptr_t)p + S_Y));
                byte mxs = *(byte*)MAP_SIZE;//map size
                byte era = *(byte*)MAP_ERA;//map era
                char* cel = (char*)*(int*)(MAP_CELLS_POINTER);//map cells
                for (int xx = x; (xx < x + 3) && (xx < mxs); xx++)
                {
                    for (int yy = y; (yy < y + 3) && (yy < mxs); yy++)
                    {
                        char buf[] = "\x4b\x1";
                        if (era == 0)buf[0] = 0x4e;//forest
                        if (era == 1)buf[0] = 0x4b;//winter
                        if (era == 2)buf[0] = 0x4a;//wast
                        if (era == 3)buf[0] = 0x50;//swamp
                        PATCH_SET((char*)(cel + 2 * xx + 2 * yy * mxs), buf);
                    }
                }
            }
        }
        //if (id==U_ ??) you can add other building if need
    }
}

PROC g_proc_00418FFE;
int* create_building(int a, int b, int id, int c)
{
    int* cr = (int*)*(int*)UNIT_RUN_UNIT_POINTER;//unit who created building
    int* original = ((int* (*)(int, int, int, int))g_proc_00418FFE)(a, b, id, c);//original function
    if (original)//created building
    {
        if (cr)//unit who created building
        {
            if ((id == U_FARM) || (id == U_PIGFARM))
            {
                byte cid = *((byte*)((uintptr_t)cr + S_ID));
                set_stat(original, cid, S_RESOURCES);//set id of creator (peon or pesant)
            }
            if (id == U_CIRCLE)
            {
                WORD xx = *((WORD*)((uintptr_t)cr + S_DRAW_X));
                WORD yy = *((WORD*)((uintptr_t)cr + S_DRAW_Y));
                ((void (*)(WORD, WORD, byte))F_BULLET_CREATE)(xx + 16, yy + 16, 21);
                unit_kill(cr);//sacrifice peon
            }
        }
    }
    return original;
}

PROC g_proc_0043A974;//placing
PROC g_proc_0043ABAB;//draw
WORD placebox_query(int* p, WORD x, WORD y, byte id)
{
    //function that checking map cells when placing building
    WORD original = ((WORD(*)(int*, WORD, WORD, byte))g_proc_0043A974)(p, x, y, id);//original
    byte mxs = *(byte*)MAP_SIZE;//map size
    byte era = *(byte*)MAP_ERA;//map era
    char* cel = (char*)*(int*)(MAP_CELLS_POINTER);//map cells
    byte pid = *((byte*)((uintptr_t)p + S_ID));//builder
    if (((id == U_FARM) && (pid == U_PEON)) || ((id == U_PIGFARM) && (pid == U_PEASANT)))
    {//make new forest to grow
        WORD dr = 0x7E;//destroyed forest
        for (int xx = x; (xx < x + 2) && (xx < mxs); xx++)
        {
            for (int yy = y; (yy < y + 2) && (yy < mxs); yy++)
            {
                WORD c = *(WORD*)(cel + 2 * xx + 2 * yy * mxs);
                if (c != dr)
                {
                    char buf[] = "\x7";
                    PATCH_SET((char*)(CAN_PLACE_TBL + (xx - x) + 4 * (yy - y)), buf);//can place tbl
                    original = 7;
                }
            }
        }
    }
    if (id == U_MINE)
    {
        WORD dr = 0xA1;//destroyed rock
        if (era == 0)dr = 0xA6;//forest
        if (era == 1)dr = 0xA1;//winter
        if (era == 2)dr = 0xA3;//wast
        if (era == 3)dr = 0xA1;//swamp
        for (int xx = x; (xx < x + 3) && (xx < mxs); xx++)
        {
            for (int yy = y; (yy < y + 3) && (yy < mxs); yy++)
            {
                WORD c = *(WORD*)(cel + 2 * xx + 2 * yy * mxs);
                if (c != dr)
                {
                    char buf[] = "\x7";
                    PATCH_SET((char*)(CAN_PLACE_TBL + (xx - x) + 4 * (yy - y)), buf);//can place tbl
                    original = 7;
                }
            }
        }
    }
    return original;
}

PROC g_proc_00424745;//entering
PROC g_proc_004529C0;//grow struct
int goods_into_inventory(int* p)
{
//use this function if you need to change amount of res peon or tanker bring back
    if (replaced)
    {
        int tr = (*(int*)((uintptr_t)p + S_ORDER_UNIT_POINTER));
        if (tr != 0)
        {
            bool f = false;
            int* trg = (int*)tr;
            byte o = *((byte*)((uintptr_t)p + S_OWNER));
            byte id = *((byte*)((uintptr_t)p + S_ID));
            byte tid = *((byte*)((uintptr_t)trg + S_ID));
            byte pf = *((byte*)((uintptr_t)p + S_PEON_FLAGS));
            int pflag = *(int*)(UNIT_GLOBAL_FLAGS + id * 4);
            int tflag = *(int*)(UNIT_GLOBAL_FLAGS + tid * 4);
            int res = 100;
            if (pf & PEON_LOADED)
            {
                if (((pflag & IS_SHIP) != 0) && ((tflag & IS_OILRIG) == 0))
                {
                    int r = get_val(REFINERY, o);
                    if (more_res)
                    {
                        res = 100 + 25 * r;
                    }
                    else
                    {
                        if (r != 0)
                        {
                            res = 125;
                        }
                        else
                        {
                            res = 100;
                        }
                    }
                    change_res(o, 2, 1, res);
                    add_total_res(o, 2, 1, res);
                    f = true;
                }
                else
                {
                    if (((tflag & IS_TOWNHALL) != 0) || ((tflag & IS_LUMBER) != 0))
                    {
                        if (((tflag & IS_TOWNHALL) != 0))
                        {
                            pf |= PEON_IN_CASTLE;
                            set_stat(p, pf, S_PEON_FLAGS);
                        }
                        if (((pf & PEON_HARVEST_GOLD) != 0) && ((tflag & IS_TOWNHALL) != 0))
                        {
                            int r2 = get_val(TH2, o);
                            int r3 = get_val(TH3, o);
                            if (more_res)
                            {
                                res = 100 + 10 * r2 + 20 * r3;
                            }
                            else
                            {
                                if (r3 != 0)
                                {
                                    res = 120;
                                }
                                else
                                {
                                    if (r2 != 0)
                                    {
                                        res = 110;
                                    }
                                    else
                                    {
                                        res = 100;
                                    }
                                }
                            }
                            pf &= ~PEON_HARVEST_GOLD;
                            change_res(o, 0, 1, res);
                            add_total_res(o, 0, 1, res);
                            f = true;
                        }
                        else
                        {
                            if (((pf & PEON_HARVEST_LUMBER) != 0))
                            {
                                int r = get_val(LUMBERMILL, o);
                                if (more_res)
                                {
                                    res = 100 + 25 * r;
                                }
                                else
                                {
                                    if (r != 0)
                                    {
                                        res = 125;
                                    }
                                    else
                                    {
                                        res = 100;
                                    }
                                }
                                pf &= ~PEON_HARVEST_LUMBER;
                                change_res(o, 1, 1, res);
                                add_total_res(o, 1, 1, res);
                                f = true;
                            }
                        }
                    }
                }
            }
            if (f)
            {
                pf &= ~PEON_LOADED;
                set_stat(p, pf, S_PEON_FLAGS);
                ((void (*)(int*))F_GROUP_SET)(p);
                return 1;
            }
        }
        return 0;
    }
    else
        return ((int(*)(int*))g_proc_00424745)(p);//original
}

void sounds_ready_table_set(byte id, WORD snd)
{
    char buf[] = "\x0\x0";
    buf[0] = snd % 256;
    buf[1] = snd / 256;
    PATCH_SET((char*)(UNIT_SOUNDS_READY_TABLE + 2 * id), buf);
}

void sounds_tables()
{
    sounds_ready_table_set(U_CRITTER, 247);
    sounds_ready_table_set(U_DEMON, 301);

    sounds_ready_table_set(U_ALLERIA, 254);
    sounds_ready_table_set(U_DANATH, 263);
    sounds_ready_table_set(U_HADGAR, 272);
    sounds_ready_table_set(U_KURDRAN, 281);
    sounds_ready_table_set(U_TYRALYON, 290);
    sounds_ready_table_set(U_UTER, 154);
    sounds_ready_table_set(U_LOTHAR, 155);

    sounds_ready_table_set(U_DEATHWING, 300);
    sounds_ready_table_set(U_DENTARG, 310);
    sounds_ready_table_set(U_GROM, 318);
    sounds_ready_table_set(U_KARGATH, 327);
    sounds_ready_table_set(U_TERON, 336);
    sounds_ready_table_set(U_ZULJIN, 204);
    sounds_ready_table_set(U_CHOGAL, 179);
    sounds_ready_table_set(U_GULDAN, 88);

}

//write your custom victory functions here
//-------------------------------------------------------------------------------
void v_human1()
{
    //your custom victory conditions
}

void v_human2()
{
    //your custom victory conditions
}

void v_human3()
{
    //your custom victory conditions
}

void v_human4()
{
    //your custom victory conditions
}

void v_human5()
{
    //your custom victory conditions
}

void v_human6()
{
    //your custom victory conditions
}

void v_human7()
{
    //your custom victory conditions
}

void v_human8()
{
    //your custom victory conditions
}

void v_human9()
{
    //your custom victory conditions
}

void v_human10()
{
    //your custom victory conditions
}

void v_human11()
{
    //your custom victory conditions
}

void v_human12()
{
    //your custom victory conditions
}

void v_human13()
{
    //your custom victory conditions
}

void v_human14()
{
    //your custom victory conditions
}

void v_xhuman1()
{
    //your custom victory conditions
}

void v_xhuman2()
{
    //your custom victory conditions
}

void v_xhuman3()
{
    //your custom victory conditions
}

void v_xhuman4()
{
    //your custom victory conditions
}

void v_xhuman5()
{
    //your custom victory conditions
}

void v_xhuman6()
{
    //your custom victory conditions
}

void v_xhuman7()
{
    //your custom victory conditions
}

void v_xhuman8()
{
    //your custom victory conditions
}

void v_xhuman9()
{
    //your custom victory conditions
}

void v_xhuman10()
{
    //your custom victory conditions
}

void v_xhuman11()
{
    //your custom victory conditions
}

void v_xhuman12()
{
    //your custom victory conditions
}

void v_orc1()
{
    //your custom victory conditions
}

void v_orc2()
{
    //your custom victory conditions
}

void v_orc3()
{
    //your custom victory conditions
}

void v_orc4()
{
    //your custom victory conditions
}

void v_orc5()
{
    //your custom victory conditions
}

void v_orc6()
{
    //your custom victory conditions
}

void v_orc7()
{
    //your custom victory conditions
}

void v_orc8()
{
    //your custom victory conditions
}

void v_orc9()
{
    //your custom victory conditions
}

void v_orc10()
{
    //your custom victory conditions
}

void v_orc11()
{
    //your custom victory conditions
}

void v_orc12()
{
    //your custom victory conditions
}

void v_orc13()
{
    //your custom victory conditions
}

void v_orc14()
{
    //your custom victory conditions
}

void v_xorc1()
{
    //your custom victory conditions
}

void v_xorc2()
{
    //your custom victory conditions
}

void v_xorc3()
{
    //your custom victory conditions
}

void v_xorc4()
{
    //your custom victory conditions
}

void v_xorc5()
{
    //your custom victory conditions
}

void v_xorc6()
{
    //your custom victory conditions
}

void v_xorc7()
{
    //your custom victory conditions
}

void v_xorc8()
{
    //your custom victory conditions
}

void v_xorc9()
{
    //your custom victory conditions
}

void v_xorc10()
{
    //your custom victory conditions
}

void v_xorc11()
{
    //your custom victory conditions
}

void v_xorc12()
{
    //your custom victory conditions
}

void v_custom()
{
    //your custom victory conditions
}
//-------------------------------------------------------------------------------

/*
void example1()
{
    //example function 1
    //lose condition - all player units dead
    //victory condition - build 6 farms and 3 barrack and 2 mills and 10 grunts AND kill blue castle
    //additions - can build critters from farms, critter gives gold
    sheep(true);//allow build critters
    byte local = *(byte*)LOCAL_PLAYER;
    find_all_alive_units(U_CRITTER);
    sort_stat(S_OWNER, local, CMP_EQ);//only player crittes, not neutral
    change_res(local, 0, 2, units);//argument2 = 0 - gold (1 - lumber,2-oil)
    //add 2*number of critters gold to player
    if (!slot_alive(local))lose(true);//lose game if player not have units
    else
    {
        int farms = get_val(FARM, local);
        int barracks = get_val(BARRACKS, local);
        int mills = get_val(LUMBERMILL, local);
        int grunts = get_val(GRUNT, local);
        int enemy_castle = get_val(TH3, P_BLUE);
        //use those values for anything you want
        if ((farms >= 6) && (barracks >= 3) && (mills >= 2) && (grunts >= 10) && (enemy_castle == 0))win(true);
    }
}
*/

/*
void example2()
{
    //example function 2
    //lose condition - hero must survive
    //victory condition - bring hero to region AND kill orange knights AND kill all enemy shipyards except blue
    //additions - peons can build portals, portals can teleport to other portals
    b3port = true;//allow building portals
    build3(true);//new build button for peon
    A_portal = true;//activate teleportation
    byte local = *(byte*)LOCAL_PLAYER;
    find_all_alive_units(U_DANATH);
    if (units == 0)lose(true);//no hero alive found = he probably dead - lose game
    else//if hero alive
    {
        set_region(10, 10, 16, 16);
        sort_in_region();
        if (units != 0)//if found hero inside of region
        {
            int ogres = get_val(KNIGHT, P_ORANGE);
            int shipyards = 0;
            for (int i = 0; i < 8; i++)
            {
                if ((i != local) && (i != P_BLUE))//not player himself and not blue comp
                    shipyards += get_val(SHIPYARD, i);
            }
            if ((ogres == 0) && (shipyards == 0))win(true);
        }
    }
}
*/

/*
void example3()
{
    //example function 3
    //lose condition - at least 2 RED footmans and at least 3 YELLOW ogres must survive
    //victory condition - kill enemy hero
    //additions - peons can build runestones; runestones give haste and blood.
    b3rune = true;//allow build runestone
    build3(true);//give peon new build button
    runes[2] = 1;//blood
    runes[3] = 1;//haste
    A_runestone = true;//activate runestone
    find_all_alive_units(U_FOOTMAN);
    sort_stat(S_COLOR, P_RED, CMP_EQ);
    int red_footmans = units;
    find_all_alive_units(U_OGRE);
    sort_stat(S_COLOR, P_YELLOW, CMP_EQ);
    int yellow_ogres = units;
    if ((red_footmans < 2) || (yellow_ogres < 3))lose(true);//needed amount of units not survived
    else
    {
        find_all_alive_units(U_GULDAN);//enemy hero
        if (units == 0)win(true);//if no alive hero found = he dead
    }
}
*/

/*
void example4()
{
    //example function 4
    //lose condition - heroes must survive
    //victory condition - destroy all dark portals and runestones
    //addition - only Hadgar can destroy portal; only Tyralyon can destroy runestone
    ua[0] = U_HADGAR;//attacker 0
    ut[0] = U_PORTAL;//target 0
    ua[1] = U_TYRALYON;//attacker 1
    ut[1] = U_RUNESTONE;//target 1
    find_all_alive_units(U_HADGAR);
    int hadgars = units;
    find_all_alive_units(U_TYRALYON);
    int tyralyons = units;
    if ((hadgars == 0) || (tyralyons == 0))lose(true);//no hero alive found = he probably dead - lose game
    else//if heros alive
    {
        int portals = get_val(PORTAL, P_NEUTRAL);
        int runestones = get_val(RUNESTONE, P_NEUTRAL);
        if ((portals == 0) && (runestones == 0))win(true);
    }
}
*/

/*
void example5()
{
    //example function 5
    //lose condition - all player units dead OR red comp have more than 50000 gold
    //victory condition - kill red
    //addition - orc player can build hero Teron from TH on tier 2; Teron have death aura
    heros[10] = U_TERON;//10 - slot 3 for orcs
    m_death_aura[0] = U_TERON;
    byte local = *(byte*)LOCAL_PLAYER;
    if (!slot_alive(local))lose(true);//lose game if player not have units
    else
    {
        int red_gold = *(int*)(GOLD + 4 * P_RED);//get red comp gold
        if (red_gold > 50000)lose(true);
        else
        {
            if (!slot_alive(P_RED))win(true);//kill red
        }
    }
}
*/

/*
void example6()
{
    //example function 6
    //lose condition - hero survive 
    //victory condition - kill all enemies
    //addition - when player bring hero to some region he will receive message (and receive it ONLY 1 time)
    //AND hero changes stats after this
    byte local = *(byte*)LOCAL_PLAYER;

    //EXAMPLE of save/load values
    int byte_id = 0;//any id from 0 to 15
    int saved_byte = *(byte*)(GB_HORSES + byte_id);//GB_HORSES is ussles massive in game
    //BUT this massive saved to *.sav file and those 16 bytes can be used to load values between games
    
    if (saved_byte == 1)//if hero WAS in region at least once (and this info saved betweed save/load games too)
    {
        //give hero new abilities
        m_sneak[0] = U_ALLERIA;//can turn invisible now
        def_stat(U_ALLERIA, 120, 16, 32, 1, 8, 0, 0, 0, 0);//120 hp 16-32 dmg 1 armor 8 range (some big changes)
        find_all_alive_units(U_ALLERIA);
        set_stat_all(S_COLOR, P_RED);//new color
    }
    else
    {
        //reset all
        m_sneak[0] = 255;
        def_stat(U_ALLERIA, 120, 10, 20, 0, 6, 0, 0, 0, 0);//120 hp 10-20 dmg 0 armor 6 range
        find_all_alive_units(U_ALLERIA);
        set_stat_all(S_COLOR, P_BLUE);//default color
    }

    find_all_alive_units(U_ALLERIA);
    if (units == 0)lose(true);//no hero alive found = he probably dead - lose game
    else//if hero alive
    {
        set_region(10, 10, 16, 16);
        sort_in_region();
        if (units != 0)//if found hero inside of region
        {
            if (saved_byte == 0)//if hero was not in region even 1 time before
            {
                *(byte*)(GB_HORSES + byte_id) = 1;//set flag that hero visited region
                char msg[] = "Hello there!";
                show_message(10, msg);//show this message for 10 sec
            }
        }
        if (!check_opponents(local))win(true);//if no more opponents = win
    }

}
*/

void (*triggers[])() = { v_human1,v_orc1,v_human2,v_orc2,v_human3,v_orc3,v_human4,v_orc4,v_human5,v_orc5,v_human6,v_orc6,v_human7,v_orc7,v_human8,v_orc8,v_human9,v_orc9,v_human10,v_orc10,v_human11,v_orc11,v_human12,v_orc12,v_human13,v_orc13,v_human14,v_orc14,v_xhuman1,v_xorc1,v_xhuman2,v_xorc2,v_xhuman3,v_xorc3,v_xhuman4,v_xorc4,v_xhuman5,v_xorc5,v_xhuman6,v_xorc6,v_xhuman7,v_xorc7,v_xhuman8,v_xorc8,v_xhuman9,v_xorc9,v_xhuman10,v_xorc10,v_xhuman11,v_xorc11,v_xhuman12,v_xorc12 };

void trig()
{
    byte lvl = *(byte*)LEVEL_OBJ;
    if (a_custom)
    {
        v_custom();
    }
    else
    {
        if ((lvl >= 0) && (lvl < 52))
            ((void (*)())triggers[lvl])();
        else
            v_custom();
    }
}

void replace_def()
{
    //set all vars to default
    memset(ua, 255, sizeof(ua));
    memset(ut, 255, sizeof(ut));
    memset(runes, 0, sizeof(runes));
    memset(hhero, 0, sizeof(hhero));
    memset(ohero, 0, sizeof(ohero));
    memset(heros, 0, sizeof(heros));
    memset(herosb, false, sizeof(herosb));
    memset(m_slow_aura, 255, sizeof(m_slow_aura));
    memset(m_death_aura, 255, sizeof(m_death_aura));
    memset(m_sneak, 255, sizeof(m_sneak));
    memset(m_devotion, 255, sizeof(m_devotion));
    memset(m_vampire, 255, sizeof(m_vampire));
    memset(m_prvnt, 255, sizeof(m_prvnt));
    table = false;
    agr = false;
    cpt = false;
    pcpt = false;
    thcpt = false;
    steal = false;
    aport = false;
    mport = false;
    b3rune = false;
    b3port = false;
    b3cirl = false;
    b3mine = false;
    b3forest = false;
    apn = false;
    manaburn = false;
    A_runestone = false;
    A_portal = false;
    A_transport = false;
    A_autoheal = false;
    blood_f = false;
    more_res = false;
}

void replace_common()
{
    //peon can build any buildings
    char ballbuildings[] = "\x0\x0";//d1 05
    PATCH_SET((char*)BUILD_ALL_BUILDINGS1, ballbuildings);
    char ballbuildings2[] = "\x0";//0a
    PATCH_SET((char*)BUILD_ALL_BUILDINGS2, ballbuildings2);
    char ballbuildings3[] = "\x0";//68
    PATCH_SET((char*)BUILD_ALL_BUILDINGS3, ballbuildings3);

    //any building can train any unit
    char ballunits[] = "\xeb";//0x74
    PATCH_SET((char*)BUILD_ALL_UNITS1, ballunits);
    char ballunits2[] = "\xA1\xBC\x47\x49\x0\x90\x90";//8b 04 85 bc 47 49 00
    PATCH_SET((char*)BUILD_ALL_UNITS2, ballunits2);

    //show kills
    byte d = S_KILLS;
    char sdmg[] = "\x8a\x90\x82\x0\x0\x0\x8b\xfa";//units
    sdmg[2] = d;
    PATCH_SET((char*)SPEED_STAT_UNITS, sdmg);
    char sdmg2[] = "\x8a\x82\x82\x0\x0\x0\x90\x90\x90";//catas
    sdmg2[2] = d;
    PATCH_SET((char*)SPEED_STAT_CATS, sdmg2);
    char sdmg3[] = "\x8a\x88\x82\x0\x0\x0\x90\x90\x90";//archers
    sdmg3[2] = d;
    PATCH_SET((char*)SPEED_STAT_ARCHERS, sdmg3);
    char sdmg4[] = "\x8a\x82\x82\x0\x0\x0\x90\x90\x90";//berserkers
    sdmg4[2] = d;
    PATCH_SET((char*)SPEED_STAT_BERSERKERS, sdmg4);
    char sdmg5[] = "\x8a\x88\x82\x0\x0\x0\x90\x90\x90";//ships
    sdmg5[2] = d;
    PATCH_SET((char*)SPEED_STAT_SHIPS, sdmg5);

    char dmg_fix[] = "\xeb";
    PATCH_SET((char*)DMG_FIX, dmg_fix);

    th_change(true);
    draw_stats_fix(true);
}

void replace_back()
{
    //replace all to default
    comps_vision(false);
    sheep(false);
    build3(false);
    demon(false);
    th_change(false);
    repair_all(false);
    repair_cat(false);
    trigger_time('\xc8');
    fireball_dmg(40);
    buff_time(0, 0xd0, 0x7);
    buff_time(1, 0xe8, 0x3);
    buff_time(2, 0xf4, 0x1);
    buff_time(3, 0xe8, 0x3);
    buff_time(4, 0xe8, 0x3);
    upgr(SWORDS, 2);
    upgr(ARMOR, 2);
    upgr(ARROWS, 1);
    upgr(SHIP_DMG, 5);
    upgr(SHIP_ARMOR, 5);
    upgr(CATA_DMG, 15);
    manacost(VISION, 70);
    manacost(HEAL, 6);
    manacost(GREATER_HEAL, 5);
    manacost(EXORCISM, 4);
    manacost(FIREBALL, 100);
    manacost(FLAME_SHIELD, 80);
    manacost(SLOW, 50);
    manacost(INVIS, 200);
    manacost(POLYMORPH, 200);
    manacost(BLIZZARD, 25);
    manacost(EYE_OF_KILROG, 70);
    manacost(BLOOD, 50);
    manacost(RAISE_DEAD, 50);
    manacost(COIL, 100);
    manacost(WHIRLWIND, 100);
    manacost(HASTE, 50);
    manacost(UNHOLY_ARMOR, 100);
    manacost(RUNES, 200);
    manacost(DEATH_AND_DECAY, 25);
    no_random_dmg(false);
    blood_fix(false);
    draw_stats_fix(false);
    brclik(false);
    rc_jmp(false);
    autoheal(false);
}

void replace_trigger()
{
    replace_back();
    replace_def();
    replace_common();

    //replace original victory trigger
    char trig_jmp[] = "\x74\x1A";//74 0F
    PATCH_SET((char*)VICTORY_JMP, trig_jmp);
    char rep[] = "\xc7\x05\x38\x0d\x4c\x0\x30\x8C\x45\x0";
    void (*repf) () = trig;
    patch_setdword((DWORD*)(rep + 6), (DWORD)repf);
    PATCH_SET((char*)VICTORY_TRIGGER, rep);
}

PROC g_proc_0042A4A1;
void new_game(int a, int b, long c)
{
    a_custom = b % 256;//custom game or campaign
	if (a_custom)*(byte*)LEVEL_OBJ=53;//remember custom obj
	else
	{
	if (*(byte*)LEVEL_OBJ==53)a_custom=1;//fix for when saved game loads custom get broken
	}
    replace_trigger();
    ((void (*)(int, int, long))g_proc_0042A4A1)(a, b, c);//original
}

void hook(int adr, PROC* p, char* func)
{
    *p = patch_call((char*)adr, func);
}

void common_hooks()
{
    hook(0x0045271B, &g_proc_0045271B, (char*)update_spells);

    hook(0x004522B9, &g_proc_004522B9, (char*)seq_run);

    hook(0x0041038E, &g_proc_0041038E, (char*)damage1);
    hook(0x00409F3B, &g_proc_00409F3B, (char*)damage2);
    hook(0x0040AF70, &g_proc_0040AF70, (char*)damage3);
    hook(0x0040AF99, &g_proc_0040AF99, (char*)damage4);
    hook(0x00410762, &g_proc_00410762, (char*)damage5);
    hook(0x004428AD, &g_proc_004428AD, (char*)damage6);

    hook(0x0043BAE1, &g_proc_0043BAE1, (char*)rc_snd);
    hook(0x0043B943, &g_proc_0043B943, (char*)rc_build_click);
    hook(0x0040DF71, &g_proc_0040DF71, (char*)bld_unit_create);
    hook(0x0040AFBF, &g_proc_0040AFBF, (char*)tower_find_attacker);
    hook(0x00451728, &g_proc_00451728, (char*)unit_kill_deselect);

    hook(0x0045614E, &g_proc_0045614E, (char*)receive_cheat);

    hook(0x004526FE, &g_proc_004526FE, (char*)grow_structure);
    hook(0x00418FFE, &g_proc_00418FFE, (char*)create_building);
    hook(0x0043A974, &g_proc_0043A974, (char*)placebox_query);
    hook(0x0043ABAB, &g_proc_0043ABAB, (char*)placebox_query);
    hook(0x00424745, &g_proc_00424745, (char*)goods_into_inventory);
    hook(0x004529C0, &g_proc_004529C0, (char*)goods_into_inventory);

    hook(0x0042A4A1, &g_proc_0042A4A1, (char*)new_game);
}

extern "C" __declspec(dllexport) void w2p_init()
{
    common_hooks();//hook functions
    sounds_tables();//fix hero sounds
}
