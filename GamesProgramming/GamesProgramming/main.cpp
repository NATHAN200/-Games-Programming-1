/*
=================
main.cpp
Main entry point for the Card application
=================
*/

#include "GameConstants.h"
#include "GameResources.h"
#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"
#include "cAlien.h"
#include "cSprite.h"
#include "cExplosion.h"
#include "cXAudio.h"
#include "cD3DXFont.h"
#include "cLaser.h"
#include <ctime>
#include "cBoss.h"

using namespace std;

HINSTANCE hInst; // global handle to hold the application instance
HWND wndHandle; // global variable to hold the window handle

// Get a reference to the DirectX Manager
static cD3DManager* d3dMgr = cD3DManager::getInstance();
int tracker = 0;
// Get a reference to the DirectX Sprite renderer Manager 
static cD3DXSpriteMgr* d3dxSRMgr = cD3DXSpriteMgr::getInstance();
vector<cAlien*> aAlien;
vector<cAlien*>::iterator iter;
vector<cAlien*>::iterator index;
vector<cAlien*>::iterator del;
time_t timer;
time_t start;
bool deadboss = false;
bool pHit = false;
bool session = true;
int lives = 5;
int bombs = 1;
int wave = 0;
//cExplosion gExplode;
bool invulnarable = false;
bool invincible = false;
RECT clientBounds;
D3DXVECTOR2 rocketTrans = D3DXVECTOR2(300,500);
cBoss theBoss;
TCHAR szTempOutput[30];

bool bombing = false;
int enemies;
bool game = false;
bool menu = true;
bool theend = false;
bool gameOver = false;
int level = 1;
bool levelstarted = false;

bool fired = false;
bool one = false;

bool gHit = false;
char lifeStr[50];
char scoreStr[50];
char bombStr[50];
char endStr[50];
D3DXVECTOR3 expPos;
list<cExplosion*> gExplode;
list<cXAudio*> music;
list<cXAudio*>::iterator sounditer;
list<cLaser*> glaser;
list<cLaser*>::iterator iterl;
int laseriter = 0;
bool fire = true;
cXAudio gExplodeSound;
cXAudio cLaserSound;
cXAudio gameSound;
cD3DXTexture* theTextures[5];
char* theTxtres[] = {"Images\\alien.png","Images\\explosion.png","Images\\player.png","Images\\laser.png","Images\\Boss.png"};
clock_t startTime;
clock_t timepassedshoot;
clock_t timepassedbomb;
clock_t invulnearabletime;
bool pressedLeft = false;
bool pressedRight = false;
bool pressedup = false;
bool presseddown = false;
bool isfiring = false;
bool isbombing = false;
bool canhurt = true;
int score = 0;

