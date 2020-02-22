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


#ifndef CItemThrower_H
#define CItemThrower_H

#include "CObjectThrowerManager.h"

class CItem;

class CItemThrower :public CObjectThrowerManager
{
	
private:
	// choose a random target
	CVector3 getTarget(int ignoreFieldX, int ignoreFieldZ );
	
public:
	CItemThrower(CMap *pMap);
	
	void add(CVector3 vStart, CItem * pBomb);
	void handleDestinationReached(CObject_Moving * pObject); 

};

#endif
