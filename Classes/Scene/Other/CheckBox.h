#ifndef __CHECK_BOX_H__
#define __CHECK_BOX_H__

#include"cocos2d.h"
#include"ui/UICheckBox.h"
#include"ui/UIText.h"

class CheckBox :public cocos2d::Layer
{
private:
	cocos2d::ui::CheckBox* _checkBox;
	void createAlert();
public:
	virtual bool init();
	void SelectedEvent(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);

	CREATE_FUNC(CheckBox);
};



#endif //__CHECK_BOX_H__