/*
==================================================================
* LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
* LPARAM lParam)
* The window procedure
==================================================================
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Check any available messages from the queue
	switch (message)
	{
		case WM_KEYDOWN:
			{
				if(menu)
				{
					if(wParam == VK_SPACE)
					{
						menu = false;
						game = true;
						lives = 5;
						bombs = 1;
						score = 0;
						wave = 0;
						start = 0;
						rocketTrans.x = 300;
						rocketTrans.y = 500;
						theBoss.sethealth(10);
						sprintf_s( lifeStr, 50, "Lives: %d", lives);
						sprintf_s( bombStr, 50, "Bombs: %d", bombs);
						sprintf_s( scoreStr, 50, "Score: %d", score);
					}
					return 0;
				}
				if(game)
				{
					if (wParam == VK_LEFT)
					{
						pressedLeft = true;
						return 0;
					}
					if (wParam == VK_RIGHT)
					{
						pressedRight = true;
						return 0;
					}
					if (wParam == VK_UP)
					{
						pressedup = true;
						return 0;
					}
					if (wParam == VK_DOWN)
					{
						presseddown = true;
						return 0;
					}
					if(wParam == 0x58)
					{
						
 						if(bombs > 0)
						{	
							
							bombs--;
							isbombing = true;
							sprintf_s( bombStr, 50, "Bombs: %d", bombs);
							
						}
						return 0;
					}
					if(wParam == 0x5A)
					{
						isfiring = true;
						return 0;
					}
				}

				if(theend)
				{
					if(wParam == VK_SPACE)
					{
						menu = true;
						theend = false;
						levelstarted = false;
						return 0;
					}
				}

				if(gameOver)
				{
					if(wParam == VK_SPACE)
					{
						gameOver = false;
						menu = true;
					}
				}
				return 0;
			}

		case WM_KEYUP:
		{
					if (wParam == VK_LEFT)
					{
						pressedLeft = false;
						return 0;
					}
					if (wParam == VK_RIGHT)
					{
						pressedRight = false;
						return 0;
					}
					if (wParam == VK_UP)
					{
						pressedup = false;
						return 0;
					}
					if (wParam == VK_DOWN)
					{
						presseddown = false;
						return 0;
					}
					if(wParam == 0x5A)
					{
						isfiring = false;
						return 0;
					}
					return 0;
		}

		case WM_CLOSE:
			{
			// Exit the Game
				PostQuitMessage(0);
				 return 0;
			}

		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
	}
	// Always return the message to the default window
	// procedure for further processing
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*
==================================================================
* bool initWindow( HINSTANCE hInstance )
* initWindow registers the window class for the application, creates the window
==================================================================
*/
bool initWindow( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;
	// Fill in the WNDCLASSEX structure. This describes how the window
	// will look to the system
	wcex.cbSize = sizeof(WNDCLASSEX); // the size of the structure
	wcex.style = CS_HREDRAW | CS_VREDRAW; // the class style
	wcex.lpfnWndProc = (WNDPROC)WndProc; // the window procedure callback
	wcex.cbClsExtra = 0; // extra bytes to allocate for this class
	wcex.cbWndExtra = 0; // extra bytes to allocate for this instance
	wcex.hInstance = hInstance; // handle to the application instance
	wcex.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_MyWindowIcon)); // icon to associate with the application
	wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_GUNSIGHT));// the default cursor
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // the background color
	wcex.lpszMenuName = NULL; // the resource name for the menu
	wcex.lpszClassName = "Balloons"; // the class name being created
	wcex.hIconSm = LoadIcon(hInstance,"Balloon.ico"); // the handle to the small icon

	RegisterClassEx(&wcex);
	// Create the window
	wndHandle = CreateWindow("Balloons",			// the window class to use
							 "Save the Universe!",			// the title bar text
							WS_OVERLAPPEDWINDOW,	// the window style
							CW_USEDEFAULT, // the starting x coordinate
							CW_USEDEFAULT, // the starting y coordinate
							800, // the pixel width of the window
							600, // the pixel height of the window
							NULL, // the parent window; NULL for desktop
							NULL, // the menu for the application; NULL for none
							hInstance, // the handle to the application instance
							NULL); // no values passed to the window
	// Make sure that the window handle that is created is valid
	if (!wndHandle)
		return false;
	// Display the window on the screen
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);
	return true;
}

