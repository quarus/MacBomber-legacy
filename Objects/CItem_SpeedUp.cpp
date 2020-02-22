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

#include "../CApplication.h"
#include "../CConfig.h"

#include "CItem_SpeedUp.h"
#include "CPlayer.h"

CItem_SpeedUp::CItem_SpeedUp ( int xBlock, int zBlock ): CItem(xBlock, zBlock)
{
	m_iType = SPEEDUP;
	m_iTexture = GOODIE_SPEEDUP_TEXTURE;
}

bool CItem_SpeedUp::affectPlayer(CPlayer * player)
{
	// only affect player if it doesn't exceed Limit
	if ( player->m_iSpeed < ( CApplication::m_pConfig->getStartSpeed() + CApplication::m_pConfig->getExtraBombs()) )	
	{
		// FIX ME: implement increaseSpeed() Method in CPlayer
		player->m_iSpeed++;
		player->m_fVelocity = 1 + (CApplication::m_pConfig->getVelocityStepping() * player->m_iSpeed);
	}
	return true;
}
