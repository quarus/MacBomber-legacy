/*
 *  CGame_MapDestruction.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 15.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CGame_MapDestruction_H
#define CGame_MapDestruction_H

#include "CGame.h"
#include "../Engine/CTimer.h"


class CApplication;
class CMapDestroyer;

class CGame_MapDestruction:public CGame
{
private:	
	//the guy, which knocks out the fields one by one
	CMapDestroyer * m_pMapDestroyer;
	//is the mapDestroyer active ?
	bool m_bMapDestroyerActive;
	void updateRunning();
	void drawRunning();
	
	CTimer m_tRoundTimer2;

public:
	CGame_MapDestruction(CApplication * pApp);
	~CGame_MapDestruction();

	void startNextRound();

};
#endif
