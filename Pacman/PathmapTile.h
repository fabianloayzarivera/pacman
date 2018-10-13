#ifndef PATHMAPTILE_H
#define PATHMAPTILE_H

class PathmapTile
{
public:
	PathmapTile(int anX, int anY, bool aIsBlockingFlag, bool aIsGateFlag);
	~PathmapTile(void);

	const int myX;
	const int myY;
	const bool myIsBlockingFlag;
	const bool myIsGateFlag;
	bool myIsVisitedFlag;

};

#endif // PATHMAPTILE_H