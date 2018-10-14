#ifndef DRAWER_H
#define DRAWER_H

#include <map>
#include "GameEntity.h"
#include "SDL_ttf.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;


using namespace std;

struct myTexture 
{
	myTexture(const int w, const int h, SDL_Texture* tex) : width(w), height(h), texture(tex) {};
	~myTexture() { SDL_DestroyTexture(texture); }
	const int width;
	const int height;
	SDL_Texture* texture;
};

class Drawer
{
public:
	static Drawer* Create(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	~Drawer(void);

	//Instead of Drawing an specific image from file. We are going to draw the texture stored in the map with id: aTextureId
	void Draw(ETextureId aTextureId, const int & aCellX = 0, const int & aCellY = 0) const;
	void DrawText(const char* aText, int aX, int aY);
	bool LoadTexture(const char* anImage, ETextureId aTextureId);
	bool LoadFont(const char* aFontFile, const unsigned int &size);

private:
	Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	bool Init();
	
	map<ETextureId, myTexture*> myTextures;
	SDL_Window*		myWindow;
	SDL_Renderer*	myRenderer;
	SDL_Surface*	world;
	TTF_Font*		font;
};

#endif // DRAWER_H