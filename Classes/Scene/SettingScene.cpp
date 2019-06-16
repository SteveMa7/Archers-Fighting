#include"Scene/SettingScene.h"
#include"Settings.h"
#include"Tool/GameAudio.h"

USING_NS_CC;

Scene* SettingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SettingScene::create();

	scene->addChild(layer);

	return scene;
}

bool SettingScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	return true;
}

void SettingScene::onEnter()
{
	Layer::onEnter();
	//////////////////************************
	GameAudio::getInstance()->playMusic("Sound/");
}