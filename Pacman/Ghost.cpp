#include "Ghost.h"
#include "World.h"
#include "PathmapTile.h"
#include "Avatar.h"

const Direction DIRECTIONS[4] = { UP, LEFT, DOWN, RIGHT };

Ghost::Ghost(const Vector2f& aPosition, Avatar* aAvatar, Direction aDirection, MoveType aMoveType)
: myStartPosition(aPosition),
  MovableGameEntity(aPosition, "ghost_32.png", ETextureId::GHOST_GREY, 30.f)
{
	myDirection = aDirection;
	myStartMoveType = myMoveType = aMoveType;
	myIsClaimableFlag = false;
	myIsDeadFlag = false;
	myAvatar = aAvatar;
	myDesiredMovementX = 0;
	myDesiredMovementY = -1;
	myGhostGhostCounter = 0.f;
}

Ghost::~Ghost(void)
{
}

void Ghost::ChangeClaimableState(bool aIsClaimable) 
{
	if (!myIsDeadFlag)
	{
		myIsClaimableFlag = aIsClaimable;
		if (aIsClaimable)
		{	
			myGhostGhostCounter = 20.f;
			if (myTextureId != ETextureId::GHOST_CLAIMABLE) myTextureId = ETextureId::GHOST_CLAIMABLE;
		}
		else if (myTextureId != ETextureId::GHOST_GREY) myTextureId = ETextureId::GHOST_GREY;

	}
	
}

void Ghost::Die()
{
	myIsDeadFlag = true;
	myPath.clear();
	myWorld->GetPath(myCurrentTileX, myCurrentTileY, 13, 13, myPath); //optimize this method
	myMoveType = DEAD;
}

void Ghost::Update(float aTime)  //Check way to refactor world on update
{
	myGhostGhostCounter -= aTime;

	if (myGhostGhostCounter <= 0)
	{
		this->ChangeClaimableState(false);
	}

	mySpeed = 100.f;
	int tileSize = 22;
	int nextTileX;
	int nextTileY;
	//printf("%d\n", myIsClaimableFlag);
	
	//int nextTileX = GetCurrentTileX() + myDesiredMovementX;
	//int nextTileY = GetCurrentTileY() + myDesiredMovementY;

	if (myIsDeadFlag)
	{
		mySpeed = 120.f;
		if (myTextureId != ETextureId::GHOST_DEAD) myTextureId = ETextureId::GHOST_DEAD;
	}
	
	if (IsAtDestination())
	{

		switch (myMoveType)
		{
		case CAGE:
			if (myPath.empty())
			{
				myWorld->GetPath(myCurrentTileX, myCurrentTileY, 13, 10, myPath);
			}
			myMoveType = LEAVE;
			break;
		case LEAVE:
			if (!myPath.empty())
			{
				PathmapTile* nextTile = myPath.front();
				myPath.pop_front();
				SetNextTile(nextTile->myX, nextTile->myY);
			}
			else 
			{
				printf("I'M OUT!\n");
				myMoveType = CHASE;
			}
			break;
		case DEAD:
			if (!myPath.empty())
			{
				PathmapTile* nextTile = myPath.front();
				myPath.pop_front();
				SetNextTile(nextTile->myX, nextTile->myY);
			}
			else
			{
				printf("ON PEN!\n");
				myIsDeadFlag = false;
				this->ChangeClaimableState(false);
				myGhostGhostCounter = 0.f;
				myMoveType = CAGE;
			}
			break;
		case CHASE:
			SearchDirectionToAvatar();
			/*switch (myDirection)
			{
			case UP: printf("UP!\n");
				break;
			case LEFT: printf("LEFT!\n");
				break;
			case DOWN: printf("DOWN!\n");
				break;
			case RIGHT: printf("RIGHT!\n");
				break;
			default:
				break;
			}*/
			UpdateDirection();
			nextTileX = GetCurrentTileX() + myDesiredMovementX;
			nextTileY = GetCurrentTileY() + myDesiredMovementY;

			

			if (myWorld->TileIsValid(nextTileX, nextTileY))
				SetNextTile(nextTileX, nextTileY);

			myIsDeadFlag = false;
			break;
		default:
			break;
		}
	}

	/*if (IsAtDestination())
	{*/
		//SetNextTile(nextTileX, nextTileY);
		//printf("Check!\n");
		/*if (!myPath.empty())
		{
			PathmapTile* nextTile = myPath.front();
			myPath.pop_front();
			SetNextTile(nextTile->myX, nextTile->myY);
		}*/
		/*else if (myWorld->TileIsValid(nextTileX, nextTileY))
		{
			SetNextTile(nextTileX, nextTileY);
		}*/
		//else
		//{
			/*if (myDesiredMovementX == 1)
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
			}*/
			

			/*SearchDirectionToAvatar();
			switch (myDirection)
			{
			case UP: printf("UP!\n");
				break;
			case LEFT: printf("LEFT!\n");
				break;
			case DOWN: printf("DOWN!\n");
				break;
			case RIGHT: printf("RIGHT!\n");
				break;
			default:
				break;
			}
			UpdateDirection();
			int nextTileX = GetCurrentTileX() + myDesiredMovementX;
			int nextTileY = GetCurrentTileY() + myDesiredMovementY;

			if (myWorld->TileIsValid(nextTileX, nextTileY))
				SetNextTile(nextTileX, nextTileY);

			myIsDeadFlag = false;*/


			//if (myTextureId != ETextureId::GHOST_GREY) myTextureId = ETextureId::GHOST_GREY;
		//}
		
	//}


	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f dir = destination - myPosition;

	float distanceToMove = aTime * mySpeed;

	if (distanceToMove > dir.Length())
	{
		myPosition = destination;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		dir.Normalize();
		myPosition += dir * distanceToMove;
	}
}

