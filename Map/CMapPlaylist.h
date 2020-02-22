/*
 *  CMapPlaylist.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 06.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include <vector>
using namespace std;

class CMapPlaylist
{
private:
	//shall the playlist entries be shuffled
	bool m_bRandom;
	int m_iTotalMapCount;
	vector<int> m_vMapEntryIndices;	
	vector<int>::iterator m_itCurrent;
public:
	CMapPlaylist();
	
	//adds an MapEntry to the playlist
	void addMapIndex(int index);
	void setNextMapIndex();
	//returns an index of the next map to play 
	int getCurrentMapIndex();
	
	void showIndices();
};
