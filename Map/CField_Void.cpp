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

#include "CField_Void.h"
#include "CMap.h"
#include "../CExplosion.h"
#include "../CApplication.h"
#include "../Engine/ParticleSystem/CParticleManager.h"

#include "../Objects/CItem.h"

CField_Void::CField_Void ( int xGrid, int yGrid, CMap * pMap ):CField( xGrid, yGrid, pMap)
{
	m_iType = VOID;	
	m_bFree = true;
}

CField_Void::~CField_Void()
{
	list<SBombContainer>::iterator it;
	for (it = m_lBombList.begin(); it != m_lBombList.end();it++)
	{
		delete (*it).pObject;
	}
	m_lBombList.clear();
}

bool CField_Void::startFall(CObject_Moving *pObject)
{
	//Schaue nach, ob die Bombe die Feld Mittellinie überschritten hat
	switch(pObject->getDirection())
	{
		case UP:
			if ( pObject->getPosition().z < m_vPos.z)
				return true;
			else
				return false;
			break;
		case DOWN:
			if ( pObject->getPosition().z > m_vPos.z)
				return true;
			else
				return false;
			break;				
		case LEFT:
			if ( pObject->getPosition().x < m_vPos.x)
				return true;
			else
				return false;
			break;
		case RIGHT:
			if ( pObject->getPosition().x > m_vPos.x)
				return true;
			else
				return false;
			break;
		default: // NONE
				return true;
			break;
	}

}

bool CField_Void::stopFall(CObject * pObject)
{
	
	if ( (pObject->getPosition().y) > -10 )
		return false;
	else
		return true;
}

bool CField_Void::hasBomb()
{
	return !(m_lBombList.empty());
}

bool CField_Void::placeBomb ( CBomb * bomb )
{
	SBombContainer newContainer;
	newContainer.pObject = bomb;
	newContainer.bDoesFall = false;	// Eine neu platzierte Bombe fällt nicht

	// Packe die Bombe in die Liste der fallenden Bomben
	m_lBombList.push_back(newContainer);
	return true;
}

void CField_Void::placeItem (CItem * pItem)
{
	SBombContainer newContainer;
	newContainer.pObject = pItem;
	newContainer.bDoesFall = false;	// Eine neu platzierte Bombe fällt nicht
	
	// Packe die Bombe in die Liste der fallenden Bomben
	m_lBombList.push_back(newContainer);

}


void CField_Void::destroy()
{
	m_bCrate = false;
	m_EndOfExplosion.setAlarm(500);
	m_iState = BURNING;
	m_pMap->m_ParticleManager.addExplosionParticle(m_vPos);

}

void CField_Void::moveBomb()
{
	list<SBombContainer>::iterator it;
	for (it = m_lBombList.begin(); it != m_lBombList.end();it++)
	{
		(*it).pObject->move();

		// Falls die Bombe noch nicht fällt, überprüfe, ob sie jetzt fallen solle
		if ( (*it).bDoesFall == false )
		{
			if (startFall( (*it).pObject))
			{
				(*it).bDoesFall = true;
				(*it).pObject->setDisplacement(CVector3(0,-1,0));
			
				if ( (*it).pObject->getType() == BOMB_OBJECT )
				{	
					CBomb * pBomb = (CBomb*)(*it).pObject;
					CMap::m_iBombsOnField[pBomb->getOwnerID()]--;
				}

			}
		}
		else
		{
			
			if (stopFall( (*it).pObject))
			{
				
				delete (*it).pObject;
				m_lBombList.erase(it++);
			}

		}

	}
}

void CField_Void::update()
{
	switch (m_iState)
	{
		case BURNING:
			m_pExplosion->update();
			if (m_EndOfExplosion.isTimeUp())
			{
				m_iState = NORMAL;
				m_pExplosion->reset();
			}
			break;
		default:
			break;
	}
	
	moveBomb();
}


void CField_Void::draw()
{
	drawExplosion();
}

void CField_Void::drawBombs()
{
	list<SBombContainer>::iterator it;
	for (it = m_lBombList.begin(); it != m_lBombList.end();it++)
	{
	
		(*it).pObject->draw();
	
	}	
}
