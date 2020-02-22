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
#include "SDL/SDL.h"

#include "CApplication.h"
#include "CConfig.h"
#include "Gametypes/CGame.h"
#include "Gametypes/CGame_Standard.h"
#include "Gametypes/CGame_MapDestruction.h"

#include "Menu/CApplicationMenu.h"
#include "Engine/CCamera.h"
#include "Controller/CController_Keyboard.h"
#include "Controller/CController_Joystick.h"

#include "Engine/CInputManager.h"

#include "Map/CMapManager.h"
#include "Engine/CMeshManager.h"
#include "Engine/CTextureManager.h"
#include "Engine/CSoundManager.h"
#include "Engine/CTextDrawer.h"
#include "Engine/CScreenFader.h"
#include "Engine/framerateCalculator.h"
#include "Engine/Init.h"
#include "Engine/CClock.h"

#include "Engine/ortho.h"
#include <CoreFoundation/CoreFoundation.h>

#include "Defines.h"

#define FREECAMERA

CCamera			* CApplication::m_pCamera			= NULL;
CMeshManager	* CApplication::m_pMeshManager		= NULL;
CTextureManager * CApplication::m_pTextureManager	= NULL;
CMapManager		* CApplication::m_pMapManager		= NULL;
CSoundManager	* CApplication::m_pSoundManager		= NULL;
CApplication	* CApplication::m_pApplication		= NULL;
CTextDrawer		* CApplication::m_pTextDrawer		= NULL;
CScreenFader	* CApplication::m_pScreenFader		= NULL;
CInputManager *   CApplication::m_pInputManager		= NULL;
CConfig			* CApplication::m_pConfig			= NULL;
CClock			* CApplication::m_pClock			= NULL;
CGame			* CApplication::m_pGame				= NULL;


float			UPDATE_FPS = 30;
Uint32			TICK_TIME = (Uint32)(1000/UPDATE_FPS);// ( TICK_TIME = 1000/FPS)
int				MAX_LOOPS = 2;
float			CApplication::m_fReciprocalFPS	= 1/UPDATE_FPS; //( 1/FPS)
string			CApplication::m_strResourcePath	= string();

int CApplication::screenWidth  = 0;
int CApplication::screenHeight = 0;

io_connect_t  root_port;    // a reference to the Root Power Domain IOService

CApplication::CApplication()
{
	m_pApplication = this;
	determineBundlePath();	
	registerSleepCallBack();
}

CApplication::~CApplication()
{	
	
	if (m_pGame != NULL)
		delete m_pGame;

	delete m_pMainMenu; 
	delete m_pCamera;
	delete m_pInputManager;
	delete m_pMapManager;
	delete m_pTextureManager;
	delete m_pMeshManager;
	delete m_pSoundManager;
	delete m_pTextDrawer; 
	delete m_pScreenFader;
	delete m_pClock; 
	delete m_pConfig;
	
}

void CApplication::determineBundlePath()
{
	char path[1024];
	// Get a reference to Applications Bundle
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	assert(mainBundle);

	// get a reference to its URL
	CFURLRef mainBundleURL =  CFBundleCopyBundleURL (mainBundle);
//	CFURLRef mainBundleURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
	assert( mainBundleURL);

	// Convert URL to File System Path 
	CFStringRef cfStringRef = CFURLCopyFileSystemPath( mainBundleURL, kCFURLPOSIXPathStyle);
	assert( cfStringRef);
	
	// Conversion CFString ---> CString
	CFStringGetCString( cfStringRef, path, 1024, kCFStringEncodingASCII);
	
	strcat(path,"/Contents/Resources");

	CFRelease( mainBundleURL);
	CFRelease( cfStringRef);

	m_strResourcePath = string(path);

}

