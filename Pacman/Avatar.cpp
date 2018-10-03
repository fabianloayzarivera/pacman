#include "Avatar.h"

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
	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f direction = destination - myPosition;

	float distanceToMove = aTime * speed; //It was set to 30.f
	
	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		//printf("X: %d, Y: %d || X: %d, Y: %d \n", myNextTileX, myNextTileY, myCurrentTileX, myCurrentTileY);
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		direction.Normalize();
		if (direction.myX > 0)
		{
			if (myTextureId != ETextureId::AVATAR_OPEN_RIGHT) myTextureId = ETextureId::AVATAR_OPEN_RIGHT;
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
//
//void Avatar::Draw(Drawer* aDrawer)
//{
//	//aDrawer->Draw(myTextureId, (int)myPosition.myX + 220, (int)myPosition.myY + 60);
//
//	//Change textureId during update???
//}