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

#include "CBombThrower.h"
#include "../Map/CMap.h"

CBombThrower::CBombThrower(CMap * pMap):CObjectThrowerManager(pMap)
{
}

CVector3 CBombThrower::getTarget(int ignoreFieldX, int ignoreFieldZ)
{
	
	int x,z;
	bool done = false;
	bool bConsiderVoid = false;
	(m_pMap->getFieldCount() < 10)?bConsiderVoid=true:bConsiderVoid=false;

	while(!done)
	{
		x = rand()%m_pMap->getWidth();
		z = rand()%m_pMap->getHeight();
				
		//Also take void fields in consideration if there are too few plain fields !
		if(bConsiderVoid)
		{
			if( ((m_pMap->getType(x,z) == FIELD) || 
				 (m_pMap->getType(x,z) == HOLE) ||
				 (m_pMap->getType(x,z) == VOID)) &&
			 (x != ignoreFieldX) && (z != ignoreFieldZ) ) 
				done = true;

		}
		else
		{
			if ( ((m_pMap->getType(x,z) == FIELD)||(m_pMap->getType(x,z) == HOLE)) &&
			 (x != ignoreFieldX) && (z != ignoreFieldZ) )
				done = true;

		}

		
	}
	float _x = (float)x+0.5f;
	float _z = (float)z+0.5f;
	
	return CVector3(_x,0.0f,_z);
	
}

void CBombThrower::add( CVector3 vStart, CBomb * pBomb )
{
	CVector3 vTarget = getTarget((int)vStart.x, (int)vStart.z);
	// add Bomb...
	addToList(vStart,vTarget, pBomb);
	// ..and disable bomb wobbling
	pBomb->setWobble(false);
	
}


void CBombThrower::handleDestinationReached(CObject_Moving * pObject)
{
	CBomb * pBomb = (CBomb*)pObject;
	// Auf dem erreichten Feld steht eine Bombe. Dieses muss zum explodieren gebracht werden
	if ( m_pMap->hasBomb(pBomb->getXBlock(),pBomb->getZBlock()) )
	{
		m_pMap->destroyBlock( pBomb->getXBlock(),pBomb->getZBlock() );
		
		CMap::m_iBombsOnField[pBomb->getOwnerID()]--;
		delete pBomb;
		
	}
	else // Rufe die entsprechende placeBomb Methode des Felds auf ( auch bei Blöcken)
	{
		pBomb->setDisplacement(CVector3(0,0,0));
		m_pMap->placeBomb(pBomb);
		
		//only call destroyBlock Method if reached Field is *not* a hole or an void field
		//(destroyBlock would cause an explosion to be drawn)
		if ( ( m_pMap->getType(pBomb->getXBlock(),pBomb->getZBlock()) != HOLE) &&
			 ( m_pMap->getType(pBomb->getXBlock(),pBomb->getZBlock()) != VOID) )
			m_pMap->destroyBlock( pBomb->getXBlock(),pBomb->getZBlock() );
		
		
	}
	
}




