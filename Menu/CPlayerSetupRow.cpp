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

#include "CPlayerSetupRow.h"

#include "../CApplication.h"
#include "../Engine/CTextureManager.h"
#include "../Defines.h"
#include "../engine/ortho.h"

#include "CPlayerSetupItem.h"
#include "CControllerSetupItem.h"

#include <GLUT/glut.h>

CPlayerSetupRow::CPlayerSetupRow(int skin, int keyset, bool bEnabled):CMenuItem(" ")
{
	m_bEnabled = bEnabled;

	//Init Items
	m_pToggleItem[0] = new CPlayerSetupItem(skin);
	m_pToggleItem[1] = new CControllerSetupItem(keyset);
	m_iCurrentItem = 1;
}

CPlayerSetupRow::~CPlayerSetupRow()
{
	delete m_pToggleItem[0];
	delete m_pToggleItem[1];
	
}

void CPlayerSetupRow::toggleEnable()
{
	m_bEnabled = !m_bEnabled;
}

void CPlayerSetupRow::setPosition(CVector3 vPos)
{	
	m_vPosition.x = vPos.x;
	m_vPosition.y = vPos.y;
	m_vPosition.z = vPos.z; 

	CVector3 vTmp = m_vPosition;
	m_pToggleItem[0]->setPosition(vTmp);
	vTmp.x+=0.3;
	m_pToggleItem[1]->setPosition(vTmp);

}

int CPlayerSetupRow::getKeySet()
{
	return m_pToggleItem[1]->getValue();  
}

int CPlayerSetupRow::getSkin()
{
	return m_pToggleItem[0]->getValue();
}

void CPlayerSetupRow::enter()
{	
	if (m_bEnabled)
		m_pToggleItem[m_iCurrentItem]->enter();
}

void CPlayerSetupRow::right()
{
	// only switch column when enabled
/*	if ( (m_iCurrentItem < 1)&&(m_bEnabled) )
	{
		m_iCurrentItem++;
	}*/
}
void CPlayerSetupRow::left()
{
	// only switch column when enabled
/*	if ( (m_iCurrentItem > 0)&&(m_bEnabled) )
	{
		m_iCurrentItem--;
	}*/
}

void CPlayerSetupRow::draw()
{
	if (m_bActive)
	{	
		m_pToggleItem[m_iCurrentItem]->setActive(true);	
	//	glColor3f(1,0,0);
	}
	//else
	//	glColor3f(1,1,1);
	
	for (int i = 0; i < 2; i++)
		m_pToggleItem[i]->draw();
	
	
	// Draw a Cross if player is disabled
	if (!m_bEnabled)
	{
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable( GL_BLEND );
		glPushMatrix();
		glTranslatef(relToAbs(m_vPosition.x,0),relToAbs(m_vPosition.y+0.05,1),10);
			CApplication::m_pTextureManager->bindTexture(PLAYER_DISABLED_TEXTURE);
			glBegin(GL_QUADS);
				/*glTexCoord2f(1,1);glVertex3f(-50,-50,10);
				glTexCoord2f(0,1);glVertex3f(400,-50,10); 
				glTexCoord2f(0,0);glVertex3f(400,50,10);
					glTexCoord2f(1,0);glVertex3f(-50,50,10);*/
				glTexCoord2f(1,1);glVertex3f(-1*relToAbs(0.0625,0)	,-1*relToAbs(0.084,1),0);
				glTexCoord2f(0,1);glVertex3f(relToAbs(0.5,0)		,-1*relToAbs(0.084,1),0); 
				glTexCoord2f(0,0);glVertex3f(relToAbs(0.5,0)		,relToAbs(0.084,1),0);
				glTexCoord2f(1,0);glVertex3f(-1*relToAbs(0.0625,0)	,relToAbs(0.084,1),0);
			glEnd();
		glPopMatrix();
		glDisable( GL_BLEND );

	}

//	m_bActive = false;
//	glColor3f(1,1,1);

}
