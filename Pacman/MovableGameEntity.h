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

	void SetNextTile(const int &anX, const int &anY);
	void SetWorld(World* &aWorld) { myWorld = aWorld; }
	int GetCurrentTileX() const { return myCurrentTileX; }
	int GetCurrentTileY() const { return myCurrentTileY; }
	bool IsAtDestination();
	void ResetTiles();
	void	SetMyNextMovement(const Vector2f &aNextMovement) { myNextMovement = aNextMovement; }
	virtual void Update(float aTime) = 0; //World maybe should not be there

protected:

	int		myCurrentTileX;
	int		myCurrentTileY;
	int		myNextTileX;
	int		myNextTileY;
	float	mySpeed;
	Vector2f myNextMovement;
	World*	myWorld;

};

#endif // MOVABLEGAMEENTITY_H