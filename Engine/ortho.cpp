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

#include <GLUT/glut.h>
#include "ortho.h"
#include "../CApplication.h"
#include "../CConfig.h"

void enableOrthoMode()
{
	//save Projection Matrix before entering Ortho Mode
	
	glMatrixMode(GL_PROJECTION);                        
	glPushMatrix();                                    
	glLoadIdentity();                                	
	
	glOrtho(0, CApplication::screenWidth, 
			0, CApplication::screenHeight,
			-100,100);

	glNormal3f(0,0,1);

	//save Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();           
}

void disableOrthoMode()
{
    // Pop off the last matrix pushed on when in projection mode (Get rid of ortho mode)
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();                                            

	// Pop off old model view matrix
    glMatrixMode( GL_MODELVIEW );                            
	glPopMatrix();


}

float relToAbs(float relValue, int axis)
{
		//axis = 0 -> x
		//axis = 1 -> y
	if (axis > 0)
		return ( CApplication::screenHeight * relValue );
	else
		return ( CApplication::screenWidth * relValue ); 
}


float absToRel(float absValue, int axis)
{
	// FIX ME : check for division by 0 
	if (axis > 0)
		return ( absValue/CApplication::screenHeight );
	else
		return ( absValue/CApplication::screenWidth ); 	
}
