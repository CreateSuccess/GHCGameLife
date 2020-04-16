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

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "GHCGameLife.h"

#define DEFAULT_MAPSIDELENGTH (9)

namespace ghcGameLife
{

GHCGameLife::GHCGameLife()
{
	m_ulMapSideLength = DEFAULT_MAPSIDELENGTH;
	m_ulTime = 0;
	m_mapLife = 0;
	CreateMap();
	RandomSetMap();
}

GHCGameLife::GHCGameLife(unsigned long ulMapSideLength)
{
	m_ulMapSideLength = ulMapSideLength;
	m_ulTime = 0;
	m_mapLife = 0;
	CreateMap();
	RandomSetMap();
}

GHCGameLife::GHCGameLife(GHCGameLifeData GHCGameLifeData)
{
	m_ulMapSideLength = GHCGameLifeData.ulMapSideLength;
	m_ulTime = 0;
	m_mapLife = 0;
	CreateMap();
	memcpy(m_mapLife, GHCGameLifeData.Map, m_ulMapSideLength * m_ulMapSideLength * sizeof(CoordinateStatus));
}

GHCGameLife::~GHCGameLife()
{
	if (m_mapLife)
	{
		free(m_mapLife);
	}
	if (m_mapNextTimeLife)
	{
		free(m_mapNextTimeLife);
	}
}

void GHCGameLife::ExportGameLife(GHCGameLifeData &GHCGameLifeData)
{
	GHCGameLifeData.ulMapSideLength = m_ulMapSideLength;
	GHCGameLifeData.Map = (CoordinateStatus *)calloc(m_ulMapSideLength, m_ulMapSideLength * sizeof(CoordinateStatus));
	memcpy(GHCGameLifeData.Map, m_mapLife, m_ulMapSideLength * m_ulMapSideLength * sizeof(CoordinateStatus));
}

std::string GHCGameLife::GetLifeMap()
{
	std::string Map;
	for (unsigned long i = 0; i < m_ulMapSideLength; i++)
	{
		char buf[10] = { 0 };
		snprintf(buf, sizeof(buf), "%02lu ", i + 1);
		Map += buf;
	}
	Map += "\n";
	for (unsigned long i = 0; i < m_ulMapSideLength; i++)
	{
		char buf[10] = { 0 };
		snprintf(buf, sizeof(buf), "___");
		Map += buf;
	}
	Map += "\n";
	for (unsigned long i = 0; i < m_ulMapSideLength * m_ulMapSideLength; i++)
	{
		unsigned long ulCoordinatesNodeX = 0, ulCoordinatesNodeY = 0;

		ulCoordinatesNodeY = (i + 1) / m_ulMapSideLength + (0 == (i + 1) % m_ulMapSideLength ? 0 : 1);
		ulCoordinatesNodeX = (i + 1) - m_ulMapSideLength * (ulCoordinatesNodeY - 1);

		switch (m_mapLife[i])
		{
		case COORDINATE_STATUS_ALIVE:
			Map += "L  ";
			break;
		case COORDINATE_STATUS_DEATH:
			Map += "   ";
			break;
		case COORDINATE_STATUS_NON_SPACE:
			Map += "X  ";
			break;
		}
		if (0 == (i+1) % m_ulMapSideLength && 0 != i)
		{
			char buf[10] = { 0 };
			snprintf(buf, sizeof(buf), "| %02lu\n", ulCoordinatesNodeY);
			Map += buf;
		}
	}
	return Map;
}

int GHCGameLife::WhetherAlive(unsigned long ulCoordinatesX, unsigned long ulCoordinatesY)
{
	if (ulCoordinatesX <= 0 || ulCoordinatesX > m_ulMapSideLength ||
		ulCoordinatesY <= 0 || ulCoordinatesY > m_ulMapSideLength)
	{
		return 0;
	}

	unsigned long site = ((ulCoordinatesY - 1) * m_ulMapSideLength) + (ulCoordinatesX - 1);

	//if (m_mapLife[site] == COORDINATE_STATUS_ALIVE ? 1 : 0)
	//{
	//	std::cout << ulCoordinatesX << "," << ulCoordinatesY << std::endl;
	//}

	return m_mapLife[site] == COORDINATE_STATUS_ALIVE ? 1 : 0;
}

void GHCGameLife::SkipOverTime(unsigned long ulTime)
{
	while (ulTime)
	{
		SkipOneTime();
		ulTime--;
	}
}

void GHCGameLife::SkipOneTime()
{
	for (unsigned long i = 0; i < m_ulMapSideLength * m_ulMapSideLength; i++)
	{
		unsigned int uiAliveNum = 0;
		unsigned long ulCoordinatesNodeX = 0, ulCoordinatesNodeY = 0;

		ulCoordinatesNodeY = (i + 1) / m_ulMapSideLength + ( 0 == (i + 1) % m_ulMapSideLength ? 0 : 1);
		ulCoordinatesNodeX = (i + 1) - m_ulMapSideLength * (ulCoordinatesNodeY - 1);


		/* 收集细胞周围活细胞数量 */
		//std::cout << "-------------B---------------" << std::endl;
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX + 1, ulCoordinatesNodeY);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX - 1, ulCoordinatesNodeY);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX, ulCoordinatesNodeY + 1);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX + 1, ulCoordinatesNodeY + 1);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX - 1, ulCoordinatesNodeY + 1);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX, ulCoordinatesNodeY - 1);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX + 1, ulCoordinatesNodeY - 1);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX - 1, ulCoordinatesNodeY - 1);
		//std::cout << "-------------E---------------" << std::endl;
		if (m_mapLife[i] == COORDINATE_STATUS_NON_SPACE)
		{
			m_mapNextTimeLife[i] = COORDINATE_STATUS_NON_SPACE;
		}
		else if (uiAliveNum == 3)
		{
			m_mapNextTimeLife[i] = COORDINATE_STATUS_ALIVE;
		}
		else if (2 <= uiAliveNum && 3 > uiAliveNum && m_mapLife[i] == COORDINATE_STATUS_ALIVE)
		{
			m_mapNextTimeLife[i] = COORDINATE_STATUS_ALIVE;
		}
		else
		{
			m_mapNextTimeLife[i] = COORDINATE_STATUS_DEATH;
		}
	}
	CoordinateStatus *pmapLife = m_mapNextTimeLife;
	m_mapNextTimeLife = m_mapLife;
	m_mapLife = pmapLife;
}

