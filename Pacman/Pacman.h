#ifndef PACMAN_H
#define PACMAN_H

#include "Vector2f.h"
#include <list>

struct SDL_Surface;
class Drawer;
class Avatar;
class World;
//class Ghost;
class MovableGameEntity;

class Pacman
{
public:
	static Pacman* Create(Drawer* aDrawer);
	~Pacman(void);

	bool Update(float aTime);
	bool Draw();
	void ChangeGhostsClaimable(const bool& aState);
	void CheckGhostsCollision();
	void ResetGhosts();
private:
	Pacman(Drawer* aDrawer);
	bool Init();
	bool UpdateInput();
	//void MoveAvatar();  
	bool CheckEndGameCondition();

	float myTimeToNextUpdate;
	//float myGhostGhostCounter;

	int myLives;
	int myScore;
	int myFps;

	Vector2f myNextMovement;

	std::list<MovableGameEntity *> myEntities;
	Avatar* myAvatar;  //Leaving a pointer of our controlled player
	//Ghost* myGhost;
	Drawer* myDrawer;
	World* myWorld;

};

#endif // PACMAN_H