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

#ifndef CPlayerSetupRow_H
#define CPlayerSetupRow_H

#include "CMenuItem.h"

class CToggleItem;

class CPlayerSetupRow:public CMenuItem
{
private:
	int m_iYPos;
	// Each Row has iCurrentItem ToggleItems
	int m_iCurrentItem;
	CToggleItem * m_pToggleItem[2];
	
	// Is this row enabled ?
	bool m_bEnabled;

public:
	CPlayerSetupRow(int skin=0, int keyset=0, bool bEnabled=false);
	~CPlayerSetupRow();

	void toggleEnable();
	void setColumn(int nr){m_iCurrentItem = nr;};
	int  getColumn(){return m_iCurrentItem;};
	void setPosition(CVector3 vPos);

	//return the selected Skin /Key of this row
	int getKeySet();
	int getSkin();
	// is this row enabled ?
	bool isEnabled(){return m_bEnabled;};

	void enter();
	void left();
	void right();
	

	void draw();
	
};

#endif
