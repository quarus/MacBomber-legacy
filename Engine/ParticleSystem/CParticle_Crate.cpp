/*
 *  CParticle_Crate.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "../../CApplication.h"
#include "CParticleManager.h"
#include "CParticle_Crate.h"
#include "CParticle_SmokeTrail.h"
#include "../../Defines.h"
#include "../CBillboard.h"
#include "../CTextureManager.h"


CParticle_Crate::CParticle_Crate(CVector3 vPos, CParticleManager * pParticleManager):CParticle(vPos)
{
	
	m_iTTL = 40;
	m_fScaleFactor = 0.8;	 
	m_fVelocity = 5 + rand()%6;
	m_vDisplacement.y = 1;
	m_pParticleManager = pParticleManager;
	m_iTextureIndex = PARTICLE_CRATE_TEXTURE;
	
	m_fAngleX = rand()%360;
	m_fAngleY = rand()%360;
	m_fAngleZ = rand()%360;
				
	float rnd = ((float)(rand()%3))/10 ; 
	m_fColor[0] = 0.8 + rnd;
	m_fColor[1] = 0.8 + rnd;
	m_fColor[2] = 0.8 + rnd;
	m_fColor[3] = 1;
	
	m_bSpawnTrailParticle = false;

}

void CParticle_Crate::update()
{
	m_iTTL--;
	if (m_iTTL < 10)
		m_fColor[3] -= 0.05;			
	move();	
	m_vDisplacement.y -= (2 * CApplication::m_fReciprocalFPS);

//	updateBillboardMatrix();
	
	m_fAngleX += 180 * CApplication::m_fReciprocalFPS; 
	m_fAngleY += 180 * CApplication::m_fReciprocalFPS; 
	m_fAngleZ += 180 * CApplication::m_fReciprocalFPS; 

	if (m_bSpawnTrailParticle)
	{
		CParticle * pParticle = new CParticle_SmokeTrail(m_vPosition);
		m_pParticleManager->m_listParticles.push_back(pParticle);
	}
	
	m_bSpawnTrailParticle = !m_bSpawnTrailParticle;
}

void CParticle_Crate::draw()
{
	glDisable(GL_CULL_FACE);
	glDisable (GL_LIGHTING);
	glEnable( GL_BLEND );   
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	
	glDepthMask(GL_FALSE);

	glColor4f(m_fColor[0],
			  m_fColor[1],
			  m_fColor[2], 
			  m_fColor[3]);

	glPushMatrix();

		glTranslatef(m_vPosition.x,
					 m_vPosition.y,
					 m_vPosition.z);


		glRotatef(m_fAngleX,1,0,0);
		glRotatef(m_fAngleY,0,1,0);
		glRotatef(m_fAngleZ,0,0,1);

		glScalef(m_fScaleFactor,
				 m_fScaleFactor,
				 m_fScaleFactor);


		CApplication::m_pTextureManager->bindTexture(m_iTextureIndex);
		glCallList(CParticleManager::m_iParticleDL);

	glPopMatrix();
	
			
	glColor4f(1,1,1,1);
	glDepthMask(GL_TRUE);
	glDisable( GL_BLEND );                     
	glEnable (GL_LIGHTING);
	glEnable(GL_CULL_FACE);


}

