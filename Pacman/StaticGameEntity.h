#ifndef STATICGAMEENTITY_H
#define STATICGAMEENTITY_H

#include "GameEntity.h"
#include "Vector2f.h"

class StaticGameEntity : public GameEntity
{
public:
	StaticGameEntity(Vector2f aPosition, const char* anImage, const char* aTextureId);
	~StaticGameEntity(void);
	virtual void Draw(Drawer* aDrawer);
};

#endif // STATICGAMEENTITY_H