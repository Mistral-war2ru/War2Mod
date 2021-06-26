//compare variable methods
#define CMP_EQ 0			//  ==
#define CMP_NEQ 1			//  !=
#define CMP_BIGGER_EQ 2		//  >=
#define CMP_SMALLER_EQ 3	//  <=
#define CMP_BIGGER 4		//  >
#define CMP_SMALLER 5		//  <

//upgrades ids
#define ARROWS 0
#define SWORDS 1
#define ARMOR 2
#define SHIP_DMG 3
#define SHIP_ARMOR 4
//5 unused
#define CATA_DMG 6

//magic ids
#define VISION 0
#define HEAL 1
#define GREATER_HEAL 2
#define EXORCISM 3
#define FLAME_SHIELD 4
#define FIREBALL 5
#define SLOW 6
#define INVIS 7
#define POLYMORPH 8
#define BLIZZARD 9
#define EYE_OF_KILROG 10
#define BLOOD 11
#define RAISE_DEAD 12
#define COIL 13
#define WHIRLWIND 14
#define HASTE 15
#define UNHOLY_ARMOR 16
#define RUNES 17
#define DEATH_AND_DECAY 18

//players ids
#define P_RED 0
#define P_BLUE 1
#define P_GREEN 2
#define P_VIOLET 3
#define P_ORANGE 4
#define P_BLACK 5
#define P_WHITE 6
#define P_YELLOW 7
#define PLAYER9 8
#define PLAYER10 9
#define PLAYER11 10
#define PLAYER12 11
#define PLAYER13 12
#define PLAYER14 13
#define PLAYER15 14
#define P_NEUTRAL 15

//AI upgrades ids
#define	UP_ARROW1 0x80
#define	UP_ARROW2 0x81
#define	UP_RANGER 0x82
#define	UP_SKILL1 0x83
#define	UP_SKILL2 0x84
#define	UP_SKILL3 0x85
#define	UP_SWORD1 0x86
#define	UP_SWORD2 0x87
#define	UP_SHIELD1 0x88
#define	UP_SHIELD2 0x89
#define	UP_CATDMG1 0x8A
#define	UP_CATDMG2 0x8B
#define	UP_BOATATK1 0x8C
#define	UP_BOATATK2 0x8D
#define	UP_BOATARM1 0x8E
#define	UP_BOATARM2 0x8F
#define	UP_CLERIC 0x90
#define	UP_CLERIC1 0x91
#define	UP_CLERIC2 0x92
#define	UP_WIZARD1 0x93
#define	UP_WIZARD2 0x94
#define	UP_WIZARD3 0x95
#define	UP_WIZARD4 0x96
#define	UP_WIZARD5 0x97
#define	UP_KEEP 0x98
#define	UP_CASTLE 0x99

