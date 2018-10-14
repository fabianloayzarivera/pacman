#include "Pacman.h"
#include "Drawer.h"
#include "SDL.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "MovableGameEntity.h"
#include "Avatar.h"
#include "World.h"
#include "Ghost.h"

Pacman* Pacman::Create(Drawer* aDrawer)
{
	Pacman* pacman = new Pacman(aDrawer);

	if (!pacman->Init())
	{
		delete pacman;
		pacman = NULL;
	}

	return pacman;
}

Pacman::Pacman(Drawer* aDrawer)
: myDrawer(aDrawer)
, myTimeToNextUpdate(0.f)
, myNextMovement(-1.f,0.f)
, myScore(0)
, myFps(0)
, myLives(3)
, myGameOver(false)
, myGameWon(false)
{
	myWorld = new World();
	Avatar* aAvatar = new Avatar(Vector2f(13*22,22*22));
	
	Ghost*  aRedGhost = new Ghost(Vector2f(13 * 22, 10 * 22), aAvatar, LEFT, CHASE, GHOST_RED);
	myEntities.push_back(aRedGhost);

	Ghost*  aBlueGhost = new Ghost(Vector2f(15 * 22, 13 * 22), aAvatar, UP, CAGE, GHOST_BLUE);
	myEntities.push_back(aBlueGhost);

	Ghost*  aOrangeGhost = new Ghost(Vector2f(13 * 22, 13 * 22), aAvatar, UP, CAGE, GHOST_ORANGE);
	myEntities.push_back(aOrangeGhost);

	Ghost*  aPinkGhost = new Ghost(Vector2f(11 * 22, 13 * 22), aAvatar, DOWN, CAGE, GHOST_PINK);
	myEntities.push_back(aPinkGhost);


	//aAvatar->SetWorld(myWorld);	
	myAvatar = aAvatar;	
	myEntities.push_back(aAvatar);
	
	
}

Pacman::~Pacman(void)
{
	//Delete list entities, avatar,world, etc
	for (std::list<MovableGameEntity*>::iterator list_iter = myEntities.begin(); list_iter != myEntities.end(); list_iter++)
	{
		delete(*list_iter);
	}
	myEntities.clear();
	delete(myWorld);
}

bool Pacman::Init()
{
	//*********** Load all the textures just once and store them in a map ****//
	
	myDrawer->LoadTexture("Big_Dot_32.png", ETextureId::BIG_DOT);
	myDrawer->LoadTexture("Small_Dot_32.png", ETextureId::DOT);
	myDrawer->LoadTexture("ghost_32_red.png", ETextureId::GHOST_RED);
	myDrawer->LoadTexture("ghost_32_cyan.png", ETextureId::GHOST_BLUE);
	myDrawer->LoadTexture("ghost_32_orange.png", ETextureId::GHOST_ORANGE);
	myDrawer->LoadTexture("ghost_32_pink.png", ETextureId::GHOST_PINK);
	myDrawer->LoadTexture("Ghost_Dead_32.png", ETextureId::GHOST_DEAD);
	myDrawer->LoadTexture("Ghost_Vulnerable_32.png", ETextureId::GHOST_CLAIMABLE);	
	myDrawer->LoadTexture("open_right_32.png", ETextureId::AVATAR_OPEN_RIGHT);
	myDrawer->LoadTexture("closed_right_32.png", ETextureId::AVATAR_CLOSED_RIGHT);
	myDrawer->LoadTexture("open_left_32.png", ETextureId::AVATAR_OPEN_LEFT);
	myDrawer->LoadTexture("closed_left_32.png", ETextureId::AVATAR_CLOSED_LEFT);
	myDrawer->LoadTexture("open_up_32.png", ETextureId::AVATAR_OPEN_UP);
	myDrawer->LoadTexture("closed_up_32.png", ETextureId::AVATAR_CLOSED_UP);
	myDrawer->LoadTexture("open_down_32.png", ETextureId::AVATAR_OPEN_DOWN);
	myDrawer->LoadTexture("closed_down_32.png", ETextureId::AVATAR_CLOSED_DOWN);
	myDrawer->LoadTexture("playfield.png", ETextureId::PLAYFIELD);
	myDrawer->LoadTexture("ghost_32.png", ETextureId::CHERRY);
	myDrawer->LoadFont("freefont-ttf\\sfd\\FreeMono.ttf", 24);
	
	for (std::list<MovableGameEntity*>::iterator list_iter = myEntities.begin(); list_iter != myEntities.end(); list_iter++)
	{
		(*list_iter)->SetGameInstance(this);
	}

	myWorld->Init();

	return true;
}

