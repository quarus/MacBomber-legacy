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

#ifndef CInputManager_H
#define CInputManager_H
#include "SDL/SDL.h"

class CApplication;
class CController;

class CInputManager
{
private:
	
	int m_iJoystickCount;
	Uint8 *m_pKeystate;
	
	CApplication * m_pApp;
	CController * m_pController[8];	
 
public:
	CInputManager(CApplication * pApp);
	~CInputManager();

	CController * getController(int ctrlID);

	//returns count of connected joysticks 
	int getJoystickCount(){return m_iJoystickCount;};

	//returns true if there are any joysticks present;
	bool joysticksPresent();
	//returns true if joystick with SDL ID joystickID is present
	bool isJoystickPresent(int joystickID);
	
	//queries joystick events
	void update();
	
};

#endif
