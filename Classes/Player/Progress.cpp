#include "Player/Progress.h"  


Progress::Progress()
	: m_progressBackground(NULL)
	, m_progressForeground(NULL)
	, m_totalProgress(0.0f)
	, m_currentProgress(0.0f)
	, m_scale(1.0f)
{

}
void Progress::Background(const char *pName)
{
	m_progressBackground = Sprite::create(pName);
	this->addChild(m_progressBackground);
}

void Progress::Fill(const char *pName)
{
	m_progressForeground = Sprite::create(pName);
	m_progressForeground->setAnchorPoint(ccp(0.0f, 0.5f));
	m_progressForeground->setPosition(ccp(-m_progressForeground->getContentSize().width * 0.5f, 0));
	this->addChild(m_progressForeground);
}

void Progress::Total_progress(float total)
{
	if (m_progressForeground == NULL)
	{
		return;
	}
	m_scale = m_progressForeground->getContentSize().width / total;
	m_totalProgress = total;
}

void Progress::Current_progress(float progress)
{
	if (m_progressForeground == NULL)
	{
		return;
	}
	if (progress < 0.0f)
	{
		progress = 0.0f;
	}
	if (progress > m_totalProgress)
	{
		progress = m_totalProgress;
	}
	m_currentProgress = progress;
	float rectWidth = progress * m_scale;
	const CCPoint from = m_progressForeground->getTextureRect().origin;
	const CCRect rect = CCRectMake(from.x, from.y, rectWidth, m_progressForeground->getContentSize().height);
	setForegroundTextureRect(rect);
}

void Progress::setForegroundTextureRect(const Rect &rect)
{
	m_progressForeground->setTextureRect(rect);
}