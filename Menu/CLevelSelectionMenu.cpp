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


#include "CLevelSelectionMenu.h"
#include "CLevelScrollListItem.h"
#include "CMapPreview.h"
#include "../Menu/CToggleItem.h"
#include "../Engine/ortho.h"
#include "../Engine/CTextDrawer.h"
#include "../Map/CMapManager.h"
#include "../CApplication.h"
#include "../Defines.h"


CLevelSelectionMenu::CLevelSelectionMenu(CMenu * pParent):CMenu("Map Selection",pParent)
{
//	m_cHelperText = "up&down keys select a map / space enables or disables a map / ESC exits";
	strcpy(m_cHelperText,"up&down keys select a map / space enables or disables a map / ESC exits");
	m_pLevelScrollList = new CLevelScrollListItem(); 
	addMenuItem(m_pLevelScrollList,CVector3(0,0.7,0));
	
	m_pEnableAllMenuItem = new CToggleItem("Enable all Maps");
	m_pEnableAllMenuItem->addOption(" ",0);
	m_pEnableAllMenuItem->addOption(" ",1);
	addMenuItem(m_pEnableAllMenuItem,CVector3(0.0625,0.1,0));

	m_pDisableAllMenuItem = new CToggleItem("Disable all Maps");
	m_pDisableAllMenuItem->addOption(" ",0);
	m_pDisableAllMenuItem->addOption(" ",1);
	addMenuItem(m_pDisableAllMenuItem,CVector3(0.4,0.1,0));


	
	m_pMapPreview = new CMapPreview();
	m_pMapPreview->setMap(CApplication::m_pMapManager->getMap(m_pLevelScrollList->getValue()));
}

CLevelSelectionMenu::~CLevelSelectionMenu()
{
	delete m_pMapPreview;
}

void CLevelSelectionMenu::update()
{
	for (int i = 0; i < (int)m_lMenuItems.size(); i++)
	{
		m_lMenuItems[i]->setActive(false);

	}
	m_lMenuItems[m_iActiveItem]->setActive(true);
	
	if (m_pEnableAllMenuItem->getValue() == 1)
	{
		CApplication::m_pMapManager->enableAll();
		m_pEnableAllMenuItem->setValue(0); 
	}
	

	if (m_pDisableAllMenuItem->getValue() == 1)
	{
		CApplication::m_pMapManager->disableAll();
		m_pDisableAllMenuItem->setValue(0); 
	}

			
}

void CLevelSelectionMenu::up()
{
	m_lMenuItems[m_iActiveItem]->down();
	m_pMapPreview->setMap(CApplication::m_pMapManager->getMap(m_pLevelScrollList->getValue()));
}

void CLevelSelectionMenu::down()
{
	m_lMenuItems[m_iActiveItem]->up();
	m_pMapPreview->setMap(CApplication::m_pMapManager->getMap(m_pLevelScrollList->getValue()));
}

void CLevelSelectionMenu::left()
{
	//FIX ME: we could simply call the up function of the base class
	if (m_iActiveItem >  0)
		m_iActiveItem--;
}

void CLevelSelectionMenu::right()
{
	//FIX ME: we could simply call the down function of the base class
	if (m_iActiveItem <  (int)m_lMenuItems.size()-1  )
		m_iActiveItem++;
}

void CLevelSelectionMenu::back()
{
	//only go back if at least one map is selected !
	if ( CApplication::m_pMapManager->getEnabledMapCount() > 0)
		gotoParentMenu();
}

void CLevelSelectionMenu::draw()
{
	
	CApplication::m_pTextDrawer->setSize(BIG);
	CApplication::m_pTextDrawer->drawTextCentered(0.5,0.90,m_cTitle);	
	CApplication::m_pTextDrawer->setSize(STD);
	
	drawHelperText();
	//draw a warning if no map is selected
	if ( CApplication::m_pMapManager->getEnabledMapCount() < 1)
		CApplication::m_pTextDrawer->drawTextCentered(0.5,0.83,"Please enable at least one map!");
	
	//loop through all MenuItems and draw them
	vector <ptrMenuItem>::iterator it;
	for ( it = m_lMenuItems.begin(); it != m_lMenuItems.end(); it++)
	{
		(*it)->draw();
	}
	
	// Draw a 3D preview of the currently selected Map. 
	// Therefore we need to get out of Ortho Mode
	disableOrthoMode();
		m_pMapPreview->draw();
	enableOrthoMode();
	
	
	
}



