/*
 *  CParticle.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include <GLUT/glut.h>
#include <OpenGL/glext.h>

#include "../../CApplication.h"
#include "../../Defines.h"
#include "../CBillboard.h"
#include "../CTextureManager.h"
#include "CParticleManager.h"
#include "CParticle.h"

CParticle::CParticle(CVector3 vPos)
{
	m_vPosition = vPos;
	m_fScaleFactorModifier = 0;
	m_fRotation = 0;
	updateBillboardMatrix();

}

bool CParticle::isDead()
{
	if (m_iTTL < 0)
		return true;
	else
		return false;
}

void CParticle::updateBillboardMatrix()
{
	calculateBillboardMatrix_Xaxis(m_vPosition,m_BillboardMatrix);
}

void CParticle::move()
{
	m_vPosition = m_vPosition + 
		((m_vDisplacement * (m_fVelocity * CApplication::m_fReciprocalFPS)) );	
	
}


void CParticle::draw()
{

	glDisable (GL_LIGHTING);
	glEnable( GL_BLEND );   
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
//	glDisable( GL_DEPTH_TEST );
	glDepthMask(GL_FALSE);


	glColor4f(m_fColor[0],
			  m_fColor[1],
			  m_fColor[2], 
			  m_fColor[3]);

	glPushMatrix();
		glMultMatrixf(m_BillboardMatrix);
		glNormal3f(0,0,1);
		glScalef(m_fScaleFactor,
				 m_fScaleFactor,
				 m_fScaleFactor);

		CApplication::m_pTextureManager->bindTexture(m_iTextureIndex);
		glRotatef(m_fRotation,0,0,1);
/*		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.0f);   
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.0f); 
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.0f);   
     		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.0f);   
		glEnd();*/
		glCallList(CParticleManager::m_iParticleDL);
	glPopMatrix();
	
			
	glColor4f(1,1,1,1);
//	glEnable( GL_DEPTH_TEST );
	glDepthMask(GL_TRUE);

	glDisable( GL_BLEND );                     
	glEnable (GL_LIGHTING);


}

CParticle::~CParticle()
{
}

void CParticle::update()
{
	m_iTTL--;
	if (m_iTTL < 10)
	{
		m_fColor[3] -= 0.1;			
	}

	m_fScaleFactor += (m_fScaleFactorModifier * CApplication::m_fReciprocalFPS);

	move();	
	updateBillboardMatrix();
}

