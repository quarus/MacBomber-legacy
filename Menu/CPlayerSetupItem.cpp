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


#include "Defines.h"
#include "CPlayerSetupItem.h"
#include "CToggleItem.h"
#include "../CApplication.h"
#include "../Engine/CMeshManager.h"
#include "../Engine/CTextureManager.h"
#include "../Engine/CTextDrawer.h"
#include "../Engine/ortho.h"

#include "../MeshObjects/CPlayerMesh.h"

CPlayerSetupItem::CPlayerSetupItem(int value):CToggleItem(" ")
{
	addOption("Red Mac",   PLAYER1_TEXTURE);
	addOption("Brown Mac", PLAYER2_TEXTURE);
	addOption("Blue Mac",  PLAYER3_TEXTURE);
	addOption("White Mac", PLAYER4_TEXTURE);
	
	setValue(value);
}

void CPlayerSetupItem::draw()
{

	glPushMatrix();
		glTranslatef(relToAbs(m_vPosition.x,0),relToAbs(m_vPosition.y,1), -30);
		glPushMatrix();
			glScalef(80,80,80);
			CApplication::m_pMeshManager->m_pPlayerMesh->configureMaterial();
			CApplication::m_pMeshManager->m_pPlayerMesh->configureTexCoord0();
			CApplication::m_pMeshManager->m_pPlayerMesh->configureTexCoord1();			
			CApplication::m_pMeshManager->m_pPlayerMesh->configureTexture0((*m_itIterator).value);
			CApplication::m_pMeshManager->m_pPlayerMesh->configureTexture1(PLAYER_HAPPY_TEXTURE);
			CApplication::m_pMeshManager->m_pPlayerMesh->enableBuffers();
			CApplication::m_pMeshManager->m_pPlayerMesh->drawVBO();
			CApplication::m_pMeshManager->m_pPlayerMesh->resetTextureEngines();
			CApplication::m_pMeshManager->m_pPlayerMesh->disableBuffers();

		glPopMatrix();

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		CApplication::m_pTextDrawer->drawText(0.03,0,(*m_itIterator).name);

	glPopMatrix();


	if (m_bActive) drawQuad();

	
}

