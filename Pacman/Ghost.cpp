#include "Ghost.h"
#include "World.h"
#include "PathmapTile.h"
#include "Drawer.h"

Ghost::Ghost(const Vector2f& aPosition)
: MovableGameEntity(aPosition, "ghost_32.png", ETextureId::GHOST_GREY, 30.f)
{
	myIsClaimableFlag = false;
	myIsDeadFlag = false;

	myDesiredMovementX = 0;
	myDesiredMovementY = -1;
}

Ghost::~Ghost(void)
{
}

void Ghost::ChangeClaimableState(bool aIsClaimable) 
{
	myIsClaimableFlag = aIsClaimable;
	if (aIsClaimable)
	{
		if (myTextureId != ETextureId::GHOST_CLAIMABLE) myTextureId = ETextureId::GHOST_CLAIMABLE;
	}
	else if (myTextureId != ETextureId::GHOST_GREY) myTextureId = ETextureId::GHOST_GREY;
	
}

void Ghost::Die(World* aWorld)
{
	myIsDeadFlag = true;
	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, 13, 13, myPath); //optimize this method
}

void Ghost::Update(float aTime, World* aWorld)
{
	speed = 30.f;
	//printf("%d\n", myIsClaimableFlag);
	int nextTileX = GetCurrentTileX() + myDesiredMovementX;
	int nextTileY = GetCurrentTileY() + myDesiredMovementY;

	if (myIsDeadFlag)
	{
		speed = 120.f;
		if (myTextureId != ETextureId::GHOST_DEAD) myTextureId = ETextureId::GHOST_DEAD;
	}
		

	if (IsAtDestination())
	{
		if (!myPath.empty())
		{
			PathmapTile* nextTile = myPath.front();
			myPath.pop_front();
			SetNextTile(nextTile->myX, nextTile->myY);
		}
		else if (aWorld->TileIsValid(nextTileX, nextTileY))
		{
			SetNextTile(nextTileX, nextTileY);
		}
		else
		{
			if (myDesiredMovementX == 1)
			{
				myDesiredMovementX = 0;
				myDesiredMovementY = 1;
			} else if (myDesiredMovementY == 1)
			{
				myDesiredMovementX = -1;
				myDesiredMovementY = 0;			
			} else if (myDesiredMovementX == -1)
			{
				myDesiredMovementX = 0;
				myDesiredMovementY = -1;
			} else
			{
				myDesiredMovementX = 1;
				myDesiredMovementY = 0;
			}

			myIsDeadFlag = false;
			//if (myTextureId != ETextureId::GHOST_GREY) myTextureId = ETextureId::GHOST_GREY;
		}
	}

	int tileSize = 22;
	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f direction = destination - myPosition;

	float distanceToMove = aTime * speed;

	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		direction.Normalize();
		myPosition += direction * distanceToMove;
	}
}

void Ghost::SetImage(const char* anImage)
{
	myImage = anImage;
}

//void Ghost::Draw(Drawer* aDrawer)
//{
//	/*if (myIsDeadFlag)
//		aDrawer->Draw("Ghost_Dead_32.png", (int)myPosition.myX + 220, (int)myPosition.myY + 60);
//	else if (myIsClaimableFlag)
//		aDrawer->Draw("Ghost_Vulnerable_32.png", (int)myPosition.myX + 220, (int)myPosition.myY + 60);
//	else
//		aDrawer->Draw(myImage, (int)myPosition.myX + 220, (int)myPosition.myY + 60);*/
//	
//	//Placeholder
//	aDrawer->Draw(myTextureId, (int)myPosition.myX + 220, (int)myPosition.myY + 60);
//	//----
//}
