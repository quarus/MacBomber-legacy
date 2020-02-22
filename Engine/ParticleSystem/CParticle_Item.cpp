/*
 *  CParticle_Item.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "../../CApplication.h"
#include "CParticleManager.h"
#include "CParticle_Item.h"
#include "../../Defines.h"

CParticle_Item::CParticle_Item(CVector3 vPos, CParticleManager * pParticleManager, int itemType):CParticle(vPos)
{
	//check Item Type and set Color/Texture accordingly
	if (( itemType == SPEEDUP) || (itemType == POWERUP) || (itemType == BOMBUP)  || (itemType == ENABLEKICK) )
	{
		m_fColor[0] = 0;
		m_fColor[1] = 0;
		m_fColor[2] = 1;
		m_fColor[3] = 0.5;		
		m_iTextureIndex = PARTICLE_GOODIE_TEXTURE;		
	}
	else
	{
		m_fColor[0] = 1;
		m_fColor[1] = 0;
		m_fColor[2] = 0;
		m_fColor[3] = 0.5;		
		m_iTextureIndex = PARTICLE_BADIE_TEXTURE;
	}
	
	m_iTTL = 40;
	m_fScaleFactor = 0.1;
	m_fVelocity = 15 + rand()%6;
	m_vDisplacement.y = 1;
	m_pParticleManager = pParticleManager;
	
	m_bSpawnTrailParticle = true;

}

void CParticle_Item::update()
{

	m_iTTL--;
	if (m_iTTL < 20)
		m_fColor[3] -= 0.05;			
	move();	
	m_vDisplacement.y -= (2 * CApplication::m_fReciprocalFPS);
	updateBillboardMatrix();

		CParticle * pParticle = new CParticle(m_vPosition);
		pParticle->m_iTTL = 20;
		pParticle->m_fScaleFactor = 1;
		pParticle->m_fVelocity = 0;
		pParticle->m_iTextureIndex = m_iTextureIndex;
		
		pParticle->m_fColor[0] = m_fColor[0];
		pParticle->m_fColor[1] = m_fColor[1];
		pParticle->m_fColor[2] = m_fColor[2];
		pParticle->m_fColor[3] = m_fColor[3];
		

		m_pParticleManager->m_listParticles.push_back(pParticle);
	
	m_bSpawnTrailParticle = !m_bSpawnTrailParticle;

}
