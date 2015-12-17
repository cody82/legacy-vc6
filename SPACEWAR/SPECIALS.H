#ifndef __SPECIALS_H
#define __SPECIALS_H

#include "include\include.h"
#include "gamedata.h"

#define SPECIAL_NONE			0
#define SPECIAL_TELEPORT		1
#define SPECIAL_TURRET			2
#define SPECIAL_REARFIRE		3
#define SPECIAL_SELFDESTRUCT	4
#define SPECIAL_SYSTEMOVERLOAD	5
#define SPECIAL_SUCKENERGY		6
#define SPECIAL_MINE			7

void SpecialRandomTeleport(Sprite2 *s);
void SpecialTurret(Sprite2 *s);
void SpecialRearFire(Sprite2 *s);
void SpecialSelfDestruct(Sprite2 *s);
void SpecialSystemOverload(Sprite2 *s);
void SpecialSuckEnergy(Sprite2 *s);
void SpecialMine(Sprite2 *s);

#endif