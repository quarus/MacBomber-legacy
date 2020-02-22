/*
 *  CGame_MapDestruction.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 15.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "CGame_MapDestruction.h"
#include "../CApplication.h"
#include "../Engine/CSoundManager.h"
#include "../Menu/CScoreScreen.h"

#include "../Engine/CMeshManager.h"
#include "../MeshObjects/CPlayerMesh.h"

#include "../Map/CMapDestroyer.h"
#include "../Map/CMap.h"
#include "../Objects/CPlayer.h"
#include "../Menu/CHUD.h"


CGame_MapDestruction::CGame_MapDestruction(CApplication * pApp):CGame(pApp)
{
	m_pMapDestroyer = NULL;
	m_bMapDestroyerActive = false;
	startNextRound();
}


CGame_MapDestruction::~CGame_MapDestruction()
{
	if(m_pMapDestroyer != NULL)
		delete m_pMapDestroyer;
}

void CGame_MapDestruction::updateRunning()
{
	if (m_bMapDestroyerActive)
	{
		m_pMapDestroyer->update();
		//if no or only 1 Players are alive then ...
		if (m_iAlivePlayerCount <= 1)
		{
			if (!m_bDeathBell)
			{	//...let the round end ahead of time, by reseting the timer
				m_tRoundTimer.setAlarm(3000);
				m_bDeathBell = true;
			}
			else
			if (m_tRoundTimer.isTimeUp())
			{			
				m_iWinner = determineWinner();
				
				m_pScoreScreen = new CScoreScreen(this);
				m_iState = SCORESCREEN;
				CApplication::m_pSoundManager->playMusic(SCORESCREEN_MUSIC,false);
			}
		}
		
	}
	else
	{
		//if no or only 1 Players are alive then ...
		if (m_iAlivePlayerCount <= 1)
		{
			if (!m_bDeathBell)
			{	//...let the round end ahead of time, by reseting the timer
				m_tRoundTimer.setAlarm(3000);
				m_bDeathBell = true;

			}
			m_pHUD->doDrawTime(false);

		}
		
		//check if time is up !
		if ( m_tRoundTimer.isTimeUp() ) 
		{
			if (m_bDeathBell)
			{
				m_iWinner = determineWinner();
				m_pScoreScreen = new CScoreScreen(this);
				m_iState = SCORESCREEN;
				CApplication::m_pSoundManager->playMusic(SCORESCREEN_MUSIC,false);
			}
			else
			{
				m_bDeathBell = false;
				m_bMapDestroyerActive = true;
				m_pMapDestroyer = new CMapDestroyer(m_pMap);
				m_pHUD->doDrawTime(false);
			}

		}
		//	return true;
		
	}
}

void CGame_MapDestruction::startNextRound()
{
	if (m_pMapDestroyer != NULL)
	{
		delete m_pMapDestroyer;
		m_pMapDestroyer = NULL;
	}
	m_bMapDestroyerActive = false;
	_startNextRound();
	
//	m_pMapDestroyer = new CMapDestroyer(m_pMap);
}

void CGame_MapDestruction::drawRunning()
{	
	CApplication::m_pMeshManager->m_pPlayerMesh->configureMaterial();
	CApplication::m_pMeshManager->m_pPlayerMesh->configureTexCoord0();
	CApplication::m_pMeshManager->m_pPlayerMesh->configureTexCoord1();
	CApplication::m_pMeshManager->m_pPlayerMesh->enableBuffers();

	//draw all Players (excluding smoke)
	for ( int i = 0; i < m_pApp->m_pConfig->getPlayerCount(); i++)
		m_pPlayer[i]->draw();
	
	CApplication::m_pMeshManager->m_pPlayerMesh->disableBuffers();
	CApplication::m_pMeshManager->m_pPlayerMesh->resetTextureEngines();

	
	//now draw all smoke Player Particlesystems
/*	for ( int i = 0; i < m_pApp->m_pConfig->getPlayerCount(); i++)
		m_pPlayer[i]->drawSmoke();*/
	
	
	//draw all Explosions & Item Particles
	m_pMap->drawExplosions();

	//draw the map
	m_pMap->draw();

	if (m_bMapDestroyerActive)
		m_pMapDestroyer->draw();	
	
	m_pHUD->draw();
}
