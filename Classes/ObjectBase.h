#pragma once

#include "cocos2d.h"

enum ObjectType
{
	objectTypeSnakeAttack,

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
	void setType(ObjectType);
	void setXY(int, int);
	int getX();
	int getY();
	void setAttack(int);
	void setDefense(int);

private:
	ObjectType type;
	int attack;
	int defense;
	bool isAlive;
	int posX;
	int posY;

	cocos2d::Sprite* eye1;
	cocos2d::Sprite* eye2;
	cocos2d::Label* attackLabel;
	cocos2d::Label* defenseLabel;
};