//units
#define U_FOOTMAN 0
#define U_GRUNT 1
#define U_PEASANT 2
#define U_PEON 3
#define U_BALLISTA 4
#define U_CATAPULT 5
#define U_KNIGHT 6
#define U_OGRE 7
#define U_ARCHER 8
#define U_TROLL 9
#define U_MAGE 10
#define U_DK 11
#define U_PALADIN 12
#define U_OGREMAGE 13
#define U_DWARWES 14
#define U_GOBLINS 15
#define U_ATTACK_PEASANT 16
#define U_ATTACK_PEON 17
#define U_RANGER 18
#define U_BERSERK 19
#define U_ALLERIA 20
#define U_TERON 21
#define U_KURDRAN 22
#define U_DENTARG 23
#define U_HADGAR 24
#define U_GROM 25
#define U_HTANKER 26
#define U_OTANKER 27
#define U_HTRANSPORT 28
#define U_OTRANSPORT 29
#define U_HDESTROYER 30
#define U_ODESTROYER 31
#define U_BATTLESHIP 32
#define U_JUGGERNAUT 33
#define TYPE_A100 34
#define U_DEATHWING 35
#define TYPE_B36 36
#define TYPE_B37 37
#define U_SUBMARINE 38
#define U_TURTLE 39
#define U_FLYER 40
#define U_ZEPPELIN 41
#define U_GRIFON 42
#define U_DRAGON 43
#define U_TYRALYON 44
#define U_EYE 45
#define U_DANATH 46
#define U_KARGATH 47
#define TYPE_A5 48
#define U_CHOGAL 49
#define U_LOTHAR 50
#define U_GULDAN 51
#define U_UTER 52
#define U_ZULJIN 53
#define TYPE_A600 54
#define U_SKELETON 55
#define U_DEMON 56
#define U_CRITTER 57
#define U_FARM 58
#define U_PIGFARM 59
#define U_HBARRACK 60
#define U_OBARRACK 61
#define U_CHURCH 62
#define U_ALTAR 63
#define U_HTOWER 64
#define U_OTOWER 65
#define U_STABLES 66
#define U_OGREMOUND 67
#define U_INVENTOR 68
#define U_ALCHEMIST 69
#define U_AVIARY 70
#define U_DRAGONROOST 71
#define U_SHIPYARD 72
#define U_WHARF 73
#define U_TOWN_HALL 74
#define U_GREAT_HALL 75
#define U_HLUMBER 76
#define U_OLUMBER 77
#define U_HFOUNDRY 78
#define U_OFOUNDRY 79
#define U_MAGE_TOWER 80
#define U_TEMPLE 81
#define U_HSMITH 82
#define U_OSMITH 83
#define U_HREFINERY 84
#define U_OREFINERY 85
#define U_HPLATFORM 86
#define U_OPLATFROM 87
#define U_KEEP 88
#define U_STRONGHOLD 89
#define U_CASTLE 90
#define U_FORTRESS 91
#define U_MINE 92
#define U_OIL 93
#define U_HSTART 94
#define U_OSTART 95
#define U_HARROWTOWER 96
#define U_OARROWTOWER 97
#define U_HCANONTOWER 98
#define U_OCANONTOWER 99
#define U_CIRCLE 100
#define U_PORTAL 101
#define U_RUNESTONE 102
#define U_HWALL 103
#define U_OWALL 104
#define ANY_BUILDING 105//dead body
#define ANY_MEN 106//dead building 1x1
#define ANY_UNITS 107//dead building 2x2
#define ANY_BUILDING_2x2 108//dead building 3x3
#define ANY_BUILDING_3x3 109//dead building 4x4
#define ANY_BUILDING_4x4 110//not unit

//bullets and effects
#define B_LIGHTNING 0
#define B_HAMMER 1
#define B_FIREBALL 2
#define B_FIRESHIELD 3
#define B_FIRESPIN 4
#define B_BLIZZARD 5
#define B_ROT 6
#define B_BIG_CANNON 7
#define B_EXORCISM 8
#define B_HEAL 9
#define B_COIL 10
#define B_RUNE 11
#define B_TORNADO 12
#define B_STONE 13
#define B_BOLT 14
#define B_ARROW 15
#define B_AXE 16
#define B_HTORPEDO 17
#define B_OTORPEDO 18
#define B_LIGHT_FIRE 19
#define B_HEAVY_FIRE 20
#define B_CAT_HIT 21
#define B_SPARKLE 22
#define B_BOOM_FIRE 23
#define B_CANNON 24
#define B_SHOT_FIRE 25
#define B_CANNON_HIT 26
#define B_DEMON_FIRE 27
#define B_CROSS 28
#define B_NONE 29

//spells sounds
#define SS_BLOOD 0
#define SS_DECAY 1
#define SS_COIL 2
#define SS_EXORCISM 3
#define SS_FLAMESHIELD 4
#define SS_HASTE 5
#define SS_HEAL 6
#define SS_VISION 7
#define SS_BLIZZARD 8
#define SS_INVIZ 9
#define SS_EYE 10
#define SS_POLYMOPH 11
#define SS_SLOW 12
#define SS_THUNDER 13
#define SS_THDARK 14
#define SS_ARMOR 15
#define SS_WIND 16

