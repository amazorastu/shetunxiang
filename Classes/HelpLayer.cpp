#include "HelpLayer.h"

USING_NS_CC;

HelpLayer::HelpLayer() :currentPicture(1)
{

}
HelpLayer::~HelpLayer()
{

}

bool HelpLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		return false;
	}

	image = Sprite::create();
	this->addChild(image);

	buttonLeft = MenuItemImage::create("res/Button5_0.png", "res/Button5_1.png", CC_CALLBACK_1(HelpLayer::buttonCallback, this));
	buttonLeft->setTag(1);
	buttonLeft->setAnchorPoint(Vec2::ZERO);
	buttonLeft->setPosition(Vec2::ZERO);
	buttonRight = MenuItemImage::create("res/Button6_0.png", "res/Button6_1.png", CC_CALLBACK_1(HelpLayer::buttonCallback, this));
	buttonRight->setTag(2);
	buttonRight->setAnchorPoint(Vec2(1.0f, 0.0f));
	buttonRight->setPosition(Director::getInstance()->getWinSize().width, 0.0f);

	menu = Menu::create(buttonLeft, buttonRight, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	label = Label::createWithTTF("1/8", "fonts/arial.ttf", 80.0f);
	label->setAnchorPoint(Vec2(0.5f, 0.0f));
	label->setTextColor(Color4B::BLACK);
	label->setPosition(Director::getInstance()->getWinSize().width*0.5f, 0.0f);
	this->addChild(label);

	image = Sprite::createWithSpriteFrameName("1.jpg");
	image->setScale(Director::getInstance()->getWinSize().width/480.0f < 3.0f?Director::getInstance()->getWinSize().width/480.0f : 3.0f);
	image->setAnchorPoint(Vec2(0.0f, 1.0f));
	image->setPosition(0.0f, Director::getInstance()->getWinSize().height);
	this->addChild(image);

	return true;
}

void HelpLayer::onEnterTransitionDidFinish()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(HelpLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
      
Scene* HelpLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = HelpLayer::create();
	sc->addChild(ly);
	return sc;
}

void HelpLayer::switchPicture(bool isBackward)
{
	if (isBackward)
	{
		currentPicture--;
		if (currentPicture < 1)currentPicture = 1;
	}
	else
	{
		currentPicture++;
		if (currentPicture > 8)currentPicture = 8;
	}
	char imagePath[6];
	sprintf(imagePath, "%d.jpg", currentPicture);
	image->setSpriteFrame(imagePath);

	char labelString[6];
	sprintf(labelString, "%d/8", currentPicture);
	label->setString(labelString);
}

void HelpLayer::buttonCallback(Ref* ref)
{
	auto button = (MenuItemImage*)ref;
	if (button->getTag() == 1)
	{
		switchPicture(true);
	}
	else if (button->getTag() == 2)
	{
		switchPicture(false);
	}
}
void HelpLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->popScene();
	}
}
