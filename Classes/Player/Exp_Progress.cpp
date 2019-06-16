#include "Player/Exp_Progress.h"
#include "Scene/GamingScene.h"
#include "Scene/Map.h"

#include <cmath>
#include <algorithm>

#define choice_num 16

using namespace cocos2d::ui;

ExpProgress::ExpProgress()
{

}

ExpProgress::~ExpProgress()
{

}

bool ExpProgress::init()
{
	expProgressView = new Progress;
	expProgressView->setPosition(ccp(960, 1015));
	expProgressView->setScale(2, 0.8);
	expProgressView->Background("GameItem/Player/expbk.png");
	expProgressView->Fill("GameItem/Player/exp.png");
	expProgressView->Total_progress(1);
	expProgressView->Current_progress(0);
	addChild(expProgressView);
	
	lv = Label::create("LV 1", "Arial", 40);
	
	lv->setPosition(ccp(960, 1015));
	lv->setScale(0.8);
	addChild(lv);

	for (int i = 0; i < choice_num + 1; i++)
		unchoose.push_back(false);

	return true;
}

void ExpProgress::ExpChange(int exp, int limit)
{
	expProgressView->Current_progress((float)exp / limit);
}

void ExpProgress::LvChange(int level, Player *player)
{
	removeChild(lv);
	if (level == 11)
	{
		lv = Label::create("LV MAX", "Arial", 40);
	}
	else
	{
		lv = Label::create(StringUtils::format("Lv%d", level), "Arial", 40);
	}

	lv->setPosition(Vec2(960, 1015));

	lv->setScale(0.8);
	addChild(lv);

	skillsave++;
	if (skillsave <= 1)
		ButtonAppear(player);
}

void ExpProgress::ButtonAppear(Player *player)
{
	srand(time(NULL));

	choice_bk1 = Sprite::create("choice_bk.png");
	choice_bk2 = Sprite::create("choice_bk.png");
	choice_bk3 = Sprite::create("choice_bk.png");

	c1 = rand() % choice_num + 1;
	while (unchoose[c1] == true)
		c1 = rand() % choice_num + 1;

	choice1 = Button::create(StringUtils::format("GameItem/Player/choice%d.png", c1));
	choice1->setPosition(ccp(850, 570));
	choice1->setScale(0.5);
	choice_bk1->setPosition(ccp(850, 565));
	choice_bk1->setScale(0.45);

	choice1->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED)
		{
			return;
		}
		Choices(c1, player);
		ButtonRemove(player);
	});

	c2 = rand() % choice_num+ 1;
	while (c2 == c1 || unchoose[c2] == true)
		c2 = rand() % choice_num + 1;

	choice2 = Button::create(StringUtils::format("GameItem/Player/choice%d.png", c2));
	choice2->setPosition(ccp(990, 570));
	choice2->setScale(0.5);
	choice_bk2->setPosition(ccp(990, 565));
	choice_bk2->setScale(0.45);

	choice2->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED)
		{
			return;
		}
		Choices(c2,player);
		ButtonRemove(player);
	});

	c3 = rand() % choice_num + 1;
	while (c3 == c1 || c3 == c2 || unchoose[c3] == true)
		c3 = rand() % choice_num + 1;

	choice3 = Button::create(StringUtils::format("GameItem/Player/choice%d.png", c3));
	choice3->setPosition(ccp(1130, 570));
	choice3->setScale(0.5);
	choice_bk3->setPosition(ccp(1130, 565));
	choice_bk3->setScale(0.45);
	choice3->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED)
			{
				return;
			}
			Choices(c3, player);
			ButtonRemove(player);
		});
	
	addChild(choice_bk1);
	addChild(choice1);

	addChild(choice_bk2);
	addChild(choice2);

	addChild(choice_bk3);
	addChild(choice3);
}

void ExpProgress::ButtonRemove(Player *player)
{
	removeChild(choice1);
	removeChild(choice2);
	removeChild(choice3);
	removeChild(choice_bk1);
	removeChild(choice_bk2);
	removeChild(choice_bk3);

	skillsave--;

	if (skillsave > 0)
		ButtonAppear(player);
}

void ExpProgress::Choices(int i, Player *player)
{
	ifchose = 1;
	switch (i)
	{
	case 1://fire
		player->weapon = 2;
		break;
	case 2://剑
		player->weapon = 3;
		break;
	case 3://加攻击力
		player->power += 1;
		break;
	case 4://加射程
		player->attack_len += 1;                          //攻击距离
		break;
	case 5://加防御
		player->defend -= 1;
		break;
	case 6://加前方
		player->front++;
		break;
	case 7://加后方
		player->back++;
		break;
	case 8://加左右
		player->left++;
		player->right++;
		break;
	case 9://红心增加更多hp
		player->HP_UP += 1;
		break;
	case 10://增加更多经验
		player->EXP_UP += 1;
		break;
	case 11://加速度
		player->speed += 1;
		break;
	case 12://血上限
		player->Hp_limit += 20;
		break;
	case 13://减血上限加攻击力
		player->Hp_limit -= 20;
		player->power += 1;
		break;
	case 14://减攻击CD
		player->attack_CD -= 0.15;
		break;
	case 15://狙击武器
		player->attack_len += 0.5;
		player->speed -= 1;
		break;
	case 16://全属性提升
		player->power += 1;
		player->attack_len += 1;
		player->defend -= 1;
		break;
	}

	char hero_mess[40];
	sprintf(hero_mess, "%d %d %d %d %d %d %d %d %d %d ",
		static_cast<int>(player->speed * 10), static_cast<int>(player->_lifevalue * 10), player->Hp_limit,
		static_cast<int>(player->power * 10), static_cast<int>(player->attack_len * 10),
		static_cast<int>(player->defend * 10),
		player->front, player->left, player->right, player->back);



	for (int i = 1; i <= 2; i++)
		unchoose[i] = false;
	unchoose[player->weapon - 1] = true;

	if (player->left == 1)
		unchoose[8] = true;

	if (player->speed <= 2)
		unchoose[15] = true;
	else unchoose[15] = false;

	if (player->attack_CD <= 0.4)
		unchoose[14] = true;


}