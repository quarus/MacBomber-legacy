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

#include "CLabelItem.h"
#include "CMenu.h"

#include "../CApplication.h"
#include "../Engine/CTextDrawer.h"

CLabelItem::CLabelItem(char * caption):CMenuItem(caption)
{
//	m_cCaption = caption;
	strcpy(m_cCaption,caption);
	m_bActive = false;
	m_bInteractive = false;

}

/*
float CLabelItem::getWidth()
{
	return CApplication::m_pTextDrawer->getLength(m_cCaption);
}*/

void CLabelItem::draw()
{
	CApplication::m_pTextDrawer->drawText(m_vPosition.x,m_vPosition.y,m_cCaption);	
}

