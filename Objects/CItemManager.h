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


#ifndef CItemManager_H
#define CItemManager_H

#include "CPlayer.h"
#include "CItem.h"
#include <list>

/* Warum einen eigenen Item Manager ?
   Damit bei den Spielern mehere Badies gleichzeitig wirken können ! -> meh Spass !! */
class CItemManager
{
private:

	CPlayer * m_pPlayer;
	
	// create a slot for every Possible Badie Item
	CItem * m_pBadieItem[4];

	//deletes all Badies in m_pBadieItem
	void clearBadies();
public:		
	CItemManager(CPlayer * pPlayer);
	~CItemManager();
	void addItem(CItem * pItem);
	// returns true if player has specified (Badie) item
	bool hasItem(int m_iType);
	
	// infects this itemmanager with the badie items of another itemmanger
	void infect(CItemManager * pItemManager);
	
	void update();
	
};
#endif
