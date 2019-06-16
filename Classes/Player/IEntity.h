#ifndef __Entity_H__
#define __Entity_H__

#include "cocos2d.h"
USING_NS_CC;

class IEntity : public Node 
{
public:
	IEntity();
	~IEntity();
	Sprite* getSprite();	
	Sprite * my_sprite;
	void bind_Sprite(Sprite* sprite);	 

};
#endif