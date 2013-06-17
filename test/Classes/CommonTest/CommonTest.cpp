#include "CommonTest.h"
#include "../testResource.h"
#include "cocos2d.h"

TESTLAYER_CREATE_FUNC(CommonRichLabel);
TESTLAYER_CREATE_FUNC(CommonCalendar);
TESTLAYER_CREATE_FUNC(CommonLocale);
TESTLAYER_CREATE_FUNC(CommonShake);

static NEWTESTFUNC createFunctions[] = {
	CF(CommonRichLabel),
    CF(CommonCalendar),
    CF(CommonLocale),
    CF(CommonShake),
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static CCLayer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static CCLayer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static CCLayer* restartAction()
{
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

void CommonTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(nextAction());

    CCDirector::sharedDirector()->replaceScene(this);
}


std::string CommonDemo::title()
{
    return "CommonTest";
}

std::string CommonDemo::subtitle()
{
    return "";
}

void CommonDemo::onEnter()
{
    CCLayer::onEnter();

    // add title and subtitle
    std::string str = title();
    const char * pTitle = str.c_str();
    CCLabelTTF* label = CCLabelTTF::create(pTitle, "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() ) 
    {
        CCLabelTTF* l = CCLabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 60) );
    }    

    // add menu
    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(CommonDemo::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(CommonDemo::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(CommonDemo::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 1);
}

void CommonDemo::onExit()
{
    CCLayer::onExit();
}

void CommonDemo::restartCallback(CCObject* pSender)
{
    CCScene* s = new CommonTestScene();
    s->addChild( restartAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void CommonDemo::nextCallback(CCObject* pSender)
{
    CCScene* s = new CommonTestScene();
    s->addChild( nextAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void CommonDemo::backCallback(CCObject* pSender)
{
    CCScene* s = new CommonTestScene();
    s->addChild( backAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

//------------------------------------------------------------------
//
// Rich Label
//
//------------------------------------------------------------------
void CommonRichLabel::onEnter()
{
    CommonDemo::onEnter();
	
	setOpacity(255);
	setColor(ccRED);
	
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	CCRichLabelTTF* label = CCRichLabelTTF::create("H[color=ff00ff00]e我[/color]llo [color=ffffffff]W[/color]orld!",
                                                   "Helvetica",
                                                   30);
	label->enableStroke(ccBLUE, 0.5f);
	label->setPosition(ccp(origin.x + visibleSize.width / 2,
						   origin.y + visibleSize.height / 5));
	label->enableShadow(CCSizeMake(3, -3), 255, 4);
	label->setFontFillColor(ccc3(179, 179, 179));
	addChild(label);
    
    label = CCRichLabelTTF::create("H[color=ff00ff00][i][b][u]ell[/u][/b][/i][/color]o[size=20][font=font/Arial Rounded MT Bold.ttf]H[i]ell[/i]o[/font][/size]",
                                   "Helvetica",
                                   30);
	label->setPosition(ccp(origin.x + visibleSize.width / 2,
						   origin.y + visibleSize.height * 2 / 5));
	addChild(label);
}

std::string CommonRichLabel::subtitle()
{
    return "Rich Label";
}

//------------------------------------------------------------------
//
// Locale
//
//------------------------------------------------------------------
void CommonLocale::onEnter()
{
    CommonDemo::onEnter();
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLocale* locale = CCLocale::sharedLocale();
    char buf[512];
    sprintf(buf, "language=%s\ncountry=%s",
            locale->getLanguage().c_str(),
            locale->getCountry().c_str());
    
    CCLabelTTF* label = CCLabelTTF::create(buf, "Helvetica", 16);
    label->setPosition(ccp(origin.x + visibleSize.width / 2,
                           origin.y + visibleSize.height / 2));
    addChild(label);
}

std::string CommonLocale::subtitle()
{
    return "Locale";
}

//------------------------------------------------------------------
//
// Calendar
//
//------------------------------------------------------------------
void CommonCalendar::onEnter()
{
    CommonDemo::onEnter();
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCCalendar* c = CCCalendar::sharedCalendar();
    char buf[512];
    sprintf(buf, "time=%f\nyear=%d\nmonth=%d\nday=%d\nweekday=%d",
            c->getTime(),
            c->getYear(),
            c->getMonth(),
            c->getDay(),
            c->getWeekday());
    
    CCLabelTTF* label = CCLabelTTF::create(buf, "Helvetica", 16);
    label->setPosition(ccp(origin.x + visibleSize.width / 2,
                           origin.y + visibleSize.height / 2));
    addChild(label);
}

std::string CommonCalendar::subtitle()
{
    return "Calendar";
}

//------------------------------------------------------------------
//
// Shake
//
//------------------------------------------------------------------
void CommonShake::onEnter()
{
    CommonDemo::onEnter();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	CCSprite* s = CCSprite::create("Images/grossini.png");
	s->setPosition(ccp(origin.x + visibleSize.width / 2,
					   origin.y + visibleSize.height / 2));
	addChild(s);
	
	s->runAction(CCRepeatForever::create(CCShake::create(1, 5)));
}

std::string CommonShake::subtitle()
{
    return "Shake";
}

