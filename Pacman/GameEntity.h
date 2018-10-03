#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "Vector2f.h"

enum ETextureId
{
	BIG_DOT,
	DOT,
	CHERRY,
	AVATAR_OPEN_RIGHT,
	AVATAR_CLOSED_RIGHT,
	AVATAR_OPEN_LEFT,
	AVATAR_OPEN_UP,
	AVATAR_OPEN_DOWN,
	GHOST_GREY,
	GHOST_CLAIMABLE,
	GHOST_DEAD,
	PLAYFIELD,


};

class Drawer;

class GameEntity
{
public:
	GameEntity(const Vector2f& aPosition, const char* anImage, ETextureId aTextureId);
	virtual ~GameEntity(void); //Make destructor virtual

	Vector2f GetPosition() const { return myPosition; }
	void SetPosition(const Vector2f& aPosition){ myPosition = aPosition; }

	bool Intersect(GameEntity* aGameEntity);
	//virtual void Draw(Drawer* aDrawer); //Make pure virtual
	void Draw(Drawer* aDrawer);

	void MarkForDelete() { myIdMarkedForDeleteFlag = true; }
	bool IsMarkedForDelete() const { return myIdMarkedForDeleteFlag; }

protected:

	bool myIdMarkedForDeleteFlag;
	Vector2f myPosition;
	const char* myImage;   //MAYBE NOT NEEDED ANYMORE?
	ETextureId myTextureId;

};

#endif // GAMEENTITY_H