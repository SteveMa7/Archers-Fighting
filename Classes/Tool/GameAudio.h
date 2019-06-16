#ifndef __GAME_AUDIO_H__
#define __GAME_AUDIO_H__

#include"cocos2d.h"
#include"SimpleAudioEngine.h"

class GameAudio
{
public:
	static GameAudio* getInstance();

	void playMusic(const char *name);
	
	void stopMusic();

	void setMusicOn(bool val);

	bool getMusicOn()const;

	void pauseMusic()const;

	void resumeMusic()const;

private:
	GameAudio()
	{
		audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
		isMusicOn = cocos2d::UserDefault::getInstance()->getBoolForKey("isMusicOn", true);
	};

	bool isMusicOn;
	std::string currentMusic;
	CocosDenshion::SimpleAudioEngine* audioEngine;
};


#endif //__GAME_AUDIO_H__
