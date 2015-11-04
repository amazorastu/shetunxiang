#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

enum AudioType
{
	audioTypeSnake,
	audioTypeElephant
};

class AudioManager
{
protected:
	AudioManager();

public:
	static AudioManager* getInstance();
	void playSoundEffect(AudioType);
	void stopBGM();
	void startBGM();


private:
	static AudioManager* instance;
	void init();
};