#include"Scene/LoginScene.h"
#include"Settings.h"
#include"Scene/ChoosePlayerScene.h"
#include"Model/User.h"
#include"Tool/GameAudio.h"
#include"Scene/Other/CheckBox.h"
#include"Scene/SettingScene.h"
#include"Scene/HelpScene.h"
#include "client.h"


USING_NS_CC;
USING_NS_CC_EXT;

Scene* LoginScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoginScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoginScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	createBackground();
	createPrettyGirl();
	createLoginButton();
	createConsoleButton();
	createSetButton();
	createHelpButton();
	createAudioControlButton();
	createCloseButton();
	
	initUserBox();
	//chuckle = client::create();
	//chuckle->send_infor();
	//chuckle->recv_infor();
	return true;
}

void LoginScene::createBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("Scene/LoginScene/Background.jpg");
	background->setScale(0.5f);
	background->setOpacity(255);
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	

	addChild(background);
}

void LoginScene::createPrettyGirl()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//////////////////////************************
	Sprite* Girl = Sprite::create("Scene/LoginScene/Girl01.png");
	Girl->setScale(0.4f);
	Girl->setOpacity(255);
	Girl->setPosition(Vec2(visibleSize.width*1 / 11, 444));

	Sprite* DialBox = Sprite::create("Scene/LoginScene/DialBox.png");
	DialBox->setScale(1.0f);
	DialBox->setOpacity(235);
	DialBox->setPosition(Vec2(visibleSize.width * 1 / 4+30, 750));

	auto* chnString = Dictionary::createWithContentsOfFile("Scene/LoginScene/Print.xml");
	std::string str1 = ((String*)chnString->objectForKey("string01"))->getCString();
	std::string str2 = ((String*)chnString->objectForKey("string02"))->getCString();
	std::string str3 = ((String*)chnString->objectForKey("string03"))->getCString();
	std::string str4 = ((String*)chnString->objectForKey("string04"))->getCString();
	Label* label1 = Label::create(str1, Settings::Font::Type::benmo, Settings::Font::Size::large);
	Label* label2 = Label::create(str2, Settings::Font::Type::benmo, Settings::Font::Size::large);
	Label* label3 = Label::create(str3, Settings::Font::Type::benmo, Settings::Font::Size::large);
	Label* label4 = Label::create(str4, Settings::Font::Type::benmo, Settings::Font::Size::large);
	label1->setPosition(Vec2(visibleSize.width * 1 / 4 + 30, 880));
	label2->setPosition(Vec2(visibleSize.width * 1 / 4 + 30, 815));
	label3->setPosition(Vec2(visibleSize.width * 1 / 4 + 30, 750));
	label4->setPosition(Vec2(visibleSize.width * 1 / 4 + 30, 685));

	addChild(Girl);
	addChild(DialBox);
	addChild(label1);
	addChild(label2);
	addChild(label3);
	addChild(label4);
}

void LoginScene::createLoginButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto loginButton = ui::Button::create("GameItem/Button/Blue_Button_01.png");
	loginButton->setTitleText("Login");
	loginButton->setTitleFontSize(Settings::Font::Size::normal);
	loginButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *0.45));
	loginButton->setOpacity(200);
	//using lambda
	loginButton->addTouchEventListener([=](Ref * sender, ui::Widget::TouchEventType type)
	{
			if (type != ui::Widget::TouchEventType::ENDED) 
			{
				return;
			}
			auto username = usernameInput->getString();

			if (username.empty()) 
			{
				MessageBox("Username can not be empty", "Alert");
			}
			else 
			{
				username.substr(0, 16);
				UserDefault::getInstance()->setStringForKey("username", username);
				//add username to user

				User::getInstance()->setName(username);

				Director::getInstance()->replaceScene(TransitionFade::create(1.2f, ChoosePlayerScene::createScene()));
			}
	});
	addChild(loginButton);
}

void LoginScene::createConsoleButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto conSoleButton = ui::Button::create("GameItem/Button/Blue_Button_01.png");
	conSoleButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 180));
	
	conSoleButton->setScale(1.0f);
	conSoleButton->setTitleText("Console");
	conSoleButton->setTitleFontSize(Settings::Font::Size::normal);
	conSoleButton->setOpacity(200);
	conSoleButton->addTouchEventListener([=](Ref * sender, ui::Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED)
			{
				return;
			}

			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ChoosePlayerScene::createScene()));

		});

	addChild(conSoleButton);
}

