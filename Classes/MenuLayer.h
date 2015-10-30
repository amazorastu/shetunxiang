#pragma once

#include "cocos2d.h"

class MenuLayer : public cocos2d::LayerColor
{
public:
	MenuLayer();
	~MenuLayer();
public:
	CREATE_FUNC(MenuLayer);
	virtual bool init();
	static cocos2d::Scene* createScene();


private:
	cocos2d::Menu* menu;
	cocos2d::MenuItemImage* button0;
	cocos2d::MenuItemImage* button1;
	cocos2d::MenuItemImage* button2;
	cocos2d::Label* label;

	virtual void onEnterTransitionDidFinish();

	void buttonCallback(cocos2d::Ref*);

	static std::string WStrToUTF8(const std::wstring& src);

};