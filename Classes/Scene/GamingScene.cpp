#include "GamingScene.h"
#include "SimpleAudioEngine.h"
#include"Scene/Map.h"
#include"Player/Player.h"
#include"Player/User.h"
#include"Scene/ChoosePlayerScene.h"

#include <math.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#define HP_GID 137
#define EXP_GID 142
#define GAP_GID 145
#define NOR_GID 138
#define MAX_NUM_BLOOD 50
#define MAX_NUM_EXE 100

USING_NS_CC;

int player_chose;



Scene* Gaming::createScene()
{	
	return Gaming::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GamingScene.cpp\n");
}

bool Gaming::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	init_map();
	init_player();	
	init_monster();
	keyboard_listener();
	mouse_listener();

	
	my_player->enemy = monster;
	monster->enemy = my_player;

	this->schedule(schedule_selector(Gaming::update), 0.02f);

	return true;
}

void Gaming::init_map()
{
	map = new MAP();

	_tileMap = map->createmap();               //地图引入

	addChild(_tileMap,1);

	_collision = map->createcollision();     //碰撞层引入

}

void Gaming::init_player()
{	
	my_player_pos = map->createplayer_pos(1);      //人物出生坐标
	my_player->_tileMap = _tileMap;
	srand(time(NULL));		
	my_player->x_coord=my_player_pos.x;
	my_player->y_coord=my_player_pos.y;
	my_player->ID = player_chose;
	my_player->_collision = _collision;

	//my_player->_map = map;
	switch (player_chose)
	{
	case 1:
		my_player->sprite = Sprite::create("GameItem/Player/Player1/player1_1.png");
		break;
	case 2:
		my_player->sprite = Sprite::create("GameItem/Player/Player2/player2_1.png");
		break;
	case 3:
		my_player->sprite = Sprite::create("GameItem/Player/Player3/player3_1.png");
		break;
	case 4:
		my_player->sprite = Sprite::create("GameItem/Player/Player4/player4_1.png");
		break;
	default:
		break;
	}
	
	//my_player->weapon = my_player->ID;

	my_player->bind_Sprite(my_player->sprite);
	my_player->setScale(2.0f, 2.0f);

	//my_player->setAnchorPoint(Vec2(0.5f, 0.5f));

	my_player->setPosition(Point(my_player->x_coord, my_player->y_coord));
    addChild(my_player, 10);
	//setViewpointCenter(Vec2(my_player_pos.x, my_player_pos.y));
	//expPro = ExpProgress::create();
	//expPro->player = my_player;
	//addChild(expPro, 10);
}

void Gaming::init_monster()
{
	monster_pos = map->createmonster_pos();
	monster->_tileMap = _tileMap;
	srand(time(NULL));
	monster->x_coord = monster_pos.x;
	monster->y_coord = monster_pos.y;
	monster->ID = 3;
	monster->sprite = Sprite::create("GameItem/Player/Player3/player3_1.png");

	monster->bind_Sprite(monster->sprite);
	monster->setScale(2.0f, 2.0f);
	monster->setAnchorPoint(Vec2(0.5f, 0.5f));
	monster->setPosition(Point(monster->x_coord, monster->y_coord));
	monster->expPro->setVisible(false);
	addChild(monster, 10);
	//setViewpointCenter(Vec2(monster_pos.x, monster_pos.y));
}

void Gaming::mouse_listener()
{
	auto listener1 = EventListenerTouchOneByOne::create();

	// trigger when you push down
	listener1->onTouchBegan = CC_CALLBACK_2(Gaming::touchBegan, this);
	listener1->onTouchEnded = CC_CALLBACK_2(Gaming::touchEnded, this);

	// Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

void Gaming::keyboard_listener()
{
	// 创建按键事件监听器
	auto listener = EventListenerKeyboard::create();
	// 设置按键事件的响应函数
	listener->onKeyPressed = CC_CALLBACK_2(Gaming::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Gaming::onKeyReleased, this);
	// 添加场景优先事件监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 按键事件响应函数实现
void Gaming::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	keys[keyCode] = true;
}

//键盘离开
void Gaming::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	keys[keyCode] = false;
}

