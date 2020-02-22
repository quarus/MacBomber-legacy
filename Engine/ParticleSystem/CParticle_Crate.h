/*
 *  CParticle_Item.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CParticle_Crate_H
#define CParticle_Crate_H

#include "CParticle.h"
#include "../CVector3.h"

class CParticleManager;


class CParticle_Crate: public CParticle
{
private:
	float m_fAngleX;			//rotation of Particle around X Axis
	float m_fAngleY;			//rotation of Particle around Y Axis
	float m_fAngleZ;			//rotation of Particle around Z Axis
	
	bool m_bSpawnTrailParticle;
	CParticleManager * m_pParticleManager;
public:
	CParticle_Crate(CVector3 m_vPos, CParticleManager * pParticleManager);
	void update();
	void draw();
};
#endif
