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
	Player  *belong;					//�ӵ���Դ
	void attacking(Player *player, Point pos);//�ӵ����
	void collide_judge();//�ж���ײ
	bool exist = false;					//�ӵ�����
	bool real = true;					//�ӵ���Դ�����ҷ����ǵз�
	void hide();						//ɾ���ӵ�
	Point arrow_point;						//�ӵ���ǰ����
	float time; 

	
	virtual void update(float dt);

private:
	Point target;						//����Ŀ�������
	float x_change, y_change,r_change;	 //x y��λʱ��ı���

                  
	float damage;                      //�˺�
	float fly_time;                    //����ʱ��
	int fly_speed;                     //�����ٶ�
	float range;                        //������Χ


	void calculate_point(Player *player, Point pos);
	//void arrow(Player *player, Point pos);
	//void fire(Player *player, Point pos);
	//void knife(Player *player, Point pos);
	bool check_collision(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
};


#endif
