
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

	
	/*************************************�������******************************************/
	Sprite *sprite ;
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer * _collision;
	LoadingBar *loadingBar;
	//MAP * _map= new MAP();
	Player *enemy;
	ExpProgress *expPro;
	Label *lv;

	int ID=1;                    //����id��������ѡ��
	bool Is_life = true;		 //�����ж�
	bool attackcd = false;     //�Ƿ��ڹ���CD��
	bool  animating;
	int  Exp_limit();			//����ֵ��
	LoadingBar* _HP;          //Ѫ��
	float _HPInterval;            //Ѫ��������
	//֡����
	cocos2d::Animation *  front_Animation;
	cocos2d::Animation *  behind_Animation;
	cocos2d::Animation *  left_Animation;
	cocos2d::Animation *  right_Animation;
	//������������
	cocos2d::Animate *  front_Animate;
	cocos2d::Animate *  behind_Animate;
	cocos2d::Animate *  left_Animate;
	cocos2d::Animate *  right_Animate;


	void player_action(int Tag);


	/***********************************��������***************************************/
	float speed = 5;                                 //�ٶ�
	float power = 1.0;                              //������
	float attack_len = 0.0;                         //��������
	float defend = 1.0;                             //������
	float radius;
	float _lifevalue = 50.0;                        //��ǰѪ��
	int   Hp_limit = 50;                            //Ѫ������
	int level = 1;			                        //�ȼ�
	int exp = 0;			                       //��ǰ����ֵ
	float x_coord = 80.0f;
	float y_coord = 80.0f;
	/*****************************************���﹥��***********************************/
															//�ӵ�����
	int front = 1;
	int left = 0;
	int right = 0;
	int back = 0;

	int weapon = 3;                                       //��������
	   
	float HP_UP = 1;                                      //Ѫ������

	float EXP_UP = 10;                                     //��������

	float attack_CD = 0.5;	                               //���ʱ��

	/******************************�������йصĺ���***********************************/
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

	bool hurt(float attack);                                            //�Ƿ��ܵ�����

	//virtual void update(float dt);
	//void check_hurt_collision();
	void attack_interval();					                            //�������
	void Hp_Up(int num);		                                        //�ȵ�����ʱѪ��������
	bool Exp_Up(int num);	                                            //����ֵ������
	virtual void update(float delta);
	void attack(Player* player, Point point);                            //��������
	void attackweapon(Player* player, float weapon_num, Point point,int Tag);      //��������������
	float calculate_angle(cocos2d::Vec2 startpos, cocos2d::Vec2 endpos);
	cocos2d::Vec2 calculate_pos(cocos2d::Vec2 startpos, cocos2d::Vec2 endpos, float length,int Tag);


	void GG(int restart_x, int restart_y);			                     //����

	void restart(int restart_x, int restart_y);		                      //����



private:
	Point restart_pos;

};

#endif/*defined (_PLAYER_H_)*/
