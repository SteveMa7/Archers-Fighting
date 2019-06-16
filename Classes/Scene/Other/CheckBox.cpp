#include"CheckBox.h"
#include"Settings.h"

USING_NS_CC;

bool CheckBox::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	createAlert();

	auto checkbox = ui::CheckBox::create("GameItem/Button/blue_button01.png","GameItem/Button/blue_button01_selected.png");
	/////////************
	checkbox->addTouchEventListener([&](cocos2d::Ref * pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
		});
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	auto loginform = Sprite::create("");
	loginform->setScale(1.5f);
	loginform->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	checkbox->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	checkbox->addEventListener(CC_CALLBACK_2(CheckBox::SelectedEvent, this));
	this->addChild(checkbox);

	return true;
}

void CheckBox::SelectedEvent(cocos2d::Ref * pSender, cocos2d::ui::CheckBox::EventType type)
{
	switch (type)
	{
	case ui::CheckBox::EventType::SELECTED:
		break;
	case ui::CheckBox::EventType::UNSELECTED:
		break;
	default:
		break;
	}
}

void CheckBox::createAlert()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	ui::Text* alert = ui::Text::create("keep login?", Settings::Font::Type::benmo, Settings::Font::Size::min);///////////////////////**************
	alert->setColor(Color3B());
	alert->setPosition(Vec2(visibleSize.width * 0.25f, visibleSize.height * 0.35f));
	this->addChild(alert);
}