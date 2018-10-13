#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(const Vector2f& aPosition, const char* anImage, ETextureId aTextureId, float aSpeed)
: GameEntity(aPosition, anImage, aTextureId), mySpeed(aSpeed)
{
	myCurrentTileX = myNextTileX =  myPosition.myX / 22;
	myCurrentTileY = myNextTileY =  myPosition.myY / 22;
	
}

MovableGameEntity::~MovableGameEntity(void)
{
}

bool MovableGameEntity::IsAtDestination()
{
	if (myCurrentTileX == myNextTileX && myCurrentTileY == myNextTileY)
	{
		return true;
	}

	return false;
}

void MovableGameEntity::SetNextTile(const int &anX, const int &anY)
{
	myNextTileX = anX;
	myNextTileY = anY;
}

void MovableGameEntity::ResetTiles() 
{
	myCurrentTileX = myNextTileX = myPosition.myX / 22;
	myCurrentTileY = myNextTileY = myPosition.myY / 22;
}
//void MovableGameEntity::Draw(Drawer* aDrawer)
//{
//	aDrawer->Draw(myTextureId, (int)myPosition.myX + 220, (int)myPosition.myY + 60);
//}