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

#include <math.h>
#include <GLUT/glut.h>

#include "CSimpleBezier.h"

CSimpleBezier::CSimpleBezier()
{
	m_pControlPoints = new CVector3[3];
	m_pControlPoints[0] = CVector3(1,0,2);
	m_pControlPoints[1] = CVector3(10,14,2);
	m_pControlPoints[2] = CVector3(19,0,13);

	
	m_iControlPointCount = 3;
	
	
}

CSimpleBezier::CSimpleBezier(CVector3 vPoint0, CVector3 vPoint1, CVector3 vPoint2)
{
	
	m_pControlPoints = new CVector3[3];
	m_pControlPoints[0] = vPoint0;
	m_pControlPoints[1] = vPoint1;
	m_pControlPoints[2] = vPoint2;
	
	m_iControlPointCount = 3;
	
}


CSimpleBezier::CSimpleBezier( CVector3 vPoint0, CVector3 vPoint1, CVector3 vPoint2, CVector3 vPoint3)
{
	
	m_pControlPoints = new CVector3[4];
	m_pControlPoints[0] = vPoint0;
	m_pControlPoints[1] = vPoint1;
	m_pControlPoints[2] = vPoint2;
	m_pControlPoints[3] = vPoint3;
	
	m_iControlPointCount = 4;

}

CSimpleBezier::~CSimpleBezier()
{
	delete [] m_pControlPoints;
}

CVector3 CSimpleBezier::calculatePoint(float t)
{
	if ( t > 1)
		t = 1;
	
	CVector3 returnValue;
	
	for ( int i = 0; i < m_iControlPointCount; i++)
	{
		returnValue = returnValue +( m_pControlPoints[i] * calculateBernsteinPolynomial(t, i));
	}
	
	return returnValue;
}


int CSimpleBezier::calculateFactorial(int number)
{
	if ( number <= 1 )
		return 1;
	
	return number * calculateFactorial(number-1);
}


int CSimpleBezier::calculateBinomialCoefficient(int n, int k)
{
	if (k==0)
	{
		return 1;
	}
	
	
	int numerator	= calculateFactorial(n);
	int denominator = calculateFactorial(k) * calculateFactorial(n-k); 
	
	return ( numerator / denominator);
}


float CSimpleBezier::calculateBernsteinPolynomial(float t, int i)
{
	int n = m_iControlPointCount-1;
	
	int binCoeffi = calculateBinomialCoefficient(n, i);
	float rest = pow(t,i) * pow((1-t),n-i); 
	
	return binCoeffi * rest; 
}

void CSimpleBezier::draw()
{
	glLineStipple (3, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);

	// Zeichne Kontrollpolygonzug
	glBegin(GL_LINE_STRIP);
		glColor3f(1.0f, 1.0f,0.0f);

		for(int i = 0; i < m_iControlPointCount; i++)
			glVertex3f(m_pControlPoints[i].x,m_pControlPoints[i].y,m_pControlPoints[i].z);
		glEnd();
	glDisable(GL_LINE_STIPPLE);
	
	// Zeichne "Kurve"
	float t = 0.0f;
	CVector3 tmp;
	glColor3f(0.0f, 1.0f,0.0f);
	glBegin(GL_LINE_STRIP);		
		
		for ( int i = 0; i < 11; i++)
		{
			tmp = calculatePoint(t);
			glVertex3f(tmp.x, tmp.y, tmp.z);
			t += 0.1f;
		}
		
	glEnd();

}


