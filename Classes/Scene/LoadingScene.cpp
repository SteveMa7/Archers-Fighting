#include"Scene/LoadingScene.h"
#include"Scene/LoginScene.h"
#include"Settings.h"
#include"SimpleAudioEngine.h"
#include"PreloadList.h"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoadingScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	createBackground();

	addChild(createLoadingBar());

	scheduleOnce(CC_SCHEDULE_SELECTOR(LoadingScene::endLoading), 0.5);

	return true;
}

void LoadingScene::createBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* cloud = Sprite::create("Scene/LoadingScene/cloud.png");
	cloud->setScale(2.0f);
	cloud->setOpacity(255);
	cloud->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+50));
	////////////////////////****************************************
	Sprite* bar = Sprite::create("Scene/LoadingScene/loading_bar_back.png");
	bar->setScale(1.0f);
	bar->setOpacity(200);
	bar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-40));

	addChild(bar);
	addChild(cloud);
}

void LoadingScene::endLoading(float dt)
{
	const auto transition = TransitionFade::create(1, LoginScene::createScene());
	Director::getInstance()->replaceScene(transition);
}

void LoadingScene::loadSound()
{

}

void LoadingScene::loadImage()
{

}

void LoadingScene::loadSpriteFrame()
{
	auto cache = SpriteFrameCache::getInstance();

	for (auto plist : Preload::plists) 
	{
		cache->addSpriteFramesWithFile(plist);
	}
}

cocos2d::ui::LoadingBar* LoadingScene::createLoadingBar()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto loadingBar = ui::LoadingBar::create("Scene/LoadingScene/loading_bar.png");

	loadingBar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 40));
	loadingBar->setScale(1.0f);
	loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingBar->setPercent(10);

	loadSpriteFrame();
	loadingBar->setPercent(40);

	loadImage();
	loadingBar->setPercent(70);

	loadSound();
	loadingBar->setPercent(100);

	return loadingBar;
}