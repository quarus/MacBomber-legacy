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

#include "CItemManager.h"

#include "CItem_Condom.h"
#include "CItem_Cocaine.h"
#include "CItem_Joint.h"
#include "CItem_Viagra.h"

CItemManager::CItemManager(CPlayer * pPlayer)
{
	m_pPlayer = pPlayer;
	m_pBadieItem[0] = NULL; //JOINT
	m_pBadieItem[1] = NULL; //COCAINE
	m_pBadieItem[2] = NULL; //VIAGRA
	m_pBadieItem[3] = NULL; //CONDOM

}

void CItemManager::clearBadies()
{
	for ( int i = 0; i < 4; i++)
	{
		if (m_pBadieItem[i] != NULL)
		{
			delete m_pBadieItem[i];
			m_pBadieItem[i] = NULL;
		}
	}
}


CItemManager::~CItemManager()
{
	for ( int i = 0; i < 4; i++)
	{
		if (m_pBadieItem[i] != NULL) 
			delete m_pBadieItem[i];
	}
}

void CItemManager::addItem(CItem * pItem)
{
	switch(pItem->getType())
	{
		case JOINT:
			if ( m_pBadieItem[0] != NULL)
				delete m_pBadieItem[0];
			m_pBadieItem[0] = pItem;
			break;
		case COCAINE:
			if ( m_pBadieItem[1] != NULL)
				delete m_pBadieItem[1];
			m_pBadieItem[1] = pItem;
			break;
		case VIAGRA:
			if ( m_pBadieItem[2] != NULL)
				delete m_pBadieItem[2];
			m_pBadieItem[2] = pItem;
			break;
		case CONDOM:
			if ( m_pBadieItem[3] != NULL)
				delete m_pBadieItem[3];
			m_pBadieItem[3] = pItem;
			break;
			
		default:
			// it must be  a goodie ! directly apply it !
			pItem->affectPlayer(m_pPlayer);
			// and delete all badies
			clearBadies();

			break;
	}
}
bool CItemManager::hasItem(int m_iType)
{
	switch (m_iType)
	{
		case JOINT:
			if (m_pBadieItem[0] == NULL)
				return false;
			else
				return true;
			break;

		case COCAINE:
			if (m_pBadieItem[1] == NULL)
				return false;
			else
				return true;
			break;
			
		case VIAGRA:
			if (m_pBadieItem[2] == NULL)
				return false;
			else
				return true;
			break;
			
		case CONDOM:
			if (m_pBadieItem[3] == NULL)
				return false;
			else
				return true;
			break;
	}
	
	//should never get here
	return false;
}

void CItemManager::infect(CItemManager * pItemManager)
{

	if (pItemManager->hasItem(JOINT))
	{
		if (m_pBadieItem[0] == NULL)
			m_pBadieItem[0] = new CItem_Joint(0,0);
	}
	if (pItemManager->hasItem(COCAINE))
	{
		if (m_pBadieItem[1] == NULL)
			m_pBadieItem[1] = new CItem_Cocaine(0,0);
	}
	if (pItemManager->hasItem(VIAGRA))
	{
		if (m_pBadieItem[2] == NULL)
			m_pBadieItem[2] = new CItem_Viagra(0,0);
	}
	
	if (pItemManager->hasItem(CONDOM))
	{
		if (m_pBadieItem[3] == NULL)
			m_pBadieItem[3] = new CItem_Condom(0,0);
	}
	
	
}


void CItemManager::update()
{

	for ( int i = 0; i < 4; i++)
	{
		if (m_pBadieItem[i] != NULL)
		{
			// apply Badies & check if we should delete it
			if (m_pBadieItem[i]->affectPlayer(m_pPlayer))
			{
				delete m_pBadieItem[i];
				m_pBadieItem[i] = NULL;
			}			
		}
	}//for
}