//allowed units 4 bytes
#define A_FOOT 0
#define A_PEON 1
#define A_CATA 2
#define A_OGRE 3
#define A_ARHC 4
#define A_MAGE 5
#define A_TANKER 6
#define A_DESTROYER 7
#define A_TRANSPORT 8
#define A_BATTLE 9
#define A_SUB 10
#define A_FLYER 11
#define A_DRAGON 12
#define A_UNUSED 13
#define A_SAP 14
#define A_AVIARY 15
#define A_FARM 16
#define A_BARRACK 17
#define A_LUMBER 18
#define A_STABLES 19
#define A_TEMPLE 20
#define A_FOUDNRY 21
#define A_REFINERY 22
#define A_INVENTOR 23
#define A_ALTAR 24
#define A_TOWER 25
#define A_TH1 26
#define A_TH2 27
#define A_TH3 28
#define A_SMITH 29
#define A_SHIPYARD 30

//allowed upgrades 4 bytes
#define A_ARROW1 0
#define A_ARROW2 1
#define A_SWORD1 2
#define A_SWORD2 3
#define A_ARMOR1 4
#define A_ARMOR2 5
#define A_SHIP_ATTACK1 6
#define A_SHIP_ATTACK2 7
#define A_SHIP_ARMOR1 8
#define A_SHIP_ARMOR2 9
#define A_UNUSED_SHIP1 10
#define A_UNUSED_SHIP2 11
#define A_CATA1 12
#define A_CATA2 13
#define A_UNUSED_SPEED1 14
#define A_UNUSED_SPEED2 15
#define A_BERSERKERS 16
#define A_RANGE 17
#define A_SCOUT 18
#define A_MARKS 19

// allowed spells 4 bytes
#define A_VISION 0
#define A_HEAL 1
#define A_GREATER_HEAL 2
#define A_EXORCISM 3
#define A_FLAME_SHIELD 4
#define A_FIREBALL 5
#define A_SLOW 6
#define A_INVIS 7
#define A_POLYMORF 8
#define A_BLIZZARD 9
#define A_EYE 10
#define A_BLOOD 11
#define A_UNUSED_HALLUCINATE 12
#define A_RAISE 13
#define A_COIL 14
#define A_WIND 15
#define A_HASTE 16
#define A_UNHOLY 17
#define A_RUNES 18
#define A_DD 19
#define A_ALTAR_UPGR 20

//learned spells ids
#define L_VISION 0
#define L_HEAL 1
#define L_GREATER_HEAL 2
#define L_EXORCISM 3
#define L_FLAME_SHIELD 4
#define L_FIREBALL 5
#define L_SLOW 6
#define L_INVIS 7
#define L_POLYMORF 8
#define L_BLIZZARD 9
#define L_EYE 10
#define L_BLOOD 11
#define L_UNUSED_HALLUCINATE 12
#define L_RAISE 13
#define L_COIL 14
#define L_WIND 15
#define L_HASTE 16
#define L_UNHOLY 17
#define L_RUNES 18
#define L_DD 19
#define L_ALTAR_UPGR 20

//unit stats
#define S_DRAW_X 0
#define S_DRAW_Y 2
#define S_SEQ 4
#define S_SEQ_FLAG 6
#define S_ANIMATION_TIMER 7
#define S_ANIMATION 8

#define ANIM_DEAD 0
#define ANIM_DIE 1
#define ANIM_STOP 2
#define ANIM_MOVE 3
#define ANIM_ATTACK 4
#define ANIM_BUILD 5
#define ANIM_TRANSPORT_SHORE 6

#define S_FRAME 9
#define S_FACE 10
#define FACE_N 0
#define FACE_NE 1
#define FACE_E 2
#define FACE_SE 3
#define FACE_S 4
#define FACE_SW 5
#define FACE_W 6
#define FACE_NW 7
//14 sequence bytes
#define S_X 24
#define S_Y 26

#define S_FLAGS1 28
	#define UF_EVEN_ALIGN 0x0002//Unit should be even matrix
	#define UF_AIR 0x0004//Unit should use the AIR map
	#define UF_WATER 0x0008//Unit is in the water
	#define UF_BUILD_ON	0x0010//
	#define UF_BUILD_CANCEL	0x0020//
	#define UF_UNLOAD_ALL 0x0040//used by transports

