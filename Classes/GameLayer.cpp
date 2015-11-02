#include "GameLayer.h"

USING_NS_CC;

GameLayer::GameLayer() :isPaused(false), isTouched(false), isMoved(false)
{

}
GameLayer::~GameLayer()
{

}
Scene* GameLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = GameLayer::create();
	sc->addChild(ly);
	return sc;
}
void GameLayer::addButtonEvents()
{
	auto eventTouch = EventListenerTouchOneByOne::create();
	eventTouch->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	eventTouch->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	eventTouch->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	eventTouch->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventTouch, this);
}
void GameLayer::addKeyboardEvents()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
void GameLayer::removeButtonEvents()
{
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
}
void GameLayer::removeKeyboardEvents()
{
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::KEYBOARD);
}
bool GameLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	snake = ObjectBase::create();
	snake->setPosition(-200.0f, -200.0f);
	snake->setType(objectTypeSnakeAttack);
	this->addChild(snake,3);
	snake->setXY(random(1, 5), random(1, 8));
	ObjectMap::addObject(snake);

	return true;
}

void GameLayer::onEnterTransitionDidFinish()
{
	this->addKeyboardEvents();
	this->addButtonEvents();
	this->scheduleUpdate();
}

void GameLayer::update(float dt)
{
	if (ObjectMap::hasElephant == false && ObjectMap::ateElephant == false)
	{
		this->addObject(objectTypeElephant);
	}

	if (ObjectMap::gameState == 0)
	{
		this->addObject(objectTypeXiang1);
	}
	else if (ObjectMap::gameState == 2)
	{
		this->addObject(objectTypeXiang2);
	}
	else if (ObjectMap::gameState == 4)
	{
		this->addObject(objectTypeXiang3);
	}
	else if (ObjectMap::gameState == 6)
	{
		this->addObject(objectTypeXiang4);
	}
	else if (ObjectMap::gameState >= 100)
	{
		this->showGameOverDialog(false);
	}
	else if (ObjectMap::gameState >= 50)
	{
		this->showGameOverDialog(true);
	}

	if (random(1, 100) == 1)
	{
		this->addObject(objectTypeAnimalAttack);
	}
	if (random(1, 100) == 1)
	{
		this->addObject(objectTypeAnimalDefense);
	}

	ObjectMap::step();
}


void GameLayer::showPauseDialog(bool show)
{
	if (show)
	{
		this->removeButtonEvents();
		this->unscheduleUpdate();
		dialog = LayerColor::create(Color4B(0, 0, 0, 128));
		auto button1 = MenuItemImage::create("res/Button3_0.png", "res/Button3_0.png", CC_CALLBACK_1(GameLayer::buttonCallback, this));
		auto button2 = MenuItemImage::create("res/Button4_0.png", "res/Button4_0.png", CC_CALLBACK_1(GameLayer::buttonCallback, this));
		button1->setTag(1);
		button2->setTag(2);
		button1->setPosition(0.0f, 200.0f);
		button2->setPosition(0.0f, -200.0f);
		auto menu = Menu::create(button1, button2, nullptr);
		menu->setPosition(Director::getInstance()->getWinSize()*0.5f);
		dialog->addChild(menu);
		this->addChild(dialog, 100);
	}
	else if (dialog != nullptr)
	{
		this->removeChild(dialog, true);
		this->addButtonEvents();
		this->scheduleUpdate();
	}
}
void GameLayer::showGameOverDialog(bool win)
{
	this->removeKeyboardEvents();
	this->removeButtonEvents();
	this->unscheduleUpdate();

	dialog = LayerColor::create(Color4B(0, 0, 0, 128));
	auto button2 = MenuItemImage::create("res/Button4_0.png", "res/Button4_0.png", CC_CALLBACK_1(GameLayer::buttonCallback, this));
	button2->setTag(2);
	button2->setPosition(0.0f, -200.0f);
	auto menu = Menu::create(button2, nullptr);
	menu->setPosition(Director::getInstance()->getWinSize()*0.5f);
	dialog->addChild(menu);

	
	auto label = Label::createWithTTF("", "fonts/simhei.ttf", 150.0f);
	
	label->setPosition(Director::getInstance()->getWinSize().width*0.5f, Director::getInstance()->getWinSize().height*0.5f + 200.0f);
	if (win)
	{
		label->setColor(Color3B::RED);
		label->setString("胜利");
	}
	else
	{
		label->setColor(Color3B::BLACK);
		label->setString("失败");
	}
	dialog->addChild(label);

	this->addChild(dialog, 100);
}

