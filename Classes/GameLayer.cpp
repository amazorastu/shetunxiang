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
	this->addChild(snake,2);
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
		snake->setXY(snake->getX() + 1, snake->getY());
		isMoved = true;
	}
	else if (currentPos.x - touchPos.x < -200.0f&&currentPos.y - touchPos.y > -100.0f&&currentPos.y - touchPos.y < 100.0f&&snake->getX() > 1)
	{
		snake->setXY(snake->getX() - 1, snake->getY());
		isMoved = true;
	}
	else if (currentPos.y - touchPos.y > 200.0f&&currentPos.x - touchPos.x > -100.0f&&currentPos.x - touchPos.x < 100.0f&&snake->getY() < 8)
	{
		snake->setXY(snake->getX(), snake->getY() + 1);
		isMoved = true;
	}
	else if (currentPos.y - touchPos.y < -200.0f&&currentPos.x - touchPos.x > -100.0f&&currentPos.x - touchPos.x < 100.0f&&snake->getY() > 1)
	{
		snake->setXY(snake->getX(), snake->getY() - 1);
		isMoved = true;
	}
}
void GameLayer::onTouchEnded(Touch *touch, Event*)
{
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
			dest.push_back(0xf0 | ((w >> 18) & 0x07));
			dest.push_back(0x80 | ((w >> 12) & 0x3f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
	return dest;
}
