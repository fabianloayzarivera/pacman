#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"

typedef enum Direction {UP, LEFT, DOWN, RIGHT};
typedef enum MoveType {LEAVE, DEAD, CHASE, CAGE};
class World;
class PathmapTile;
class Avatar;
class Ghost : public MovableGameEntity
{
public:
	Ghost(const Vector2f& aPosition, Avatar* aAvatar, Direction aDirection, MoveType aMoveType);
	~Ghost(void);

	virtual void	Update(float aTime);
	const bool		GetIsClaimable() const { return myIsClaimableFlag; }
	const bool		GetIsDead() const { return myIsDeadFlag; }
	void			ChangeClaimableState(bool aClaimable);
	void			SetImage(const char* anImage);
	void			Die();
	void			Reset();
	void			SearchDirectionToAvatar();
	bool			IsNotOpposite(Direction aDirection);
	Direction		GetRandomDirection();
	void			UpdateDirection();
	const float		GetGhostCounter() const { return myGhostGhostCounter; }
	bool			CheckIsPortal(const int &nextTileX, const int& nextTileY);
protected:

	int myDesiredMovementX;
	int myDesiredMovementY;
	std::list<PathmapTile*> myPath;

private:
	bool myIsClaimableFlag;
	bool myIsDeadFlag;
	Avatar*	myAvatar;
	Direction myDirection;
	const Vector2f myStartPosition;
	MoveType myMoveType;
	MoveType myStartMoveType;
	float myGhostGhostCounter;
	//ADD GHOST TEXTURES ID'S? IN CONSTRUCTOR, EG: GHOST NORMAL, GHOST CLAIMABLE, GHOST DEAD

};

#endif // GHOST_H