#include "GameEntity.h"
#include "Drawer.h"

GameEntity::GameEntity(const Vector2f& aPosition, ETextureId aTextureId)
:myPosition(aPosition)
,myIdMarkedForDeleteFlag(false)
,myTextureId(aTextureId)
{
}

GameEntity::~GameEntity(void)
{
}

bool GameEntity::Intersect(GameEntity* aGameEntity)
{

	return false;	
}

void GameEntity::Draw(Drawer* aDrawer)
{
	aDrawer->Draw(myTextureId,(int)myPosition.myX + 220, (int)myPosition.myY + 60); 
}
