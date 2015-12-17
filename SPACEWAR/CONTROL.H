#ifndef __CONTROL_H
#define __CONTROL_H

#include "include\include.h"

struct kbcontrol
{
	int up;
	int down;
	int left;
	int right;
	int fire;
	int special;
};

void ProcessKeyboardEx(Sprite2 *s,kbcontrol *kbc);
void ProcessMouse(Sprite2 *s);
void ProcessControllersEx(Sprite2 *s,joystick *j);
BOOL loadkbcontrol(kbcontrol *kbc,char *filename,char *section);

#endif