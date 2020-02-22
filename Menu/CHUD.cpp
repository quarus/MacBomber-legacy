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
#include "CHUD.h"

#include <GLUT/glut.h>
#include <OpenGL/glext.h>


#include "../CApplication.h"
#include "../Gametypes/CGame.h"
#include "../Defines.h"
#include "../Engine/CTextDrawer.h"
#include "../Engine/CTextureManager.h"
#include "../Engine/ortho.h"
#include "../Engine/CTimer.h"
#include "../Engine/intToString.h"
#include "../Engine/CCamera.h"
#include "../Map/CMapManager.h"
#include "../Map/StMapEntry.h"
#include "CTimebar.h"

#include<iostream>
#include<sstream>
CHUD::CHUD(int index)
{
	
	StMapEntry tmpEntry = CApplication::m_pMapManager->getMap(index);
	m_strLevelName = string(tmpEntry.name); 
	m_fLevelName_Xpos = 1-CApplication::m_pTextDrawer->getLength(m_strLevelName.c_str());
	m_fMargin = 0.00625;
	m_fScalefactor_Warning = 0;
	m_fAlpha_Warning = 1;

	m_bDrawTime = true;
	m_bDrawWarning = false;
	m_bPause = false;
	m_pTimebar = new CTimebar(CApplication::m_pGame->getTotalTime());
	
}
CHUD::~CHUD()
{
	delete m_pTimebar;
}


void CHUD::drawTime()
{

	if (m_bDrawTime)
	{
		CApplication::m_pTextureManager->bindTexture(CLOCK_TEXTURE);
		glEnable( GL_BLEND );
		glPushMatrix();
			glTranslatef(relToAbs(m_fMargin,0),relToAbs(0.94,1),0);
			glBegin(GL_QUADS);
			glTexCoord2f(1,1);glVertex3f(40,40,0);
			glTexCoord2f(0,1);glVertex3f(0,40,0); 
			glTexCoord2f(0,0);glVertex3f(0,0,0);
			glTexCoord2f(1,0);glVertex3f(40,0,0);
			glEnd();
		glPopMatrix();
		glDisable( GL_BLEND );
		
		string strTime = convertValueToString(m_iTime);		
		CApplication::m_pTextDrawer->drawText(m_fMargin + 0.05,0.96,strTime.c_str());
	//	m_pTimebar->draw();
	}
}

void CHUD::drawWarning()
{
		if (m_bDrawWarning)
		{
			glColor4f(1,0,0,m_fAlpha_Warning);
			glEnable( GL_BLEND );
			CApplication::m_pTextDrawer->setSize(BIG);
			CApplication::m_pTextDrawer->drawTextCentered(0.5,0.5,"Hurry up!",m_fScalefactor_Warning);		
			CApplication::m_pTextDrawer->setSize(STD);
			glDisable( GL_BLEND );
			glColor3f(1,1,1);
		}
}


void CHUD::drawLevelName()
{
	CApplication::m_pTextDrawer->drawTextCentered(0.5,0.96,m_strLevelName.c_str());	
}

void CHUD::drawView()
{
	CApplication::m_pTextureManager->bindTexture(EYE_TEXTURE);
	glEnable( GL_BLEND );
	glPushMatrix();
		glTranslatef(relToAbs(1-m_fMargin-0.08,0),relToAbs(0.94,1),0);
		glBegin(GL_QUADS);
		glTexCoord2f(1,1);glVertex3f(40,40,0);
		glTexCoord2f(0,1);glVertex3f(0,40,0); 
		glTexCoord2f(0,0);glVertex3f(0,0,0);
		glTexCoord2f(1,0);glVertex3f(40,0,0);
		glEnd();
	glPopMatrix();
	glDisable( GL_BLEND );
	
	string strView = convertValueToString(m_iView);		
	CApplication::m_pTextDrawer->drawText(1-m_fMargin-0.02,0.96,strView.c_str());	
}


void CHUD::startPause()
{
	m_bPause = true;
}

void CHUD::stopPause()
{
	m_bPause = false;
}

void CHUD::update()
{
		
	m_iTime = (CApplication::m_pConfig->getRoundTime()*1000 - CApplication::m_pGame->getElapsedTime()) / 1000;
	m_iView = CApplication::m_pCamera->getPreset() + 1; // +1: don't let view indeces star at 0
	
	if  (m_iTime <= 33)
	{
		m_bDrawWarning = true;
		
		if (m_iTime >= 31)
		{
			if (m_fScalefactor_Warning >= 1 )
				m_fScalefactor_Warning = 1;
			else
				m_fScalefactor_Warning += 2 * CApplication::m_fReciprocalFPS;

		}
		else
		if (m_iTime >=29)
		{
			m_fScalefactor_Warning += 3 * CApplication::m_fReciprocalFPS;
			m_fAlpha_Warning -= 1 * CApplication::m_fReciprocalFPS;
		}
		else
			m_bDrawWarning = false;
	}
	
		m_pTimebar->update(m_iTime);	
}


void CHUD::draw()
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	
	//disable lighting - this way we can speciy text color by calling glColor() 
	glDisable (GL_LIGHTING);
	glColor3f(1,1,1);
	enableOrthoMode();
		if ( m_bPause == false)
		{
			drawTime();
		}
		else
		{
			CApplication::m_pTextDrawer->drawText(m_fMargin,0.96,"Game paused!");
		}
		drawWarning();
		drawLevelName();
		drawView();
		
	disableOrthoMode();
	glEnable (GL_LIGHTING);

}
