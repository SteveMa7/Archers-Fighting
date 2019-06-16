#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include"Scene/Map.h"
#include"Player/Player.h"
#include"Player/User.h"
#include"Scene/ChoosePlayerScene.h"
#include"client.h"
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
//int player_chose;//ȫ�ֱ������ҷ�����ѡ��	

Scene* Game::createScene()
{

	return Game::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GamingScene.cpp\n");
}

bool Game::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	init_map();
	init_player();
	init_enemy();
	keyboard_listener();
	mouse_listener();

	my_player->enemy = enemy_player;
	enemy_player->enemy = my_player;

	this->schedule(schedule_selector(Game::update), 0.02f);

	return true;

}
//��ʼ����ͼ
void Game::init_map()
{
	map = new MAP();
	_tileMap = map->createmap();               //��ͼ����
	addChild(_tileMap, 1);
	_collision = map->createcollision();     //��ײ������
}
//��ʼ���ҷ�����
void Game::init_player()
{
	my_player_pos = map->createplayer_pos(1/*Client->���ܵĿͻ��˺�*/);  //�����������
	my_player->_tileMap = _tileMap;
	my_player->x_coord = my_player_pos.x;
	my_player->y_coord = my_player_pos.y;
	my_player->ID = player_chose;
	my_player->_collision = _collision;
	switch (my_player->ID)
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
	my_player->bind_Sprite(my_player->sprite);
	my_player->setScale(2.0f, 2.0f);
	my_player->setAnchorPoint(Vec2(0.5f, 0.5f));
	my_player->setPosition(Point(my_player->x_coord, my_player->y_coord));
	addChild(my_player, 10);
	setViewpointCenter(Vec2(my_player_pos.x, my_player_pos.y));
}
//��ʼ���з�����
void Game::init_enemy()
{
	enemy_player_pos = map->createplayer_pos(2/*3- Client->���ܵĿͻ��˺�*/);
	enemy_player->_tileMap = _tileMap;
	enemy_player->x_coord = enemy_player_pos.x;
	enemy_player->y_coord = enemy_player_pos.y;
	enemy_player->ID = 2/*Client->���ܵ�����ѡ��*/;
	enemy_player->_collision = _collision;
	switch (enemy_player->ID)
	{
	case 1:
		enemy_player->sprite = Sprite::create("GameItem/Player/Player1/player1_1.png");
		break;
	case 2:
		enemy_player->sprite = Sprite::create("GameItem/Player/Player2/player2_1.png");
		break;
	case 3:
		enemy_player->sprite = Sprite::create("GameItem/Player/Player3/player3_1.png");
		break;
	case 4:
		enemy_player->sprite = Sprite::create("GameItem/Player/Player4/player4_1.png");
		break;
	default:
		break;
	}
	enemy_player->bind_Sprite(enemy_player->sprite);
	enemy_player->setScale(2.0f, 2.0f);
	enemy_player->setAnchorPoint(Vec2(0.5f, 0.5f));
	enemy_player->setPosition(Point(enemy_player->x_coord, enemy_player->y_coord));
	addChild(enemy_player, 10);
}

//������
void Game::mouse_listener()
{
	auto listener1 = EventListenerTouchOneByOne::create();

	// trigger when you push down
	listener1->onTouchBegan = CC_CALLBACK_2(Game::touchBegan, this);
	listener1->onTouchEnded = CC_CALLBACK_2(Game::touchEnded, this);

	// Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

//���̼���
void Game::keyboard_listener()
{
	// ���������¼�������
	auto listener = EventListenerKeyboard::create();
	// ���ð����¼�����Ӧ����
	listener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Game::onKeyReleased, this);
	// ��ӳ��������¼�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// �����¼���Ӧ����ʵ��
void Game::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	keys[keyCode] = true;
}
//�����뿪
void Game::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	keys[keyCode] = false;
}
//�ƶ�
void Game::keyPressedDuration(EventKeyboard::KeyCode keyCode, Player *player)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (map->check_collision(Vec2(player->x_coord - 16, player->y_coord)))
		{
			player->x_coord -= 4;
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (map->check_collision(Vec2(player->x_coord + 16, player->y_coord)))
		{
			player->x_coord += 4;
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (map->check_collision(Vec2(player->x_coord, player->y_coord + 16)))
		{
			player->y_coord += 4;
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (map->check_collision(Vec2(player->x_coord, player->y_coord - 30)))
		{
			player->y_coord -= 4;
		}
		break;
	default:
		break;
	}
	player->setPosition(Vec2(player->x_coord, player->y_coord));
	if (player == my_player) {
		setViewpointCenter(Vec2(my_player_pos.x, my_player_pos.y));
	}	
}

//�ж��Ƿ���
bool Game::isKeyPressed(EventKeyboard::KeyCode keyCode, Player *player) {
	if (player == my_player) {
		if (keys[keyCode]) {
			return true;
		}
		else {
			return false;
		}
	}
	else
	{
		if (keys_enemy[keyCode]) {
			return true;
		}
		else {
			return false;
		}
	}
}

//�����ƶ�
void Game::player_move(Player *player)
{
	int i = 0;
	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	auto rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	auto upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW;
	auto downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	if (isKeyPressed(leftArrow,player))
	{
		keyPressedDuration(leftArrow,player);
		if (i == 0) {
			player->player_action(2);
		}
		i++;
	}
	if (isKeyPressed(rightArrow, player))
	{
		keyPressedDuration(rightArrow, player);
		if (i == 0) {
			player->player_action(3);
		}
		i++;
	}
	if (isKeyPressed(upArrow, player))
	{
		keyPressedDuration(upArrow, player);
		if (i == 0) {
			player->player_action(4);
		}
		i++;
	}
	if (isKeyPressed(downArrow, player))
	{
		keyPressedDuration(downArrow, player);
		if (i == 0) {
			player->player_action(1);
		}
		i++;
	}
}

void Game::update(float delta)
{
	Node::update(delta);
	Time += 1;
	player_move(my_player);
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
		my_player->expPro->ExpChange(my_player->exp, my_player->Exp_limit());			//����ֵ��
	
	float x = my_player->getPositionX(), y = my_player->getPositionY();
	my_player->x_coord = x; my_player->y_coord = y;
	setViewpointCenter(Vec2(my_player_pos.x, my_player_pos.y));
}

//ʹ��������Ļ����
void Game::setViewpointCenter(cocos2d::Vec2 position)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - visibleSize.height / 2);

	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	Vec2 pointB = Vec2(x, y);

	Vec2 offset = pointA - pointB;
	offset_pos = offset;
	this->setPosition(offset);
}