#define S_FLAGS2 29
	#define UF_RESCUE 0x0100//unit is being res

#define S_FLAGS3 30
	#define SF_UNIT_FREE 0x0001// unit not used
	#define SF_DIEING 0x0002// death sequence
	#define SF_DEAD 0x0004// no longer on map
	#define SF_HIDDEN 0x0008// inside building
	#define SF_SKIP_BOX 0x0010// not in visible window
	#define SF_PREPLACED 0x0020// unit was already on the map
	#define SF_TELEPORT 0x0040//0040 is free mem (now used for teleport flag)
	#define SF_COMPLETED 0x0080// unit completed building

#define S_FLAGS4 31
	#define SF_BUILD_FOUNDATION 0x01// early stages of building
	#define SF_INHIBIT_RETARG 0x02
	#define SF_MAP_HEADER 0x04// listed in map header
	#define SF_PAUSE_TOGGLE 0x08// used to tell a peon to pause
	#define SF_IS_PAUSED 0x10// set when peon actually pauses
	#define SF_SELECTED 0x20// selected by local player
	#define SF_TARGET_CHANGED 0x40
	#define SF_UNDER_ATTACK 0x80

#define S_AIFLAGS1 32
#define S_AIFLAGS2 33
#define S_HP 34
#define S_SOUND_COUNTER 36
#define S_COMMANDS 37
#define S_MANA 38
#define S_ID 39
//40 41 vision mask
#define S_MOVEMENT_TYPE 42

#define MOV_LAND 0
#define MOV_AIR 1
#define MOV_WATER 2
#define MOV_SHORE 3

#define S_SPRITE 43
#define S_OWNER 44
#define S_COLOR 45
#define S_ORDER 46
#define S_NEXT_ORDER 47

#define ORDER_DEAD 0
#define ORDER_DIE 1
#define ORDER_STOP 2
#define ORDER_MOVE 3
#define ORDER_MOVE_PATROL 4
#define ORDER_PATROL 5
#define ORDER_FOLLOW 6
#define ORDER_FOLLOW_GUARD 7
#define ORDER_ATTACK 8
#define ORDER_ATTACK_TARGET 9
#define ORDER_ATTACK_AREA 10
#define ORDER_ATTACK_WALL 11
#define ORDER_DEFEND 12
#define ORDER_STAND 13
#define ORDER_STAND_ATTACK 14
#define ORDER_DEFEND_GROUND 15
#define ORDER_DEFEND_STOPPED 16
#define ORDER_ATTACK_GROUND 17
#define ORDER_ATTACK_GROUND_MOVE 18
#define ORDER_DEMOLISH 19
#define ORDER_DEMOLISH_NEAR 20
#define ORDER_DEMOLISH_AT 21
#define ORDER_PEON_BUILD 22
#define ORDER_HARVEST 23
#define ORDER_RETURN 24
#define ORDER_ENTER 25
#define ORDER_LEAVE 26
#define ORDER_REPAIR 27
#define ORDER_CREATE_BLDG 28
#define ORDER_UNLOAD_ALL 29
#define ORDER_DOCK 30
#define ORDER_UNDOCK 31
#define ORDER_WAIT 32
#define ORDER_BLDG_WAIT 33
#define ORDER_ENTER_TRANSPORT 34
#define ORDER_LEAVE_TRANSPORT 35
#define ORDER_TRAVELING 36
#define ORDER_BLDG_BUILD 37
#define ORDER_SPELL_VISION 38
#define ORDER_SPELL_HEAL 39
#define ORDER_SPELL_AREAHEAL 40
#define ORDER_SPELL_EXORCISM 41
#define ORDER_SPELL_FIRESHIELD 42
#define ORDER_SPELL_FIREBALL 43
#define ORDER_SPELL_SLOW 44
#define ORDER_SPELL_INVIS 45
#define ORDER_SPELL_POLYMORPH 46
#define ORDER_SPELL_BLIZZARD 47
#define ORDER_SPELL_EYE 48
#define ORDER_SPELL_BLOODLUST 49
#define ORDER_SPELL_RAISEDEAD 50
#define ORDER_SPELL_DRAINLIFE 51
#define ORDER_SPELL_WHIRLWIND 52
#define ORDER_SPELL_HASTE 53
#define ORDER_SPELL_ARMOR 54
#define ORDER_SPELL_RUNES 55
#define ORDER_SPELL_ROT 56
#define ORDER_RESURRECT 57
#define ORDER_WAIT_CONVERT 58
#define ORDER_VICTORY_CIRCLE 59
#define ORDER_NONE 60

