#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Vector2f.h"

class Avatar : public MovableGameEntity
{
public:
	Avatar(const Vector2f& aPosition);
	~Avatar(void);
	virtual void Update(float aTime);
	void	Die();
	void	FlipFlopTexture(); //Method that will change between open and closed mouth texture
	bool	CheckIsPortal(const int &nextTileX, const int &nextTileY); //This method could've been virtual in movableentity
private:
	int		myCherryCounter;

};

#endif //AVATAR_H