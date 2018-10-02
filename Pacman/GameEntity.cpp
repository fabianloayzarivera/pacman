#include "GameEntity.h"
#include "SDL_image.h"

GameEntity::GameEntity(const Vector2f& aPosition, const char* anImage, const char* aTextureId)
:myPosition(aPosition)
,myImage(anImage)
,myIdMarkedForDeleteFlag(false)
,myTextureId(aTextureId)
{
}

GameEntity::~GameEntity(void)
{
	//SDL_FreeSurface(const_cast<SDL_Surface* >(aSurface)); //Use is marked for delete?
}

bool GameEntity::Intersect(GameEntity* aGameEntity)
{

	return false;	
}

//void GameEntity::Draw(Drawer* aDrawer)
//{
//	//aDrawer->Draw(aSurface,(int)myPosition.myX + 220, (int)myPosition.myY + 60); //moved to static game entity
//}
