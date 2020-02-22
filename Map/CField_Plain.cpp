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

#include "CField_Plain.h"

//#include "CField.h"
#include "../Defines.h"
#include "CMap.h"
#include "../Objects/CCrate.h"
#include "../Objects/CItem_PowerUp.h"
#include "../Objects/CItem_BombUp.h"
#include "../Objects/CItem_SpeedUp.h"
#include "../Objects/CItem_Cocaine.h"
#include "../Objects/CItem_Joint.h"
#include "../CExplosion.h"
#include "../Engine/CMeshManager.h"
#include "../CApplication.h"
#include "../MeshObjects/CSquareMesh.h"


CField_Plain::CField_Plain( int xGridPos, int zGridPos, bool bCrate, CMap * pMap ):CField( xGridPos, zGridPos, pMap)
{
    m_iType = FIELD;

	if (bCrate)
		placeCrate();
	
	
	//throw the dice to see if this field has a second texture	
	if (rand()%6 == 0)
	{
	
		m_bDecal = true;			
		m_iDecalOrientation = rand()%4;

		// now decide which second texture
		switch (rand()%3)
		{
			case 0:
				m_iDecalTexture = FIELD_MUD0_TEXTURE;
				break;
			case 1:
				m_iDecalTexture = FIELD_MUD1_TEXTURE;
				break;
			case 2:
				//only assign if this square has a crate
				if (bCrate)
					m_iDecalTexture = FIELD_CRATEDEBRIS_TEXTURE;
				else
					m_bDecal = false;
				break;
		}
	}
	else
		m_bDecal = false;			

}

CField_Plain::~CField_Plain()
{

}
void CField_Plain::placeCrate()
{
	if (m_bCrate == false)
	{
		m_bCrate = true;
		m_bFree = false;
		m_pCrate = new CCrate(m_iXGrid, m_iZGrid);
		
	}
}


bool CField_Plain::placeBomb ( CBomb * bomb )
{
	//There can only be one bomb per square
    if ( m_bBomb == false )
    {
		m_bBomb = true;
		m_pBomb = bomb;
		
		// Das Feld ist nicht begehbar, falls eine Bombe gelegt wurde
		m_bFree = false;
		return true;
    }
    else
	{
		delete bomb;
		return false;    
	}
}

void CField_Plain::moveBomb()
{
	if (m_bBomb)
	{
		float fSize = m_pBomb->getSize()/2;
		CVector3 vPos_next = m_pBomb->getPosition() + ( m_pBomb->getDisplacement() * fSize);
		
		// Ist vPos_next noch im selben Feld ?
		if ( (int(vPos_next.x) == m_iXGrid ) &&
			 (int(vPos_next.z) == m_iZGrid ) )
		{
					
				// Die Bome kann ohne Bedenken bewegt werden, falls sie sich denn bewegen soll
				if ( m_pBomb->doesMove() )
				{
					m_pBomb->move();
				}

		}
		else
		{
			//Ist das neu erreicht Feld frei & kein Player ?
			if ( ((m_pMap->isFree(m_iXGrid + (int)m_pBomb->getDisplacement().x,m_iZGrid + (int)m_pBomb->getDisplacement().z)) &&
				 (!m_pMap->hasPlayer(m_iXGrid + (int)m_pBomb->getDisplacement().x,m_iZGrid + (int)m_pBomb->getDisplacement().z)))// && 
				 //(!m_pMap->hasItem(m_iXGrid + m_pBomb->getDisplacement().x,m_iZGrid + m_pBomb->getDisplacement().z)) 
				)
				//hier check auf ITEM?
			{
				// bewege die Bombe
				m_pBomb->move();
				
				// Ist der Mittelpunkt der Bombe in einem neuem Feld gelandet ?
				// Falls ja, wird die Bombe an dieses Feld übergeben
				if ( (m_pBomb->getXBlock() != m_iXGrid ) ||
					 (m_pBomb->getZBlock() != m_iZGrid ) ) 
				{
					// Die Bombe wird an das nächste Feld übergeben
					m_pMap->placeBomb(m_pBomb);
					dispatchBomb();
				}

			}
			else
			{
				m_pBomb->stopMovement();
			}
		}
		
	}
}

void CField_Plain::kickBomb(int dir)
{
	if (m_bBomb)
	{
		m_pBomb->setDirection(dir);
	}
}

void CField_Plain::update()
{			
	updateItem();
	checkBomb();

	switch (m_iState)
	{
		case(FALLING):
			
			m_vPos.y -= (CApplication::m_fReciprocalFPS * 4);
			m_fAngle += (CApplication::m_fReciprocalFPS * 90);		
			if (m_bItem)
			{
				CVector3 vVector = m_pItem->getPosition();
				vVector.y -= (CApplication::m_fReciprocalFPS * 4);
				m_pItem->setPosition(vVector);
			}
				
			if (m_bBomb)
			{
				CVector3 vVector = m_pBomb->getPosition();
				vVector.y -= (CApplication::m_fReciprocalFPS * 4);
				m_pBomb->setPosition(vVector);
			}
				
			break;

		case BURNING:
			m_pExplosion->update();			
			if (m_EndOfExplosion.isTimeUp())
			{
				m_iState = NORMAL;
				m_pExplosion->reset();			
			}
			break;
		case NORMAL:
			moveBomb();
			break;
		default:
			break;
	}

}

void CField_Plain::draw()
{
	
	
	glPushMatrix();			
		glTranslatef( m_vPos.x, m_vPos.y, m_vPos.z);

		//only rotatie if there is a crate on this field
		if ( (m_iState == FALLING) && (m_bCrate) )
			glRotatef(m_fAngle,m_vRotationAxis.x,m_vRotationAxis.y,m_vRotationAxis.z);

		if( m_bCrate )
			m_pCrate->draw();
		else
		{

			if (m_bDecal)
			{
				CApplication::m_pMeshManager->m_pSquareMesh->configureTexture1(m_iDecalTexture);
				CApplication::m_pMeshManager->m_pSquareMesh->configureTexCoord1(m_iDecalOrientation);
			}

			CApplication::m_pMeshManager->m_pSquareMesh->drawVBO();

			if (m_bDecal)
			{
				glActiveTextureARB(GL_TEXTURE1_ARB);
				glDisable(GL_TEXTURE_2D);
			}
		}
	glPopMatrix();
}
