#include "GameLayer.h"



USING_NS_CC;

GameLayer::GameLayer()
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

bool GameLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}



	return true;
}