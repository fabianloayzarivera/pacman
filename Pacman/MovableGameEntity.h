#ifndef MOVABLEGAMEENTITY_H
#define MOVABLEGAMEENTITY_H

#include "GameEntity.h"
#include "Vector2f.h"
#include "Drawer.h"

class World;
class MovableGameEntity : public GameEntity
{
public:
	MovableGameEntity(const Vector2f& aPosition, const char* anImage, ETextureId aTextureId, float aSpeed = 0.f);
	~MovableGameEntity(void);

	void SetNextTile(int anX, int anY);
	int GetCurrentTileX() const { return myCurrentTileX; }
	int GetCurrentTileY() const { return myCurrentTileY; }
	bool IsAtDestination();
	virtual void Update(float aTime, World* aWorld = nullptr) = 0; //World maybe should not be there

protected:

	int		myCurrentTileX;
	int		myCurrentTileY;
	int		myNextTileX;
	int		myNextTileY;
	float	speed;

};

#endif // MOVABLEGAMEENTITY_H