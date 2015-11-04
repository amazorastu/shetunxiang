#pragma once

#include "cocos2d.h"

enum ObjectType
{
	objectTypeSnakeAttack = 11,

	objectTypeXiang1 = 1,
	objectTypeXiang2 = 2,
	objectTypeXiang3 = 3,
	objectTypeXiang4 = 4,

	objectTypeAnimalDefense = 6,
	objectTypeAnimalAttack = 7,
	objectTypeElephant = 8
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
	ObjectType getType();
	void setXY(int, int);
	int getX();
	int getY();
	void setAttack(int);
	void setDefense(int);
	int getAttack();
	int getDefense();
	bool getDirection();
	void setDefending(bool);
	bool getDefending();
	int timer;
	void remove(int, int);

private:
	ObjectType type;
	int attack;
	int defense;
	bool isDefending;
	int posX;
	int posY;

	
	bool direction;

	cocos2d::Sprite* eye1;
	cocos2d::Sprite* eye2;
	cocos2d::Label* attackLabel;
	cocos2d::Label* defenseLabel;
};