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

#include "CTimer.h"
#include "../CApplication.h"
#include "CClock.h"
CTimer::CTimer()
{
	m_iAlarmTime = 0;
//	m_iStartTime = SDL_GetTicks();
	m_iStartTime = CApplication::m_pClock->getTicks();
}

CTimer::CTimer(uint alarm)
{
//	m_iAlarmTime = SDL_GetTicks() + alarm;
	m_iAlarmTime = CApplication::m_pClock->getTicks() + alarm;
}


bool CTimer::isTimeUp()
{
//	if ( SDL_GetTicks() > m_iAlarmTime )
	if ( CApplication::m_pClock->getTicks() > m_iAlarmTime )
		return true;
	else
		return false;
}

void CTimer::setAlarm(uint alarmTime)
{
//	m_iAlarmTime = SDL_GetTicks() + alarmTime;
//	m_iStartTime = SDL_GetTicks();

	m_iAlarmTime = CApplication::m_pClock->getTicks() + alarmTime;
	m_iStartTime = CApplication::m_pClock->getTicks();


}

uint CTimer::getElapsedTime()
{
//	return SDL_GetTicks() - m_iStartTime;
	return CApplication::m_pClock->getTicks() - m_iStartTime;
}


