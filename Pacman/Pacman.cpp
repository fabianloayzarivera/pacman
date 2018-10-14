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
//, myCherryCounter(0)
//, myGhostGhostCounter(0.f)
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
		//myDrawer->DrawText("You win!", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 70);
		myGameWon = true;
		return true;
	}
	else if (myLives <= 0)
	{
		//myDrawer->DrawText("You lose!", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 70);	
		myGameOver = true;
		//myDrawer->DrawText("You lose!", 20, 70);
		return true;
	}

	//MoveAvatar();
	//myAvatar->SetMyNextMovement(myNextMovement);  //Get last input 
	//myAvatar->Update(aTime);
	//myGhost->Update(aTime, myWorld);

	for (std::list<MovableGameEntity*>::iterator list_iter = myEntities.begin(); list_iter != myEntities.end(); list_iter++)
	{
		(*list_iter)->Update(aTime);
	}

	//Move this to update avatar ---------------------
	/*if (myWorld->HasIntersectedDot(myAvatar->GetPosition()))
	{
		myCherryCounter++;
		myScore += 10;
		if (myCherryCounter >= 70)
		{
			myWorld->SpawnCherry();
			myCherryCounter = 0;
		}
			
	}*/
	
	/*if (myWorld->HasIntersectedCherry(myAvatar->GetPosition())) 
	{
		myScore += 200;
	}*/

	//myGhostGhostCounter -= aTime;

	//if (myWorld->HasIntersectedBigDot(myAvatar->GetPosition()))
	//{
	//	myScore += 20;
	//	//myGhostGhostCounter = 20.f;
	//	//myGhost->ChangeClaimableState(true);
	//	ChangeGhostsClaimable(true);
	//}

	//----------------------------------------------
	//printf("%f\n", myGhostGhostCounter);
	//Move this to Ghost update ------------------------
	//if (myGhostGhostCounter <= 0)
	//{
	//	//myGhost->ChangeClaimableState(false);
	//}

	CheckGhostsCollision();

	//if ((myGhost->GetPosition() - myAvatar->GetPosition()).Length() < 10.f)
	//{
	//	if (myGhostGhostCounter <= 0.f)
	//	{
	//		myLives--;

	//		myAvatar->SetPosition(Vector2f(13*22,22*22));
	//		myGhost->SetPosition(Vector2f(13*22,13*22));
	//	}
	//	else if (myGhost->GetIsClaimable() && !myGhost->GetIsDead())
	//	{
	//		myScore += 50;
	//		//myGhost->myIsDeadFlag = true;
	//		myGhost->Die(myWorld);
	//	}
	//}
	//--------------------------------
	
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

//void Pacman::MoveAvatar()
//{
//	/*int nextTileX = myAvatar->GetCurrentTileX() + (int)myNextMovement.myX;
//	int nextTileY = myAvatar->GetCurrentTileY() + (int)myNextMovement.myY;
//
//	if (myAvatar->IsAtDestination())
//	{
//		if (myWorld->TileIsValid(nextTileX, nextTileY))
//		{
//			myAvatar->SetNextTile(nextTileX, nextTileY);
//		}
//	}*/
//}

const bool Pacman::CheckEndGameCondition()
{
	return myWorld->CheckEndGame();
}

bool Pacman::Draw()
{
	myWorld->Draw(myDrawer);
	//myAvatar->Draw(myDrawer);
	//myGhost->Draw(myDrawer);
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
	/*myDrawer->DrawText("Score", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 50);
	myDrawer->DrawText(scoreString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 90, 50);*/

	std::string livesString;
	std::stringstream liveStream;
	liveStream << myLives;
	livesString = liveStream.str();
	myDrawer->DrawText("Lives", 20, 80);
	myDrawer->DrawText(livesString.c_str(), 90, 80);
	/*myDrawer->DrawText("Lives", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 80);
	myDrawer->DrawText(livesString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 90, 80);*/

	myDrawer->DrawText("FPS", 880, 50);
	//myDrawer->DrawText("FPS", "freefont-ttf\\sfd\\FreeMono.ttf", 880, 50);
	std::string fpsString;
	std::stringstream fpsStream;
	fpsStream << myFps;
	fpsString = fpsStream.str();
	myDrawer->DrawText(fpsString.c_str(), 930, 50);

	if(myGameWon)
		myDrawer->DrawText("You win!", 20, 100);
	if(myGameOver)
		myDrawer->DrawText("You lose!", 20, 100);

	//printf("%s\n", fpsString.c_str());
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
					//Reset positions
					//myAvatar->SetPosition(Vector2f(13 * 22, 22 * 22));
					//myAvatar->ResetTiles();
					myNextMovement = Vector2f(-1.f, 0.f);
					ResetGhosts();
					myAvatar->Die();
					//aGhost->SetPosition(Vector2f(13 * 22, 13 * 22));
					return;
					
				}
				else if (aGhost->GetIsClaimable() && !aGhost->GetIsDead())
				{
					myScore += 50;
					//myGhost->myIsDeadFlag = true;
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