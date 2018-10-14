#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "Vector2f.h"

enum ETextureId   //Enum with all the possible texture Ids in the game
{
	BIG_DOT,
	DOT,
	CHERRY,
	AVATAR_OPEN_RIGHT,
	AVATAR_CLOSED_RIGHT,
	AVATAR_OPEN_LEFT,
	AVATAR_CLOSED_LEFT,
	AVATAR_OPEN_UP,
	AVATAR_CLOSED_UP,
	AVATAR_OPEN_DOWN,
	AVATAR_CLOSED_DOWN,
	GHOST_RED,
	GHOST_BLUE,
	GHOST_ORANGE,
	GHOST_PINK,
	GHOST_CLAIMABLE,
	GHOST_DEAD,
	PLAYFIELD,

};

class Drawer;
class Pacman;
class GameEntity
{
public:

	//****** Changed the constructor to use only texture id instead of image path ******//
	GameEntity(const Vector2f& aPosition, ETextureId aTextureId);
	virtual ~GameEntity(void); //Made destructor virtual so all other child destructors are going to be called

	Vector2f GetPosition() const { return myPosition; }
	void SetPosition(const Vector2f& aPosition){ myPosition = aPosition; }
	void SetGameInstance(Pacman *Pacman) { myGameInstance = Pacman; }
	bool Intersect(GameEntity* aGameEntity);
	void Draw(Drawer* aDrawer); //GameEntity is the only class that will declare/define the Draw method

	void MarkForDelete() { myIdMarkedForDeleteFlag = true; }
	bool IsMarkedForDelete() const { return myIdMarkedForDeleteFlag; }

protected:

	bool myIdMarkedForDeleteFlag;
	Vector2f myPosition;
	ETextureId myTextureId; //Only texture Id is needed to draw the entities
	Pacman * myGameInstance; //GameInstance pointer, in order for the GameEntity to update or get values from the Pacman instance
};

#endif // GAMEENTITY_H