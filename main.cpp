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

#include <iostream>
#include "GHCGameLife.h"

using namespace std;

using namespace ghcGameLife;

void defaultStartGame()
{
	/* 
	默认游戏空间为 9 X 9 小方块组成的空间
	内部随机部署活细胞和死细胞
	*/
	ghcGameLife::GHCGameLife game;

	/* 
	打印当前游戏地图
	地图对应坐标点L代表活细胞，空格为死细胞
	*/
	cout << game.GetLifeMap() << endl;

	for (int i = 0; i < 10; i++)
	{
		/*
		游戏推进1回合
		*/
		game.SkipOverTime(1);

		/*
		打印当前游戏地图
		地图对应坐标点L代表活细胞，空格为死细胞
		*/
		cout << game.GetLifeMap() << endl;
	}

	/*
	游戏推进100回合
	*/
	game.SkipOverTime(100);

	/*
	打印当前游戏地图
	地图对应坐标点L代表活细胞，空格为死细胞
	*/
	cout << game.GetLifeMap() << endl;

	return;
}

void customStartGame()
{
	/*
	定制游戏空间为 20 X 20 小方块组成的空间
	内部随机部署活细胞和死细胞
	*/
	ghcGameLife::GHCGameLife game(20);

	/*
	打印当前游戏地图
	地图对应坐标点L代表活细胞，空格为死细胞
	*/
	cout << game.GetLifeMap() << endl;

	/*
	游戏推进200回合
	*/
	game.SkipOverTime(200);

	/*
	打印当前游戏地图
	地图对应坐标点L代表活细胞，空格为死细胞
	*/
	cout << game.GetLifeMap() << endl;

	return;
}

void saveGame()
{
	/*
	默认游戏空间为 9 X 9 小方块组成的空间
	内部随机部署活细胞和死细胞
	*/
	ghcGameLife::GHCGameLife game;
	GHCGameLifeData GHCGameLifeData;

	/*
	导出game数据
	*/
	game.ExportGameLife(GHCGameLifeData);

	/*
	导入game数据
	*/
	ghcGameLife::GHCGameLife game2(GHCGameLifeData);

	free(GHCGameLifeData.Map);

	/*
	打印当前游戏地图
	地图对应坐标点L代表活细胞，空格为死细胞
	*/
	cout << game.GetLifeMap() << endl;

	/*
	打印当前游戏地图
	地图对应坐标点L代表活细胞，空格为死细胞
	*/
	cout << game2.GetLifeMap() << endl;

	return;
}

void anomalySpaceSatrtGame()
{
	/*
	定制游戏空间为 10 X 10 小方块组成的空间
	内部随机部署活细胞和死细胞
	*/
	ghcGameLife::GHCGameLife game(10);


	/*
	随机将20 X 20 空间中的几个空间设置为无法生存
	即该类空间不存在活或者死细胞
	*/
	game.RandSetNoSpace();

	/*
	打印当前游戏地图
	地图对应坐标点L代表活细胞，空格代表死细胞，X代表空间不可用
	*/
	cout << game.GetLifeMap() << endl;


	for (int i = 0; i < 10; i++)
	{
		/*
		游戏推进1回合
		*/
		game.SkipOverTime(1);

		/*
		打印当前游戏地图
		地图对应坐标点L代表活细胞，空格代表死细胞，X代表空间不可用
		*/
		cout << game.GetLifeMap() << endl;
	}

	/*
	游戏推进100回合
	*/
	game.SkipOverTime(100);

	/*
	打印当前游戏地图
	地图对应坐标点L代表活细胞，空格为死细胞
	*/
	cout << game.GetLifeMap() << endl;

	return;
}

int main()
{
	defaultStartGame();
	//customStartGame();
	//saveGame();
	//anomalySpaceSatrtGame();
	return 0;
}