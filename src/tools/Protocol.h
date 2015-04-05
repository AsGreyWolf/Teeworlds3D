#ifndef PROTOCOL_H
#define PROTOCOL_H
#include "quad2.h"
#define MAX_PLAYERS 16
enum WEAPONS{
	WEAPON_HAMMER,
	WEAPON_GUN,
	WEAPON_SHOTGUN,
	WEAPON_GRENADE,
	WEAPON_RIFLE,
	WEAPON_NINJA,
	NUM_WEAPONS,
};
enum EMOTES
{
	EMOTE_NORMAL,
	EMOTE_ANGRY,
	EMOTE_PAIN,
	EMOTE_HAPPY,
	EMOTE_BLINK,
	EMOTE_SURPRISE,
	NUM_EMOTES
};
#endif