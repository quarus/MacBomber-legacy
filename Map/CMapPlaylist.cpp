/*
 *  CMapPlaylist.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 06.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "../CApplication.h"
#include "../CConfig.h"

#include "CMapPlaylist.h"

CMapPlaylist::CMapPlaylist()
{
	m_bRandom = CApplication::m_pConfig->getRandomMapOrder();
	m_iTotalMapCount = 0;
	m_itCurrent = m_vMapEntryIndices.begin();
}

void CMapPlaylist::addMapIndex(int index)
{	
	m_iTotalMapCount++;
	if (m_bRandom)
	{
		if  (m_vMapEntryIndices.size() == 0)
		{
			m_vMapEntryIndices.push_back(index);
		}
		else
		{
			//insert index at a random postion within the vector
			int iPosition = rand()%m_vMapEntryIndices.size();
			vector<int>::iterator it = m_vMapEntryIndices.begin();
			it+=iPosition;
			m_vMapEntryIndices.insert(it,index);
		}
		
	}
	else
		m_vMapEntryIndices.push_back(index);
	
	m_itCurrent = m_vMapEntryIndices.begin();

}

void CMapPlaylist::setNextMapIndex()
{
	// Did we reach the end of the vector ?
	if (m_itCurrent+1 == m_vMapEntryIndices.end())
		m_itCurrent = m_vMapEntryIndices.begin();
	else
		m_itCurrent++;	
	
}

int CMapPlaylist::getCurrentMapIndex()
{
	return *m_itCurrent;
}

void CMapPlaylist::showIndices()
{
	vector<int>::iterator it;
	for ( it = m_vMapEntryIndices.begin(); it != m_vMapEntryIndices.end();it++)
	{
		printf("%d\n",*it);
	}
	printf("\n");
}

