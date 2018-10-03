#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"

class World;
class PathmapTile;

class Ghost : public MovableGameEntity
{
public:
	Ghost(const Vector2f& aPosition);
	~Ghost(void);
	void		Update(float aTime, World* aWorld);
	const bool  GetIsClaimable() const { return myIsClaimableFlag; }
	const bool  GetIsDead() const { return myIsDeadFlag; }
	void		ChangeClaimableState(bool aClaimable);
	void		SetImage(const char* anImage);
	void		Die(World* aWorld);

protected:

	int myDesiredMovementX;
	int myDesiredMovementY;

	std::list<PathmapTile*> myPath;

private:
	bool myIsClaimableFlag;
	bool myIsDeadFlag;

	//ADD GHOST TEXTURES ID'S? IN CONSTRUCTOR, EG: GHOST NORMAL, GHOST CLAIMABLE, GHOST DEAD

};

#endif // GHOST_H