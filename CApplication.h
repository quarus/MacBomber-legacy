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

#ifndef CApplication_H
#define CApplication_H

#include <string>

#include <mach/mach_port.h>
#include <mach/mach_interface.h>
#include <mach/mach_init.h>
#include <IOKit/pwr_mgt/IOPMLib.h>
#include <IOKit/IOMessage.h>

using namespace std;

class CClock;
class CGame;
class CCamera;
class CController;
class CInputManager;
class CMapManager;
class CTextureManager;
class CSoundManager;
class CTextDrawer;
class CScreenFader;
class CMeshManager;
class CConfig;
class CApplicationMenu;


class CApplication
{
private:
	

	// definition of states in which the Application can be. 
	enum state{MENU=0, GAME, GAME_PAUSED, QUIT};
	//the current State the application is in
	int m_iState;
	void render();
	//starts a new Game
	void startNewGame();

	//determines the Path of the .app Bundle in MacOS 
	void determineBundlePath();	
	//registers the callback "sleepCallback"  to receive system sleep notifications
	void registerSleepCallBack();
	/*	callback function: gets called when Mac OS wants to sleep.
		see http://developer.apple.com/qa/qa2004/qa1340.html
	*/
	static void sleepCallBack(void * refCon, io_service_t service, natural_t messageType, void * messageArgument);

public:
		
	/* The following Vars are Pointers to Game Classes. By making them static, we can easily access them
		by using CApplication::m_p........
		*/
		
		
	// The reciprocal Value of the FPS. Used for time Based Movement throughout the game
	static float m_fReciprocalFPS;

	CApplicationMenu * m_pMainMenu;
	static CClock * m_pClock;
	static CGame * m_pGame;
	static CCamera * m_pCamera;
	static CMeshManager * m_pMeshManager;
	static CTextureManager * m_pTextureManager;
	static CTextDrawer * m_pTextDrawer;
	static CScreenFader * m_pScreenFader;
	static CMapManager * m_pMapManager;
	static CInputManager * m_pInputManager;
	static CConfig * m_pConfig;
	static CSoundManager * m_pSoundManager;

	// this pointer is needed for the static callback function "sleepCallBack" 
	static CApplication * m_pApplication;

	static string m_strResourcePath;
	
	bool m_bSuspendEvent;

	// Display resolution. These values are read once from config and the used throughout the game
	// (can be discarded, when ingame resolution switching is done)
	static int screenWidth;
	static int screenHeight;
	
	CApplication();
	~CApplication();

	void init();	
	void run();
	
	//gets called when pause key was pressed
	void pause();
	
	//gets called whenever application should be paused
	void startPause();
	void stopPause();
	
	
	//sets a state
	void setState(int state);
};

#endif
