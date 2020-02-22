/*
 *  CParticleManager.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CParticleManager_H
#define CParticleManager_H

#include <GLUT/glut.h>
#include "CParticle.h"
#include "CParticle_Explosion.h"

#include "../CVector3.h"

#include <list>

class CParticleManager
{
	friend class CParticle_Item;
	friend class CParticle_Crate;
	friend class CParticle_SmokeTrail;
private:
	//calculates a random displacment vector, which lays on hemisphere with radius 1 around m_vPos
	void calculateDisplacement(CVector3 & vDisplacement,int minAngle, int maxAngle);
	//calculates a new startPosition, wehich lays within a sphere with radius "radius" araound m_vPos
	void randomizeStartPosition(CVector3 & vPosition, float radius = 1);
	
	
	//list, which contains all particles except explosion particle
	list <CParticle*> m_listParticles;
	/**
	list which keeps all explosion particles.
	this is used to ensure that all debirs, smoke particles are drawn on top of the explosions
	*/ 
	list <CParticle_Explosion*> m_listExplosionParticles; 
public:
	static GLuint m_iParticleDL;

	CParticleManager();
	~CParticleManager();

	void addItemParticle(CVector3 vPos, int count, int itemType);
	void addSmokeParticle(CVector3 vPos, int count);
	void addPlayerSmokeParticle(CVector3 vPos, int count);
	void addCrateParticle(CVector3 vPos, int count);
	void addExplosionParticle(CVector3 vPos);
	void addWileyParticle(CVector3 vPos, int count);

	void update();	
	void draw();
};

#endif
