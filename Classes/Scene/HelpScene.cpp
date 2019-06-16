#include"Scene/HelpScene.h"
#include"Tool/GameAudio.h"
#include"scene/LoginScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
Scene* HelpSceneOne::createScene()
{
	auto scene = Scene::create();

	auto layer = HelpSceneOne::create();

	scene->addChild(layer);

	return scene;
}

bool HelpSceneOne::init()
{
	if (!Layer::init()) {
		return false;
	}
	/****************************************************************************************/
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto last_button = Button::create("blue_button01.png");
	last_button->setPosition(Vec2(visibleSize.width / 5, visibleSize.height*0.1));
	last_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionSlideInL::create(2.0, LoginScene/*选择界面*/::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(last_button);//设置返回键按钮，跳转到初始选择页面
/*********************************************************************************************/
	auto next_button = Button::create("blue_button01.png");
	next_button->setPosition(Vec2(visibleSize.width / 5+50, visibleSize.height*0.1));
	next_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionSlideInL::create(2.0, HelpSceneTwo/*选择界面*/::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(next_button,100);//下一界面按钮，跳转到HelpSceneTwo页面
/**********************************************************************************************/
	auto choice1 = Sprite::create("GameItem/Player/choice1.png");
	choice1->setPosition(Vec2(visibleSize.width *0.4, visibleSize.height*0.4));
	this->addChild(choice1);
	auto text1 = Text::create("nail", "Arial", 40);
	text1->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.2));
	this->addChild(text1);
	auto choice2 = Sprite::create("GameItem/Player/choice2.png");
	choice2->setPosition(Vec2(visibleSize.width *0.6, visibleSize.height*0.4));
	this->addChild(choice2);
	auto text2 = Text::create("sword", "Arial", 40);
	text2->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.2));
	this->addChild(text2);
	auto choice3 = Sprite::create("GameItem/Player/choice3.png");
	choice3->setPosition(Vec2(visibleSize.width *0.4, visibleSize.height*0.8));
	this->addChild(choice3);
	auto text3 = Text::create("kunai", "Arial", 40);
	text3->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.6));
	this->addChild(text3);
	auto choice4 = Sprite::create("GameItem/Player/choice4.png");
	choice4->setPosition(Vec2(visibleSize.width *0.6, visibleSize.height*0.8));
	this->addChild(choice4);
	auto text4 = Text::create("attack enhancement", "Arial", 40);
	text4->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.6));
	this->addChild(text4);
	auto choice5 = Sprite::create("GameItem/Player/choice5.png");
	choice5->setPosition(Vec2(visibleSize.width *0.2, visibleSize.height*0.4));
	this->addChild(choice5);
	auto text5 = Text::create("range increase", "Arial", 40);
	text5->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.2));
	this->addChild(text5);
	auto choice6 = Sprite::create("GameItem/Player/choice6.png");
	choice6->setPosition(Vec2(visibleSize.width *0.8, visibleSize.height*0.4));
	this->addChild(choice6);
	auto text6 = Text::create("defence increase", "Arial", 40);
	text6->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.2));
	this->addChild(text6);
	auto choice7 = Sprite::create("GameItem/Player/choice7.png");
	choice7->setPosition(Vec2(visibleSize.width *0.2, visibleSize.height*0.8));
	this->addChild(choice7);
	auto text7 = Text::create("double continuous fire", "Arial", 40);
	text7->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.6));
	this->addChild(text7);
	auto choice8 = Sprite::create("GameItem/Player/choice8.png");
	choice8->setPosition(Vec2(visibleSize.width *0.8, visibleSize.height*0.8));
	this->addChild(choice8);
	auto text8 = Text::create("twins", "Arial", 40);
	text8->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.6));
	this->addChild(text8);

	return true;
}

void HelpSceneOne::onEnter()
{
	Layer::onEnter();
	/////////////////////////////////////////
	GameAudio::getInstance()->playMusic("Music/");
}

