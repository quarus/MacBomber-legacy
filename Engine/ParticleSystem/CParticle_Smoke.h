/*
 *  CParticle_Item.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CParticle_Smoke_H
#define CParticle_Smoke_H

#include "CParticle.h"
#include "../CVector3.h"



class CParticle_Smoke: public CParticle
{
private:
public:
	CParticle_Smoke(CVector3 m_vPos);
	void update();
};
#endif
