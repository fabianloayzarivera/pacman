#include "StaticGameEntity.h"
#include "Drawer.h"

StaticGameEntity::StaticGameEntity(Vector2f aPosition,ETextureId aTextureId)
: GameEntity(aPosition, aTextureId)
{
}

StaticGameEntity::~StaticGameEntity(void)
{
}
