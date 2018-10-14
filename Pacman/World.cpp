#include "World.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include "PathmapTile.h"
#include "Cherry.h"
#include "Dot.h"
#include "BigDot.h"
#include "Drawer.h"

World::World(void)
{
}

World::~World(void)
{
	for (std::list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		delete(*list_iter);
	}
	myPathmapTiles.clear();
	for (std::list<Dot*>::iterator list_iter = myDots.begin(); list_iter != myDots.end(); list_iter++)
	{
		delete(*list_iter);
	}
	myDots.clear();
	for (std::list<BigDot*>::iterator list_iter = myBigDots.begin(); list_iter != myBigDots.end(); list_iter++)
	{
		delete(*list_iter);
	}
	myBigDots.clear();
	delete(myCherry);
}

void World::Init()
{
	InitPathmap();
	InitDots();
	InitBigDots();
}

bool World::InitPathmap()
{
	std::string line;
	std::ifstream myfile ("map.txt");
	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			std::getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				PathmapTile* tile = new PathmapTile(i, lineIndex, (line[i] == 'x'), (line[i] == 'g'));
				myPathmapTiles.push_back(tile);
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

bool World::InitDots()
{
	std::string line;
	std::ifstream myfile ("map.txt");
	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			std::getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == '.')
				{
					Dot* dot = new Dot(Vector2f((float)(i * 22), (float)(lineIndex * 22)));
					myDots.push_back(dot);
				}
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

bool World::InitBigDots()
{
	std::string line;
	std::ifstream myfile ("map.txt");
	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			std::getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == 'o')
				{
					BigDot* dot = new BigDot(Vector2f((float)(i*22), (float)(lineIndex*22)));
					myBigDots.push_back(dot);
				}
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

void World::Draw(Drawer* aDrawer)
{

	aDrawer->Draw(ETextureId::PLAYFIELD);
	
	for(std::list<Dot*>::iterator list_iter = myDots.begin(); list_iter != myDots.end(); list_iter++)
	{
		(*list_iter)->Draw(aDrawer);
	}

	for(std::list<BigDot*>::iterator list_iter = myBigDots.begin(); list_iter != myBigDots.end(); list_iter++)
	{
		(*list_iter)->Draw(aDrawer);
	}

	if (myCherry)
		myCherry->Draw(aDrawer);

}

bool World::TileIsValid(int anX, int anY)
{
	for(std::list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;

		if (anX == tile->myX && anY == tile->myY && !tile->myIsBlockingFlag && !tile->myIsGateFlag)
			return true;
	}

	return false;
}

bool World::HasIntersectedDot(const Vector2f& aPosition)
{
	for(std::list<Dot*>::iterator list_iter = myDots.begin(); list_iter != myDots.end(); list_iter++)
	{
		Dot* dot = *list_iter;
		if (((*list_iter)->GetPosition() - aPosition).Length() < 5.f)
		{
			myDots.remove(*list_iter);
			delete(dot);
			return true;
		}
	}

	return false;
}

bool World::HasIntersectedBigDot(const Vector2f& aPosition)
{
	for(std::list<BigDot*>::iterator list_iter = myBigDots.begin(); list_iter != myBigDots.end(); list_iter++)
	{
		BigDot* dot = *list_iter;
		if (((*list_iter)->GetPosition() - aPosition).Length() < 5.f)
		{
			myBigDots.remove(*list_iter);
			delete (dot);
			return true;
		}
	}

	return false;
}

bool World::HasIntersectedCherry(const Vector2f& aPosition)
{
	if (myCherry) 
	{
		if ((myCherry->GetPosition() - aPosition).Length() < 5.f) 
		{
			delete(myCherry);
			myCherry = nullptr;
			return true;
		}			
	}
	return false;
}

void World::GetPath(int aFromX, int aFromY, int aToX, int aToY, std::list<PathmapTile*>& aList)
{
	PathmapTile* fromTile = GetTile(aFromX, aFromY);
	PathmapTile* toTile = GetTile(aToX, aToY);

	for(std::list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		tile->myIsVisitedFlag = false;
	}

	Pathfind(fromTile, toTile, aList);
	
}

PathmapTile* World::GetTile(int aFromX, int aFromY)
{
	for(std::list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		if (tile->myX == aFromX && tile->myY == aFromY)
		{
			return tile;
		}
	}

	return NULL;
}

bool World::ListDoesNotContain(PathmapTile* aFromTile, std::list<PathmapTile*>& aList)
{
	for(std::list<PathmapTile*>::iterator list_iter = aList.begin(); list_iter != aList.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		if (tile == aFromTile)
		{
			return false;
		}
	}

	return true;
}

bool SortFromGhostSpawn(PathmapTile* a, PathmapTile* b)
{
	int la = abs(a->myX - 13) + abs(a->myY - 13);
	int lb = abs(b->myX - 13) + abs(b->myY - 13);

    return la < lb;
}

bool SortFromDistance(PathmapTile* a, PathmapTile* b)
{
	int la = a->distance;
	int lb = b->distance;

	return la < lb;
}

bool World::Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, std::list<PathmapTile*>& aList)
{
	aFromTile->myIsVisitedFlag = true;

	if (aFromTile->myIsBlockingFlag)
		return false;

	if (aFromTile == aToTile)
		return true;

	std::list<PathmapTile*> neighborList;

	PathmapTile* up = GetTile(aFromTile->myX, aFromTile->myY - 1);
	if (up && !up->myIsVisitedFlag && !up->myIsBlockingFlag && ListDoesNotContain(up, aList))
	{
		up->distance = sqrt(abs(up->myX - aToTile->myX) * abs(up->myX - aToTile->myX) + abs(up->myY - aToTile->myY) * abs(up->myY - aToTile->myY));
		neighborList.push_front(up);
	}		

	PathmapTile* down = GetTile(aFromTile->myX, aFromTile->myY + 1);
	if (down && !down->myIsVisitedFlag && !down->myIsBlockingFlag && ListDoesNotContain(down, aList))
	{
		down->distance = sqrt(abs(down->myX - aToTile->myX) * abs(down->myX - aToTile->myX) + abs(down->myY - aToTile->myY) * abs(down->myY - aToTile->myY));
		neighborList.push_front(down);
	}		

	PathmapTile* right = GetTile(aFromTile->myX + 1, aFromTile->myY);
	if (right && !right->myIsVisitedFlag && !right->myIsBlockingFlag && ListDoesNotContain(right, aList))
	{
		right->distance = sqrt(abs(right->myX - aToTile->myX) * abs(right->myX - aToTile->myX) + abs(right->myY - aToTile->myY) * abs(right->myY - aToTile->myY));
		neighborList.push_front(right);
	}		

	PathmapTile* left = GetTile(aFromTile->myX - 1, aFromTile->myY);
	if (left && !left->myIsVisitedFlag && !left->myIsBlockingFlag && ListDoesNotContain(left, aList))
	{
		left->distance = sqrt(abs(left->myX - aToTile->myX) * abs(left->myX - aToTile->myX) + abs(left->myY - aToTile->myY) * abs(left->myY - aToTile->myY));
		neighborList.push_front(left);
	}

	neighborList.sort(SortFromDistance);

	for (std::list<PathmapTile*>::iterator list_iter = neighborList.begin(); list_iter != neighborList.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;

		aList.push_back(tile);

		if (Pathfind(tile, aToTile, aList))
			return true;

		aList.pop_back();
	}

	return false;
}

bool World::SpawnCherry() 
{
	if(!myCherry)
	{
		myCherry = new Cherry(Vector2f(13 * 22, 22 * 22));
		printf("Yup that's a cherry.\n");
		return true;
	}
	return false;

}

bool World::CheckEndGame() 
{
	if (myDots.size() == 0 && myBigDots.size() == 0)
		return true;
	else
		return false;
	
}