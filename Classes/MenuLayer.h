#pragma once

#include "cocos2d.h"

#include "GameLayer.h"
#include "HelpLayer.h"
#include "ObjectMap.h"

class MenuLayer : public cocos2d::LayerColor
{
public:
	MenuLayer();
	~MenuLayer();

	CREATE_FUNC(MenuLayer);
	virtual bool init();
	static cocos2d::Scene* createScene();

private:
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * pEvent);
	virtual void onEnterTransitionDidFinish();

	void addKeyboardEvent();

public:

private:
	cocos2d::Sprite* logo;

	cocos2d::Menu* menu;
	cocos2d::MenuItemImage* button0;
	cocos2d::MenuItemImage* button1;
	cocos2d::MenuItemImage* button2;
	cocos2d::Label* label;

	void buttonCallback(cocos2d::Ref*);

	static std::string WStrToUTF8(const std::wstring& src);

};