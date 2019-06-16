#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include"cocos2d.h"

class HelpSceneOne :public cocos2d::Layer 
{
private:

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void onEnter();

	CREATE_FUNC(HelpSceneOne);

};

class HelpSceneTwo :public cocos2d::Layer
{
private:

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void onEnter();

	CREATE_FUNC(HelpSceneTwo);

};




#endif //__HELP_SCENE_H__