//移动
void Gaming::keyPressedDuration(EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		if (map->check_collision(Vec2(my_player_pos.x - 16, my_player_pos.y)))
		{
			my_player_pos.x -= 4;		
			my_player->setPosition(Vec2(my_player_pos.x,my_player_pos.y));
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		if (map->check_collision(Vec2(my_player_pos.x + 16, my_player_pos.y)))
		{
			my_player_pos.x += 4;
			my_player->setPosition(Vec2(my_player_pos.x, my_player_pos.y));
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		if (map->check_collision(Vec2(my_player_pos.x, my_player_pos.y + 16)))
		{
			my_player_pos.y += 4;
			my_player->setPosition(Vec2(my_player_pos.x, my_player_pos.y));
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		if (map->check_collision(Vec2(my_player_pos.x, my_player_pos.y - 30)))
		{
			my_player_pos.y -= 4;
			my_player->setPosition(Vec2(my_player_pos.x, my_player_pos.y));		
		}
		break;
	default:
		break;
	}
	setViewpointCenter(Vec2(my_player_pos.x, my_player_pos.y));
}

//判断是否按下
bool Gaming::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

void Gaming::player_move()
{
	int i = 0;
	auto leftArrow = EventKeyboard::KeyCode::KEY_A, rightArrow = EventKeyboard::KeyCode::KEY_D, upArrow = EventKeyboard::KeyCode::KEY_W, downArrow = EventKeyboard::KeyCode::KEY_S;

	if (isKeyPressed(leftArrow))
	{
		keyPressedDuration(leftArrow);
		if (i == 0) {
			my_player->player_action(2);
		}
		i++;
		
	}
	if (isKeyPressed(rightArrow))
	{
		keyPressedDuration(rightArrow);
		if (i == 0) {
			my_player->player_action(3);
		}
		i++;
	}
	if (isKeyPressed(upArrow))
	{
		keyPressedDuration(upArrow);
		if (i == 0) {
			my_player->player_action(4);
		}
		i++;
	}
	if (isKeyPressed(downArrow))
	{
		keyPressedDuration(downArrow);
		if (i == 0) {
			my_player->player_action(1);
		}
		i++;
	}
}

void Gaming::FakekeyPressedDuration_monster(int direction)
{
	switch (direction)
	{
	case 1:
		if (map->check_collision(Vec2(monster_pos.x - 16, monster_pos.y)))
		{
			monster_pos.x -= 4;
			monster->x_coord = monster_pos.x;
			monster->setPosition(Vec2(monster_pos.x, monster_pos.y));
			monster->player_action(2);
		}
		break;
	case 2:
		if (map->check_collision(Vec2(monster_pos.x + 16, monster_pos.y)))
		{
			monster_pos.x += 4;
			monster->x_coord = monster_pos.x;
			monster->setPosition(Vec2(monster_pos.x, monster_pos.y));
			monster->player_action(3);
		}
		break;
	case 3:
		if (map->check_collision(Vec2(monster_pos.x, monster_pos.y + 16)))
		{
			monster_pos.y += 4;
			monster->y_coord = monster_pos.y;
			monster->setPosition(Vec2(monster_pos.x, monster_pos.y));
			monster->player_action(4);
		}
		break;
	case 4:
		if (map->check_collision(Vec2(monster_pos.x, monster_pos.y - 30)))
		{
			monster_pos.y -= 4;
			monster->y_coord = monster_pos.y;
			monster->setPosition(Vec2(monster_pos.x, monster_pos.y));
			monster->player_action(1);
		}
		break;
	default:
		break;
	}
}

void Gaming::monster_random_move()
{
	srand(time(NULL));
	int move_count = rand();
	if (move_count % 4 == 0)
	{
		FakekeyPressedDuration_monster(1);
	}
	if (move_count % 4 == 1)
	{
		FakekeyPressedDuration_monster(2);
	}
	if (move_count % 4 == 2)
	{
		FakekeyPressedDuration_monster(3);
	}
	if (move_count % 4 == 3)
	{
		FakekeyPressedDuration_monster(4);
	}
}

void Gaming::monster_attack()
{
	float x = monster_pos.x - my_player_pos.x;
	float y = monster_pos.y - my_player_pos.y;
	float dis = sqrt(pow(x, 2) + pow(y, 2));
	if (dis <= 150)
	{
		monster->attack(monster, my_player_pos);
	}
}

//更新
void Gaming::update(float delta)
{
	Node::update(delta);
	Time += 1;
	player_move();
	add_something(1);
	add_something(2);
	find_something(1);
	find_something(2);

	if (my_player->expPro->ifchose)
	{		
		my_player->expPro->ifchose = 0;
	}
	if (my_player->level == 11)
		my_player->expPro->ExpChange(1, 1);
	else
		my_player->expPro->ExpChange(my_player->exp, my_player->Exp_limit());			//经验值满


	float x = my_player->getPositionX(), y = my_player->getPositionY();
	my_player->x_coord = x; my_player->y_coord = y;
	monster_random_move();
	if (Time % 10 == 0) 
	{
		monster_attack();
	}
	setViewpointCenter(Vec2(my_player_pos.x, my_player_pos.y));
	
}

//使人物在屏幕中央
void Gaming::setViewpointCenter(cocos2d::Vec2 position)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - visibleSize.height / 2);

	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	Vec2 pointB = Vec2(x, y);

	Vec2 offset = pointA - pointB;
	//Point actualPosition = Point(position.x, position.y);
	//Point centerOfView = Point(visibleSize.width / 2, visibleSize.height / 2);
	//Point viewPoint = centerOfView - actualPosition;
	offset_pos = offset;
	this->setPosition(offset);
}

