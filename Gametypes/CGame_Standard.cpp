/*
 *  CGame_Standard.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 15.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "CGame_Standard.h"
#include "../CApplication.h"
#include "../Engine/CSoundManager.h"
#include "../Menu/CScoreScreen.h"

#include "../Engine/CMeshManager.h"
#include "../MeshObjects/CPlayerMesh.h"

#include "../Map/CMap.h"
#include "../Objects/CPlayer.h"
#include "../Menu/CHUD.h"

CGame_Standard::CGame_Standard(CApplication * pApp):CGame(pApp)
{
	startNextRound();
}

CGame_Standard::~CGame_Standard()
{
}

void CGame_Standard::updateRunning()
{		
	//if no or only 1 Players are alive then ...
	if (m_iAlivePlayerCount <= 1   )
	{
		if (!m_bDeathBell)
		{	//...let the round end ahead of time, by reseting the timer
			m_tRoundTimer.setAlarm(3000);
			m_bDeathBell = true;
			m_pHUD->doDrawTime(false);

		}
	}
				
	//check if time is up !
	if ( m_tRoundTimer.isTimeUp() )
	{
		// check which player won
		m_iWinner = determineWinner();
		
		// time is Up ! generate a scorescreen & switch State to ScoreScreen
		m_pScoreScreen = new CScoreScreen(this);
		m_iState = SCORESCREEN;
		CApplication::m_pSoundManager->playMusic(SCORESCREEN_MUSIC,false);
	}
	//	return true;
}

void CGame_Standard::startNextRound()
{
	_startNextRound();
			
}

void CGame_Standard::drawRunning()
{
	
	
		
	
	CApplication::m_pMeshManager->m_pPlayerMesh->configureMaterial();
	CApplication::m_pMeshManager->m_pPlayerMesh->configureTexCoord0();
	CApplication::m_pMeshManager->m_pPlayerMesh->configureTexCoord1();

	CApplication::m_pMeshManager->m_pPlayerMesh->enableBuffers();

	//draw all Players
	for ( int i = 0; i < m_pApp->m_pConfig->getPlayerCount(); i++)
		m_pPlayer[i]->draw();
	
	CApplication::m_pMeshManager->m_pPlayerMesh->disableBuffers();
	CApplication::m_pMeshManager->m_pPlayerMesh->resetTextureEngines();
	
	//draw Map (including all explosions, particle FX, etc.)...
	m_pMap->draw();
	//....and above all the HUD
	m_pHUD->draw();
}
