#include "Map.h"
#include "Scene/GamingScene.h"
#include "SimpleAudioEngine.h"
#include <math.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cocos2d.h>
USING_NS_CC;


Scene* MAP::createScene()
{
	return MAP::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GamingScene.cpp\n");
}

bool MAP::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	return true;
}

//返回地图
cocos2d::TMXTiledMap * MAP::createmap()
{
	//地图
	_tileMap = TMXTiledMap::create("map/map1.tmx");
	_tileMap->setAnchorPoint(ccp(0, 0));
	mapSize = _tileMap->getMapSize();
	return _tileMap;
}
//返回人物出生坐标
cocos2d::Vec2 MAP::createplayer_pos(int Tag)
{
//对象层
	TMXObjectGroup * group = _tileMap->getObjectGroup("object");
	ValueMap spawnpoint;
	if (Tag == 1) {
		spawnpoint = group->getObject("player1");
	}
	else
	{
		spawnpoint = group->getObject("player2");
	}

	cocos2d::Vec2 pos;
	//人物出生的坐标
	pos.x= spawnpoint["x"].asFloat();
	pos.y= spawnpoint["y"].asFloat();
	return pos;
}

cocos2d::Vec2 MAP::createmonster_pos()
{
	//对象层
	TMXObjectGroup * group = _tileMap->getObjectGroup("object");
	ValueMap spawnpoint = group->getObject("player2");
	cocos2d::Vec2 pos;
	//怪物出生的坐标
	pos.x = spawnpoint["x"].asFloat();
	pos.y = spawnpoint["y"].asFloat();
	return pos;
}

//返回碰撞层
cocos2d::TMXLayer* MAP::createcollision()
{
	//碰撞层检测		
	_collision = _tileMap->getLayer("border");	
	return _collision;
}

//判断检测
bool MAP::check_collision(cocos2d::Vec2 position)
{
	bool ans = true;
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	int tileGid = _collision->getTileGIDAt(tileCoord);
	if (tileGid > 0)
	{
		ans = false;
	}
	//switch (direction)
	//{
	//case 1://down
	//	if (position.y - 10 > 0 && position.y - 10 < mapSize.y)
	//	{
	//		Vec2 tileCoord1 = this->tileCoordFromPosition(Vec2(position.x, position.y - 10));
	//		int tileGid1= _collision->getTileGIDAt(tileCoord1);
	//		if (tileGid1 > 0)
	//		{
	//			ans = false;
	//		}
	//	}
	//	break;
	//case 2://left
	//	if (position.x - 10 > 0 && position.x - 10 < mapSize.x)
	//	{
	//		Vec2 tileCoord2 = this->tileCoordFromPosition(Vec2(position.x - 10, position.y));
	//		int tileGid2 = _collision->getTileGIDAt(tileCoord2);
	//		if (tileGid2 > 0)
	//		{
	//			ans = false;
	//		}
	//	}
	//	break;
	//case 3://right
	//	if (position.x + 10 > 0 && position.x + 10 < mapSize.x)
	//	{
	//		Vec2 tileCoord3 = this->tileCoordFromPosition(Vec2(position.x + 10, position.y));
	//		int tileGid3 = _collision->getTileGIDAt(tileCoord3);
	//		if (tileGid3 > 0)
	//		{
	//			ans = false;
	//		}
	//	}
	//	break;
	//case 4://up
	//	if (position.y + 10 > 0 && position.y + 10 < mapSize.y)
	//	{
	//		Vec2 tileCoord4 = this->tileCoordFromPosition(Vec2(position.x, position.y + 10));
	//		int tileGid4 = _collision->getTileGIDAt(tileCoord4);
	//		if (tileGid4 > 0)
	//		{
	//			ans = false;
	//		}
	//	}
	//	break;
	//default:
	//	break;
	//}
	return ans;
}
//转化为tile坐标
cocos2d::Vec2 MAP::tileCoordFromPosition(cocos2d::Vec2 position) {
	int x = (int)(position.x / (_tileMap->getTileSize().width / CC_CONTENT_SCALE_FACTOR()));
	float pointHeight = _tileMap->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = (int)((_tileMap->getMapSize().height * pointHeight - position.y) / pointHeight);
	return Vec2(x, y);
}