#ifndef STATICGAMEENTITY_H
#define STATICGAMEENTITY_H

#include "GameEntity.h"
#include "Vector2f.h"

class StaticGameEntity : public GameEntity
{
public:
	StaticGameEntity(Vector2f aPosition, const char* anImage, ETextureId aTextureId);
	~StaticGameEntity(void);
	//virtual void Draw(Drawer* aDrawer); //Maybe Just Game Entity?
};

#endif // STATICGAMEENTITY_H