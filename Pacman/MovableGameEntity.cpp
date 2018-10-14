#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(const Vector2f& aPosition, ETextureId aTextureId, float aSpeed)
: myStartPosition(aPosition),
  GameEntity(aPosition, aTextureId), mySpeed(aSpeed)
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
