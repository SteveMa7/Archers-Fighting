#include "IEntity.h"

IEntity::IEntity()
{
	my_sprite = NULL;
}

IEntity::~IEntity()
{
}

Sprite* IEntity::getSprite()
{
	return this->my_sprite;
}

void IEntity::bind_Sprite(Sprite* sprite)
{
	this->my_sprite = sprite;
	this->addChild(my_sprite);
}
