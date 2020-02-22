/*
 *  CParticle_Item.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CParticle_Explosion_H
#define CParticle_Explosion_H

#include "CParticle.h"
#include "../CVector3.h"


class CParticle_Explosion: public CParticle
{
private:
public:
	CParticle_Explosion(CVector3 m_vPos);

	void update();
	void draw();
};
#endif
