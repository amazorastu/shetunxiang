#pragma once

#include "cocos2d.h"

class HelpLayer : public cocos2d::LayerColor
{
public:
	HelpLayer();
	~HelpLayer();

public:
	CREATE_FUNC(HelpLayer);
	virtual bool init();
	static cocos2d::Scene* createScene();

private:
	virtual void onEnterTransitionDidFinish();
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void buttonCallback(cocos2d::Ref*);

	void switchPicture(bool);

	cocos2d::Sprite* image;
	cocos2d::Menu* menu;
	cocos2d::MenuItemImage* buttonLeft;
	cocos2d::MenuItemImage* buttonRight;
	cocos2d::Label* label;
	int currentPicture;
};