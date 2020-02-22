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

#ifndef CApplicationMenu_H
#define CApplicationMenu_H

class CMenu;
class CMenuItem;
class CToggleItem;
class CMenuSwitchItem;
class CTimer;


class CApplicationMenu
{
private:
	CMenu * m_pMainMenu;					//the menu, with which the player ist greeted
		CMenu * m_pStartgameMenu;			//the menu, which is used to start a game
		CMenu * m_pOptionsMenu;				//Optionsmenu
			CMenu * m_pGoodieslimitMenu;		//set the maxmimum amount of collectible Goodies
			CMenu * m_pGoodiesMenu;				//Enable/Disable Goodies
			CMenu * m_pBadiesMenu;				//Enable/Disable Badies
		CMenu *	m_pPlayerSetupMenu;			//select playerskins and inputkeys. enable/disable player
		CMenu * m_pSoundSetupMenu;			
		CMenu *	m_pVideoSetupMenu;
		CMenu * m_pLevelSelectionMenu;
		CMenu *	m_pCredits;					//a menu consisting of textlabels and one back "switchitem"
	
	//Pointer to Menuitems. Used to retrieve the menuitem values 
	CMenuItem * m_pQuitGameMenuItem;
			
	CMenuItem * m_pStartGameMenuItem;
	CMenuItem * m_pRoundTimeMenuItem;
	CMenuItem * m_pPointsToWinMenuItem;
	CMenuItem * m_pRandomMapOrderMenuItem;
	CMenuItem * m_pGameTypeMenuItem;
	
	CMenuItem * m_pStartBombsMenuItem;
	CMenuItem * m_pStartPowerMenuItem;
	CMenuItem * m_pStartSpeedMenuItem;
	CMenuItem * m_pStartKickMenuItem;
	CMenuItem * m_pExtraBombsMenuItem;
	CMenuItem * m_pExtraPowerMenuItem;
	CMenuItem * m_pExtraSpeedMenuItem;
	
	CMenuItem * m_pToggleBombUpMenuItem;
	CMenuItem * m_pTogglePowerUpMenuItem;
	CMenuItem * m_pToggleSpeedUpMenuItem;
	CMenuItem * m_pToggleKickMenuItem;

	CMenuItem * m_pToggleJointMenuItem;
	CMenuItem * m_pToggleViagraMenuItem;
	CMenuItem * m_pToggleCocaineMenuItem;
	CMenuItem * m_pToggleCondomMenuItem;
	
	CMenuItem * m_pToggleSoundFXItem;
	CMenuItem * m_pToggleMusicItem;
	CMenuItem * m_pSoundFXVolumeItem;
	CMenuItem * m_pMusicVolumeItem;
	
	CMenuItem * m_pToggleResolutionItem;
	CMenuItem * m_pToggleFullscreenItem;
	
	
	//Pointer pointing to the Main application
	CApplication * m_pApp;

	//used to determine when Input repetition should be activated
	//( so that the user just to hold for e.g down to navigate down a menu) 
	CTimer * m_pActivateRepetitionTimer;
	
	void handleInput();
public:
	//creates Menuelement and initializes them according to Config
	CApplicationMenu(CApplication * pApp);
	~CApplicationMenu();

	// saves the values of the GUI Elements to the config object 
	void storeSettings();

	void update();
	void draw();
};

#endif
