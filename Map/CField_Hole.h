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

#ifndef CField_Hole_H
#define CField_Hole_H

#include "../Map/CField.h"
//#include "../Objects/CBombThrower.h"
//#include "../Objects/CObjectThrower.h" 
#include <list>

//class CParticleSystem_Hole;
class CTimer;

class CField_Hole : public CField
{
protected:
	
	struct SBombContainer
	{
		CBomb * pBomb;
		bool bDoesFall;	// Bewegt sich die Bombe noch Richtung Feld Mitte ?
		bool bDoesFly;	// wurde sie bereits katapultiert ?
		CTimer tDelayTimer; // Erst katapultieren wenn der Delay vorbei ist
		bool bDraw;
	};

	// contains all bombs, which are moving _into_ the hole
	list<SBombContainer> m_lBombList;
	
	bool startFall(CBomb * pBomb);
	bool stopFall(CBomb * pBomb);
	
	CTimer m_tParticleDeactivationTimer;
	
public:
	CField_Hole ( int xGrid, int yGrid, CMap * pMap );
	~CField_Hole();

	bool hasBomb();

	bool placeBomb ( CBomb * bomb );

	void moveBomb();
	void update();
	void draw();
	void drawBombs();

};

#endif 
