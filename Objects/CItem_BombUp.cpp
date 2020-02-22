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

#include "CItem_BombUp.h"
#include "CPlayer.h"

#include "../CApplication.h"
#include "../CConfig.h"

CItem_BombUp::CItem_BombUp ( int xBlock, int zBlock ): CItem(xBlock, zBlock)
{
	m_iType = BOMBUP;
	m_iTexture = GOODIE_BOMBUP_TEXTURE;

}

bool CItem_BombUp::affectPlayer(CPlayer * player)
{
	if ( player->m_iBombCount < ( CApplication::m_pConfig->getStartBombs() + CApplication::m_pConfig->getExtraBombs()) )
	{
		player->m_iBombCount++;
	}
	return true;
}

