#pragma once

#include "cocos2d.h"

#include "ObjectBase.h"

class ObjectMap
{
public:
	ObjectMap();
	~ObjectMap();

public:
	static ObjectBase* map[7][10];

	static void init();

	static void doMove(int posX, int posY, int direction);

	static bool dealContact(ObjectBase*, ObjectBase*);

	static bool addObject(ObjectBase*);

	static void removeObject(int, int, bool eat = false);

	static void removeObject(int, int, int, int, bool eat = false);

	static void step();

	static int gameState;
	
	static bool hasElephant;

	static bool ateElephant;
};