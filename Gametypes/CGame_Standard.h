/*
 *  CGame_Standard.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 15.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CGame_Standard_H
#define CGame_Standard_H

#include "CGame.h"

class CApplication;

class CGame_Standard:public CGame
{
private:
	void updateRunning();
	void drawRunning();

public:
	CGame_Standard(CApplication * pApp);
	~CGame_Standard();
	
	void startNextRound();

};

#endif