void GameLayer::addObject(ObjectType pType)
{
	auto obj = ObjectBase::create();
	obj->setOpacity(0.0f);
	this->addChild(obj,2);
	

	switch (pType)
	{
	case objectTypeXiang1:
		obj->setType(objectTypeXiang1);
		break;
	case objectTypeXiang2:
		obj->setType(objectTypeXiang2);
		break;
	case objectTypeXiang3:
		obj->setType(objectTypeXiang3);
		break;
	case objectTypeXiang4:
		obj->setType(objectTypeXiang4);
		break;
	case objectTypeAnimalAttack:
		obj->setType(objectTypeAnimalAttack);
		break;
	case objectTypeAnimalDefense:
		obj->setType(objectTypeAnimalDefense);
		break;
	case objectTypeElephant:
		obj->setType(objectTypeElephant);
		break;
	default:
		break;
	}
	if (obj->getDirection())
	{
		obj->setXY(0, 0);
	}
	else
	{
		obj->setXY(6, 0);
	}
	obj->setXY(obj->getX(), random(1, 8));
	obj->stopAllActions();
	obj->setPosition(Vec2((Director::getInstance()->getWinSize().width - 1250.0f)*0.5f + obj->getX()*250.0f - 125.0f, obj->getY()*250.0f - 125.0f));
	obj->runAction(FadeIn::create(1.0f));
	if (!ObjectMap::addObject(obj))
	{
		obj->removeFromParentAndCleanup(true);
	}
}




bool GameLayer::onTouchBegan(Touch *touch, Event*)
{
	if (isTouched)return false;
	isTouched = true;

	touchPos = touch->getLocation();

	return true;
}
void GameLayer::onTouchMoved(Touch *touch, Event*)
{
	if (isMoved)return;
	auto currentPos = touch->getLocation();
	if (currentPos.x - touchPos.x > 200.0f&&currentPos.y - touchPos.y > -100.0f&&currentPos.y - touchPos.y < 100.0f&&snake->getX() < 5)
	{
		ObjectMap::doMove(snake->getX(), snake->getY(), 2);
		//snake->setXY(snake->getX() + 1, snake->getY());
		isMoved = true;
	}
	else if (currentPos.x - touchPos.x < -200.0f&&currentPos.y - touchPos.y > -100.0f&&currentPos.y - touchPos.y < 100.0f&&snake->getX() > 1)
	{
		ObjectMap::doMove(snake->getX(), snake->getY(), 0);
		//snake->setXY(snake->getX() - 1, snake->getY());
		isMoved = true;
	}
	else if (currentPos.y - touchPos.y > 200.0f&&currentPos.x - touchPos.x > -100.0f&&currentPos.x - touchPos.x < 100.0f&&snake->getY() < 8)
	{
		ObjectMap::doMove(snake->getX(), snake->getY(), 1);
		//snake->setXY(snake->getX(), snake->getY() + 1);
		isMoved = true;
	}
	else if (currentPos.y - touchPos.y < -200.0f&&currentPos.x - touchPos.x > -100.0f&&currentPos.x - touchPos.x < 100.0f&&snake->getY() > 1)
	{
		ObjectMap::doMove(snake->getX(), snake->getY(), 3);
		//snake->setXY(snake->getX(), snake->getY() - 1);
		isMoved = true;
	}
}
void GameLayer::onTouchEnded(Touch *touch, Event*)
{
	auto currentPos = touch->getLocation();
	if (isMoved == false && currentPos.x - touchPos.x > -50.0f&&currentPos.x - touchPos.x<50.0f&&currentPos.y - touchPos.y>-50.0f&&currentPos.y - touchPos.y < 50.0f)
	{
		snake->setDefending(!snake->getDefending());
	}
	isTouched = false;
	isMoved = false;
}
void GameLayer::onTouchCancelled(Touch *touch, Event*)
{
	isTouched = false;
	isMoved = false;
}
void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		
		if (!isPaused)
		{
			isPaused = true;
			this->showPauseDialog(true);
		}
		else
		{
			isPaused = false;
			this->showPauseDialog(false);
		}
	}
}
void GameLayer::buttonCallback(Ref* ref)
{
	auto button = (MenuItemImage*)ref;
	switch (button->getTag())
	{
	case 1:
		this->showPauseDialog(false);
		break;
	case 2:
		Director::getInstance()->popScene();
		break;
	default:
		break;
	}
}

std::string GameLayer::WStrToUTF8(const std::wstring& src)
{
	std::string dest;
	dest.clear();
	for (size_t i = 0; i < src.size(); i++)
	{
		wchar_t w = src[i];
		if (w <= 0x7f)
		{
			dest.push_back((char)w);
		}
		else if (w <= 0x7ff)
		{
			dest.push_back(0xc0 | ((w >> 6) & 0x1f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (w <= 0xffff)
		{
			dest.push_back(0xe0 | ((w >> 12) & 0x0f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)
		{
			dest.push_back(0xf0 | ((w >> 16) & 0x07));
			dest.push_back(0x80 | ((w >> 12) & 0x3f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
	return dest;
}
