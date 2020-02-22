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

#include "CSoundManager.h"
#include "../Defines.h"
#include "../CConfig.h"
#include "../CApplication.h"

#include <iostream.h>

CSoundManager::CSoundManager()
{	
	m_Samples[EXPlOSION_SOUND] = Mix_LoadWAV(expand("/Sounds/explode.wav"));
	m_Samples[PUTBOMB_SOUND] = Mix_LoadWAV(expand("/Sounds/putbomb.wav"));
	m_Samples[CRUNCH_SOUND] = Mix_LoadWAV(expand("/Sounds/crunch.wav"));
	
	m_Music[MENU_MUSIC] = Mix_LoadMUS(expand("/Sounds/macbomber_theme.mp3"));
	m_Music[SCORESCREEN_MUSIC] = Mix_LoadMUS(expand("/Sounds/macbomber_fanfare.mp3"));
	m_Music[GAME_MUSIC] = Mix_LoadMUS(expand("/Sounds/macbomber_game.mp3"));

	m_bMusicPlaying = false;
	m_bLoopMusic = false;;
	m_bMusicWaiting = false;
	Mix_HookMusicFinished(CSoundManager::musicDone);
	

}

CSoundManager::~CSoundManager()
{
	Mix_FreeChunk(m_Samples[EXPlOSION_SOUND]);
	Mix_FreeChunk(m_Samples[PUTBOMB_SOUND]);
	
	Mix_HaltMusic();
	Mix_FreeMusic(m_Music[MENU_MUSIC]);
	Mix_FreeMusic(m_Music[SCORESCREEN_MUSIC]);
	Mix_FreeMusic(m_Music[GAME_MUSIC]);

}


const char * CSoundManager::expand(char * path)
{
	string tmp = CApplication::m_strResourcePath;
	tmp = tmp + path;
	
	return tmp.c_str(); 
}

void CSoundManager::musicDone()
{
	
	CApplication::m_pSoundManager->handelMusicDone();
}


void CSoundManager::setVolumeSoundFX(int vol)
{
	// Maximum: 125; 125/ 5 = 25
	Mix_Volume(-1,25*vol);

}

void CSoundManager::setVolumeMusic(int vol)
{
	//Maximum: 128; 128 / 5 ~= 25
	Mix_VolumeMusic(25 * vol);
}

void CSoundManager::playSoundFX(int nr)
{
	//Only Play if Sound is enabled
	if (CApplication::m_pConfig->getSoundFX() )
		Mix_PlayChannel(-1,m_Samples[nr], 0);
}

void CSoundManager::handelMusicDone()
{
	if (m_bMusicWaiting)
	{
		Mix_FadeInMusic(m_Music[m_iCurrentMusic], m_bLoopMusic?-1:1, 500);
		m_bMusicPlaying = true;
	}
	else
		m_bMusicPlaying = false;

	m_bMusicWaiting = false;
}

void CSoundManager::playMusic(int nr,bool bLoop)
{
	//Only startMusic if Music is enabled
	if (!CApplication::m_pConfig->getMusic() )
		return;
	
	m_iCurrentMusic = nr;
	m_bLoopMusic = bLoop;
	// Music is already playing.
	// ->stop current Music
	if (m_bMusicPlaying)
	{
		m_bMusicWaiting = true;
		stopMusic();
	}
	else //if there is no Music playing. grant request
	{
		m_bMusicPlaying = true;
		m_bMusicWaiting = false;
		Mix_FadeInMusic(m_Music[m_iCurrentMusic], m_bLoopMusic?-1:1, 500);
	}

}

void CSoundManager::stopMusic()
{
	Mix_FadeOutMusic(500);
}


void CSoundManager::pauseMusic()
{
	Mix_PauseMusic();
}

void CSoundManager::resumeMusic()
{
	Mix_ResumeMusic();
}

