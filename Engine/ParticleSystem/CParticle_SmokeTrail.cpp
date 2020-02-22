
#include "CParticle_SmokeTrail.h"
#include "../../CApplication.h"
#include "../../Defines.h"

CParticle_SmokeTrail::CParticle_SmokeTrail(CVector3 vPos):CParticle(vPos)
{
	m_iTTL = 20;
	m_fScaleFactor = 0.2 + ((rand()%3) *0.1);
	m_fVelocity = 0;
	m_iTextureIndex = PARTICLE_SMOKE1_TEXTURE;
				
	float fColorMod = 0.6 + ( (rand()%5) *0.1);
	m_fColor[0] = fColorMod ;
	m_fColor[1] = fColorMod;
	m_fColor[2] = fColorMod;
	m_fColor[3] = 0.5 + ( (rand()%4) * 0.1 );	
	

}

void CParticle_SmokeTrail::update()
{

	m_iTTL--;
	if (m_iTTL < 10)
		m_fColor[3] -= 0.05;		
	
	if (m_iTTL > 10)
	{
		m_fColor[0] -= 0.01;
		m_fColor[1] -= 0.01;
		m_fColor[2] -= 0.01;
		m_fScaleFactor += 0.01;
	}
	move();	
	updateBillboardMatrix();

}
