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

#ifndef CMapDestroyer_H
#define CMapDestroyer_H

#include "../Engine/CVector3.h"
class CMap;
class CObjectThrower;
class CWiley;

class CMapDestroyer
{
private:
	
	// The Object which jumps around
	CWiley * m_pWiley;

	CMap * m_pMap;
	// throws the destroyer along a ballistic curve
	CObjectThrower * m_pDestroyerThrower;

	//the amount of field, which need to be destroyed
	int m_iFieldsLeft;
	
	//true if there a no more fields to destroy
	bool m_bMapCleared;

	//randomly chooses a new target
	CVector3 getTarget();
	
	//used to determine if a particle should be added to wileys trail
	int m_iTicks;
public:
	CMapDestroyer(CMap * pMap);
	~CMapDestroyer();	
	//returns true when map has been cleared 
	bool isDone(){return m_bMapCleared;};
	void update();
	void draw();
	
};
#endif
