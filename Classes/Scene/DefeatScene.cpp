#include"Scene/DefeatScene.h"
#include"Tool/GameAudio.h"
#include"scene/LoginScene.h"
#include "ui/CocosGUI.h"
#include"Settings.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

Scene* DefeatScene::createScene()
{
	auto scene = Scene::create();

	auto layer = DefeatScene::create();

	scene->addChild(layer);

	return scene;
}

bool DefeatScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	createBackground();
	createReturnButton();
	createPrettyGirl();
	return true;
}

void  DefeatScene::createBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("Scene/finish_background.jpg");
	background->setScale(1.0f);
	background->setOpacity(255);
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));


	addChild(background,1);
}
void DefeatScene::createPrettyGirl()//����һ��girl 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//////////////////////************************
	Sprite* Girl = Sprite::create("GameItem/Girl/PrettyGirl.png");
	Girl->setScale(0.6f);
	Girl->setOpacity(255);
	Girl->setPosition(Vec2(visibleSize.width * 1 / 9, 444));//girl position 

	Sprite* DialBox = Sprite::create("Scene/LoginScene/DialBox.png");//�Ի��� 
	DialBox->setScale(1.0f);
	DialBox->setOpacity(235);
	DialBox->setPosition(Vec2(visibleSize.width * 1 / 4 + 30, 750));

	/*auto text1 = Text::create("�����أ�����", "Arial", 40);
	text1->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.4));//����ı�����λ��

	auto text2 = Text::create("��Ҫ���ģ���", "Arial", 40);
	text2->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.3));//����ı�����λ��

	auto text3 = Text::create("�μ���Ŷ��", "Arial", 40);
	text3->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.2));//����ı�����λ��*/
	auto* chnString = Dictionary::createWithContentsOfFile("Scene/LoginScene/defeat.xml");
	std::string str1 = ((String*)chnString->objectForKey("string01"))->getCString();
	std::string str2 = ((String*)chnString->objectForKey("string02"))->getCString();
	std::string str3 = ((String*)chnString->objectForKey("string03"))->getCString();
	//std::string str4 = ((String*)chnString->objectForKey("string04"))->getCString();
	Label* label1 = Label::create(str1, Settings::Font::Type::benmo, Settings::Font::Size::large);
	Label* label2 = Label::create(str2, Settings::Font::Type::benmo, Settings::Font::Size::large);
	Label* label3 = Label::create(str3, Settings::Font::Type::benmo, Settings::Font::Size::large);
	//Label* label4 = Label::create(str4, Settings::Font::Type::benmo, Settings::Font::Size::large);
	label1->setPosition(Vec2(visibleSize.width * 1 / 4 + 30,835));
	label2->setPosition(Vec2(visibleSize.width * 1 / 4 + 30, 775));
	label3->setPosition(Vec2(visibleSize.width * 1 / 4 + 30, 715));

	addChild(Girl,3);
	addChild(DialBox,2);
	addChild(label1,5);
	addChild(label2,5);
	addChild(label3,5);
}
void DefeatScene::createReturnButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto return_button = Button::create("Return.png");
	return_button->setPosition(Vec2(visibleSize.width / 5, visibleSize.height*0.1));
	return_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionSlideInL::create(2.0, LoginScene/*ѡ�����*/::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	addChild(return_button,5);//���÷��ؼ���ť����ת����ʼѡ��ҳ��
}

void DefeatScene::onEnter()
{
	Layer::onEnter();
	/////////////////////////////////////////
	GameAudio::getInstance()->playMusic("Defeat.mp3");
}