void CApplication::registerSleepCallBack()
{

    IONotificationPortRef  notifyPortRef;   // notification port allocated by IORegisterForSystemPower
    io_object_t            notifierObject;  // notifier object, used to deregister later
    void*                  refCon = NULL;          // this parameter is passed to the callback

    // register to receive system sleep notifications
    root_port = IORegisterForSystemPower( refCon, &notifyPortRef, CApplication::sleepCallBack, &notifierObject );
    if ( root_port == NULL )
    {
            printf("IORegisterForSystemPower failed\n");
    }

    // add the notification port to the application runloop
    CFRunLoopAddSource( CFRunLoopGetCurrent(),
                        IONotificationPortGetRunLoopSource(notifyPortRef),
                        kCFRunLoopCommonModes );

    /*
       Start the run loop to receive sleep notifications.  You don't need to
       call this if you already have a Carbon or Cocoa EventLoop running.
    */
 //   CFRunLoopRun();
}

void CApplication::sleepCallBack( void * refCon, io_service_t service, natural_t messageType, void * messageArgument)
{
	
	switch ( messageType )
    {

        case kIOMessageCanSystemSleep:
            /*
               Idle sleep is about to kick in.
               Applications have a chance to prevent sleep by calling IOCancelPowerChange.
               Most applications should not prevent idle sleep.

               Power Management waits up to 30 seconds for you to either allow or deny idle sleep.
               If you don't acknowledge this power change by calling either IOAllowPowerChange
               or IOCancelPowerChange, the system will wait 30 seconds then go to sleep.
            */

            
			// we will allow idle sleep
            IOAllowPowerChange( root_port, (long)messageArgument );
            break;

        case kIOMessageSystemWillSleep:
            /* The system WILL go to sleep. If you do not call IOAllowPowerChange or
                IOCancelPowerChange to acknowledge this message, sleep will be
               delayed by 30 seconds.

               NOTE: If you call IOCancelPowerChange to deny sleep it returns kIOReturnSuccess,
               however the system WILL still go to sleep.
            */
						
			// if we are not paused -> pause
			m_pApplication->startPause();	
            // we cannot deny forced sleep
            IOAllowPowerChange( root_port, (long)messageArgument );
            break;

		case kIOMessageSystemWillPowerOn:
			m_pApplication->m_bSuspendEvent = true;
			// Delay seems to be necessary for SDL_GetTicks to work properly (?)
			SDL_Delay(1000);
            /* The system WILL wake up*/
			break;
        default:			
            break;
		}
}

void CApplication::init()
{
	cout << "Starting MacBomber v. 0.5.1" << endl;

	//load Config first, since we need to know which screen resolution to use
	m_pConfig = new CConfig();
	m_pConfig->loadConfig();
			
	initSDL();
	initGL();
	sizeGLWindow();
	
	screenWidth  = m_pConfig->getScreenWidth();
	screenHeight = m_pConfig->getScreenHeight();

	
	m_pSoundManager = new CSoundManager();
		
	m_iState = MENU;
	m_pClock = new CClock();
		
	m_pCamera = new CCamera();
	m_pCamera->setPreset(m_pConfig->getCameraPreset());
	m_pMapManager = new CMapManager();

	m_pMeshManager = new CMeshManager();
	m_pTextureManager = new CTextureManager();
	m_pTextureManager->loadTextures();
	
	m_pTextDrawer = new CTextDrawer(); 
	m_pScreenFader = new CScreenFader();
	
	m_pInputManager = new CInputManager(this);	
	m_pMainMenu = new CApplicationMenu(this);
	
	m_bSuspendEvent = false;	
	setState(MENU);

	//initiate "random" number generator
	sranddev();

}

void CApplication::render()
{
//    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClear ( GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();      
	
#ifdef FREECAMERA	
	m_pCamera->setViewByMouse();
#endif
    m_pCamera->setView();
   
 
	switch (m_iState)
	{
		case MENU:
			m_pMainMenu->draw();
			break;
		case GAME_PAUSED:
		case GAME:
			m_pGame->draw();
			break;
		case QUIT:
			break;
	}

	SDL_GL_SwapBuffers( );		
}

