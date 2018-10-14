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

	bool		Update(const float aTime);
	bool		Draw();
	void		ChangeGhostsClaimable(const bool& aState);
	void		CheckGhostsCollision();
	void		ResetGhosts();
	void		AddScore(const int& aScore) { myScore += aScore; }
	World*		GetWorld() const { return myWorld; }
	std::list<MovableGameEntity *> GetEntities() { return myEntities; }
	Vector2f	GetLastInput() { return myNextMovement; }
private:
	Pacman(Drawer* aDrawer);
	bool		Init();
	bool		UpdateInput();
	//void MoveAvatar();  
	const bool	CheckEndGameCondition();
	float		myTimeToNextUpdate;
	//float myGhostGhostCounter;
	int			myLives;
	int			myScore;
	int			myFps;
	bool		myGameOver;
	bool		myGameWon;
	//int myCherryCounter;
	Vector2f	myNextMovement;
	std::list<MovableGameEntity *> myEntities;
	Avatar*		myAvatar;  //Leaving a pointer of our controlled player
	//Ghost* myGhost;
	Drawer*		myDrawer;
	World*		myWorld;

};

#endif // PACMAN_H