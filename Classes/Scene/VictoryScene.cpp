#include"Scene/VictoryScene.h"
#include"Tool/GameAudio.h"
#include"scene/LoginScene.h"
#include "ui/CocosGUI.h"
#include"Scene/SettingScene.h"
#include"Settings.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

Scene* VictoryScene::createScene()
{
	
	auto scene = Scene::create();
	auto layer = VictoryScene::create();

	scene->addChild(layer);

	return scene;
}

bool VictoryScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	createBackground();
	createReturnButton();
	createPrettyGirl();
	return true;
}

void  VictoryScene::createBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("Scene/finish_background.jpg");
	background->setScale(1.0f);
	background->setOpacity(255);
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));


	addChild(background,1);
}
void VictoryScene::createPrettyGirl()//创建一个girl 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//////////////////////************************
	Sprite* Girl = Sprite::create("GameItem/Girl/PrettyGirl.png");
	Girl->setScale(0.6f);
	Girl->setOpacity(255);
	Girl->setPosition(Vec2(visibleSize.width * 1 / 11, 444));//girl position 

	Sprite* DialBox = Sprite::create("Scene/LoginScene/DialBox.png");//对话框 
	DialBox->setScale(1.0f);
	DialBox->setOpacity(235);
	DialBox->setPosition(Vec2(visibleSize.width * 1 / 4 + 30, 750));

	/*auto text1 = Text::create("win the game", "Arial", 40);
	//auto text1 = Text::create("恭喜主人游戏", "Arial", 40);
	text1->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.2));//待会改变文字位置

	auto text2 = Text::create("Victory!", "Arial", 40);
	//auto text2 = Text::create("胜利了哦！", "Arial", 40);
	text2->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.2));//待会改变文字位置*/
	auto* chnString = Dictionary::createWithContentsOfFile("Scene/LoginScene/victory.xml");
	std::string str1 = ((String*)chnString->objectForKey("string01"))->getCString();
	std::string str2 = ((String*)chnString->objectForKey("string02"))->getCString();
	//std::string str3 = ((String*)chnString->objectForKey("string03"))->getCString();
	//std::string str4 = ((String*)chnString->objectForKey("string04"))->getCString();
	Label* label1 = Label::create(str1, Settings::Font::Type::benmo, Settings::Font::Size::large);
	Label* label2 = Label::create(str2, Settings::Font::Type::benmo, Settings::Font::Size::large);
	//Label* label3 = Label::create(str3, Settings::Font::Type::benmo, Settings::Font::Size::large);
	//Label* label4 = Label::create(str4, Settings::Font::Type::benmo, Settings::Font::Size::large);
	label1->setPosition(Vec2(visibleSize.width * 1 / 4 + 30, 815));
	label2->setPosition(Vec2(visibleSize.width * 1 / 4 + 30, 685));
//	label3->setPosition(Vec2(visibleSize.width * 1 / 4 + 30, 750));
	//label4->setPosition(Vec2(visibleSize.width * 1 / 4 + 30, 685));



	addChild(Girl,2);
	addChild(DialBox,2);
//	addChild(text1,3);
	//addChild(text2,3);
	addChild(label1,5);
	addChild(label2,5);
}
void VictoryScene::createReturnButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto return_button = Button::create("Return.png");
	return_button->setPosition(Vec2(visibleSize.width / 5, visibleSize.height*0.1));
	return_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionSlideInL::create(2.0, LoginScene/*选择界面*/::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	addChild(return_button,5);//设置返回键按钮，跳转到初始选择页面
}

void VictoryScene::onEnter()
{
	Layer::onEnter();
	/////////////////////////////////////////
	GameAudio::getInstance()->playMusic("Victory.mp3");
}