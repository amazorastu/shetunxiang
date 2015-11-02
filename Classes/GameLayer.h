#pragma once

#include "cocos2d.h"

#include "ObjectBase.h"
#include "ObjectMap.h"

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

	static std::string WStrToUTF8(const std::wstring& src);

	bool isPaused;
	bool isTouched;
	bool isMoved;
	
	cocos2d::Vec2 touchPos;
	/***********************************************************/
private:
	void showPauseDialog(bool);
	void showGameOverDialog(bool);

	void addObject(ObjectType);

	cocos2d::LayerColor* dialog;

	ObjectBase* snake;

};