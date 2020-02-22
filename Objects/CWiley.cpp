/*
 *  CWiley.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 13.10.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "CWiley.h"
#include "../Engine/CMeshManager.h"
#include "../Engine/CTriangleMesh.h"
#include "../Defines.h"
#include "../CApplication.h"
#include "../MeshObjects/CBombMesh.h"

CWiley::CWiley():CObject_Moving(-10, 0, 1)
{
	m_bDoesDrop = false;
	m_iDirection = NONE;
	m_fVelocity = 10.0f;
}


void CWiley::draw()
{	
	glPushMatrix();
		glTranslatef(m_vPos.x, m_vPos.y,m_vPos.z);
		CApplication::m_pMeshManager->m_pBombMesh->configureTexCoord0();
		CApplication::m_pMeshManager->m_pBombMesh->configureTexture0(DESTROYER_TEXTURE);
		CApplication::m_pMeshManager->m_pBombMesh->enableBuffers();
		CApplication::m_pMeshManager->m_pBombMesh->drawVBO();
		CApplication::m_pMeshManager->m_pBombMesh->disableBuffers();
		CApplication::m_pMeshManager->m_pBombMesh->resetTextureEngines();

	glPopMatrix();

}