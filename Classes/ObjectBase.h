#pragma once

#include "cocos2d.h"

enum ObjectType
{
	objectTypeSnakeAttack,
	objectTypeSnakeDefense,

	objectTypeXiang0,
	objectTypeXiang1,
	objectTypeXiang2,
	objectTypeXiang3,

	objectTypeAnimalAttack,
	objectTypeAnimalDefense
};

class ObjectBase : public cocos2d::Sprite
{
public:
	ObjectBase();
	~ObjectBase();

	CREATE_FUNC(ObjectBase);
	virtual bool init();

/*******************************************************************/
public:
	


private:
	int attack;
	int defense;
	bool isAlive;
	int posX;
	int posY;

};