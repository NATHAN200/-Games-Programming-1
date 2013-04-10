/*
=================
cBalloon.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#ifndef _CBOSS_H
#define _CBOSS_H
#include "cSprite.h"

class cBoss : public cSprite
{
private:
	bool mActive;
	int mScore;
	eDirection mDirection;
	D3DXVECTOR2 LDirection;
	bool fired;
	bool one;
	int health;

public:
	cBoss();
	cBoss(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename); // Constructor
	void update(float deltaTime);					// update the balloons position based on the translation
	eDirection getDirection();      // Rturns the current direction of the sprite
	void setDirection(eDirection theDirection);
	void setActive(bool sActive);			// Set the sprite to active.
	bool isActive();
	void setLaser(D3DXVECTOR2 laserdirection);
	D3DXVECTOR2 getLaser();	
	void setfired(bool fire);
	bool getfired();
	void setone(bool ones);
	bool getone();
	void hurt();
	int gethealth();
	void sethealth(int hp);	// Sets the current direction for the sprite.
};
#endif