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
#ifndef CPlayerSetupMenu_H
#define CPlayerSetupMenu_H

#include "CMenu.h"

class CPlayerSetupRow;

class CPlayerSetupMenu :public CMenu
{
private:
	int m_iCurrentRow;
	CPlayerSetupRow * m_pRows[4];
	
	int m_iEnabledPlayerCount;
	// determines the amount of enabled players
	void determineEnabledPlayerCount();
	
public:
	CPlayerSetupMenu(CMenu * pParent);
	~CPlayerSetupMenu();
	
	void storeSettings();
	void update();
	void draw();
	
	void up();
	void down();
	/*void left();
	void right();
	void enter();*/
	void back();
	void space();

	
};
#endif
