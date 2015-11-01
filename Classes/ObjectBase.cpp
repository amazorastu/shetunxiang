#include "ObjectBase.h"

USING_NS_CC;

ObjectBase::ObjectBase() :attack(0), defense(0), isAlive(true)
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
	default:
		break;
	}
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