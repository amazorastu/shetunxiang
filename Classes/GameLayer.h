#pragma once

#include "cocos2d.h"

class GameLayer : public cocos2d::LayerColor
{
public:
	GameLayer();
	~GameLayer();
public:
	CREATE_FUNC(GameLayer);
	virtual bool init();
	static cocos2d::Scene* createScene();

public:


private:


};