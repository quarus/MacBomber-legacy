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

#include "CController.h"
#include "Defines.h"

CController::CController()
{
	for (int i = 0; i < 7; i++)
	{
		m_bKeyHold[i] = false;
		m_bKeyPressed[i] = false;
	}

}

CController::~CController()
{
}

void CController::reset()
{
	for (int i = 0; i < 7; i++)
		m_bKeyPressed[i] = false;
}

bool CController::isUpPressed()
{
	return m_bKeyPressed[UP];	
}

bool CController::isDownPressed()
{
	return m_bKeyPressed[DOWN];
}

bool CController::isLeftPressed()
{
	return m_bKeyPressed[LEFT];
}

bool CController::isRightPressed()
{
	return m_bKeyPressed[RIGHT];
}

bool CController::isBombPressed()
{
	return m_bKeyPressed[4]; 
}


bool CController::isSpacePressed()
{
	return m_bKeyPressed[6]; 
}

bool CController::isBackPressed()
{
	return m_bKeyPressed[5]; 
}



bool CController::isUpHold()
{
	return m_bKeyHold[UP];
}

bool CController::isDownHold()
{
	return m_bKeyHold[DOWN];
}

bool CController::isLeftHold()
{
	return m_bKeyHold[LEFT];
}

bool CController::isRightHold()
{
	return m_bKeyHold[RIGHT];
}
