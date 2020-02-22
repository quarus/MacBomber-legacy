
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
#include <OpenGL/glext.h>

#include "CPlayerSetupMenu.h"
#include "CPlayerSetupRow.h"
#include "CControllerSetupItem.h"
#include "CMenu.h"
#include "CController_Keyboard.h"
#include "CTimer.h"
#include "CTextDrawer.h"
#include "../CApplication.h"
#include "../Engine/CTextDrawer.h"
#include "../Engine/ortho.h"
#include "../CConfig.h"
#include "../Defines.h"

CPlayerSetupMenu::CPlayerSetupMenu(CMenu * pParent):CMenu("Player Setup",pParent)
{
//	m_cHelperText = "up&down navigates/ space enables or disables player / return modifies option / ESC exits";
	strcpy(m_cHelperText,"up&down navigates/ space enables or disables player / return modifies option / ESC exits");
	m_iCurrentRow = 0;
	m_pRows[0] = new CPlayerSetupRow(CApplication::m_pConfig->getPlayerSkin(0),
									 CApplication::m_pConfig->getPlayerKeySet(0),
									 CApplication::m_pConfig->isPlayerEnabled(0));

	m_pRows[1] = new CPlayerSetupRow(CApplication::m_pConfig->getPlayerSkin(1),
									 CApplication::m_pConfig->getPlayerKeySet(1),
									 CApplication::m_pConfig->isPlayerEnabled(1));
	
	m_pRows[2] = new CPlayerSetupRow(CApplication::m_pConfig->getPlayerSkin(2),
									 CApplication::m_pConfig->getPlayerKeySet(2),
									 CApplication::m_pConfig->isPlayerEnabled(2));
	
	m_pRows[3] = new CPlayerSetupRow(CApplication::m_pConfig->getPlayerSkin(3),
									 CApplication::m_pConfig->getPlayerKeySet(3),
									 CApplication::m_pConfig->isPlayerEnabled(3));
	
/*	m_pRows[1] = new CPlayerSetupRow();
	m_pRows[2] = new CPlayerSetupRow();
	m_pRows[3] = new CPlayerSetupRow();*/

	addMenuItem(m_pRows[0],CVector3(0.312,0.66,0));
	addMenuItem(m_pRows[1],CVector3(0.312,0.48,0));
	addMenuItem(m_pRows[2],CVector3(0.312,0.30,0));
	addMenuItem(m_pRows[3],CVector3(0.312,0.12,0));
	
	

}


CPlayerSetupMenu::~CPlayerSetupMenu()
{
/*	delete m_pRows[0];
	delete m_pRows[1];
	delete m_pRows[2];
	delete m_pRows[3];*/
}


void CPlayerSetupMenu::determineEnabledPlayerCount()
{
	m_iEnabledPlayerCount = 0;
	
	//determine the amount of enabled players
	for (int i = 0; i < 4;i++)
	{
		if (m_pRows[i]->isEnabled()) 
			m_iEnabledPlayerCount++;
	}
	
}

void CPlayerSetupMenu::storeSettings()
{
	int iPlayerCount = 0;
	
	//save all settings to the config Object
	for(int i=0; i < 4;i++)
	{
		CApplication::m_pConfig->setPlayerKeySet(i,m_pRows[i]->getKeySet());
		CApplication::m_pConfig->setPlayerSkin(i,m_pRows[i]->getSkin());
		CApplication::m_pConfig->setPlayerEnabled(i,m_pRows[i]->isEnabled());

		//determine active Player Count
		if  (m_pRows[i]->isEnabled())
			iPlayerCount++;
	}
	
	CApplication::m_pConfig->setPlayerCount(iPlayerCount);

	
}

void CPlayerSetupMenu::update()
{
	
//	(*m_itIterator)->setActive();
	for (int i = 0; i < (int)m_lMenuItems.size(); i++)
	{
		m_lMenuItems[i]->setActive(false);		
	}
	m_lMenuItems[m_iActiveItem]->setActive(true);
	determineEnabledPlayerCount();	
}

void CPlayerSetupMenu::draw()
{	

	// Draw MenuTitle
	CApplication::m_pTextDrawer->setSize(BIG);
	CApplication::m_pTextDrawer->drawTextCentered(0.5,0.90,m_cTitle);
	
	drawHelperText();
	
	CApplication::m_pTextDrawer->setSize(STD);
	
	//loop through all MenuItems and draw them
	vector <ptrMenuItem>::iterator it;
	for ( it = m_lMenuItems.begin(); it != m_lMenuItems.end(); it++)
	{
		(*it)->draw();
	}
	
	if ( m_iEnabledPlayerCount <= 1)
	{
		CApplication::m_pTextDrawer->setSize(STD);
		CApplication::m_pTextDrawer->drawTextCentered(0.5,0.84,"Please enable at least two players!");
	}
	
}


void CPlayerSetupMenu::up()
{
	if ( m_iActiveItem > 0 )
	{
//		((CPlayerSetupRow*)m_lMenuItems[m_iActiveItem])->setColumn(0);
		m_iActiveItem--;
		
	}
	else
		m_iActiveItem = (int)m_lMenuItems.size() -1;
}

void CPlayerSetupMenu::down()
{
	if ( m_iActiveItem < (int)m_lMenuItems.size() -1)
	{
//		((CPlayerSetupRow*)m_lMenuItems[m_iActiveItem])->setColumn(0);
		m_iActiveItem++;

	}
	else
		m_iActiveItem = 0;
	
}
void CPlayerSetupMenu::back()
{
	// only exit menu if at least two players are enabled
	if (m_iEnabledPlayerCount > 1)
		gotoParentMenu();
}

void CPlayerSetupMenu::space()
{
	CPlayerSetupRow * pSetupRow = (CPlayerSetupRow*)m_lMenuItems[m_iActiveItem];
	pSetupRow->toggleEnable();
}

