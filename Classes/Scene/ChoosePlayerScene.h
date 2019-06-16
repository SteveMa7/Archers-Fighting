#ifndef __CHOOSE_PLAYER_SECNE_H__
#define __CHOOSE_PLAYER_SECNE_H__

#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include"cocos-ext.h"
#include"cocostudio/CocoStudio.h"
#include<string>

using namespace cocos2d::ui;
extern int player_chose;
class ChoosePlayerScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void createPlayer();
	void createBackground();

	void createOkButton();
	void createReturnButton();

	std::string playerChosen = "no";
	int player_chosen;

	CREATE_FUNC(ChoosePlayerScene);
};

#endif  //__CHOOSE_PLAYER_SECNE_H__