bool Game::touchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Point pos = touch->getLocation();     //�������
	pos -= offset_pos;
	my_player->attack(my_player, pos);
	return true;
}

void Game::touchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{

}

//��������ĽǶ�
float Game::calculate_angle(cocos2d::Vec2 startpos, cocos2d::Vec2 endpos)
{
	Vec2 dis = endpos - startpos;
	float angle = Vec2(dis.y, dis.x).getAngle() / 3.14f * 180;
	return angle;
}
//���������յ�����
cocos2d::Vec2 Game::calculate_pos(cocos2d::Vec2 startpos, cocos2d::Vec2 endpos, float length)
{
	cocos2d::Vec2 pos;
	float distance = (float)sqrt(pow(endpos.x - startpos.x, 2) + pow(endpos.y - startpos.y, 2));
	pos.x = (length*endpos.x - length * startpos.x + distance * startpos.x) / distance;
	pos.y = (length*endpos.y - length * startpos.y + distance * startpos.y) / distance;
	return pos;
}
//�����������
cocos2d::Vec2 Game::random_map()
{
	cocos2d::Vec2 pos;
	pos.x = rand() % 7350;
	pos.y = rand() % 3500;
	if (map->check_collision(pos))
	{
		return pos;
	}
	else
	{
		random_map();
	}
}

//����Ѫ��&����
void Game::add_something(int name)
{
	switch (name)
	{
	case 1:for (int i = 0; i < MAX_NUM_BLOOD; i++)
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

//�Ծ���Ѫ��
void Game::find_something(int name)
{
	switch (name)
	{
	case 1:for (int i = 0; i < MAX_NUM_BLOOD; i++)
	{
		if (blood[i] != nullptr)
		{

			if (abs(enemy_player->getPositionX() - blood[i]->getPositionX()) <= 25.0&&abs(enemy_player->getPositionY() - blood[i]->getPositionY()) <= 25.0)
			{
				enemy_player->Hp_Up(1);
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
			if (abs(enemy_player->getPositionX() - exe[i]->getPositionX()) <= 25.0&&abs(enemy_player->getPositionY() - exe[i]->getPositionY()) <= 25.0)
			{
				enemy_player->Exp_Up(1);
				exe[i]->runAction(FadeOut::create(0.1f));
				exe[i] = nullptr;
			}
			else if (abs(my_player->getPositionX() - exe[i]->getPositionX()) <= 25.0&&abs(my_player->getPositionY() - exe[i]->getPositionY()) <= 25.0)
			{
				my_player->Exp_Up(1);
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

void Game::menuCloseCallback(cocos2d::Ref* pSender)
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

//void Game::process_data(char *buf)
//{
//	if (buf[0] == 1) {
//		if (buf[1] == 1)
//		{
//			keys_enemy[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
//		}
//		else if (buf[1] == 2)
//		{
//			keys_enemy[EventKeyboard::KeyCode::KEY_UP_ARROW] = true;
//		}
//
//		if (buf[2] == 1)
//		{
//			keys_enemy[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;
//		}
//		else if (buf[2] == 2)
//		{
//			keys_enemy[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = true;
//		}
//
//		if (buf[3] == 1)
//		{
//			keys_enemy[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
//		}
//		else if (buf[3] == 2)
//		{
//			keys_enemy[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = true;
//		}
//
//		if (buf[4] == 1)
//		{
//			keys_enemy[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
//		}
//		else if (buf[4] == 2)
//		{
//			keys_enemy[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = true;
//		}
//
//		if (buf[5] == 1) {
//
//		}
//
//			
//			
//		
//	}
//	else if (buf[0] == 2)//������Ч
//	{
//		return;
//	}
//
//}