void LoginScene::createSetButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto setButton = ui::Button::create("Scene/LoginScene/Setting.png");
	setButton->setPosition(Vec2(visibleSize.width*9 / 10+40, visibleSize.height*1/7));
	setButton->setOpacity(255);
	setButton->setScale(0.8f);

	setButton->addTouchEventListener([=](Ref * sender, ui::Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED) 
			{
				return;
			}

			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, SettingScene::createScene()));

		});

	addChild(setButton);

}

void LoginScene::createHelpButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto helpButton = ui::Button::create("Scene/LoginScene/Help.png");
	helpButton->setPosition(Vec2(visibleSize.width * 9 / 10+130, visibleSize.height/7));
	helpButton->setOpacity(255);
	helpButton->setScale(0.5f);

	helpButton->addTouchEventListener([=](Ref * sender, ui::Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED) 
			{
				return;
			}

			Director::getInstance()->replaceScene(TransitionFade::create(1.3f, HelpSceneOne::createScene()));

		});

	addChild(helpButton);
}

void LoginScene::createCloseButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto closeButton = ui::Button::create("GameItem/Button/CloseButton.png");
	closeButton->setPosition(Vec2(visibleSize.width * 9 / 10 + 130, visibleSize.height *5/ 6));
	closeButton->setOpacity(255);
	closeButton->setScale(1.0f);

	closeButton->addTouchEventListener([=](Ref * sender, ui::Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED)
			{
				return;
			}

			#if(CC_TARGET_PLATFORM==CC_PLATFORM_WP8)||(CC_TARGET_PLATFORM==CC_PLATFORM_WINRT)
				return;
			#endif

				Director::getInstance()->end();//win and android

		});

	addChild(closeButton);
}

void LoginScene::createAudioControlButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto soundControl = ControlSwitch::create(
		Sprite::create("Scene/LoginScene/AudioOn.png"),
		Sprite::create("Scene/LoginScene/AudioOn.png"),
		Sprite::create("Scene/LoginScene/AudioOff.png"),
		Sprite::create(),
		Label::create(),
		Label::create()
	);

	soundControl->addTargetWithActionForControlEvents(this,
		cccontrol_selector(LoginScene::soundSwitch),
		Control::EventType::VALUE_CHANGED
	);

	soundControl->setScale(0.5f);
	soundControl->setPosition(Vec2(visibleSize.width * 9 / 10 - 50, visibleSize.height / 7));

	this -> addChild(soundControl);

}

void LoginScene::initUserBox()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	usernameBG = Sprite::create("Scene/LoginScene/input_normal.png");
	usernameBG->setScale(1.2f);
	//Layer:setCascadeOpacityEnabled(true);
	usernameBG->setOpacity(120);

	usernameInput = ui::TextField::create("Input Username Here", Settings::Font::Type::benmo, Settings::Font::Size::light);
	usernameInput->setString(UserDefault::getInstance()->getStringForKey("username",""));
	
	usernameInput->setColor(Color3B::BLACK);
	usernameInput->setCursorChar('|');//Cursor
	usernameInput->setCursorEnabled(true);
	usernameInput->setMaxLength(15);
	usernameInput->setMaxLengthEnabled(true);
	usernameInput->setPosition(usernameBG->getContentSize() / 2);
	usernameInput->addEventListener(CC_CALLBACK_2(LoginScene::textFieldEvent, this));

	usernameBG->addChild(usernameInput);

	usernameBG->setScale(1.5f);
	usernameBG->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + usernameBG->getContentSize().height * 2));

	addChild(usernameBG);
	
}

void LoginScene::textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType event)
{
	/////////////////////////////////////
	switch (event) {
	case ui::TextField::EventType::ATTACH_WITH_IME://焦点进入
		usernameBG->setTexture("Scene/LoginScene/input_avtive.");
		break;
	case ui::TextField::EventType::DETACH_WITH_IME://焦点离开
		usernameBG->setTexture("Scene/LoginScene/input_normal.png");
		break;
	}
}

void LoginScene::onEnter()
{
	Layer::onEnter();
	GameAudio::getInstance()->playMusic("Music/LoginScene.mp3");
}

void LoginScene::menuBackCallBack(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

void LoginScene::soundSwitch(Ref* pSender, Control::EventType controlEvent)
{
	ControlSwitch* pSwitch = (ControlSwitch*)pSender;
	if (pSwitch->isOn()) {
		GameAudio::getInstance()->resumeMusic();
	}
	else {
		GameAudio::getInstance()->pauseMusic();
	}
}