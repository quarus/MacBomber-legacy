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

#include "CItem_PowerUp.h"
#include "CPlayer.h"

#include "../CApplication.h"
#include "../CConfig.h"

CItem_PowerUp::CItem_PowerUp ( int xBlock, int zBlock ): CItem(xBlock, zBlock)
{
	m_iType = POWERUP;
	m_iTexture = GOODIE_POWERUP_TEXTURE;

}

bool CItem_PowerUp::affectPlayer(CPlayer * player)
{
	// only affect player if it doesn't exceed Limit
	if (player->m_iBombStrength < (CApplication::m_pConfig->getStartPower() + CApplication::m_pConfig->getExtraPower()) )
	{
		player->m_iBombStrength++;
	}
	return true;
}

