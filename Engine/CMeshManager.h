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

#ifndef CMeshManager_H
#define CMeshManager_H

class CTriangleMesh;

class CBlockMesh;
class CBombMesh;
class CCrateMesh;
class CItemMesh;
class CPlayerMesh;
class CCupMesh;
class CSquareMesh;


class CMeshManager
{
private:

	struct stMaterial
	{
		float ambientDiffuse[4];
		float specular[4];
	};
	
	
	// Array Contains all TriangleMeshes
	CTriangleMesh * m_pTriangleMesh;		
	// These Arrays contain Material Information for each Mesh
	stMaterial m_stMaterials[7];
	
	const char * expand(char * path);

	
public:
	// These are pointers to our Meshobjects (public for now)
	// to draw an object we call m_p<*>Mesh->drawVBO();
	CBlockMesh	* m_pBlockMesh;
	CBombMesh	* m_pBombMesh;
	CCrateMesh	* m_pCrateMesh;
	CItemMesh	* m_pItemMesh;
	CPlayerMesh * m_pPlayerMesh;
	CCupMesh	* m_pCupMesh;
	CSquareMesh * m_pSquareMesh;

	CMeshManager();
	~CMeshManager();
	// load all Meshes 
	//void loadMeshes();

	//draws the specified Mesh
	//void drawMesh(int index);
};
#endif