void GHCGameLife::CreateMap()
{
	m_mapLife = (CoordinateStatus *)calloc(m_ulMapSideLength, m_ulMapSideLength * sizeof(CoordinateStatus));
	m_mapNextTimeLife = (CoordinateStatus *)calloc(m_ulMapSideLength, m_ulMapSideLength * sizeof(CoordinateStatus));
}

void GHCGameLife::RandomSetMap()
{
	CoordinateStatus status[] = { COORDINATE_STATUS_ALIVE, COORDINATE_STATUS_DEATH };
	int statusSize = sizeof(status) / sizeof(CoordinateStatus);
	
	srand((unsigned)time(NULL));
	for (unsigned long i = 0; i < m_ulMapSideLength * m_ulMapSideLength; i++)
	{
		m_mapLife[i] = status[rand() % statusSize];
	}
}

void GHCGameLife::RandSetNoSpace()
{
	CoordinateStatus status[] = { COORDINATE_STATUS_ALIVE, COORDINATE_STATUS_DEATH, COORDINATE_STATUS_NON_SPACE};
	int statusSize = sizeof(status) / sizeof(CoordinateStatus);

	srand((unsigned)time(NULL));
	for (unsigned long i = 0; i < m_ulMapSideLength * m_ulMapSideLength; i++)
	{
		m_mapLife[i] = status[rand() % statusSize];
	}
}


}