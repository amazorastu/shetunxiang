#pragma once

#include "cocos2d.h"

#include "ObjectBase.h"

enum MoveResult
{
	moveResultWin,
	moveResultLose
};

class Map
{
public:
	static ObjectBase* map[7][10];

	static MoveResult doMove(int posX, int posY, int direction);

	static void addObject(ObjectBase*);

	static void step();
};