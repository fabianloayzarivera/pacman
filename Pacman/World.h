#ifndef WORLD_H
#define WORLD_H

#include <list>
#include <memory>
#include "Vector2f.h"

class Drawer;
class PathmapTile;
class Dot;
class BigDot;
class Cherry;

class World
{
public:
	World(void);
	~World(void);

	void Init();

	void Draw(Drawer* aDrawer);
	bool TileIsValid(int anX, int anY);

	bool HasIntersectedDot(const Vector2f& aPosition);
	bool HasIntersectedBigDot(const Vector2f& aPosition);
	bool HasIntersectedCherry(const Vector2f& aPosition);

	//void Update();
	bool CheckEndGame();
	void GetPath(int aFromX, int aFromY, int aToX, int aToY, std::list<PathmapTile*>& aList);
	bool SpawnCherry();
private:

	PathmapTile* GetTile(int aFromX, int aFromY);
	bool Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, std::list<PathmapTile*>& aList);
	
	bool ListDoesNotContain(PathmapTile* aFromTile, std::list<PathmapTile*>& aList);

	bool InitPathmap();
	bool InitDots();
	bool InitBigDots();

	std::list<PathmapTile*> myPathmapTiles;
	std::list<Dot*>			myDots;
	std::list<BigDot*>		myBigDots;
	Cherry*					myCherry;
	
	//**** We could also use (if supported) Smart Pointers *** //
	/*std::list<std::shared_ptr<PathmapTile>> myPathmapTiles;
	std::list<std::shared_ptr<Dot>>			myDots;
	std::list<std::shared_ptr<BigDot>>		myBigDots;
	std::list<std::shared_ptr<Cherry>>		myCherry;*/
	
};

#endif // WORLD_H