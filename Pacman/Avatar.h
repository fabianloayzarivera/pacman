#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Vector2f.h"

class Avatar : public MovableGameEntity
{
public:
	Avatar(const Vector2f& aPosition);
	~Avatar(void);
	//void Draw(Drawer* aDrawer);
	virtual void Update(float aTime);
	void	Die();
	void	FlipFlopTexture();
private:
	

};

#endif //AVATAR_H