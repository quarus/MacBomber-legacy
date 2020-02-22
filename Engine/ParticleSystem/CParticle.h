/*
 *  CParticle.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CParticle_H
#define CParticle_H
#include "../CVector3.h"

class CParticle
{
protected:
	
	void updateBillboardMatrix();
	//moves the particle
	void move(); 
public:
	float m_fVelocity;			// the speed of the particle
	CVector3 m_vDisplacement;	// the Direction it travels
	CVector3 m_vPosition;		// the position of the particle
	int m_iTTL;					// the amount of ticks it has to live ( Time To Live)
	
	float m_fColor[4];			//the particles Color (R,G,B,A )
	int m_iTextureIndex;		// particles can have different textures
	float m_fScaleFactor;		// the scalefactor for the particles Texture	
	float m_fScaleFactorModifier;
	float m_fRotation;			// rotation of the particle
	float m_BillboardMatrix[16];
	
	CParticle(CVector3 vPos);
	
	bool isDead();
	bool m_bHasTrail;
	
	virtual ~CParticle();
	virtual void update();
	virtual void draw();
};
#endif
