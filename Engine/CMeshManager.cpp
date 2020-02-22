/*MacBomber - Copyright (C) 2006  Altay Cebe

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include<string>
using namespace std;

#include "CMeshManager.h"
#include "CTriangleMesh.h"
#include "lib3ds/file.h"
#include "../Defines.h"
#include "../CApplication.h"

#include "../MeshObjects/CBlockMesh.h"
#include "../MeshObjects/CBombMesh.h"
#include "../MeshObjects/CItemMesh.h"
#include "../MeshObjects/CCrateMesh.h"
#include "../MeshObjects/CPlayerMesh.h"
#include "../MeshObjects/CCupMesh.h"
#include "../MeshObjects/CSquareMesh.h"

CMeshManager::CMeshManager()
{
	m_pBlockMesh = new CBlockMesh();
	m_pBombMesh	 = new CBombMesh();
	m_pCrateMesh = new CCrateMesh();
	m_pItemMesh  = new CItemMesh();
	m_pPlayerMesh = new CPlayerMesh();
	m_pCupMesh    = new CCupMesh();
	m_pSquareMesh = new CSquareMesh();
	
	m_pTriangleMesh = new CTriangleMesh[7];
	
	float tmp[4] = {1,1,1,1};
	memcpy(m_stMaterials[PLAYER_OBJECT].ambientDiffuse,tmp, sizeof(m_stMaterials[PLAYER_OBJECT].ambientDiffuse));	
	tmp[0] =0.5;tmp[1] = 0.5;tmp[2] = 0.5;tmp[3] = 0.5;
	memcpy(m_stMaterials[PLAYER_OBJECT].specular,tmp, sizeof(m_stMaterials[PLAYER_OBJECT].specular));	

	tmp[0] =1;tmp[1] = 1;tmp[2] = 1;tmp[3] = 1;
	memcpy(m_stMaterials[ITEM_OBJECT].ambientDiffuse,tmp, sizeof(m_stMaterials[ITEM_OBJECT].ambientDiffuse));	
	tmp[0] =0.7;tmp[1] = 0.7;tmp[2] = 0.7;tmp[3] = 1;
	memcpy(m_stMaterials[ITEM_OBJECT].specular,tmp, sizeof(m_stMaterials[ITEM_OBJECT].ambientDiffuse));	
	
	tmp[0] =0;tmp[1] = 1;tmp[2] = 1;tmp[3] = 1;
	memcpy(m_stMaterials[FIELD_OBJECT].ambientDiffuse,tmp, sizeof(m_stMaterials[FIELD_OBJECT].ambientDiffuse));	
	tmp[0] =0.0;tmp[1] = 0.0;tmp[2] = 0.0;tmp[3] = 0;
	memcpy(m_stMaterials[FIELD_OBJECT].specular,tmp, sizeof(m_stMaterials[FIELD_OBJECT].ambientDiffuse));	
	
	tmp[0] =1;tmp[1] = 1;tmp[2] = 1;tmp[3] = 1;
	memcpy(m_stMaterials[BLOCK_OBJECT].ambientDiffuse,tmp, sizeof(m_stMaterials[BLOCK_OBJECT].ambientDiffuse));	
	tmp[0] =0.2;tmp[1] = 0.2;tmp[2] = 0.2;tmp[3] = 1;
	memcpy(m_stMaterials[BLOCK_OBJECT].specular,tmp, sizeof(m_stMaterials[BLOCK_OBJECT].ambientDiffuse));	
		
	tmp[0] =1;tmp[1] = 1;tmp[2] = 1;tmp[3] = 1;
	memcpy(m_stMaterials[CRATE_OBJECT].ambientDiffuse,tmp, sizeof(m_stMaterials[CRATE_OBJECT].ambientDiffuse));	
	tmp[0] =0.4;tmp[1] = 0.4;tmp[2] = 0.4;tmp[3] = 1;
	memcpy(m_stMaterials[CRATE_OBJECT].specular,tmp, sizeof(m_stMaterials[CRATE_OBJECT].ambientDiffuse));	
		
	tmp[0] =0.8;tmp[1] = 0.8;tmp[2] = 0.8;tmp[3] = 1;
	memcpy(m_stMaterials[BOMB_OBJECT].ambientDiffuse,tmp, sizeof(m_stMaterials[BOMB_OBJECT].ambientDiffuse));	
	tmp[0] =0.8;tmp[1] = 0.8;tmp[2] = 0.8;tmp[3] = 1;
	memcpy(m_stMaterials[BOMB_OBJECT].specular,tmp, sizeof(m_stMaterials[BOMB_OBJECT].ambientDiffuse));	

	tmp[0] =0;tmp[1] = 1;tmp[2] = 1;tmp[3] = 1;
	memcpy(m_stMaterials[CUP_OBJECT].ambientDiffuse,tmp, sizeof(m_stMaterials[CUP_OBJECT].ambientDiffuse));	
	tmp[0] =1;tmp[1] = 1;tmp[2] = 1;tmp[3] = 1;
	memcpy(m_stMaterials[CUP_OBJECT].specular,tmp, sizeof(m_stMaterials[CUP_OBJECT].ambientDiffuse));	
	
	
}

CMeshManager::~CMeshManager()
{
	delete m_pBlockMesh;
	delete m_pBombMesh;
	delete m_pCrateMesh;
	delete m_pItemMesh;
	delete m_pPlayerMesh;
	delete m_pCupMesh;
	delete m_pSquareMesh;

	delete [] m_pTriangleMesh;
}


const char * CMeshManager::expand(char * path)
{
	string tmp = CApplication::m_strResourcePath;
	tmp = tmp + path;
	
	return tmp.c_str(); 
}

/*
void CMeshManager::loadMeshes()
{
	Lib3dsFile * pFile;

	//pFile = lib3ds_file_load(expand("/MeshObjects/mac3.3ds"));
	pFile = lib3ds_file_load(expand("/Meshes/MacClassic.3ds"));
	m_pTriangleMesh[PLAYER_OBJECT].load3dsFile(pFile);
	m_pTriangleMesh[PLAYER_OBJECT].createVBO();
	lib3ds_file_free(pFile);
	
	pFile = lib3ds_file_load(expand("/Meshes/item.3ds")); 
	m_pTriangleMesh[ITEM_OBJECT].load3dsFile(pFile);
	m_pTriangleMesh[ITEM_OBJECT].createVBO();
	lib3ds_file_free(pFile);
	

	
	pFile = lib3ds_file_load(expand("/Meshes/block.3ds"));
	m_pTriangleMesh[BLOCK_OBJECT].load3dsFile(pFile);
	m_pTriangleMesh[BLOCK_OBJECT].createVBO();
	lib3ds_file_free(pFile);
	
	pFile = lib3ds_file_load(expand("/Meshes/crate.3ds"));
	m_pTriangleMesh[CRATE_OBJECT].load3dsFile(pFile);
	m_pTriangleMesh[CRATE_OBJECT].createVBO();	
	lib3ds_file_free(pFile);
	
	pFile = lib3ds_file_load(expand("/Meshes/bomb.3ds")); 
	m_pTriangleMesh[BOMB_OBJECT].load3dsFile(pFile);
	m_pTriangleMesh[BOMB_OBJECT].createVBO();	
	lib3ds_file_free(pFile);
	
	pFile = lib3ds_file_load(expand("/Meshes/cup.3ds")); 
	m_pTriangleMesh[CUP_OBJECT].load3dsFile(pFile);
	m_pTriangleMesh[CUP_OBJECT].createVBO();	
	lib3ds_file_free(pFile);
	
}

void CMeshManager::drawMesh(int index)
{
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m_stMaterials[index].ambientDiffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, m_stMaterials[index].specular);

	
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
	glColor3f(1,1,1);


	float blub[4]= {1,1,1,1};
	glMaterialfv(GL_FRONT, GL_SPECULAR, blub);
	glMateriali(GL_FRONT, GL_SHININESS, 50);
									
 	

	m_pTriangleMesh[index].drawVBO();
//	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
	
}*/
