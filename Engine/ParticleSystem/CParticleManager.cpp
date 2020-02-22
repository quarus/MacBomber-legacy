/*
 *  CParticleManager.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include <GLUT/glut.h>
#include <OpenGL/glext.h>


#include "CParticleManager.h"
#include "CParticle_Item.h"
#include "CParticle_Smoke.h"
#include "CParticle_Crate.h"
#include "CParticle_Explosion.h"

#include "../3DMath.h"
#include "../CTextureManager.h"
#include "../../CApplication.h"
#include "../../Defines.h"

#define PI 3.14159265

GLuint CParticleManager::m_iParticleDL = 0;


CParticleManager::CParticleManager()
{
	m_iParticleDL=glGenLists(1);
	glNewList(m_iParticleDL,GL_COMPILE);
	 	glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.0f);   
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.0f); 
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.0f);   
     		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.0f);   
		glEnd();		
	glEndList();
}

CParticleManager::~CParticleManager()
{
	{
	list<CParticle*>::iterator it;
	for (it = m_listParticles.begin(); it != m_listParticles.end(); it++)
	{
		delete (*it);
	}	
	m_listParticles.clear();
	}
	
	list<CParticle_Explosion*>::iterator it;
	for (it = m_listExplosionParticles.begin(); it != m_listExplosionParticles.end(); it++)
	{
		delete (*it);
	}	
	m_listExplosionParticles.clear();
	glDeleteLists(m_iParticleDL,1);
}



void CParticleManager::addItemParticle(CVector3 vPos, int count, int itemType)
{
	for (int i = 0; i < count; i++)
	{
		
		CParticle * particle = new CParticle_Item(vPos,this, itemType);
		calculateDisplacement(particle->m_vDisplacement,60,120);	

		m_listParticles.push_back(particle);
	}
}

void CParticleManager::addCrateParticle(CVector3 vPos, int count)
{
	for (int i = 0; i < count; i++)
	{
		CParticle * particle = new CParticle_Crate(vPos,this);
		calculateDisplacement(particle->m_vDisplacement,20,160);	
		m_listParticles.push_back(particle);
	}

}

void CParticleManager::addSmokeParticle(CVector3 vPos, int count)
{
	for (int i = 0; i < count; i++)
	{
		CParticle * particle = new CParticle_Smoke(vPos);
		randomizeStartPosition(particle->m_vPosition, 0.5);	
		particle->m_vPosition.y = 0;
		m_listParticles.push_back(particle);
	}

}

void CParticleManager::addPlayerSmokeParticle(CVector3 vPos, int count)
{
	for (int i = 0; i < count; i++)
	{
		CParticle * particle = new CParticle_Smoke(vPos);
		randomizeStartPosition(particle->m_vPosition, 0.5);	
		particle->m_iTTL = 100;
		particle->m_fScaleFactor = 0.75	;
		particle->m_fScaleFactorModifier = 1;	 

		float fColorMod = 0.5 + ( (rand()%7) *0.1);
		particle->m_fColor[0] = fColorMod ;
		particle->m_fColor[1] = fColorMod;
		particle->m_fColor[2] = fColorMod;
		particle->m_fColor[3] = 0.8;

		particle->m_fVelocity = 1 + ((rand()%11)* 0.1);
		particle->m_vDisplacement.y = 1;
		particle->m_iTextureIndex = PARTICLE_SMOKE0_TEXTURE;
		
		m_listParticles.push_back(particle);
	}
}

void CParticleManager::addExplosionParticle(CVector3 vPos)
{
	CParticle_Explosion * particle = new CParticle_Explosion(vPos);
	//randomizeStartPosition(particle->m_vPosition, 0.2);
	m_listExplosionParticles.push_back(particle);
}

void CParticleManager::addWileyParticle(CVector3 vPos, int count)
{
	for (int i = 0; i < count; i++)
	{
		CParticle * particle = new CParticle(vPos);
		randomizeStartPosition(particle->m_vPosition, 0.25);	
		particle->m_iTTL = 50;
		particle->m_fScaleFactor = 0.75	;
		particle->m_fScaleFactorModifier = -0.5;	 
		particle->m_fRotation = rand()%360;
		
		//determine randomly a yellow color 
		float fColorMod = 0.1 + ( (rand()%5) *0.1);
		particle->m_fColor[0] = 1;
		particle->m_fColor[1] = 1;
		particle->m_fColor[2] = fColorMod;
		particle->m_fColor[3] = 0.8;

		particle->m_fVelocity = 1;
		particle->m_vDisplacement.y = -1;
		particle->m_iTextureIndex = PARTICLE_WILEY_TEXTURE;
		
		m_listParticles.push_back(particle);
	}
}


void CParticleManager::calculateDisplacement(CVector3 & vDisplacement,int minAngle, int maxAngle)
{
	float angle;
	float x,y,z;

	//randomly choose an angle between minAngle - maxAngle;
	angle = rand()%(maxAngle-minAngle);
	angle += minAngle;
	//convert deg -> rad
	angle = (angle*PI/180);
	
	//caluclate intial values of the displacement vector
	x = cos (angle);
	y = sin (angle);
	z = 0;
	
	//rotate the point (x,z) araund the y axis by a random angle
	rotateAroundYAxis(x,z,rand()%360);
	
	vDisplacement.x = x;
	vDisplacement.y = y;
	vDisplacement.z = z;

}

void CParticleManager::randomizeStartPosition(CVector3 & vPosition, float radius)
{
	float angle;
	float x,y,z;

	//randomly choose an angle between minAngle - maxAngle;
	angle = rand()%360;
	//convert deg -> rad
	angle = (angle*PI/180);
	
	//caluclate intial values of the displacement vector
	x = cos (angle);
	y = sin (angle);
	z = 0;
	
	//rotate the point (x,z) araund the y axis by a random angle
	rotateAroundYAxis(x,z,rand()%360);
	
	vPosition.x += x * radius;
	vPosition.y += y * radius;
	vPosition.z += z * radius;
}

void CParticleManager::update()
{
	{
	list<CParticle*>::iterator it;
	for (it = m_listParticles.begin(); it != m_listParticles.end();)
	{
		if ((*it)->isDead	() )
		{
			delete (*it);
			m_listParticles.erase(it++);
			
		}
		else
		{
			(*it)->update();
			++it;
		}
	}
	}
	
	list<CParticle_Explosion*>::iterator it;
	for (it = m_listExplosionParticles.begin(); it != m_listExplosionParticles.end();)
	{
		if ((*it)->isDead	() )
		{
			delete (*it);
			m_listExplosionParticles.erase(it++);
			
		}
		else
		{
			(*it)->update();
			++it;
		}
	}

}

void CParticleManager::draw()
{

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	list<CParticle_Explosion*>::reverse_iterator it;
	for (it = m_listExplosionParticles.rbegin(); it != m_listExplosionParticles.rend(); it++)
	{
		(*it)->draw();
	}	

	{
	list<CParticle*>::reverse_iterator it;
	for (it = m_listParticles.rbegin(); it != m_listParticles.rend(); it++)
	{
		(*it)->draw();
	}	
	}
	
	
}

