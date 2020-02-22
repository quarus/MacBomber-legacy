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
#include <GLUT/glut.h>
#include <OpenGL/glext.h>

#include "CField_Hole.h"
#include "CMap.h"
#include "../Engine/CMeshManager.h"
#include "../Engine/CTimer.h"
#include "../Engine/ParticleSystem/CParticleManager.h"

#include "../MeshObjects/CSquareMesh.h"
#include "../CExplosion.h"
#include "CApplication.h"
#include "../Defines.h"

CField_Hole::CField_Hole( int xGrid, int yGrid, CMap *pMap):CField( xGrid, yGrid, pMap)
{

	m_iType = HOLE;
	m_bFree = true;

}

CField_Hole::~CField_Hole()
{
	list<SBombContainer>::iterator it;
	for (it = m_lBombList.begin(); it != m_lBombList.end();it++)
	{
		delete (*it).pBomb;
	}
	m_lBombList.clear();
}


bool CField_Hole::startFall(CBomb *pBomb)
{
	//Nur flippen wenn d	ie Richtung nicht stimmt
	//if (m_pBomb->getDirection() != m_iDirection)
	
	//Schaue nach, ob die Bombe die Feld Mittellinie überschritten hat
	switch(pBomb->getDirection())
	{
		case UP:
			if ( pBomb->getPosition().z < m_vPos.z)
				return true;
			else
				return false;
			break;
		case DOWN:
			if ( pBomb->getPosition().z > m_vPos.z)
				return true;
			else
				return false;
			break;				
		case LEFT:
			if ( pBomb->getPosition().x < m_vPos.x)
				return true;
			else
				return false;
			break;
		case RIGHT:
			if ( pBomb->getPosition().x > m_vPos.x)
				return true;
			else
				return false;
			break;
		case NONE:
			return true;
			break;

		default:
			return false;
			break;
	}
	
}

bool CField_Hole::stopFall(CBomb * pBomb)
{
	
	if ( (pBomb->getPosition().y) > -4 )
		return false;
	else
		return true;
}

bool CField_Hole::hasBomb()
{
	return !(m_lBombList.empty());
}

bool CField_Hole::placeBomb ( CBomb * bomb )
{
	SBombContainer newContainer;
	newContainer.pBomb = bomb;
	newContainer.bDoesFall = false;	// Eine neu platzierte Bombe fällt nicht
	newContainer.bDoesFly = false;	// Eine neu platzierte Bombe fällt nicht
	newContainer.bDraw = true;
	// Packe die Bombe in die Liste der fallenden Bomben
	m_lBombList.push_back(newContainer);
	return true;
}

void CField_Hole::moveBomb()
{
	list<SBombContainer>::iterator it;
	for (it = m_lBombList.begin(); it != m_lBombList.end();it++)
	{
	
			(*it).pBomb->update();
			(*it).pBomb->move();
			
			// Falls die Bombe noch nicht fällt, überprüfe, ob sie jetzt fallen solle
			if ( (*it).bDoesFall == false )
			{
				if (startFall( (*it).pBomb))
				{
					(*it).bDoesFall = true;
					(*it).pBomb->setDisplacement(CVector3(0,-1,0));

				}
	
			}
			else
			{
				if (stopFall( (*it).pBomb)) 
				{
					(*it).bDoesFall = false;
					(*it).bDoesFly = true;
	
					
					(*it).pBomb->setPosition(m_vPos);
					m_pMap->addBombToThrower(m_vPos, (*it).pBomb);
					m_lBombList.erase(it++);
					
					m_pMap->m_ParticleManager.addSmokeParticle(m_vPos,15);

/*					m_pSmoke->activate();
					m_tParticleDeactivationTimer.setAlarm(800);*/
				}
				
				//draw bombs till they are completley under the hole 
				if( ((*it).bDraw == true) && (((*it).pBomb)->getPosition().y < -1) ) 
					(*it).bDraw = false;
				
			}
	}
		
}
	



void CField_Hole::update()
{
	switch (m_iState)
	{
		case FALLING:
			m_vPos.y -= (CApplication::m_fReciprocalFPS * 4);
			m_fAngle += (CApplication::m_fReciprocalFPS * 90);		
			break;
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
			
	};
	
	moveBomb();
	
}


void CField_Hole::draw()
{
	
	glPushMatrix();
		glTranslatef( m_vPos.x, m_vPos.y, m_vPos.z);
		CApplication::m_pMeshManager->m_pSquareMesh->drawVBO();
		
	glPopMatrix();

	

	
//	pBombThrower->draw();
}

void CField_Hole::drawBombs()
{
	list<SBombContainer>::iterator it;
	for (it = m_lBombList.begin(); it != m_lBombList.end();it++)
	{
		if ((*it).bDraw == true)
		{
			(*it).pBomb->draw();
		}
	}
}
