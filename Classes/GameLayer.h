#pragma once

#include "cocos2d.h"

#include "ObjectBase.h"
#include "ObjectMap.h"
#include "AudioManager.h"

class GameLayer : public cocos2d::LayerColor
{
public:
	GameLayer();
	~GameLayer();

	CREATE_FUNC(GameLayer);
	virtual bool init();
	static cocos2d::Scene* createScene();

private:
	void addKeyboardEvents();
	void addButtonEvents();
	void removeButtonEvents();
	void removeKeyboardEvents();

	void update(float);
	void onEnterTransitionDidFinish();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void buttonCallback(cocos2d::Ref* ref);
	void tickTime();

	static std::string WStrToUTF8(const std::wstring& src);

	bool isPaused;
	bool isTouched;
	bool isMoved;
	
	int moveInterval;
	
	cocos2d::Vec2 touchPos;

	
	/***********************************************************/
private:
	void showPauseDialog(bool);
	void showGameOverDialog(bool);

	void addObject(ObjectType);

	cocos2d::LayerColor* dialog;
	cocos2d::Label* label1;
	cocos2d::Label* label2;

	char timeString[6];
	int timer;
	cocos2d::Label* timeLabel;

	ObjectBase* snake;

};