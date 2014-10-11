/*
 * Player.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: war1oc
 */

#include "Player.h"

Player::~Player()
{
	CC_SAFE_RELEASE(idleAnimate);
	CC_SAFE_RELEASE(moveAnimate);
}

Player * Player::create()
{
	Player * player = new Player();
	if(player && player->initWithFile("idle_1.png"))
	{
		player->autorelease();
		player->initPlayer();
		return player;
	}

	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initPlayer()
{
	moving = false;
	char str[100] = {0};

	Vector<SpriteFrame*> idleAnimFrames(6);
	for(int i = 1; i <= 2; i++) //Iterate for the number of images you have
	{
		sprintf(str, "idle_%i.png",i);
		auto frame = SpriteFrame::create(str,Rect(0,0,40,160)); //The size of the images in an action should be the same
		idleAnimFrames.pushBack(frame);
	}

	auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.20f);
	idleAnimate = Animate::create(idleAnimation);
	idleAnimate->retain(); //Retain to use it later
	this->runAction(RepeatForever::create(idleAnimate)); //This will be the starting animation

	Vector<SpriteFrame*> moveAnimFrames(6);
	for(int i = 1; i <= 4; i++)
	{
		sprintf(str, "move_%i.png",i);
		auto frame = SpriteFrame::create(str,Rect(0,0,68,160));
		moveAnimFrames.pushBack(frame);
	}

	auto moveAnimation = Animation::createWithSpriteFrames(moveAnimFrames, 0.09f);
	moveAnimate = Animate::create(moveAnimation);
	moveAnimate->retain();
}

void Player::move(int directionParam)
{
	this->stopAllActions();
	this->runAction(RepeatForever::create(moveAnimate));

	direction = directionParam;
	moving = true;
}

void Player::idle()
{
	moving = false;
	this->stopAllActions();
	this->runAction(RepeatForever::create(idleAnimate));
}

void Player::update()
{
	if(moving) //check if moving
	{
		if(direction == 0) //check if going left
		{
			this->setScaleX(-1); //flip
			this->setPositionX(this->getPositionX() - 5);
		}
		else
		{
			this->setScaleX(1); //flip
			this->setPositionX(this->getPositionX() + 5);
		}
	}
}
