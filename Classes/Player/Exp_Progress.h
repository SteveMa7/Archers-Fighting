#ifndef __EXP_PROGRESS_H__
#define __EXP_PROGRESS_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Player/Player.h"
#include "Player/Progress.h"

USING_NS_CC;
class Player;
class ExpProgress :public cocos2d::CCLayer
{
private:
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
public:
	ExpProgress();
	~ExpProgress();
	virtual bool init();
	CREATE_FUNC(ExpProgress);
	void ExpChange(int exp, int limit);
	void LvChange(int level, Player *player);
	void ButtonAppear(Player *player);
	void ButtonRemove(Player *player);
	void Choices(int i, Player *player);

	//Player *player;
	float x_coord = 80.0f;
	float y_coord = 80.0f;
	bool ifchose = 0;


private:
	Progress * expProgressView;
	Label *lv;
	ui::Button* choice1;
	ui::Button* choice2;
	ui::Button* choice3;
	Sprite *choice_bk1;
	Sprite *choice_bk2;
	Sprite *choice_bk3;
	int c1, c2, c3;
	int skillsave = 0;
	std::vector<bool>unchoose;
};

#endif