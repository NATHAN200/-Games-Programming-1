/*
=================
cLaser.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cLaser.h"
/*
=================
- Data constructor initializes the cLaser to the data passed to 
- the constructor from the paramater sPosition.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
cLaser::cLaser(): cSprite() 			// Default constructor
{
	/* initialize random seed: */

}

cLaser::cLaser(D3DXVECTOR3 sPosition, cD3DXTexture* aTexture,D3DXVECTOR2 translation, bool isenemy) 			// Default constructor
{
	mActive = true;
	cSprite::setTexture(aTexture);
	cSprite::setSpritePos(sPosition);
	cSprite::setTranslation(translation);
	enemy = isenemy;

}
cLaser::cLaser(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename): cSprite(sPosition,pd3dDevice,theFilename)  // Constructor
{

}
/*
=================
- update the position etc of the sprite.
=================
*/
void cLaser::update(float deltaTime) 					// update the balloons position based on the translation
{
	D3DXVECTOR2 tempV2;
	D3DXVECTOR3 tempV3;
	tempV2 = cLaser::getSpritePos2D() + (cLaser::getTranslation())*deltaTime;
	tempV3 = D3DXVECTOR3(tempV2.x,tempV2.y,0.0f);
	cLaser::setSpritePos(tempV3);
	cSprite::update();
}
/*
=================
- Returns the current direction of the sprite.
=================
*/
eDirection cLaser::getDirection()       // Rturns the current direction of the sprite
{
	return cLaser::mDirection;
}
/*
=================
- Sets the current direction for the sprite.
=================
*/
void cLaser::setDirection(eDirection theDirection)  // Sets the current direction for the sprite.
{
	cLaser::mDirection = theDirection;
}

void cLaser::setActive(bool sActive) 			// Set the sprite to active.
{
	mActive = sActive;
}
/*
=================
- Determine if the sprite is active.
=================
*/
bool cLaser::isActive() 						// Determine if the sprite is active.
{
	return mActive;
}

bool cLaser::getEnemy() 						// Determine if the Laser is hostile.
{
	return enemy;
}

void cLaser::setEnemy(bool isit) 						// set if the laser is hostile.
{
	enemy = isit;
}
