#ifndef MOVABLEGAMEENTITY_H
#define MOVABLEGAMEENTITY_H

#include "GameEntity.h"
#include "Vector2f.h"
#include "Drawer.h"

class World;
class MovableGameEntity : public GameEntity
{
public:
	MovableGameEntity(const Vector2f& aPosition, ETextureId aTextureId, float aSpeed = 0.f);
	~MovableGameEntity(void);

	void		SetNextTile(const int &anX, const int &anY);
	int			GetCurrentTileX() const { return myCurrentTileX; }
	int			GetCurrentTileY() const { return myCurrentTileY; }
	bool		IsAtDestination();
	void		ResetTiles();
	void		SetMyNextMovement(const Vector2f &aNextMovement) { myNextMovement = aNextMovement; }
	virtual void Update(float aTime) = 0; //Pure Virtual function, so all MovableGameEntities will override this update method

protected:

	int			myCurrentTileX;
	int			myCurrentTileY;
	int			myNextTileX;
	int			myNextTileY;
	float		mySpeed;
	const Vector2f myStartPosition;
	Vector2f	myNextMovement;

};

#endif // MOVABLEGAMEENTITY_H