/*
==================================================================
// This is winmain, the main entry point for Windows applications
==================================================================
*/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	// Initialize the window
	if ( !initWindow( hInstance ) )
		return false;
	// called after creating the window
	if ( !d3dMgr->initD3DManager(wndHandle) )
		return false;
	if ( !d3dxSRMgr->initD3DXSpriteMgr(d3dMgr->getTheD3DDevice()))
		return false;

	// Grab the frequency of the high def timer
	__int64 freq = 0;				// measured in counts per second;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	float sPC = 1.0f / (float)freq;			// number of seconds per count

	__int64 currentTime = 0;				// current time measured in counts per second;
	__int64 previousTime = 0;				// previous time measured in counts per second;
	__int64 previousshoottime = 0;

	float numFrames   = 0.0f;				// Used to hold the number of frames
	float timeElapsed = 0.0f;				// cumulative elapsed time

	GetClientRect(wndHandle,&clientBounds);

	float fpsRate = 1.0f/25.0f;

	D3DXVECTOR3 aAlienPos;

	sprintf_s( lifeStr, 50, "Lives:%d", lives);

	//===========================================================
	// Load three textures for the balloons; yellow, green, red
	//===========================================================
	for (int txture = 0; txture < 5; txture++)
	{
		theTextures[txture] = new cD3DXTexture(d3dMgr->getTheD3DDevice(), theTxtres[txture]);
	}


	D3DXVECTOR3 AlienPos;
	D3DXVECTOR3 laserPos;

	LPDIRECT3DSURFACE9 GameBackground;
	LPDIRECT3DSURFACE9 EndBackground;		
	LPDIRECT3DSURFACE9 MenuBackground;	
	LPDIRECT3DSURFACE9 GameOverBackground;		// the Direct3D surface
	LPDIRECT3DSURFACE9 theBackbuffer = NULL;  // This will hold the back buffer
	
	D3DXVECTOR3 rocketPos = D3DXVECTOR3(300,500,0);
	cSprite theRocket;
	theRocket.setSpritePos(rocketPos);
	theRocket.setTranslation(D3DXVECTOR2(5.0f,0.0f));	//create the players character
	theRocket.setTexture(theTextures[(2)]);
	startTime = clock();
	theBoss.setTranslation(D3DXVECTOR2(0.0f,0.0f)); // ready the boss
	theBoss.setTexture(theTextures[4]);
	theBoss.setSpritePos(D3DXVECTOR3((float)clientBounds.right/2 - (float)clientBounds.right/4,50,0));
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	// Create the background surface
	GameBackground = d3dMgr->getD3DSurfaceFromFile("Images\\Background.png"); // sets all the backgrounds
	EndBackground = d3dMgr->getD3DSurfaceFromFile("Images\\End.png");
	MenuBackground = d3dMgr->getD3DSurfaceFromFile("Images\\Start.png");
	GameOverBackground = d3dMgr->getD3DSurfaceFromFile("Images\\GameOver.png");
	gameSound.playSound(L"Sounds\\game.wav",true); // plays the background music and loops it
	// load custom font
	cD3DXFont* Font = new cD3DXFont(d3dMgr->getTheD3DDevice(),hInstance, "JI Solid Balloon Caps");


	RECT lifePos;
	RECT bombPos;
	RECT scorePos;
	RECT endPos;
	SetRect(&lifePos, 50, 10, 400, 100);
	SetRect(&scorePos, 200, 10, 400, 100);
	SetRect(&bombPos, 50, 50, 400, 100);
	SetRect(&endPos, 500,10, 400, 100);		// set up the rectagles for the text

	QueryPerformanceCounter((LARGE_INTEGER*)&previousTime);

	while( msg.message!=WM_QUIT )
	{
		// Check the message queue
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			if(menu == true)
			{

					d3dMgr->beginRender();
  					theBackbuffer = d3dMgr->getTheBackBuffer();// displays the menu background
					d3dMgr->updateTheSurface(MenuBackground, theBackbuffer);
					d3dMgr->releaseTheBackbuffer(theBackbuffer);
					d3dMgr->endRender();
			}

			else if(game == true)
			{
				time(&timer);
				startTime = clock();
				// Game code goes here
				QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
				float dt = (currentTime - previousTime)*sPC;
				// Accumulate how much time has passed.
				timeElapsed += dt;
				if(isfiring == true)
				{
					if(startTime > timepassedshoot + 500) // reload the players weapon
					{
						timepassedshoot = startTime;
						fire = true;
					}
				}
				if(invincible == true)
				{
					if(startTime > invulnearabletime + 1000) // counts down the players grace period after losing a life
					{
						
						invincible = false;
					}
				}
				if(isbombing == true) // sets a bomb off if the player has pressed the button
				{
					isbombing = false;
					if(startTime > timepassedbomb + 1000) // reloads the players bomb
					{
						timepassedbomb = startTime;
						bombing = true;
					}
				}
				if(lives == 0) // checks to see if the player has lost all their lives
				{
					game = false;
					gameOver = true;
				}
				if( timer > start + 5 && wave == 0) // spawns all enemies for the wave
				{
					enemies = 4;
					start = timer;
					wave++;
						for(int loop = 0; loop < 4; loop++)		//creates the enemies of the wave and gives them starting position and movement
						{
							if(loop == 0)
							{
								aAlien.push_back(new cAlien());
								AlienPos = D3DXVECTOR3((float)clientBounds.left - 60,200,0);
								aAlien[loop]->setTranslation(D3DXVECTOR2(100.0f,0.0f));
								aAlien[loop]->setTexture(theTextures[0]);
								aAlien[loop]->setSpritePos(AlienPos);
								aAlien[loop]->setLaser(D3DXVECTOR2(200,0.0));
							}
							if(loop == 1)
							{
								aAlien.push_back(new cAlien());
								AlienPos = D3DXVECTOR3((float)clientBounds.right + 60,200,0);
								aAlien[loop]->setTranslation(D3DXVECTOR2(-100.0f,0.0f));
								aAlien[loop]->setTexture(theTextures[0]);
								aAlien[loop]->setSpritePos(AlienPos);
								aAlien[loop]->setLaser(D3DXVECTOR2(-200,0.0));
							}
							if(loop == 2)
							{
								aAlien.push_back(new cAlien());
								AlienPos = D3DXVECTOR3((float)clientBounds.right/2,-100,0);
								aAlien[loop]->setTranslation(D3DXVECTOR2(0.0f,100.0f));
								aAlien[loop]->setTexture(theTextures[0]);
								aAlien[loop]->setSpritePos(AlienPos);
								aAlien[loop]->setLaser(D3DXVECTOR2(200,0.0));
							}
							if(loop == 3)
							{
								aAlien.push_back(new cAlien());
								AlienPos = D3DXVECTOR3((float)clientBounds.right/2,(float)clientBounds.bottom+100,0);
								aAlien[loop]->setTranslation(D3DXVECTOR2(0.0f,-100.0f));
								aAlien[loop]->setTexture(theTextures[0]);
								aAlien[loop]->setSpritePos(AlienPos);
								aAlien[loop]->setLaser(D3DXVECTOR2(-200,0.0));
							}

						}
				}

				if(theBoss.gethealth() <= 0)
				{
					game = false;
					theend = true;
				}

				if(timeElapsed > fpsRate)
				{
					if (pressedLeft == true) // moves the player if the buttons are pressed
					{
						if(rocketTrans.x > 0)
						{
							rocketTrans.x -= 10.0f;
						}
					}
					if (pressedRight == true)
					{
						if(rocketTrans.x < clientBounds.right - 60)
						{
							rocketTrans.x += 10.0f;
						}
					}
					if (pressedup == true)
					{
						if(rocketTrans.y > 0)
						{
							rocketTrans.y -= 10.0f;
						}
					}
					if (presseddown == true)
					{
						if(rocketTrans.y <clientBounds.bottom - 60)
						{
							rocketTrans.y += 10.0f;
						}
					}
					if(isfiring)
					{
						if(fire)
						{	
         					fire = false;		// checks to see if the player fired their weapons, creates lasers if they did
  							D3DXVECTOR3 rocketPos = D3DXVECTOR3(rocketTrans.x,rocketTrans.y,0);
							D3DXVECTOR3 rocketPos2 = D3DXVECTOR3(rocketTrans.x + 60.0f,rocketTrans.y,0); // starting position for the lasers
							D3DXVECTOR2 aim = D3DXVECTOR2(0.0F,-200.0F);
							glaser.push_back(new cLaser(rocketPos,theTextures[3],aim,false));
							glaser.push_back(new cLaser(rocketPos2,theTextures[3],aim,false));
							cLaserSound.playSound(L"Sounds\\laser.wav",false); // plays the laser shooting noise
						}	
					}

					rocketPos = D3DXVECTOR3(rocketTrans.x,rocketTrans.y,0);
					theRocket.setSpritePos(rocketPos);
					theRocket.update();
					theBoss.update(dt);
					if(bombing)	//checks to see if the player used a bomb if true all enemies currently in game are destroyed
					{
						bombing = false;
						for(index = aAlien.begin(); index != aAlien.end(); ++index)
						{
							expPos = (*index)->getSpritePos();
							gExplode.push_back(new cExplosion(expPos,theTextures[1]));
							gExplodeSound.playSound(L"Sounds\\explosion.wav",false);
							(*index)->setActive(false);
							score = score + 1;
							sprintf_s( scoreStr, 50, "Score: %d", score);

						}
					
					}
					if(theRocket.collidedWith(theRocket.getBoundingRect(),theBoss.getBoundingRect()) && !pHit && !invincible)
					{
							rocketTrans.x = 300;
							rocketTrans.y = 500;
							expPos = theRocket.getSpritePos();
							gExplode.push_back(new cExplosion(expPos,theTextures[1]));
							gExplodeSound.playSound(L"Sounds\\explosion.wav",false);// moves the player back to respawn point
							lives--;						//removes a player life
							sprintf_s( lifeStr, 50, "Lives: %d", lives);
							pHit = true;
							invincible = true;
							invulnearabletime = startTime;
					}
					for(iterl = glaser.begin(); iterl != glaser.end(); ++iterl)
					{
						laserPos =(*iterl)->getSpritePos();
						(*iterl)->update(timeElapsed);
						if (laserPos.x>(clientBounds.right) || laserPos.x < -30 || laserPos.y>(clientBounds.bottom + 60) || laserPos.y < -30) // sets the laser to be destroyed if it hits the outside of the screen
						{
							(*iterl)->setActive(false);
						}
						else
						{
							for(index = aAlien.begin(); index != aAlien.end(); ++index) // checks all lasers to see if they hit an enemy
							{
								if ((*iterl)->collidedWith((*iterl)->getBoundingRect(),(*index)->getBoundingRect()) && !gHit)
								{
								gHit = true;
								OutputDebugString("Collision!!");
								(*iterl)->setActive(false);		// sets the laser to be destroyed if it hit an enemy
								(*index)->setActive(false);		// sets the enemy to be destroyed if hit by a enemy
								expPos = (*index)->getSpritePos();
								gExplode.push_back(new cExplosion(expPos,theTextures[1]));
								gExplodeSound.playSound(L"Sounds\\explosion.wav",false);
								(*index)->setActive(false);
								score = score + 1;
								sprintf_s( scoreStr, 50, "Score: %d", score);
								}
							}
						}
						if((*iterl)->collidedWith((*iterl)->getBoundingRect(),theBoss.getBoundingRect()))	//check to see if a laser hit the boss
						{
							(*iterl)->setActive(false);		//destroys the lasr
							theBoss.hurt();					//removes health from the boss
						}

					}
					gHit = false;
					iter = aAlien.begin();
					while (iter != aAlien.end() && !gHit)					// checks all enemies to see if they are set to be destroyed
					{
					
						if((*iter)->isActive() == false)
						{
							gHit = true;
							iter = aAlien.erase(iter);						// destroys any enemies that are set to be
						}
						else
						{
							++iter;
						}
					}
					gHit = false;

					for(iter = aAlien.begin(); iter != aAlien.end(); ++iter)
					{

						(*iter)->update(timeElapsed);			// update Enemy
						aAlienPos = (*iter)->getSpritePos();  // get the position of the current Enemy
						if ((*iter)->collidedWith((*iter)->getBoundingRect(),theRocket.getBoundingRect()) && !pHit && !invincible) // Checks to see if the PLayer collided with an enemy
						{
							rocketTrans.x = 300;
							rocketTrans.y = 500;
							expPos = theRocket.getSpritePos();
							gExplode.push_back(new cExplosion(expPos,theTextures[1]));
							gExplodeSound.playSound(L"Sounds\\explosion.wav",false);// moves the player back to respawn point
							lives--;						//removes a player life
							sprintf_s( lifeStr, 50, "Lives: %d", lives);
							pHit = true;
							invincible = true;
							invulnearabletime = startTime;
							
						}
						if((aAlienPos.x < -500) || aAlienPos.x > (float)clientBounds.right + 500 || (aAlienPos.y < -500) || aAlienPos.y > (float)clientBounds.bottom + 500) // destroys enemies after they leave the screen
						{
							(*iter)->setActive(false);
						}
					}
					pHit = false;
					d3dMgr->beginRender();
  					theBackbuffer = d3dMgr->getTheBackBuffer();
					d3dMgr->updateTheSurface(GameBackground, theBackbuffer);
					d3dMgr->releaseTheBackbuffer(theBackbuffer);
				
					d3dxSRMgr->beginDraw();
					d3dxSRMgr->setTheTransform(theRocket.getSpriteTransformMatrix());  
					d3dxSRMgr->drawSprite(theRocket.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					d3dxSRMgr->setTheTransform(theBoss.getSpriteTransformMatrix());  
					d3dxSRMgr->drawSprite(theBoss.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					vector<cAlien*>::iterator iterB = aAlien.begin();
					for(iterB = aAlien.begin(); iterB != aAlien.end(); ++iterB)		
					{
						d3dxSRMgr->setTheTransform((*iterB)->getSpriteTransformMatrix());  
						d3dxSRMgr->drawSprite((*iterB)->getTexture(),NULL,NULL,NULL,0xFFFFFFFF);		// draws all Enemies
				
					}
					list<cExplosion*>::iterator iter = gExplode.begin();
					while(iter != gExplode.end())
					{
						if((*iter)->isActive() == false)
						{
							iter = gExplode.erase(iter);
						}
						else
						{
							(*iter)->update(timeElapsed);
							d3dxSRMgr->setTheTransform((*iter)->getSpriteTransformMatrix());  
							d3dxSRMgr->drawSprite((*iter)->getTexture(),&((*iter)->getSourceRect()),NULL,NULL,0xFFFFFFFF); // draws all explosions
							++iter;
						}
					}

					list<cLaser*>::iterator iterC = glaser.begin();
					while(iterC != glaser.end())
					{
						if((*iterC)->isActive() == false)
						{
							iterC = glaser.erase(iterC);
						}
						else
						{

							(*iterC)->update(timeElapsed);
							d3dxSRMgr->setTheTransform((*iterC)->getSpriteTransformMatrix());  
							d3dxSRMgr->drawSprite((*iterC)->getTexture(),NULL,NULL,NULL,0xFFFFFFFF); // draw all lasers
							iterC++;
						}
					}
					d3dxSRMgr->endDraw();
					Font->printText(lifeStr,lifePos);
					Font->printText(bombStr,bombPos);
					Font->printText(scoreStr,scorePos);
					d3dMgr->endRender();
					OutputDebugString("timeElapsed > fpsRate");
					timeElapsed = 0.0f;
				}

				previousTime = currentTime;
			}

			else if(theend == true)
				{
					iter = aAlien.begin();
					while (iter != aAlien.end())		// deletes all enemies
					{
							iter = aAlien.erase(iter);
					}
					d3dMgr->beginRender();
  					theBackbuffer = d3dMgr->getTheBackBuffer();
					d3dMgr->updateTheSurface(EndBackground, theBackbuffer);						//display the background
					d3dMgr->releaseTheBackbuffer(theBackbuffer);					
					Font->printText(scoreStr,endPos);
					d3dMgr->endRender();
			}
			else if(gameOver == true)
			{
				iter = aAlien.begin();
					while (iter != aAlien.end()) // deletes all enemies
					{
							iter = aAlien.erase(iter);
					}
					d3dMgr->beginRender();
  					theBackbuffer = d3dMgr->getTheBackBuffer();
					d3dMgr->updateTheSurface(GameOverBackground, theBackbuffer);		//display the background
					d3dMgr->releaseTheBackbuffer(theBackbuffer);
					d3dMgr->endRender();

			}
		}
	}

	d3dxSRMgr->cleanUp();
	d3dMgr->clean();
	return (int) msg.wParam;
}