#define S_MOV_PATH01 49
//20 movement path bytes

#define S_INVIZ 68
#define S_SHIELD 70
#define S_BLOOD 72
#define S_HASTE 74
#define S_AI_SPELLS 76
/*
	#define US_DRAIN			0x0001
	#define US_POLYMORPH		0x0002
	#define US_VISION			0x0004
	#define US_EXORCISM			0x0008
	#define US_HEAL				0x0010
	#define US_RAISE			0x0020
	#define US_WHIRLWIND		0x0040
*/
#define S_NEXT_FIRE 78
#define S_FLASH_COLOR 80
#define S_FLASH_COUNTER 81
//82 83 unknown bytes
#define S_ATTACKER_POINTER 84
//ai bytes
#define S_AI_DEST_X 88
#define S_AI_DEST_Y 90
#define S_AI_DEST_REGION 92
#define S_AI_ORDER 94

	#define AI_ORDER_NONE 0
	#define AI_ORDER_DEFEND 1
	#define AI_ORDER_ATTACK 2
	#define AI_ORDER_TRANSPORT 3
	#define AI_ORDER_PATROL 4
	#define AI_ORDER_GUARD 5
	#define AI_ORDER_SHIP_PATROL 6

#define S_AI_AIFLAGS 95

//ai flags
	#define AI_PLEASE_TRANSPORT 0x1
	#define AI_PASSIVE 0x2

#define S_NEXT_UNIT_POINTER 104

//peon type
#define S_LAST_HARVEST_X 108
#define S_LAST_HARVEST_Y 110
#define S_PEON_GOLDMINE_POINTER 112
#define S_PEON_TREE_CHOPS 116
#define S_PEON_FLAGS 117

#define PEON_HARVEST_GOLD	0x80
#define PEON_HARVEST_LUMBER	0x40
#define PEON_LOADED			0x20
#define PEON_ENTERED		0x10
#define PEON_SAVED_LOCATION	0x08
#define PEON_IN_CASTLE		0x04
#define PEON_CHOPPING		0x02

#define S_PEON_AI_PARM 118
/*
#define PEON_HARVEST_GOLD	0x80
#define PEON_HARVEST_LUMBER	0x40
#define PEON_LOADED			0x20
#define PEON_ENTERED		0x10
#define PEON_SAVED_LOCATION	0x08
#define PEON_IN_CASTLE		0x04
#define PEON_CHOPPING		0x02
*/

//build type
#define S_BUILD_ORDER 108
#define S_BUILD_TYPE 109
#define S_BUILD_PROGRES 110
#define S_BUILD_PROGRES_TOTAL 112

#define S_KILLS 120//unknown byte used for kills
//byte 121?
#define S_ATTACK_COUNTER 122
//unknown bytes

//peon type 2
#define S_PEON_BUILD 127
#define S_PEON_BUILD_X 128
#define S_PEON_BUILD_Y 130

//build type 2
#define S_RESOURCES 130
//byte 131?

#define S_ORDER_X 132
#define S_ORDER_Y 134
#define S_ORDER_UNIT_POINTER 136
//unknown byte 140
#define S_RETARGET_ORDER 141
//unknown byte timer? 142
//unknown byte 143
#define S_RETARGET_X1 144
#define S_RETARGET_Y1 146
#define S_RETARGET_X2 148
#define S_RETARGET_Y2 150
//152 END