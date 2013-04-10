/*
=================
cBalloon.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#ifndef _CBALLOON_H
#define _CBALLOON_H
#include "cSprite.h"

class cBalloon : public cSprite
{
private:
	bool mActive;
	int mScore;
	eDirection mDirection;
	D3DXVECTOR2 LDirection;

public:
	cBalloon();
	cBalloon(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename); // Constructor
	void update(float deltaTime);					// update the balloons position based on the translation
	eDirection getDirection();      // Rturns the current direction of the sprite
	void setDirection(eDirection theDirection);
	void setActive(bool sActive);			// Set the sprite to active.
	bool isActive();
	void setLaser(D3DXVECTOR2 laserdirection);
	D3DXVECTOR2 getLaser();	// Sets the current direction for the sprite.
};
#endif