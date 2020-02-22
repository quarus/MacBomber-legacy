/*
 *  CParticle_Item.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CParticle_Item_H
#define CParticle_Item_H

#include "CParticle.h"
#include "../CVector3.h"

class CParticleManager;


class CParticle_Item: public CParticle
{
private:
	bool m_bSpawnTrailParticle;

	CParticleManager * m_pParticleManager;
public:
	CParticle_Item(CVector3 m_vPos, CParticleManager * pParticleManager, int itemType);
	void update();
};
#endif
