#include "AudioManager.h"

USING_NS_CC;
using namespace CocosDenshion;

AudioManager* AudioManager::instance;

AudioManager::AudioManager()
{

}

AudioManager* AudioManager::getInstance()
{
	if (!instance)
	{
		instance = new AudioManager();
		instance->init();
	}

	return instance;
}

void AudioManager::init()
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("se/Elephant.mp3");
}

void AudioManager::stopBGM()
{
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
}

void AudioManager::startBGM()
{
	if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("se/Elephant.mp3", true);
	}
}

void AudioManager::playSoundEffect(AudioType pType)
{
	switch (pType)
	{
	case audioTypeSnake:
		SimpleAudioEngine::getInstance()->playEffect("se/Snake.mp3");
		break;
	case audioTypeElephant:
		SimpleAudioEngine::getInstance()->playEffect("se/Elephant.mp3");
		break;
	default:
		break;
	}
}