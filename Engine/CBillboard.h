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

#ifndef Billboard_h
#define Billboard_h
class CVector3;
class CCamera;

void createBillboardMatrix(const CVector3 & vPos,const CVector3 & vLook, 
						   const CVector3 & vUp, const CVector3 & vRight,
						   float * pMatrix);

void calculateBillboardMatrix_Point(const CVector3 & vPos,float * pMatrix);
void calculateBillboardMatrix_Xaxis(const CVector3 & vPos,float * pMatrix);
void calculateBillboardMatrix_Yaxis(const CVector3 & vPos,float * pMatrix);
void calculateBillboardMatrix_Zaxis(const CVector3 & vPos,float * pMatrix);

#endif
