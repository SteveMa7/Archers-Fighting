#include"Tool/GameAudio.h"
#include"extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

GameAudio* GameAudio::getInstance()
{
	static GameAudio INSTANCE;
	return &INSTANCE;
}

void GameAudio::playMusic(const char* name)
{
	if (currentMusic != name) 
	{
		currentMusic = name;
		audioEngine->playBackgroundMusic(name, true);
	}
	if (!isMusicOn)
	{
		stopMusic();
	}
}

void GameAudio::stopMusic()
{
	audioEngine->stopBackgroundMusic();
}

void GameAudio::setMusicOn(bool val)
{
	isMusicOn = val;
	if (val)
	{
		audioEngine->resumeBackgroundMusic();
	}
	else 
	{
		stopMusic();
	}
}

bool GameAudio::getMusicOn()const
{
	return isMusicOn;
}

void GameAudio::pauseMusic()const
{
	audioEngine->pauseBackgroundMusic();
}

void GameAudio::resumeMusic()const
{
	audioEngine->resumeBackgroundMusic();
}