void CApplication::startNewGame()
{
	// set Game state
	m_iState = GAME;
	
	//start Game - depending on selected gametype
	switch(m_pConfig->getGameType())
	{
		case 0:
			m_pGame = new CGame_Standard(this);	
			break;
		case 1:
			m_pGame = new CGame_MapDestruction(this);
			break;
		default:
			m_pGame = new CGame_Standard(this);	
			break;
	}
}

void CApplication::run()
{
	Uint32 time1 = SDL_GetTicks();
	Uint32 time0 = time1;
	int numLoops = 0; 

	while (m_iState != QUIT)
	{
#ifdef FREECAMERA
		Uint8 * keystate;
		keystate = SDL_GetKeyState ( NULL );
		
		if ( keystate [SDLK_a] == SDL_PRESSED )
		{
			m_pCamera->strafeCamera( -0.05f );
		}
		
		if ( keystate [SDLK_w] == SDL_PRESSED )
		{
			m_pCamera->moveCamera( 0.05f );
		}
		
		if ( keystate [SDLK_d] == SDL_PRESSED )
		{			
			m_pCamera->strafeCamera( 0.05f );
		}
		
		if ( keystate [SDLK_s] == SDL_PRESSED )
		{
			m_pCamera->moveCamera( -0.05f );
		}

		
#endif	
	//	calculateFramerate();
	
		time1 = SDL_GetTicks();
		numLoops = 0;

		/*Reset time values once after wake up from sleep.
		  This is needed because, the system doesn't go to sleep immediatley.
		  SDL could be running for a while, while MacBomber isn't updated anymore. This could
		  cause time1 and time0 values to be too small, upon awakening, because the SDL Ticks
		  was kept updated after MacBomber went to bed.   
		 */
		if (m_bSuspendEvent)
		{
				time1 = SDL_GetTicks();
				time0 = time1;
				m_bSuspendEvent = false;
		}
		
		while ( ((time1 - time0) > TICK_TIME) && (numLoops < MAX_LOOPS) )
		{
			m_pInputManager->update();
			switch (m_iState)
			{
				case MENU:
					m_pMainMenu->update();
					break;
				case GAME:
				case GAME_PAUSED:
					m_pGame->update();
					break;
				default:
					break;
			}		
			time0 += TICK_TIME;
			numLoops++;
			
	
		}
		render();
	}
}

void CApplication::pause()
{ 
	//only pause, when game is running
	switch(m_iState)
	{
		case GAME:
			startPause();
			break;
		case GAME_PAUSED:
			stopPause();
			break;
		default:
			break;
	}
}

void CApplication::startPause()
{
	//check needed for suspend event
	if (m_iState == GAME)
	{
		m_pGame->startPause();
		m_pClock->startPause();
		m_pSoundManager->pauseMusic();
		setState(GAME_PAUSED);
	}
}

void CApplication::stopPause()
{
	//if this method gets called while we are in Pause -> continue!
	m_pGame->stopPause();
	m_pClock->stopPause();
	m_pSoundManager->resumeMusic();
	m_iState = GAME;
}


void CApplication::setState(int state)
{
	m_iState = state;

	switch (state)
	{
		case MENU:
			if (m_pGame != NULL)
			{	
				delete m_pGame;
				m_pGame = NULL;
			}
			m_pSoundManager->playMusic(MENU_MUSIC);
			break;
		case GAME:
			m_pSoundManager->stopMusic();
			startNewGame();			
			break;
		case QUIT:
			// store which maps were enabled /disabled
			m_pMapManager->storeSettings();
			// store menu settings
			m_pMainMenu->storeSettings();
			// store camera settings 
			m_pConfig->setCameraPreset(m_pCamera->getPreset());
			// save everything to config (file)
			m_pConfig->saveConfig();
			break;
	}
}
