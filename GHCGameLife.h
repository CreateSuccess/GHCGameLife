#ifndef __GHC_GAME_LIFE_H
#define __GHC_GAME_LIFE_H

/***************************************************************************
 * Copyright (c) 1996 - 2020, Wang jianbin, <869538952@qq.com>
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
#include <string>
#include <iostream>

namespace ghcGameLife
{

enum CoordinateStatus
{
	COORDINATE_STATUS_ALIVE = 1,
	COORDINATE_STATUS_DEATH,
	COORDINATE_STATUS_NON_SPACE,
	COORDINATE_STATUS_NON_MAX,
};

typedef struct {
	CoordinateStatus *Map;
	unsigned long ulMapSideLength;
}GHCGameLifeData;

class GHCGameLife
{

public:
	GHCGameLife(); 
	GHCGameLife(unsigned long ulMapSideLength); 
	GHCGameLife(GHCGameLifeData GHCGameLifeData);
	~GHCGameLife();


public:
	std::string GetLifeMap();
	void SkipOverTime(unsigned long ulTime);
	void ExportGameLife(GHCGameLifeData &GHCGameLifeData);
	void RandSetNoSpace();

private:
	void CreateMap();
	void RandomSetMap();
	void SkipOneTime();
	int WhetherAlive(unsigned long ulCoordinatesX, unsigned long ulCoordinatesY);

private:
	unsigned long m_ulMapSideLength;
	unsigned long m_ulTime;
	CoordinateStatus *m_mapLife;
	CoordinateStatus *m_mapNextTimeLife;
};


}



#endif


#pragma once
