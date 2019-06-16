#ifndef _WEAPON__
#define _WEAPON__

#include "Player/IEntity.h"
#include "Player/Player.h"
#include"Scene/Map.h"

class Player;
class Weapon :public IEntity
{
public:
	Weapon();
	~Weapon();
	CREATE_FUNC(Weapon);
	virtual bool init();
	//MAP * map;
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer * _collision;
	Player *enemy;
	Player  *belong;					//子弹来源
	void attacking(Player *player, Point pos);//子弹射出
	void collide_judge();//判断碰撞
	bool exist = false;					//子弹存在
	bool real = true;					//子弹来源属于我方还是敌方
	void hide();						//删除子弹
	Point arrow_point;						//子弹当前坐标
	float time; 

	
	virtual void update(float dt);

private:
	Point target;						//攻击目标的坐标
	float x_change, y_change,r_change;	 //x y单位时间改变量

                  
	float damage;                      //伤害
	float fly_time;                    //飞行时间
	int fly_speed;                     //弹道速度
	float range;                        //攻击范围


	void calculate_point(Player *player, Point pos);
	//void arrow(Player *player, Point pos);
	//void fire(Player *player, Point pos);
	//void knife(Player *player, Point pos);
	bool check_collision(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
};


#endif
