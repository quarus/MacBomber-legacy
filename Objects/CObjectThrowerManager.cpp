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

#include "CObjectThrowerManager.h"
#include "../Map/CMap.h"
#include "CObject_Moving.h"

CObjectThrowerManager::CObjectThrowerManager(CMap * pMap)
{
	m_pMap = pMap;
}

CObjectThrowerManager::~CObjectThrowerManager()
{
	list<SThrowerContainer>::iterator it;
	for ( it =m_listThrower.begin(); it != m_listThrower.end(); it++ )
	{
		delete (*it).pObject;
		m_listThrower.erase(it++);
	}
	m_listThrower.clear();	
}

void CObjectThrowerManager::addToList(CVector3 vStart,CVector3 vEnd, CObject_Moving * pObject/*, CParticleSystem * pParticleSystem*/)
{
	SThrowerContainer pContainer;
	pObject->setVelocity(7);
	pContainer.pThrower = new CObjectThrower(vStart, vEnd,pObject);
	pContainer.pObject  = pObject; 

	m_listThrower.push_back(pContainer);
}

void CObjectThrowerManager::update()
{
	list<SThrowerContainer>::iterator it;
	for ( it =m_listThrower.begin(); it != m_listThrower.end(); it++ )
	{
				
		if ((*it).pThrower->isDone())
		{
			handleDestinationReached((*it).pObject);
			delete (*it).pThrower;
			m_listThrower.erase(it++);
		}
		else
			(*it).pThrower->update();

	}
}


void CObjectThrowerManager::draw()
{
	list<SThrowerContainer>::iterator it;
	for ( it =m_listThrower.begin(); it != m_listThrower.end(); it++ )
	{
		(*it).pObject->draw();			
	}
}
