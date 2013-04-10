/*
=================
cBoss.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBoss.h"
/*
=================
- Data constructor initializes the cBoss to the data passed to 
- the constructor from the paramater sPosition.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
cBoss::cBoss(): cSprite() 			// Default constructor
{
	mActive = true;
	/* initialize random seed: */
	srand ( (unsigned int)time(NULL) );
	/* generate secret number: */
	mScore = (rand() % 10 + 1)*10;
	mDirection = static_cast<eDirection>(rand() % 2);
	health = 10;
}
cBoss::cBoss(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename): cSprite(sPosition,pd3dDevice,theFilename)  // Constructor
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
void cBoss::update(float deltaTime) 					// update the balloons position based on the translation
{
	D3DXVECTOR2 tempV2;
	D3DXVECTOR3 tempV3;
	tempV2 = cBoss::getSpritePos2D() + (cBoss::getTranslation())*deltaTime;
	tempV3 = D3DXVECTOR3(tempV2.x,tempV2.y,0.0f);
	cBoss::setSpritePos(tempV3);
	cSprite::update();
}
/*
=================
- Returns the current direction of the sprite.
=================
*/
eDirection cBoss::getDirection()       // Rturns the current direction of the sprite
{
	return cBoss::mDirection;
}
/*
=================
- Sets the current direction for the sprite.
=================
*/
void cBoss::setDirection(eDirection theDirection)  // Sets the current direction for the sprite.
{
	cBoss::mDirection = theDirection;
}

void cBoss::setActive(bool sActive) 			// Set the sprite to active.
{
	mActive = sActive;
}
/*
=================
- Determine if the sprite is active.
=================
*/
bool cBoss::isActive() 						// Determine if the sprite is active.
{
	return mActive;
}

void cBoss::setLaser(D3DXVECTOR2 laserd) 			// Set the Lasers to direction.
{
	LDirection = laserd;
}
/*
=================
- Determine if the sprite is active.
=================
*/
D3DXVECTOR2 cBoss::getLaser() 						// Get the laser's direction.
{
	return LDirection;
}

void cBoss::setfired(bool fires) 			// Set the Lasers to direction.
{
	fired = fires;
}
/*
=================
- Determine if the sprite is active.
=================
*/
bool cBoss::getfired() 						// Get the laser's direction.
{
	return fired;
}

void cBoss::setone(bool ones) 			// Set the Lasers to direction.
{
	one = ones;
}

bool cBoss::getone() 						// Get the laser's direction.
{
	return one;
}

void cBoss::hurt() 			// take health off
{
	health--;
}


int cBoss::gethealth() 						// Retuns the Boss' health
{
	return health;
}

void cBoss::sethealth(int hp)
{
	health = hp;
}