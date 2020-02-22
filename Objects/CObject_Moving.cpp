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

#include "CObject_Moving.h"
#include "../CApplication.h"

CObject_Moving::CObject_Moving(int xBlock, int zBlock, float size):CObject(xBlock, zBlock, size)
{
	m_bDoesDrop = false;
	m_iDirection = NONE;
	m_fVelocity = 0.0f;
}


void CObject_Moving::setDirection(int dir)
{
	/* Map coord. system
	*			19
	* O------------------x
	* |
	* |	
	* |
	* |	
	* | 15
	* |
	* z
	*		   .
	*		camera
	*/
	
	
	m_iDirection = dir;
	switch ( m_iDirection )
	{
		case UP:
			m_vDisplacement = CVector3(0,0,-1);
			m_fOrientation = 180;
			break;
		case DOWN:
			m_vDisplacement = CVector3(0,0,1);
			m_fOrientation = 0;
			break;
		case LEFT:
			m_vDisplacement = CVector3(-1,0,0);
			m_fOrientation = 270;			
			break;
		case RIGHT:
			m_vDisplacement = CVector3(1,0,0);
			m_fOrientation = 90;			
			break;
		case NONE:
			m_vDisplacement = CVector3(0,0,0);
			break;
		default:
			m_vDisplacement = CVector3(0,0,0);
			break;
	}
			
}

void CObject_Moving::setDrop(bool bDrop)
{
	m_bDoesDrop = bDrop;
}

void CObject_Moving::setDisplacement(CVector3 vDisplacement)
{
	m_vDisplacement = vDisplacement;
}

void CObject_Moving::move()
{
	m_vPos = m_vPos + (m_vDisplacement * (m_fVelocity * CApplication::m_fReciprocalFPS));

	// aktualisiere die Blockkoordinaten
	m_xBlock = int ( m_vPos.x );
	m_zBlock = int ( m_vPos.z );

	m_pBBox->update(m_vPos);        
}

void CObject_Moving::move(CVector3 vDisplacement)
{
	m_vPos = m_vPos + (vDisplacement* (m_fVelocity * CApplication::m_fReciprocalFPS));
}

bool CObject_Moving::doDrop()
{
	
	CVector3 vVerticalDisplacement(0,-1,0);
	vVerticalDisplacement = vVerticalDisplacement;
	
	if ( m_vPos.y > -8.0f )
	{
		m_vPos = m_vPos + (vVerticalDisplacement * 0.05f);
		return true;
	}
	else
	{
		setDirection(NONE);
		return false;
	}
}
