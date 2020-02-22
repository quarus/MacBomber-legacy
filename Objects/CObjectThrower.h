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

#ifndef CObjectThrower_H
#define CObjectThrower_H

#include "CVector3.h"

class CSimpleBezier;
class CObject_Moving;

class CObjectThrower
{
private:

	// the speed with which the object travels along the path
	float m_fVelocity;
	
	CObject_Moving * m_pObject;
	CSimpleBezier * m_pBezier;
	
	//these vectors describe the objects trajectory
	int m_iWayPointCount;
	CVector3 * m_pPath;

	// the index of the waypoint the object is traveling to
	int m_iCurrentWayPoint;

	// this is the length of the way between origin and destination
	float m_fLength;
	// tells us how far we already traveled (0 to m_fLength)
	float m_fLengthTraveled;
	
	bool m_bDone; // True wenn das Objekt ihr Ziel erreicht hat
	CVector3 m_vObjectPosition;
	CVector3 m_vDisplacement;
	
	//Calculates waypoints based on a Bezier Curve
	void calculateWayPoints(CVector3 vStart, CVector3 vEnd);

	//Calculates Displacment vector of the objects and the number of of times move() should be called
	void calculateParameters();
	
public:
	CObjectThrower(CVector3 vStart, CVector3 vEnd, CObject_Moving * pObject);
	~CObjectThrower();

	CVector3 getObjectPosition(){return m_vObjectPosition;};
	CVector3 getDisplacement(){return m_vDisplacement;};
	
	void setVelocity(float velocity){m_fVelocity = velocity;};
	bool isDone(){return m_bDone;};
	void update();
	
	void draw();
};

#endif

