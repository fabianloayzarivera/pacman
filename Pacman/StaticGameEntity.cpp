#include "StaticGameEntity.h"
#include "Drawer.h"

StaticGameEntity::StaticGameEntity(Vector2f aPosition, const char* anImage, const char* aTextureId)
: GameEntity(aPosition, anImage, aTextureId)
{
}

StaticGameEntity::~StaticGameEntity(void)
{
}

void StaticGameEntity::Draw(Drawer* aDrawer)
{
	aDrawer->Draw(myTextureId,(int)myPosition.myX + 220, (int)myPosition.myY + 60); 
}