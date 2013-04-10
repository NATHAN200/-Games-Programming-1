/*
=================
cBalloon.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#ifndef _CLASER_H
#define _CLASER_H
#include "cSprite.h"

class cLaser : public cSprite
{
private:
	bool mActive;
	int mScore;
	eDirection mDirection;
	bool enemy;

public:
	cLaser();
	cLaser(D3DXVECTOR3 sPosition, cD3DXTexture* aTexture,D3DXVECTOR2 translation, bool isenemy); 
	cLaser(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename); // Constructor
	void update(float deltaTime);					// update the balloons position based on the translation
	eDirection getDirection();      // Rturns the current direction of the sprite
	void setDirection(eDirection theDirection);// Sets the current direction for the sprite.
	bool isActive();
	void setActive(bool sActive);
	void setEnemy(bool enemy);
	bool getEnemy();
};
#endif