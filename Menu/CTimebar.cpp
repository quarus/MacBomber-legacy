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
#include "CApplication.h"
#include "../Defines.h"
#include "../Engine/CTextureManager.h"
#include "CTimebar.h"

CTimebar::CTimebar(int totalTime)
{
	float length;
	m_vVertices[0] = CVector3(0,590,0);
	m_vVertices[1] = CVector3(200,590,0);
	m_vVertices[2] = CVector3(200,570,0);
	m_vVertices[3] = CVector3(0,570,0);

	length = m_vVertices[1].x - m_vVertices[0].x;
	m_fStepPerSecond = length /(float)totalTime; 
	m_fStepPerSecond_Tex = 1  / (float)totalTime;
	m_fTexCoordX = 1;
}

void CTimebar::update(int time)
{
	// shrink the bar
//	m_vVertices[1].x = m_fStepPerSecond * (float)time;
//	m_vVertices[2].x = m_fStepPerSecond * (float)time;
//	m_fTexCoordX	 = m_fStepPerSecond_Tex * (float)time;

	m_fTexCoordX	 -= m_fStepPerSecond_Tex * CApplication::m_fReciprocalFPS;
	m_vVertices[1].x -= (m_fStepPerSecond * CApplication::m_fReciprocalFPS);
	m_vVertices[2].x -= (m_fStepPerSecond * CApplication::m_fReciprocalFPS);


}

void CTimebar::draw()
{
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glEnable( GL_BLEND );   

	CApplication::m_pTextureManager->bindTexture(TIMEBAR_TEXTURE);
	
//	glColor3f(1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex3f(m_vVertices[0].x,m_vVertices[0].y,m_vVertices[0].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(m_vVertices[3].x,m_vVertices[3].y,m_vVertices[3].z);
		glTexCoord2f(m_fTexCoordX, 0.0); glVertex3f(m_vVertices[2].x,m_vVertices[2].y,m_vVertices[2].z);
		glTexCoord2f(m_fTexCoordX, 1.0); glVertex3f(m_vVertices[1].x,m_vVertices[1].y,m_vVertices[1].z);
	glEnd();
	glColor3f(1,1,1);
	
	glDisable(GL_BLEND);

}
