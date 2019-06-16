#include"ChoosePlayerScene.h"
#include"SimpleAudioEngine.h"
#include"Scene/LoginScene.h"
#include"ui/CocosGUI.h"
#include"Player/User.h"
#include"Scene/GamingScene.h"
#include "Map.h"

USING_NS_CC;

Scene* ChoosePlayerScene::createScene()
{
	auto scene = Scene::create();

	auto layer = ChoosePlayerScene::create();

	scene->addChild(layer);

	return scene;
}

bool ChoosePlayerScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	createBackground();
	createPlayer();

	createReturnButton();
	createOkButton();

	return true;
}

void ChoosePlayerScene::createBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("Scene/ChoosePlayerScene/background.jpg");
	background->setScale(1.0f);
	background->setOpacity(255);
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));


	addChild(background);
}

void ChoosePlayerScene::createPlayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto* player1 = Button::create("GameItem/Player/Player1/Player01.png");
	auto* player2 = Button::create("GameItem/Player/Player2/Player02.png");
	auto* player3 = Button::create("GameItem/Player/Player3/Player03.png");
	auto* player4 = Button::create("GameItem/Player/Player4/Player04.png");

	player1->setPosition(Vec2(visibleSize.width * 1 / 8, visibleSize.height * 3 / 4));
	player2->setPosition(Vec2(visibleSize.width * 3 / 8, visibleSize.height * 3 / 4));
	player3->setPosition(Vec2(visibleSize.width * 5 / 8, visibleSize.height * 3 / 4));
	player4->setPosition(Vec2(visibleSize.width * 7 / 8, visibleSize.height * 3 / 4));

	player1->setScale(0.9f);
	player2->setScale(0.9f);
	player3->setScale(0.9f);
	player4->setScale(0.9f);

	this->addChild(player1);
	this->addChild(player2);
	this->addChild(player3);
	this->addChild(player4);

	player1->addTouchEventListener([=](Ref * pSender, Widget::TouchEventType type) {
		if (type != ui::Widget::TouchEventType::ENDED)
		{
			return;
		}
		if (playerChosen != "1") {
			player1->setScale(1.1f);
			player2->setScale(0.9f);
			player3->setScale(0.9f);
			player4->setScale(0.9f);
		}
		playerChosen = "1";

	});

	player2->addTouchEventListener([=](Ref * pSender, Widget::TouchEventType type) {
		if (type != ui::Widget::TouchEventType::ENDED)
		{
			return;
		}

		if (playerChosen != "2") {
			player1->setScale(0.9f);
			player2->setScale(1.1f);
			player3->setScale(0.9f);
			player4->setScale(0.9f);
		}
		playerChosen = "2";

	});

	player3->addTouchEventListener([=](Ref * pSender, Widget::TouchEventType type) {
		if (type != ui::Widget::TouchEventType::ENDED)
		{
			return;
		}

		if (playerChosen != "3") {
			player1->setScale(0.9f);
			player2->setScale(0.9f);
			player3->setScale(1.1f);
			player4->setScale(0.9f);
		}
		playerChosen = "3";

	});

	player4->addTouchEventListener([=](Ref * pSender, Widget::TouchEventType type) {
		if (type != ui::Widget::TouchEventType::ENDED)
		{
			return;
		}

		if (playerChosen != "1") {
			player1->setScale(0.9f);
			player2->setScale(0.9f);
			player3->setScale(0.9f);
			player4->setScale(1.1f);
		}
		playerChosen = "4";

	});

}

void ChoosePlayerScene::createReturnButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto returnButton = ui::Button::create("GameItem/Button/ReturnButton.png");
	returnButton->setPosition(Vec2(visibleSize.width * 9 / 10 + 130, visibleSize.height / 7));
	returnButton->setOpacity(255);
	returnButton->setScale(1.0f);

	returnButton->addTouchEventListener([=](Ref * sender, ui::Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED)
			{
				return;
			}

			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LoginScene::createScene()));

		});

	addChild(returnButton);
}

void ChoosePlayerScene::createOkButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto okButton = ui::Button::create("GameItem/Button/OkButton.png");
	okButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 7));
	okButton->setOpacity(255);
	okButton->setScale(1.0f);

	okButton->addTouchEventListener([=](Ref * sender, ui::Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED)
			{
				return;
			}

			if (playerChosen == "no") {
				MessageBox("You should choose your role !", "Alert");
			}
			else 
			{
				User::getInstance()->setRole(playerChosen);

				if (playerChosen == "1")player_chose = 1;
				if (playerChosen == "2")player_chose = 2;
				if (playerChosen == "3")player_chose = 3;
				if (playerChosen == "4")player_chose = 4;
			
				Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Gaming::createScene()));


				
			}
			

		});

	addChild(okButton);
}