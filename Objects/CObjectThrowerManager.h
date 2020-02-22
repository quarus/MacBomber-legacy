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

#ifndef CObjectThrowerManager_H
#define CObjectThrowerManager_H

#include <list>
#include "CObjectThrower.h"
#include "CVector3.h"

class CMap;
class CObject_Moving;

class CObjectThrowerManager
{
protected:
	struct SThrowerContainer
	{
		CObjectThrower * pThrower;
		CObject_Moving * pObject;					// pObject reicht für setPosition()
	};

	list <SThrowerContainer> m_listThrower;
	CMap * m_pMap;
	
	virtual CVector3 getTarget(int ignoreFieldX, int ignoreFieldZ) = 0;
	virtual void handleDestinationReached(CObject_Moving * pObject) = 0;
	void addToList(CVector3 vStart,CVector3 vStart,CObject_Moving * pObject);
	
public:
	CObjectThrowerManager(CMap * pMap);
	virtual ~CObjectThrowerManager();
	void update();
	void draw();
};

#endif