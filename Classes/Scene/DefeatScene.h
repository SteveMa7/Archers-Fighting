#ifndef __DEFEAT_SCENE_H__
#define __DEFEAT_SCENE_H__

#include"cocos2d.h"
#include"ui/CocosGUI.h"

/*class DefeatScene :public cocos2d::Layer
{
private:

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void onEnter();

	CREATE_FUNC(DefeatScene);

};*/

class DefeatScene :public cocos2d::Layer
{
private:
	cocos2d::Sprite* usernameBG;
	cocos2d::ui::TextField* usernameInput;

	void createBackground();
	void createReturnButton();
	void createPrettyGirl();


	void onEnter();

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(DefeatScene);
};


#endif //__DEFEAT_SCENE_H__

