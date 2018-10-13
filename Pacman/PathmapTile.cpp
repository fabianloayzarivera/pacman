#include "PathmapTile.h"

PathmapTile::PathmapTile(int anX, int anY, bool aIsBlockingFlag, bool aIsGateFlag)
: myX(anX)
, myY(anY)
, myIsBlockingFlag(aIsBlockingFlag)
, myIsGateFlag(aIsGateFlag)
,myIsVisitedFlag(false)
{
}

PathmapTile::~PathmapTile(void)
{
}
