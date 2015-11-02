#include "ObjectBase.h"

USING_NS_CC;

ObjectBase::ObjectBase() :attack(0), defense(0), isDefending(false), timer(0)
{

}
ObjectBase::~ObjectBase()
{

}
bool ObjectBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	//direction = (bool)random(0, 1);
	direction = true;

	eye1 = Sprite::create();
	eye2 = Sprite::create();
	attackLabel = Label::createWithTTF("", "fonts/arial.ttf", 80.0f);
	attackLabel->setTextColor(Color4B::RED);
	defenseLabel = Label::createWithTTF("", "fonts/arial.ttf", 80.0f);
	defenseLabel->setTextColor(Color4B::BLACK);

	return true;
}

void ObjectBase::setType(ObjectType pType)
{
	type = pType;

	switch (type)
	{
	case objectTypeSnakeAttack:
		this->setSpriteFrame("Snake1.png");
		eye1->setSpriteFrame("Eye1.png");
		eye2->setSpriteFrame("Eye2.png");
		eye1->setPosition(Vec2(62.5f, 187.5f));
		eye2->setPosition(Vec2(187.5f, 187.5f));
		this->addChild(eye1);
		this->addChild(eye2);
		attack = 0;
		defense = 1;
		attackLabel->setString("0");
		defenseLabel->setString("1");
		attackLabel->setPosition(eye1->getPosition());
		defenseLabel->setPosition(eye2->getPosition());
		this->addChild(attackLabel);
		this->addChild(defenseLabel);
		break;

	case objectTypeXiang1:
		attack = -2;
		defense = -2;
		this->setSpriteFrame("X1.png");
		break;
	case objectTypeXiang2:
		attack = -2;
		defense = -2;
		this->setSpriteFrame("X2.png");
		break;
	case objectTypeXiang3:
		attack = -2;
		defense = -2;
		this->setSpriteFrame("X3.png");
		break;
	case objectTypeXiang4:
		attack = -2;
		defense = -2;
		this->setSpriteFrame("X4.png");
		break;
	case objectTypeAnimalDefense:
		attack = 0;
		defense = 0;
		attackLabel->setString("0");
		defenseLabel->setString("0");
		this->setAttack(random(0, 8));
		this->setDefense(random(2, 8));
		attackLabel->setPosition(Vec2(50.0f, 125.0f));
		defenseLabel->setPosition(Vec2(200.0f, 125.0f));
		this->addChild(attackLabel);
		this->addChild(defenseLabel);
		this->setSpriteFrame("Animal0.png");
		break;
	case objectTypeAnimalAttack:
		attack = 0;
		defense = 0;
		attackLabel->setString("0");
		defenseLabel->setString("0");
		this->setAttack(random(1, 8));
		this->setDefense(random(0, 8));
		attackLabel->setPosition(Vec2(50.0f, 175.0f));
		defenseLabel->setPosition(Vec2(200.0f, 175.0f));
		this->addChild(attackLabel);
		this->addChild(defenseLabel);
		this->setSpriteFrame("Animal1.png");
		break;
	case objectTypeElephant:
		attack = 7;
		defense = 8;
		attackLabel->setString("7");
		defenseLabel->setString("8");
		attackLabel->setPosition(Vec2(20.0f, 175.0f));
		defenseLabel->setPosition(Vec2(230.0f, 175.0f));
		this->addChild(attackLabel);
		this->addChild(defenseLabel);
		this->setSpriteFrame("Elephant.png");
		break;
	default:
		break;
	}
}
ObjectType ObjectBase::getType()
{
	return type;
}
void ObjectBase::setXY(int px, int py)
{
	posX = px;
	posY = py;
	this->stopAllActions();
	this->runAction(MoveTo::create(0.2f, Vec2((Director::getInstance()->getWinSize().width-1250.0f)*0.5f+posX*250.0f - 125.0f, posY*250.0f - 125.0f)));
}
int ObjectBase::getX()
{
	return posX;
}
int ObjectBase::getY()
{
	return posY;
}
bool ObjectBase::getDirection()
{
	return direction;
}
int ObjectBase::getAttack()
{
	return attack;
}
int ObjectBase::getDefense()
{
	return defense;
}
void ObjectBase::setAttack(int param)
{
	attack = param;
	char temp[3];
	sprintf(temp, "%d", attack);
	attackLabel->setString(temp);
	if (attack >= 0)
	{
		attackLabel->setOpacity(255.0f);
		if (this->getType() == objectTypeSnakeAttack)
		{
			eye1->setOpacity(255.0f);
		}
	}
	else
	{
		attackLabel->setOpacity(0.0f);
		if (this->getType() == objectTypeSnakeAttack)
		{
			eye1->setOpacity(0.0f);
		}
	}
}
void ObjectBase::setDefense(int param)
{
	defense = param;
	char temp[3];
	sprintf(temp, "%d", defense);
	defenseLabel->setString(temp);
	if (defense >= 0)
	{
		defenseLabel->setOpacity(255.0f);
		if (this->getType() == objectTypeSnakeAttack)
		{
			eye2->setOpacity(255.0f);
		}
	}
	else
	{
		defenseLabel->setOpacity(0.0f);
		if (this->getType() == objectTypeSnakeAttack)
		{
			eye2->setOpacity(0.0f);
		}
	}
}
void ObjectBase::setDefending(bool defending)
{
	if (defending)
	{
		this->setSpriteFrame("Snake2.png");
		isDefending = true;
	}
	else
	{
		this->setSpriteFrame("Snake1.png");
		isDefending = false;
	}
}
bool ObjectBase::getDefending()
{
	return isDefending;
}