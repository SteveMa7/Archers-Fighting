#include "Player/Weapon.h"
#include"Scene/Map.h"

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}	

bool Weapon::init()
{
	//schedule(schedule_selector(Weapon::update), 0.02);
	return true;
}

void Weapon::attacking(Player *player, Point pos)
{
	belong = player;
	_collision = _tileMap->getLayer("border");
	if (belong->weapon == 1)
	{
		damage = 5;
		fly_speed = 150;
		range = 150.0;
		calculate_point(player, pos);
	}
	else if (belong->weapon == 2)
	{
		damage = 8;
		fly_speed = 140;
		range = 220;
		calculate_point(player, pos);
	}
	else if (belong->weapon == 3)
	{
		damage = 12;
		fly_speed = 150;
		range = 100;
		calculate_point(player, pos);
	}
}

void Weapon::calculate_point(Player *player, Point pos)
{                  
	fly_time = (range+belong->attack_len) / (fly_speed);
	time = 0;
	arrow_point.x = player->x_coord;
	arrow_point.y = player->y_coord;
	target.x = pos.x;
	target.y = pos.y;


	x_change = (pos.x - player->x_coord) / fly_time * 0.02;
	y_change = (pos.y - player->y_coord) / fly_time * 0.02;

}

void Weapon::hide()
{
	exist = false;
	auto del = CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, this));
	this->runAction(del);
}

void Weapon::update(float dt)
{
	if (getSprite() != NULL)
	{
		time += 0.02f;	
		if (time<fly_time)
		{
			arrow_point.x += x_change;
			arrow_point.y += y_change;
			if (check_collision(arrow_point)) 
			{
				this->setPosition(arrow_point);
				collide_judge();
			}
			else 
			{
				this->hide();
			}			
		}
		else
		{
			arrow_point = target;
			this->hide();
		}
	}
}

void Weapon::collide_judge()
{	
	if (abs(enemy->x_coord - arrow_point.x) <= 20 && abs(enemy->y_coord - arrow_point.y) <= 20)
	{
		this->hide();
		enemy->hurt(damage * belong->power);
		return;
	}
	//if (check_collision(arrow_point))
	//{
	//	this->hide();
	//	return;
	//}


}

////ÅÐ¶Ï¼ì²â
//bool Weapon::check_collision(cocos2d::Vec2 position)
//{
//	bool ans = true;
//	Vec2 tileCoord = this->tileCoordFromPosition(position);
//	int tileGid = 0;
//	if (tileCoord.x > 0 && tileCoord.x < _tileMap->getMapSize().width && tileCoord.y>0 && tileCoord.y < _tileMap->getMapSize().height)
//	{
//		tileGid = _collision->getTileGIDAt(tileCoord);
//	}	
//	if (tileGid > 0)
//	{
//		ans = false;
//	}
//	return ans;
//}

//ÅÐ¶Ï¼ì²â
bool Weapon::check_collision(cocos2d::Vec2 position)
{
	bool ans = true;
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	int tileGid = _collision->getTileGIDAt(tileCoord);
	if (tileGid > 0)
	{
		ans = false;
	}

	return ans;
}

//×ª»¯Îªtile×ø±ê
cocos2d::Vec2 Weapon::tileCoordFromPosition(cocos2d::Vec2 position) {
	int x = (int)(position.x / (_tileMap->getTileSize().width / CC_CONTENT_SCALE_FACTOR()));
	float pointHeight = _tileMap->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = (int)((_tileMap->getMapSize().height * pointHeight - position.y) / pointHeight);
	return Vec2(x, y);
}
