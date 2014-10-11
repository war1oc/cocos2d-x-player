#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
			origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Hello World", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
			origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	player = Player::create();
	player->setPosition(Vec2(origin.x + visibleSize.width / 2
			, origin.y + visibleSize.height / 2));
	this->addChild(player, 5);

	this->scheduleUpdate();

	return true;
}

void HelloWorld::update(float dt)
{
	player->update();
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
	if(touch->getLocation().x < player->getPositionX())
	{
		player->move(0); // param '0' for left
	}
	if(touch->getLocation().x > player->getPositionX())
	{
		player->move(1); // param '0' for right
	}

	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
	player->idle();
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
