/*
=================
cAlien.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cAlien.h"
/*
=================
- Data constructor initializes the cAlien to the data passed to 
- the constructor from the paramater sPosition.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
cAlien::cAlien(): cSprite() 			// Default constructor
{
	mActive = true;
	/* initialize random seed: */
	srand ( (unsigned int)time(NULL) );
	/* generate secret number: */
	mScore = (rand() % 10 + 1)*10;
	mDirection = static_cast<eDirection>(rand() % 2);
}
cAlien::cAlien(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename): cSprite(sPosition,pd3dDevice,theFilename)  // Constructor
{
	mActive = true;
	/* initialize random seed: */
	srand ( (unsigned int)time(NULL) );
	/* generate secret number: */
	mScore = (rand() % 10 + 1)*10;
	mDirection = static_cast<eDirection>(rand() % 2);
}
/*
=================
- update the position etc of the sprite.
=================
*/
void cAlien::update(float deltaTime) 					// update the balloons position based on the translation
{
	D3DXVECTOR2 tempV2;
	D3DXVECTOR3 tempV3;
	tempV2 = cAlien::getSpritePos2D() + (cAlien::getTranslation())*deltaTime;
	tempV3 = D3DXVECTOR3(tempV2.x,tempV2.y,0.0f);
	cAlien::setSpritePos(tempV3);
	cSprite::update();
}
/*
=================
- Returns the current direction of the sprite.
=================
*/
eDirection cAlien::getDirection()       // Rturns the current direction of the sprite
{
	return cAlien::mDirection;
}
/*
=================
- Sets the current direction for the sprite.
=================
*/
void cAlien::setDirection(eDirection theDirection)  // Sets the current direction for the sprite.
{
	cAlien::mDirection = theDirection;
}

void cAlien::setActive(bool sActive) 			// Set the sprite to active.
{
	mActive = sActive;
}
/*
=================
- Determine if the sprite is active.
=================
*/
bool cAlien::isActive() 						// Determine if the sprite is active.
{
	return mActive;
}

void cAlien::setLaser(D3DXVECTOR2 laserd) 			// Set the Lasers to direction.
{
	LDirection = laserd;
}
/*
=================
- Determine if the sprite is active.
=================
*/
D3DXVECTOR2 cAlien::getLaser() 						// Get the laser's direction.
{
	return LDirection;
}

void cAlien::setfired(bool fires) 			// Set the Lasers to direction.
{
	fired = fires;
}
/*
=================
- Determine if the sprite is active.
=================
*/
bool cAlien::getfired() 						// Get the laser's direction.
{
	return fired;
}

void cAlien::setone(bool ones) 			// Set the Lasers to direction.
{
	one = ones;
}
/*
=================
- Determine if the sprite is active.
=================
*/
bool cAlien::getone() 						// Get the laser's direction.
{
	return one;
}