bool Pacman::Update(const float aTime)
{
	if (!UpdateInput())
		return false;

	if (CheckEndGameCondition())
	{
		myGameWon = true;
		return true;
	}
	else if (myLives <= 0)
	{
		myGameOver = true;
		return true;
	}

	for (std::list<MovableGameEntity*>::iterator list_iter = myEntities.begin(); list_iter != myEntities.end(); list_iter++)
	{
		(*list_iter)->Update(aTime);
	}

	CheckGhostsCollision();
	
	if (aTime > 0)
		myFps = (int) (1 / aTime);

	return true;
}

bool Pacman::UpdateInput()
{
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_UP])
		myNextMovement = Vector2f(0.f, -1.f);
	else if (keystate[SDL_SCANCODE_DOWN])
		myNextMovement = Vector2f(0.f, 1.f);
	else if (keystate[SDL_SCANCODE_RIGHT])
		myNextMovement = Vector2f(1.f, 0.f);
	else if (keystate[SDL_SCANCODE_LEFT])
		myNextMovement = Vector2f(-1.f, 0.f);

	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;

	return true;
}

const bool Pacman::CheckEndGameCondition()
{
	return myWorld->CheckEndGame();
}

bool Pacman::Draw()
{
	myWorld->Draw(myDrawer);
	for (std::list<MovableGameEntity*>::iterator list_iter = myEntities.begin(); list_iter != myEntities.end(); list_iter++)
	{
		(*list_iter)->Draw(myDrawer);
	}

	std::string scoreString;
	std::stringstream scoreStream;
	scoreStream << myScore;
	scoreString = scoreStream.str();
	myDrawer->DrawText("Score", 20, 50);
	myDrawer->DrawText(scoreString.c_str(), 90, 50);

	std::string livesString;
	std::stringstream liveStream;
	liveStream << myLives;
	livesString = liveStream.str();
	myDrawer->DrawText("Lives", 20, 80);
	myDrawer->DrawText(livesString.c_str(), 90, 80);

	myDrawer->DrawText("FPS", 880, 50);
	std::string fpsString;
	std::stringstream fpsStream;
	fpsStream << myFps;
	fpsString = fpsStream.str();
	myDrawer->DrawText(fpsString.c_str(), 930, 50);

	if(myGameWon)
		myDrawer->DrawText("You win!", 20, 100);
	if(myGameOver)
		myDrawer->DrawText("You lose!", 20, 100);

	return true;
}

void Pacman::ChangeGhostsClaimable(const bool &aState) 
{
	for (std::list<MovableGameEntity*>::iterator list_iter = myEntities.begin(); list_iter != myEntities.end(); list_iter++)
	{
		Ghost* aGhost = dynamic_cast<Ghost*>(*list_iter);
		if (aGhost)
			aGhost->ChangeClaimableState(aState);
	}
}

void Pacman::CheckGhostsCollision() 
{
	for (std::list<MovableGameEntity*>::iterator list_iter = myEntities.begin(); list_iter != myEntities.end(); list_iter++)
	{
		Ghost* aGhost = dynamic_cast<Ghost*>(*list_iter);
		if (aGhost)
		{
			if ((aGhost->GetPosition() - myAvatar->GetPosition()).Length() < 10.f)
			{
				if (aGhost->GetGhostCounter() <= 0.f)
				{
					myLives--;
					myNextMovement = Vector2f(-1.f, 0.f);
					ResetGhosts();
					myAvatar->Die();
					return;
					
				}
				else if (aGhost->GetIsClaimable() && !aGhost->GetIsDead())
				{
					myScore += 50;
					aGhost->Die();
				}
			}
		}
	}
}

void Pacman::ResetGhosts() 
{
	for (std::list<MovableGameEntity*>::iterator list_iter = myEntities.begin(); list_iter != myEntities.end(); list_iter++)
	{
		Ghost* aGhost = dynamic_cast<Ghost*>(*list_iter);
		if (aGhost)
		{
			aGhost->Reset();
		}
	}
}