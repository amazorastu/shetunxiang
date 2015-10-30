#include "MenuLayer.h"

USING_NS_CC;

MenuLayer::MenuLayer()
{

}
MenuLayer::~MenuLayer()
{

}
Scene* MenuLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = MenuLayer::create();
	sc->addChild(ly);
	return sc;
}

bool MenuLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/texture.plist");

	label = Label::createWithTTF(WStrToUTF8(L"������"), "fonts/simhei.ttf", 150.0f);
	label->setColor(Color3B::BLACK);
	label->setPosition(Director::getInstance()->getWinSize().width*0.5f, 1700.0f);
	this->addChild(label, 2);

	button0 = MenuItemImage::create("res/Button0_0.png", "res/Button0_1.png", CC_CALLBACK_1(MenuLayer::buttonCallback, this));
	button1 = MenuItemImage::create("res/Button1_0.png", "res/Button1_1.png", CC_CALLBACK_1(MenuLayer::buttonCallback, this));
	button2 = MenuItemImage::create("res/Button2_0.png", "res/Button2_1.png", CC_CALLBACK_1(MenuLayer::buttonCallback, this));
	button0->setOpacity(0.0f);
	button1->setOpacity(0.0f);
	button2->setOpacity(0.0f);
	button0->setPosition(0.0f, 250.0f);
	button1->setPosition(0.0f, -100.0f);
	button2->setPosition(0.0f, -450.0f);

	menu = Menu::create(button0, button1, button2, nullptr);
	menu->setPosition(Director::getInstance()->getWinSize()*0.5f);
	this->addChild(menu);

	return true;
}

void MenuLayer::onEnterTransitionDidFinish()
{
	button0->runAction(FadeIn::create(0.5f));
	button1->runAction(FadeIn::create(0.5f));
	button2->runAction(FadeIn::create(0.5f));
}

void MenuLayer::buttonCallback(Ref* ref)
{
	log("1");
}

std::string MenuLayer::WStrToUTF8(const std::wstring& src)
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
