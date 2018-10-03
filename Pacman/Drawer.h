#ifndef DRAWER_H
#define DRAWER_H

#include <map>
#include "GameEntity.h"
//enum class ETextureId;
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;

using namespace std;

struct myTexture 
{
	myTexture(int w, int h, SDL_Texture* tex) : width(w), height(h), texture(tex) {};
	~myTexture(); //Free texture!!
	int width;
	int height;
	SDL_Texture* texture;
};

class Drawer
{
public:
	static Drawer* Create(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	~Drawer(void);

	//void Draw(const char* anImage, int aCellX = 0, int aCellY = 0);
	void Draw(ETextureId aTextureId, const int & aCellX = 0, const int & aCellY = 0) const;
	void DrawText(const char* aText, const char* aFontFile, int aX, int aY);
	bool LoadTexture(const char* anImage, ETextureId aTextureId);

private:
	Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	bool Init();
	
	map<ETextureId, myTexture*> myTextures; //map ids and textures CHANGE const char* with ENUM
	SDL_Window* myWindow;
	SDL_Renderer* myRenderer;
	SDL_Surface* world;
};

#endif // DRAWER_H