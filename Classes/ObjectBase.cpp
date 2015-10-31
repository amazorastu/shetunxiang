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



	return true;
}