#pragma once

#include "cocos2d.h"

#include "GameLayer.h"

class GameMap
{
public:
	GameMap();
	GameMap(GameLayer*);
	~GameMap();

/*************************************************/
public:

private:
	GameLayer* layer;

};