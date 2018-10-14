#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"

enum Direction {UP, LEFT, DOWN, RIGHT};
enum MoveType {LEAVE, DEAD, CHASE, CAGE, FRIGHTENED};

class World;
class PathmapTile;
class Avatar;
class Ghost : public MovableGameEntity
{
public:
	Ghost(const Vector2f& aPosition, Avatar* aAvatar, Direction aDirection, MoveType aMoveType, ETextureId aGhostTexture);
	~Ghost(void);

	virtual void	Update(float aTime);		
	const bool		GetIsClaimable() const { return myIsClaimableFlag; }
	const bool		GetIsDead() const { return myIsDeadFlag; }
	void			ChangeClaimableState(bool aClaimable);
	void			Die();
	void			Reset();
	void			SearchDirectionToAvatar();	//This method will use basic operations to find next move to avatar
	bool			IsNotOpposite(Direction aDirection);
	Direction		GetRandomDirection();		// Gets a random direction, different from opposite
	void			UpdateDirection();
	const float		GetGhostCounter() const { return myGhostGhostCounter; }
	bool			CheckIsPortal(const int &nextTileX, const int& nextTileY);
protected:

	int				myDesiredMovementX;
	int				myDesiredMovementY;
	std::list<PathmapTile*> myPath;

private:
	bool			myIsClaimableFlag;
	bool			myIsDeadFlag;
	Avatar*			myAvatar;			//Used to pathfinding
	Direction		myDirection;
	MoveType		myMoveType;
	const MoveType	myStartMoveType;
	float			myGhostGhostCounter;
	ETextureId		myOriginalTexture;

};

#endif // GHOST_H