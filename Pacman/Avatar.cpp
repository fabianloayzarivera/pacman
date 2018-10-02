#include "Avatar.h"

Avatar::Avatar(const Vector2f& aPosition)
: MovableGameEntity(aPosition, "open_32.png", "OpenRight")
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

	float distanceToMove = aTime * 100.f; //It was set to 30.f

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
//
//void Avatar::Draw(Drawer* aDrawer)
//{
//	//aDrawer->Draw(myTextureId, (int)myPosition.myX + 220, (int)myPosition.myY + 60);
//
//	//Change textureId during update???
//}