#ifndef __ONX_H
#define __ONX_H

#include "include\include.h"
#include "gamedata.h"
#include "game1.h"

#define RESPAWNSPRITENUMBER 47

void OnSpriteDestroy(Sprite2 *s);
void OnSpriteShieldDown(Sprite2 *s);
void OnSpriteRespawn(Sprite2 *s);
void OnItemClick(BaseItem *i);
void OnSpriteHullCritical(Sprite2 *s);
void OnSpriteCollision(Sprite2 *s1,Sprite2 *s2);
void OnPreFlip();
void OnSpriteFire(Sprite2 *s,int n);


#endif