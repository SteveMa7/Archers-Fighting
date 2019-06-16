#ifndef __MAP_H__
#define __MAP_H__

#include "cocos2d.h"
#include"Player/Player.h"
#include"Player/Weapon.h"
#include <vector>
#include<iostream>


USING_NS_CC;
using namespace std;

class MAP :public cocos2d::Scene
{
	 cocos2d::TMXTiledMap *_tileMap;
	 cocos2d::Sprite *_player;
	 cocos2d::Sprite *_monster;
	 cocos2d::TMXLayer * _collision;
	 cocos2d::Vec2 mapSize;
	
public: 
	cocos2d::TMXLayer * createcollision();
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	static cocos2d::Scene *createScene();
	cocos2d::Vec2 createplayer_pos(int Tag);
	cocos2d::Vec2 createmonster_pos();
	cocos2d::TMXTiledMap *createmap();
	virtual bool init();

	bool check_collision(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	
	CREATE_FUNC(MAP);

};

#endif //__MAP_H__