#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(const Vector2f& aPosition, const char* anImage, const char* aTextureId)
: GameEntity(aPosition, anImage, aTextureId)
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

void MovableGameEntity::SetNextTile(int anX, int anY)
{
	myNextTileX = anX;
	myNextTileY = anY;
}

void MovableGameEntity::Draw(Drawer* aDrawer)
{
	aDrawer->Draw(myTextureId, (int)myPosition.myX + 220, (int)myPosition.myY + 60);
}