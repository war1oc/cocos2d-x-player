/*
 * Player.h
 *
 *  Created on: Oct 11, 2014
 *      Author: war1oc
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class Player : public cocos2d::Sprite {
public:
	Animate * idleAnimate;
	Animate * moveAnimate;

	static Player * create(void);
	void move(int directionParam);
	void idle();

	void update();

private:
	~Player();

	bool moving;
	int direction;

	void initPlayer();
};

#endif /* PLAYER_H_ */
