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
#ifndef CController_H
#define CController_H

#include "SDL/SDL.h"

/*
 Die Controller Klassen werden zu Beginn des Programms initialisiert. Anschließend werden sie bei Konstruktion
 eines CGame Objekts den Spielern zu gewiesen. Die Kontroller erhalten ihre Werte aus dem SDL Event Main Loop.
 Dies ist wahrscheinlich keine optimale Lösung. Bei Nichtbedarf können die Controller mittels deactivate() 
 deaktiviert werden.
 */
class CController
{
protected:
	int m_iID;

	bool m_bKeyPressed[7];
	bool m_bKeyHold[7];
	
public:
	CController();
	virtual ~CController();
	void reset();

	virtual void update(SDL_Event & event) = 0;
	
	
	//Pressed: true if an Key has been pressed (single event).
	bool isUpPressed();
	bool isDownPressed();
	bool isLeftPressed();
	bool isRightPressed();
	bool isBombPressed();
	bool isSpacePressed();
	bool isBackPressed();
	
	//Hold: true if a key is beeing pressed down
	bool isUpHold();
	bool isDownHold();
	bool isLeftHold();
	bool isRightHold();
	

		
};
#endif
