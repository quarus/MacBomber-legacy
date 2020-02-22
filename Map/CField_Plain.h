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

#ifndef CField_Plain_H
#define CField_Plain_H

#include <GLUT/glut.h>
#include <OpenGL/glext.h>

#include "CField.h"
#include "CVector3.h"
#include "../Objects/CBomb.h"


class CItem;
class CTimer;
class CMap;

class CField_Plain: public CField
{
private:
	//plain fields can have a second decal texture (mud, flowers, etc..)
	bool m_bDecal;			// true, if a mud texture should be drawn on the main texture
	int m_iDecalTexture;	// index of the fields second decal texture
	int m_iDecalOrientation;// specifies in which direction the decal should be rotated
	void placeCrate();

public:
	CField_Plain( int xGrid, int yGrid,bool bCrate,CMap * pMap );
	
    ~CField_Plain();
    
    
    // returniert true, falls eine Bombe platziert werden konnte
    bool placeBomb ( CBomb * bomb );
 	void moveBomb();
	void kickBomb(int dir);
	void update();
    void draw();
};    



#endif
