#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include"extensions/cocos-ext.h"
#include"client.h"
USING_NS_CC_EXT;

class LoginScene :public cocos2d::Layer
{
private:
	cocos2d::Sprite* usernameBG;
	cocos2d::ui::TextField* usernameInput;
	//client *chuckle;
	void createBackground();
	void createLoginButton();
	void createConsoleButton();
	void createPrettyGirl();
	void createSetButton();
	void createHelpButton();
	void createAudioControlButton();
	void createCloseButton();

	void soundSwitch(Ref* pSender, Control::EventType controlEvent);

	void initUserBox();

	void menuBackCallBack(cocos2d::Ref* pSender);
	void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType event);

	void onEnter();

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(LoginScene);
};

#endif //__LOGIN_SCENE_H__