void Ghost::SetImage(const char* anImage)
{
	myImage = anImage;
}

void Ghost::Reset() 
{
	this->SetPosition(myStartPosition);
	this->myMoveType = myStartMoveType;
	this->ResetTiles();	
}

void Ghost::SearchDirectionToAvatar() 
{
	int possible = 0;
	Direction possibleDirections[4];
	if (GetCurrentTileY() < myAvatar->GetCurrentTileY())
		possibleDirections[possible++] = Direction::DOWN;
	if (GetCurrentTileY() >  myAvatar->GetCurrentTileY())
		possibleDirections[possible++] = Direction::UP;

	if (GetCurrentTileX() < myAvatar->GetCurrentTileX())
		possibleDirections[possible++] = Direction::RIGHT;
	if (GetCurrentTileX() >  myAvatar->GetCurrentTileX())
		possibleDirections[possible++] = Direction::LEFT;

	Direction usableDirections[4];
	int usable = 0;
	for (int i = 0; i < possible; ++i)
	{
		int tempNextTileX = GetCurrentTileX();
		int tempNextTileY = GetCurrentTileY();

		switch (possibleDirections[i])
		{
		case UP:
			tempNextTileX += 0;
			tempNextTileY += -1;
			break;
		case LEFT:
			tempNextTileX += -1;
			tempNextTileY += 0;
			break;
		case DOWN:
			tempNextTileX += 0;
			tempNextTileY += 1;
			break;
		case RIGHT:
			tempNextTileX += 1;
			tempNextTileY += 0;
			break;
		default:
			break;
		}
		
		if (myWorld->TileIsValid(tempNextTileX, tempNextTileY) && IsNotOpposite(possibleDirections[i]))
			usableDirections[usable++] = possibleDirections[i];
	}

	if (usable == 0)
		myDirection = GetRandomDirection();
	else
		myDirection = usableDirections[rand() % usable];

}

void Ghost::UpdateDirection() 
{
	switch (myDirection)
	{
	case UP:
		myDesiredMovementX = 0;
		myDesiredMovementY = -1;
		break;
	case LEFT:
		myDesiredMovementX = -1;
		myDesiredMovementY = 0;
		break;
	case DOWN:
		myDesiredMovementX = 0;
		myDesiredMovementY = 1;
		break;
	case RIGHT:
		myDesiredMovementX = 1;
		myDesiredMovementY = 0;
		break;
	default:
		break;
	}
	
}

bool Ghost::IsNotOpposite(Direction aDirection)
{
	switch (aDirection)
	{
	case UP:	return myDirection == DOWN ? false : true;
		break;
	case LEFT:  return myDirection == RIGHT ? false : true;
		break;
	case DOWN:  return myDirection == UP ? false : true;
		break;
	case RIGHT: return myDirection == LEFT? false : true;
		break;
	default: return true;
		break;
	}
	
}

Direction Ghost::GetRandomDirection() 
{
	bool found = false;
	Direction randDirection;
	while (!found) 
	{
		int tempNextTileX = GetCurrentTileX();
		int tempNextTileY = GetCurrentTileY();
		randDirection = DIRECTIONS[rand() % 4];
		switch (randDirection)
		{
		case UP:
			tempNextTileX += 0;
			tempNextTileY += -1;
			break;
		case LEFT:
			tempNextTileX += -1;
			tempNextTileY += 0;
			break;
		case DOWN:
			tempNextTileX += 0;
			tempNextTileY += 1;
			break;
		case RIGHT:
			tempNextTileX += 1;
			tempNextTileY += 0;
			break;
		default:
			break;
		}
		if (!CheckIsPortal(tempNextTileX, tempNextTileY))
		{
			if (myWorld->TileIsValid(tempNextTileX, tempNextTileY) && IsNotOpposite(randDirection))
				found = true;
		}
		else
			found = true;
	}
	return randDirection;
}

bool Ghost::CheckIsPortal(const int &nextTileX, const int &nextTileY)
{
	if (nextTileX >= 26 && nextTileY == 13)
	{
		this->myCurrentTileX = 0;
		this->SetPosition(Vector2f(0 * 22, 13 * 22));
		return true;
	}
	else if (nextTileX < 0 && nextTileY == 13)
	{
		this->myCurrentTileX = 25;
		this->SetPosition(Vector2f(25 * 22, 13 * 22));
		return true;
	}
	return false;
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