bool Gaming::touchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Point pos = touch->getLocation();     //鼠标坐标
	pos -= offset_pos;
	my_player->attack(my_player, pos);

	return true;
}

void Gaming::touchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{

}

//计算两点的角度
float Gaming::calculate_angle(cocos2d::Vec2 startpos, cocos2d::Vec2 endpos)
{
	Vec2 dis = endpos - startpos;
	float angle = Vec2(dis.y, dis.x).getAngle() / 3.14f * 180;
	return angle;
}
//计算武器终点坐标
cocos2d::Vec2 Gaming::calculate_pos(cocos2d::Vec2 startpos, cocos2d::Vec2 endpos, float length)
{
	cocos2d::Vec2 pos;
	float distance = (float)sqrt(pow(endpos.x - startpos.x, 2) + pow(endpos.y - startpos.y, 2));
	pos.x = (length*endpos.x - length * startpos.x + distance * startpos.x) / distance;
	pos.y = (length*endpos.y - length * startpos.y + distance * startpos.y) / distance;
	return pos;
}

//随机产生坐标
cocos2d::Vec2 Gaming::random_map()
{
	cocos2d::Vec2 pos;
	pos.x = rand()%7350;
	pos.y = rand()%3500;
	if (map->check_collision(pos))
	{
		return pos;
	}
	else
	{
		random_map();
	}
}

//生成血包&经验
void Gaming::add_something(int name)
{
	switch (name) 
	{
	case 1:for (int i = 0; i < MAX_NUM_BLOOD;i++)
	{
		if (blood[i] == nullptr)
		{
			blood[i] = Sprite::create("GameItem/Map/RED.png");
			cocos2d::Vec2 blood_pos;
			blood_pos = random_map();
			blood[i]->setPosition(blood_pos);
			addChild(blood[i], 10);
		}
	}
		   break;
	case 2:for (int i = 0; i < MAX_NUM_EXE; i++)
	{
		if (exe[i] == nullptr)
		{
			exe[i] = Sprite::create("GameItem/Map/BLUE.png");
			cocos2d::Vec2 exe_pos;
			exe_pos = random_map();
			exe[i]->setPosition(exe_pos);
			addChild(exe[i], 10);
		}
	}
		   break;
	default:
		break;
	}
	
}

//吃经验血包
void Gaming::find_something(int name)
{
	switch (name)
	{
	case 1:for (int i = 0; i < MAX_NUM_BLOOD; i++)
	{
		if (blood[i] != nullptr)
		{
		
			if (abs(monster->getPositionX() - blood[i]->getPositionX()) <= 25.0&&abs(monster->getPositionY() - blood[i]->getPositionY()) <= 25.0)
			{
				monster->Hp_Up(1);
				blood[i]->runAction(FadeOut::create(0.1f));
				blood[i] = nullptr;
			}
			else if (abs(my_player->getPositionX() - blood[i]->getPositionX()) <= 25.0&&abs(my_player->getPositionY() - blood[i]->getPositionY()) <= 25.0)
			{
				my_player->Hp_Up(1);
				blood[i]->runAction(FadeOut::create(0.1f));
				blood[i] = nullptr;
			}
		}
	}
		   break;
	case 2:for (int i = 0; i < MAX_NUM_EXE; i++)
	{
		if (exe[i] != nullptr)
		{
			if (abs(monster->getPositionX() - exe[i]->getPositionX()) <= 25.0&&abs(monster->getPositionY() - exe[i]->getPositionY()) <= 25.0)
			{
				//monster->Exp_Up(1);
				exe[i]->runAction(FadeOut::create(0.1f));
				exe[i] = nullptr;
			}
			else if (abs(my_player->getPositionX() - exe[i]->getPositionX()) <= 25.0&&abs(my_player->getPositionY() - exe[i]->getPositionY()) <= 25.0)
			{
				if (my_player->Exp_Up(1))
				{
					Level_up();
				}
				exe[i]->runAction(FadeOut::create(0.1f));
				exe[i] = nullptr;
			}
		}
	}
		   break;
	default:
		break;
	}
}

void Gaming::Level_up()
{
	my_player->speed -= 1;

	char hero_mess[40];
	sprintf(hero_mess, "%d %d %d %d %d %d %d %d %d %d",
		static_cast<int>(my_player->speed * 10), static_cast<int>(my_player->_lifevalue * 10), my_player->Hp_limit,
		static_cast<int>(my_player->power * 10), static_cast<int>(my_player->attack_len * 10),
		static_cast<int>(my_player->defend * 10),
		my_player->front, my_player->left, my_player->right, my_player->back);

	my_player->expPro->LvChange(my_player->level, my_player);
}

void Gaming::menuCloseCallback(cocos2d::Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}