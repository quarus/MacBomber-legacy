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

#include "CField_Block.h"
#include "../Engine/CTriangleMesh.h"
#include "../Engine/CMeshManager.h"
#include "../MeshObjects/CBlockMesh.h"
#include "CApplication.h"
#include "../Defines.h"



CField_Block::CField_Block ( int xGrid, int yGrid,CMap * pMap ):CField( xGrid, yGrid, pMap)
{
	m_iType = BLOCK;
	m_bFree = false;
	m_vPos.y = 0.0f;
	
	//randomly choose between 0,90,180 and 270
	m_iOrientation = (rand()%4) *90;
}


bool CField_Block::placeBomb ( CBomb * bomb )
{
	delete bomb;
	return false;
}


void CField_Block::draw()
{
	
	
	glPushMatrix();
		glTranslatef( m_vPos.x, m_vPos.y, m_vPos.z);
		
		if (m_iState == FALLING)
		{
			glRotatef(m_fAngle,0,1,0);
			glRotatef(5,1,0,0);			
		}

		glRotatef(m_iOrientation,0,1,0);		
		CApplication::m_pMeshManager->m_pBlockMesh->drawVBO();
	glPopMatrix();	
	
}

void CField_Block::update()
{
	if (m_iState == FALLING)
	{
		m_vPos.y -= (CApplication::m_fReciprocalFPS * 4);
		m_fAngle += (CApplication::m_fReciprocalFPS * 90);		
	}
	
}

