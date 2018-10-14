#include "Avatar.h"
#include "Pacman.h"
#include "World.h"

float tickAvatar = 0;
Avatar::Avatar(const Vector2f& aPosition)
: MovableGameEntity(aPosition, ETextureId::AVATAR_OPEN_RIGHT, 150.f)
{
	myCherryCounter = 0;
}

Avatar::~Avatar(void)
{
}

void Avatar::Update(float aTime)
{
	int tileSize = 22;
	tickAvatar += aTime;
	float distanceToMove = aTime * mySpeed;
	this->SetMyNextMovement(myGameInstance->GetLastInput());


	//***************** Move Avatar *************************************///
	int nextTileX = this->GetCurrentTileX() + (int)myNextMovement.myX;
	int nextTileY = this->GetCurrentTileY() + (int)myNextMovement.myY;

	if (!CheckIsPortal(nextTileX, nextTileY))
	{
		if (this->IsAtDestination())
		{
			if (myGameInstance->GetWorld()->TileIsValid(nextTileX, nextTileY))
			{
				this->SetNextTile(nextTileX, nextTileY);
			}
		}
	}
	
	

	Vector2f destination((float)(myNextTileX * tileSize), (float)(myNextTileY * tileSize));
	Vector2f direction = destination - myPosition;

	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		//******************* Check which texture I need to use on movement ****************//
		direction.Normalize();
		if (direction.myX > 0)
		{
			if (myTextureId != ETextureId::AVATAR_OPEN_RIGHT && myTextureId != ETextureId::AVATAR_CLOSED_RIGHT) myTextureId = ETextureId::AVATAR_OPEN_RIGHT;
		}
		else if (direction.myX < 0)
		{
			if (myTextureId != ETextureId::AVATAR_OPEN_LEFT && myTextureId != ETextureId::AVATAR_CLOSED_LEFT) myTextureId = ETextureId::AVATAR_OPEN_LEFT;
		}
		else if (direction.myY > 0)
		{
			if (myTextureId != ETextureId::AVATAR_OPEN_DOWN && myTextureId != ETextureId::AVATAR_CLOSED_DOWN) myTextureId = ETextureId::AVATAR_OPEN_DOWN;
		}
		else if (direction.myY < 0)
			if (myTextureId != ETextureId::AVATAR_OPEN_UP && myTextureId != ETextureId::AVATAR_CLOSED_UP) myTextureId = ETextureId::AVATAR_OPEN_UP;

		myPosition += direction * distanceToMove;
		FlipFlopTexture();
	}

	//******** Intersect Dot **************//
	if(myGameInstance->GetWorld()->HasIntersectedDot(this->GetPosition()))
	{
		myCherryCounter++;
		myGameInstance->AddScore(10);
		if (myCherryCounter >= 70)
		{
			myGameInstance->GetWorld()->SpawnCherry();
			myCherryCounter = 0;
		}

	}

	//********* Intersect Cherry ********* //
	if (myGameInstance->GetWorld()->HasIntersectedCherry(this->GetPosition()))
		myGameInstance->AddScore(200);

	// ******** Intersect Big Dot ***********//
	if (myGameInstance->GetWorld()->HasIntersectedBigDot(this->GetPosition()))
	{
		myGameInstance->AddScore(20);
		myGameInstance->ChangeGhostsClaimable(true);
	}

}

void Avatar::Die() 
{
	
	this->SetPosition(Vector2f(13 * 22, 22 * 22));
	this->ResetTiles();
	
}

void Avatar::FlipFlopTexture() 
{
	if(tickAvatar >= .1f)
	{
		switch (myTextureId)
		{
		case AVATAR_OPEN_RIGHT: myTextureId = AVATAR_CLOSED_RIGHT;
			break;
		case AVATAR_CLOSED_RIGHT: myTextureId = AVATAR_OPEN_RIGHT;
			break;
		case AVATAR_OPEN_LEFT: myTextureId = AVATAR_CLOSED_LEFT;
			break;
		case AVATAR_CLOSED_LEFT: myTextureId = AVATAR_OPEN_LEFT;
			break;
		case AVATAR_OPEN_UP: myTextureId = AVATAR_CLOSED_UP;
			break;
		case AVATAR_CLOSED_UP: myTextureId = AVATAR_OPEN_UP;
			break;
		case AVATAR_OPEN_DOWN: myTextureId = AVATAR_CLOSED_DOWN;
			break;
		case AVATAR_CLOSED_DOWN:myTextureId = AVATAR_OPEN_DOWN;
			break;
		default:
			break;
		}
		tickAvatar = 0;
	}
}

bool Avatar::CheckIsPortal(const int &nextTileX, const int &nextTileY)
{
	if (nextTileX >= 26 && nextTileY == 13)
	{
		printf("PortalRight!");
		this->myCurrentTileX = 0;
		this->myNextTileX = 0;
		this->SetPosition(Vector2f(0 * 22, 13 * 22));
		return true;
	}
	else if (nextTileX < 0 && nextTileY == 13)
	{
		printf("Portal!");
		this->myCurrentTileX = 25;
		this->myNextTileX = 25;
		this->SetPosition(Vector2f(25 * 22, 13 * 22));
		return true;
	}
	return false;
}
