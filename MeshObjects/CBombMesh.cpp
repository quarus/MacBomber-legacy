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

#include "CBombMesh.h"

#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include "Workaround.h"

#include "../CApplication.h"
#include "../Engine/CTextureManager.h"


CBombMesh::CBombMesh():CMesh("/Meshes/bomb.3ds")
{
	mat_amb_diff[0] = 0.0;
	mat_amb_diff[1] = 0.0;
	mat_amb_diff[2] = 0.0;
	mat_amb_diff[3] = 1.0;
	
	mat_specular[0] = 1.0;
	mat_specular[1] = 1.0;
	mat_specular[2] = 1.0;
	mat_specular[3] = 1.0;

	mat_shininess = 128;

}


void CBombMesh::configureMaterial()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

void CBombMesh::resetTextureEngines()
{

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D);

}
