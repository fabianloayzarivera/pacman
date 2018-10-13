#include "Avatar.h"
#include "World.h"

float tickAvatar = 0;
Avatar::Avatar(const Vector2f& aPosition)
: MovableGameEntity(aPosition, "open_32.png", ETextureId::AVATAR_OPEN_RIGHT, 150.f)
{

}

Avatar::~Avatar(void)
{
}

void Avatar::Update(float aTime)
{
	int tileSize = 22;
	tickAvatar += aTime;
	float distanceToMove = aTime * mySpeed; //It was set to 30.f
	//printf("%d, %d\n", GetCurrentTileX(), GetCurrentTileY());
	//***************** Move Avatar *************************************///
	int nextTileX = this->GetCurrentTileX() + (int)myNextMovement.myX;
	int nextTileY = this->GetCurrentTileY() + (int)myNextMovement.myY;

	if (this->IsAtDestination())
	{
		if (myWorld->TileIsValid(nextTileX, nextTileY))
		{
			this->SetNextTile(nextTileX, nextTileY);
		}
	}
	
	

	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f direction = destination - myPosition;

	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		//printf("X: %d, Y: %d || X: %d, Y: %d \n", myNextTileX, myNextTileY, myCurrentTileX, myCurrentTileY);
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		//******************* Check which texture I need to use on movement ****************//
		direction.Normalize();
		if (direction.myX > 0)
		{
			if (myTextureId != ETextureId::AVATAR_OPEN_RIGHT) myTextureId = ETextureId::AVATAR_OPEN_RIGHT;

			//if (tickAvatar > 1.0f)
			//{
			//	FlipFlopTexture();
			//	//if (myTextureId != ETextureId::AVATAR_OPEN_RIGHT) myTextureId = ETextureId::AVATAR_OPEN_RIGHT;
			//	tickAvatar = 0.f;
			//}
			
		}
		else if (direction.myX < 0)
			if (myTextureId != ETextureId::AVATAR_OPEN_LEFT) myTextureId = ETextureId::AVATAR_OPEN_LEFT;

		if (direction.myY > 0)
		{
			if (myTextureId != ETextureId::AVATAR_OPEN_DOWN) myTextureId = ETextureId::AVATAR_OPEN_DOWN;
		}
		else if (direction.myY < 0)
			if (myTextureId != ETextureId::AVATAR_OPEN_UP) myTextureId = ETextureId::AVATAR_OPEN_UP;

		myPosition += direction * distanceToMove;
	}
}

void Avatar::Die() 
{
	
	this->SetPosition(Vector2f(13 * 22, 22 * 22));
	this->ResetTiles();
	
}

void Avatar::FlipFlopTexture() 
{
	
}
//
//void Avatar::Draw(Drawer* aDrawer)
//{
//	//aDrawer->Draw(myTextureId, (int)myPosition.myX + 220, (int)myPosition.myY + 60);
//
//	//Change textureId during update???
//}