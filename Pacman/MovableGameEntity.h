#ifndef MOVABLEGAMEENTITY_H
#define MOVABLEGAMEENTITY_H

#include "GameEntity.h"
#include "Vector2f.h"
#include "Drawer.h"

class MovableGameEntity : public GameEntity
{
public:
	MovableGameEntity(const Vector2f& aPosition, const char* anImage, const char* aTextureId);
	~MovableGameEntity(void);

	void SetNextTile(int anX, int anY);
	int GetCurrentTileX() const { return myCurrentTileX; }
	int GetCurrentTileY() const { return myCurrentTileY; }
	virtual void Draw(Drawer* aDrawer);
	bool IsAtDestination();

protected:

	int myCurrentTileX;
	int myCurrentTileY;

	int myNextTileX;
	int myNextTileY;

};

#endif // MOVABLEGAMEENTITY_H