Scene* HelpSceneTwo::createScene()
{
	auto scene = Scene::create();

	auto layer = HelpSceneTwo::create();

	scene->addChild(layer);

	return scene;
}

bool HelpSceneTwo::init()
{
	if (!Layer::init()) {
		return false;
	}
	/****************************************************************************************/
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto last_button = Button::create("blue_button01.png");
	last_button->setPosition(Vec2(visibleSize.width / 5, visibleSize.height*0.1));
	last_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionSlideInL::create(2.0, HelpSceneOne/*HelpOne界面*/::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(last_button,100);//设置返回键按钮，跳转到HelpSceneOne页面
/*********************************************************************************************/
	//auto next_button = Button::create("right.png");
	//next_button->setPosition(Vec2(visibleSize.width / 5, visibleSize.height*0.1));
	//next_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
	//	if (type == Widget::TouchEventType::ENDED) {
	//		auto transition = TransitionSlideInL::create(2.0, HelpSceneTwo/*选择界面*/::createScene());
	//		Director::getInstance()->replaceScene(transition);
	//	}
//	});
	//this->addChild(next_button);//下一界面按钮，跳转到HelpSceneTwo页面
/**********************************************************************************************/
	auto choice1 = Sprite::create("GameItem/Player/choice9.png");
	choice1->setPosition(Vec2(visibleSize.width *0.4, visibleSize.height*0.4));
	this->addChild(choice1);
	auto text1 = Text::create("nail", "Arial", 40);
	text1->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.2));
	this->addChild(text1);
	auto choice2 = Sprite::create("GameItem/Player/choice10.png");
	choice2->setPosition(Vec2(visibleSize.width *0.6, visibleSize.height*0.4));
	this->addChild(choice2);
	auto text2 = Text::create("sword", "Arial", 40);
	text2->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.2));
	this->addChild(text2);
	auto choice3 = Sprite::create("GameItem/Player/choice11.png");
	choice3->setPosition(Vec2(visibleSize.width *0.4, visibleSize.height*0.8));
	this->addChild(choice3);
	auto text3 = Text::create("kunai", "Arial", 40);
	text3->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.6));
	this->addChild(text3);
	auto choice4 = Sprite::create("GameItem/Player/choice12.png");
	choice4->setPosition(Vec2(visibleSize.width *0.6, visibleSize.height*0.8));
	this->addChild(choice4);
	auto text4 = Text::create("attack enhancement", "Arial", 40);
	text4->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.6));
	this->addChild(text4);
	auto choice5 = Sprite::create("GameItem/Player/choice13.png");
	choice5->setPosition(Vec2(visibleSize.width *0.2, visibleSize.height*0.4));
	this->addChild(choice5);
	auto text5 = Text::create("range increase", "Arial", 40);
	text5->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.2));
	this->addChild(text5);
	auto choice6 = Sprite::create("GameItem/Player/choice14.png");
	choice6->setPosition(Vec2(visibleSize.width *0.8, visibleSize.height*0.4));
	this->addChild(choice6);
	auto text6 = Text::create("defence increase", "Arial", 40);
	text6->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.2));
	this->addChild(text6);
	auto choice7 = Sprite::create("GameItem/Player/choice15.png");
	choice7->setPosition(Vec2(visibleSize.width *0.2, visibleSize.height*0.8));
	this->addChild(choice7);
	auto text7 = Text::create("double continuous fire", "Arial", 40);
	text7->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.6));
	this->addChild(text7);
	auto choice8 = Sprite::create("GameItem/Player/choice16.png");
	choice8->setPosition(Vec2(visibleSize.width *0.8, visibleSize.height*0.8));
	this->addChild(choice8);
	auto text8 = Text::create("twins", "Arial", 40);
	text8->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.6));
	this->addChild(text8);

	return true;
}



void HelpSceneTwo::onEnter()
{
	Layer::onEnter();
	/////////////////////////////////////////
	GameAudio::getInstance()->playMusic("Music/");
}