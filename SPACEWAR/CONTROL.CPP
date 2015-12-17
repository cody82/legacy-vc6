#include "control.h"
#include "game1.h"

void ProcessKeyboardEx(Sprite2 *s,kbcontrol *kbc)
{
	s->currentacceleration=0;
	if(kbc->up!=-1&&mainengine.keyboard.GetKeyState(kbc->up))s->currentacceleration=s->maxacceleration;//s->Accelerate(1);
	if(kbc->down!=-1&&mainengine.keyboard.GetKeyState(kbc->down))s->currentacceleration=(float)(s->maxacceleration*-0.25);//s->Accelerate(-0.25);
	if(kbc->left!=-1&&mainengine.keyboard.GetKeyState(kbc->left))s->currentturnspeed-=s->turnspeed;
	if(kbc->right!=-1&&mainengine.keyboard.GetKeyState(kbc->right))s->currentturnspeed+=s->turnspeed;
	if(s->currentturnspeed>s->turnspeed)
			s->currentturnspeed=s->turnspeed;
	if(s->currentturnspeed<-s->turnspeed)
			s->currentturnspeed=-s->turnspeed;
		if(!(kbc->left!=-1&&mainengine.keyboard.GetKeyState(kbc->left))&& !(kbc->right!=-1&&mainengine.keyboard.GetKeyState(kbc->right)))
		{
			s->currentturnspeed=0;
		}
	
		if(kbc->fire!=-1&&mainengine.keyboard.GetKeyState(kbc->fire))
		{
			s->Fire(s->weapon->nlaunch);
		}
		if(kbc->special!=-1&&mainengine.keyboard.GetKeyState(kbc->special))
		{
			s->Special();
		}

} /* ProcessKeyboardEx */

void ProcessMouse(Sprite2 *s)
{
	POINT p;
	float destangle;

	p=mainengine.mouse.GetPos();

	destangle=(float)(90-(   atan2((p.y+mainengine.ScreenPos.y-(s->position.y+s->size.y/2))*-1,p.x+mainengine.ScreenPos.x-(s->position.x+s->size.x/2))    /PI*180));
	if(destangle>=360)destangle-=360;
	if(destangle<0)destangle+=360;
	//destangle=mainengine.GetAngle(s,mainengine.cursor);
	//s->angle=angle;
	
	if(s->angle<destangle)
		{
			if(destangle-s->angle<180)
				s->currentturnspeed=s->turnspeed;
			else if(destangle-s->angle>180)
				s->currentturnspeed=-s->turnspeed;
		}
	else if(s->angle>destangle)
		{
			if(s->angle-destangle<180)
				s->currentturnspeed=-s->turnspeed;
			else if(s->angle-destangle>180)
				s->currentturnspeed=s->turnspeed;
		}
		
		if(mainengine.mouse.ButtonPressed(0))
		{
			s->Fire(s->weapon->nlaunch);
		}
		if(mainengine.mouse.ButtonPressed(1))
		{
			s->Special();
		}

} /* ProcessMouse */

void ProcessControllersEx(Sprite2 *s,joystick *j)
{

		j->UpdateJoystick();
		
		s->currentacceleration=0;
		s->currentturnspeed=0;
		if(j->GetYpos()<32768-DEADZONE)s->currentacceleration=s->maxacceleration;
		if(j->GetYpos()>32768+DEADZONE)s->currentacceleration=(float)(s->maxacceleration*-0.25);
		if(j->GetXpos()<32768-DEADZONE)s->currentturnspeed-=s->turnspeed;
		if(j->GetXpos()>32768+DEADZONE)s->currentturnspeed+=s->turnspeed;
		if(s->currentturnspeed>s->turnspeed)
			s->currentturnspeed=s->turnspeed;
		if(s->currentturnspeed<-s->turnspeed)
			s->currentturnspeed=-s->turnspeed;
/*		if((j->GetXpos()>32768-DEADZONE)&&(j->GetXpos()<32768+DEADZONE))
		{
			s->currentturnspeed=0;
		}*/

		if(j->GetButtonState(1))
		{
			s->Fire(s->weapon->nlaunch);
		}
		if(j->GetButtonState(2))
		{
			s->Special();
		}

} /* ProcessControllersEx */

BOOL loadkbcontrol(kbcontrol *kbc,char *filename,char *section)
{
	int i;
	i=GetPrivateProfileIntCurrentDir(filename,section,"up",-1);
	kbc->up=i;

	i=GetPrivateProfileIntCurrentDir(filename,section,"down",-1);
	if(i==-1)return(FALSE);
	kbc->down=i;

	i=GetPrivateProfileIntCurrentDir(filename,section,"left",-1);
	kbc->left=i;

	i=GetPrivateProfileIntCurrentDir(filename,section,"right",-1);
	kbc->right=i;
	
	i=GetPrivateProfileIntCurrentDir(filename,section,"fire",-1);
	kbc->fire=i;

	i=GetPrivateProfileIntCurrentDir(filename,section,"special",-1);
	kbc->special=i;

	return(TRUE);
}
