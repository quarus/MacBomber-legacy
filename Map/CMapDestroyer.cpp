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


#include "CMapDestroyer.h"
#include "../Defines.h"
#include "../CApplication.h"
#include "../Engine/CVector3.h"
#include "../Engine/CMeshManager.h"
#include "../Engine/CTextureManager.h"
#include "../Engine/CSoundManager.h"
#include "../Engine/ParticleSystem/CParticleManager.h"
#include "../Map/CMap.h"
#include "../Objects/CObjectThrower.h"
#include "../Objects/CWiley.h"

#include <GLUT/glut.h>

CMapDestroyer::CMapDestroyer(CMap * pMap)
{
	m_bMapCleared = false;
	m_pMap = pMap;
	m_iFieldsLeft = m_pMap->getFieldCount();
	
	m_pWiley = new CWiley();
	m_pDestroyerThrower = new CObjectThrower(CVector3(-10,0,0),getTarget(),m_pWiley);

	m_iTicks = 0;
}

CMapDestroyer::~CMapDestroyer()
{
	delete m_pDestroyerThrower;
	delete m_pWiley;
}



//randomly chooses a new target
CVector3 CMapDestroyer::getTarget()
{
	// FIX ME: don't choose field randomly if count is below 5
	
	float x,z,y = 0;
	bool done = false;
	while(!done)
	{
		x = rand()%m_pMap->getWidth();
		z = rand()%m_pMap->getHeight();		

		// Don't choose a void field
		if (m_pMap->getType((int)x,(int)z) != VOID)
			done = true;
		
		x += 0.5;
		z += 0.5;
				
		//if a block has been chosen or this field has a crate/item
		//-> set the y coordinate of the target a bit higher (otherwise it looks wrong)
		if ( (m_pMap->getType((int)x,(int)z) == BLOCK) ||
			 (m_pMap->hasCrate((int)x,(int)z)) ||
			 (m_pMap->hasItem((int)x,(int)z))
			 )  
			y = 1;
		
		
	}
	
	return CVector3(x,y,z);
}


void CMapDestroyer::update()
{
	
	
	if (m_bMapCleared)
	{
		if (!m_pDestroyerThrower->isDone())
			m_pDestroyerThrower->update();
	}
	else
	{
		m_pDestroyerThrower->update();

		if ( (m_iTicks++)%5 == 0)
			m_pMap->m_ParticleManager.addWileyParticle(m_pWiley->getPosition(),3);
		
		//Did the the destroyer reach his target?
		if (m_pDestroyerThrower->isDone())
		{
			//get destroyers position & a new target
			CVector3 vDestination;
			
			//one field less to go
			m_iFieldsLeft--;

			// has last field been destroyed ?
			if (m_iFieldsLeft <= 0)
			{
				m_bMapCleared = true;
				// let mapdestroyer hop out of the map
				vDestination = CVector3(-10,0,0);
			}
			else
			{
				vDestination = getTarget();
				//play a crunching sound
				CApplication::m_pSoundManager->playSoundFX(CRUNCH_SOUND);
			}
			
			//tell the map do drop field x,z
			m_pMap->doDrop(m_pWiley->getXBlock(),m_pWiley->getZBlock());

			//create a new Thrower and choose a new target
			delete m_pDestroyerThrower;
			m_pDestroyerThrower = new CObjectThrower(m_pWiley->getPosition(), vDestination,m_pWiley);
			
		}
	}	

	
}

void CMapDestroyer::draw()
{
	glPushMatrix();
		m_pWiley->draw();
	glPopMatrix();
}
