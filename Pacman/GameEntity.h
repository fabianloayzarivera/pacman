#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "Vector2f.h"

class Drawer;
struct SDL_Surface;
struct SDL_Texture;

class GameEntity
{
public:
	GameEntity(const Vector2f& aPosition, const char* anImage, const char* aTextureId);
	virtual ~GameEntity(void); //Make destructor virtual

	Vector2f GetPosition() const { return myPosition; }
	void SetPosition(const Vector2f& aPosition){ myPosition = aPosition; }

	bool Intersect(GameEntity* aGameEntity);
	//virtual void Draw(Drawer* aDrawer); //Make pure virtual
	virtual void Draw(Drawer* aDrawer) = 0;

	void MarkForDelete() { myIdMarkedForDeleteFlag = true; }
	bool IsMarkedForDelete() const { return myIdMarkedForDeleteFlag; }

protected:

	bool myIdMarkedForDeleteFlag;
	Vector2f myPosition;
	const char* myImage;   //MAYBE NOT NEEDED ANYMORE?
	const char* myTextureId;

};

#endif // GAMEENTITY_H