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

#include "CItemThrower.h"
#include "CItem.h"
#include "../Map/CMap.h"

CItemThrower::CItemThrower(CMap * pMap):CObjectThrowerManager(pMap)
{
}

CVector3 CItemThrower::getTarget(int ignoreFieldX, int ignoreFieldZ )
{
	int x,z;
	bool bDone = false;
	// true if Void fields should be considered
	bool bConsiderVoid = false;
	(m_pMap->getFieldCount() < 10)?bConsiderVoid=true:bConsiderVoid=false;
	 
	while(!bDone)
	{
		
		x = rand()%m_pMap->getWidth();
		z = rand()%m_pMap->getHeight();
		
		//Also take void fields in consideration if there are too few plain fields !
		if(bConsiderVoid)
		{
			if	(	(/*(m_pMap->getType(x,z) == FIELD) || */(m_pMap->getType(x,z) == VOID) )&&
					(!m_pMap->hasCrate(x,z)) &&
					(x != ignoreFieldX) && (z != ignoreFieldZ) )
					bDone = true;
		}
		else
		{
			// Only throw items on an plain field, if it has no crates
			if	((m_pMap->getType(x,z) == FIELD)&&
				(!m_pMap->hasCrate(x,z)) &&
				(x != ignoreFieldX) && (z != ignoreFieldZ) )
					bDone = true;
		}
			
		
	}
	
	return CVector3(((float)x)+0.5f,0,((float)z)+0.5f);	
}

void CItemThrower::add( CVector3 vStart, CItem * pItem )
{
	addToList(vStart,getTarget((int)vStart.x,(int)vStart.z), pItem);
	pItem->setWobble(false);
}


void CItemThrower::handleDestinationReached(CObject_Moving * pObject)
{
	CItem *pItem = (CItem*)pObject;
	m_pMap->placeItem(pItem);

}

