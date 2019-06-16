
#ifndef __PLAYER__H_
#define __PLAYER__H_
#include<iostream>
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include"Player/IEntity.h"
#include"Scene/Map.h"
#include"Player/Weapon.h"


USING_NS_CC;
using namespace ui;
class  Weapon;
class ExpProgress;
class Progress;
class  Player :public IEntity
{
public:
	CREATE_FUNC(Player);
	virtual bool init();

	Size visibleSize = CCDirector::getInstance()->getVisibleSize();

	
	/*************************************人物基础******************************************/
	Sprite *sprite ;
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer * _collision;
	LoadingBar *loadingBar;
	//MAP * _map= new MAP();
	Player *enemy;
	ExpProgress *expPro;
	Label *lv;

	int ID=1;                    //人物id就是人物选择
	bool Is_life = true;		 //死亡判定
	bool attackcd = false;     //是否在攻击CD中
	bool  animating;
	int  Exp_limit();			//经验值满
	LoadingBar* _HP;          //血条
	float _HPInterval;            //血条更新量
	//帧动画
	cocos2d::Animation *  front_Animation;
	cocos2d::Animation *  behind_Animation;
	cocos2d::Animation *  left_Animation;
	cocos2d::Animation *  right_Animation;
	//动画动作对象
	cocos2d::Animate *  front_Animate;
	cocos2d::Animate *  behind_Animate;
	cocos2d::Animate *  left_Animate;
	cocos2d::Animate *  right_Animate;


	void player_action(int Tag);


	/***********************************人物属性***************************************/
	float speed = 5;                                 //速度
	float power = 1.0;                              //攻击力
	float attack_len = 0.0;                         //攻击距离
	float defend = 1.0;                             //防御力
	float radius;
	float _lifevalue = 50.0;                        //当前血量
	int   Hp_limit = 50;                            //血量上限
	int level = 1;			                        //等级
	int exp = 0;			                       //当前经验值
	float x_coord = 80.0f;
	float y_coord = 80.0f;
	/*****************************************人物攻击***********************************/
															//子弹数量
	int front = 1;
	int left = 0;
	int right = 0;
	int back = 0;

	int weapon = 3;                                       //武器种类
	   
	float HP_UP = 1;                                      //血量增加

	float EXP_UP = 10;                                     //经验增加

	float attack_CD = 0.5;	                               //间隔时间

	/******************************与人物有关的函数***********************************/
	//void run();
	std::vector<Weapon*>bubsum;                     
	void  setlifeValue(int lifevalue)
	{
		_lifevalue = lifevalue;
	}
	int getlifeValue()
	{
		return _lifevalue;
	}
	void setHP(LoadingBar* HP)
	{
		_HP = HP;
	}
	LoadingBar* getHP()
	{
		return _HP;
	}
	void setHPInterval(float HPinterval)
	{
		_HPInterval = HPinterval;
	}
	int getHPInterval() 
	{
		return _HPInterval;
	}

	bool hurt(float attack);                                            //是否受到攻击

	//virtual void update(float dt);
	//void check_hurt_collision();
	void attack_interval();					                            //攻击间隔
	void Hp_Up(int num);		                                        //踩到道具时血量的增加
	bool Exp_Up(int num);	                                            //经验值的增加
	virtual void update(float delta);
	void attack(Player* player, Point point);                            //攻击函数
	void attackweapon(Player* player, float weapon_num, Point point,int Tag);      //产生攻击的武器
	float calculate_angle(cocos2d::Vec2 startpos, cocos2d::Vec2 endpos);
	cocos2d::Vec2 calculate_pos(cocos2d::Vec2 startpos, cocos2d::Vec2 endpos, float length,int Tag);


	void GG(int restart_x, int restart_y);			                     //死亡

	void restart(int restart_x, int restart_y);		                      //复活



private:
	Point restart_pos;

};

#endif/*defined (_PLAYER_H_)*/
