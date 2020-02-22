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

#ifndef CField_Void_H
#define CField_Void_H

#include "CField.h"
#include <list>

//FIX ME: Item/Bomb handling is messy. Clean up (e.g convert Items to moving_objects)

class CField_Void : public CField
{
protected:
	
	// FIX ME: this is not a clean solution....
	struct SBombContainer
	{
		CObject_Moving * pObject;
		bool bDoesFall;
	};
	
	
	//Liste, die alle fallenden Bomben enthält
	list<SBombContainer> m_lBombList;
	// Returniert true wenn die Bombe fallen darf (Mittellinie überschrittenn) 
	bool startFall(CObject_Moving *pObject);
	bool stopFall(CObject *pObject);
	
public:
	CField_Void (int xGrid, int yGrid, CMap * pMap );
	~CField_Void();
	
	bool hasBomb();
	bool placeBomb (CBomb * bomb);
	void placeItem (CItem * pItem);
	void destroy();

	void moveBomb();
	void update();
	void draw();
	void drawBombs();
};

#endif 
