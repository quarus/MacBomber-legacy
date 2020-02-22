
/*MacBomber - Copyright (C) 2006  Altay Cebe

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef CController_Joystick_H
#define CController_Joystick_H

#include "SDL/SDL.h"
#include "CController.h"

class CController_Joystick:public CController
{
private:
	bool m_bBomb;
	int  m_iDeadZone;
	SDL_Joystick * m_pJoystick;

public:
	CController_Joystick(int ID, SDL_Joystick * pJoystick);
	~CController_Joystick();
	void update(SDL_Event & event);

	

	
};

#endif

