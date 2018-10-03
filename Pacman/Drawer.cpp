#include "Drawer.h"
#include "SDL.h"
#include "SDL_image.h"


Drawer* Drawer::Create(SDL_Window* aWindow, SDL_Renderer* aRenderer)
{
	Drawer* drawer = new Drawer(aWindow, aRenderer);

	if (!drawer->Init())
	{
		delete drawer;
		drawer = NULL;
	}

	return drawer;
}

Drawer::Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer)
: myWindow(aWindow)
, myRenderer(aRenderer)
{
	myTextures.clear();
}

Drawer::~Drawer(void)
{
	//DELETE ALL TEXTURES FROM MAP!!
	for (map<ETextureId, myTexture*>::iterator itr = myTextures.begin(); itr != myTextures.end(); itr++)
	{
		delete (itr->second);
	}
	myTextures.clear();
	TTF_CloseFont(font);
}

bool Drawer::Init()
{
	if (!myWindow)
		return false;

	return true;
}

//void Drawer::Draw(const char* anImage, int aCellX, int aCellY) //change const char* to SDL_Texture pointer to draw
void Drawer::Draw(ETextureId aTextureId, const int &aCellX, const int &aCellY) const
{
	//SDL_Surface* surface = IMG_Load( anImage ) ; //Load surface only once for each object and store them in each object.

	/*if (!aSurface) //NEED TO IMPLEMENT!
		return;*/

	//SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(myRenderer, const_cast<SDL_Surface*>(aSurface));
	if (myTextures.size() > 0 && myTextures.at(aTextureId)) //Check out of range error????
	{
		myTexture* aTexture = myTextures.at(aTextureId);
		SDL_Rect sizeRect;
		sizeRect.x = 0;
		sizeRect.y = 0;
		sizeRect.w = aTexture->width;
		sizeRect.h = aTexture->height;

		SDL_Rect posRect;
		posRect.x = aCellX;
		posRect.y = aCellY;
		posRect.w = sizeRect.w;
		posRect.h = sizeRect.h;
		SDL_RenderCopy(myRenderer, aTexture->texture, &sizeRect, &posRect);  //SDLCOPYEX??? flip?

	}
	else 
	{
		//No texture found!
	}

	//SDL_DestroyTexture(optimizedSurface); destructor?

}

void Drawer::DrawText(const char* aText, int aX, int aY)
{
	//TTF_Font* font=TTF_OpenFont(aFontFile, 24);
	SDL_Color fontColor={255,0,0,255};

	SDL_Surface* surface = TTF_RenderText_Solid(font, aText, fontColor);
	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(myRenderer, surface);
	
    SDL_Rect sizeRect;
    sizeRect.x = 0 ;
    sizeRect.y = 0 ;
    sizeRect.w = surface->w ;
    sizeRect.h = surface->h ;

    SDL_Rect posRect ;
    posRect.x = aX;
    posRect.y = aY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(myRenderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
}

bool Drawer::LoadTexture(const char* anImage, ETextureId aTextureId)
{
	SDL_Surface* surface = IMG_Load( anImage ) ; //Load surface only once for each object and store them in each object.

	if (!surface)
		return false;

	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(myRenderer, const_cast<SDL_Surface*>(surface));
	myTextures[aTextureId] = new myTexture(surface->w, surface->h, optimizedSurface);
	
	SDL_FreeSurface(surface);

	if (optimizedSurface)
		return true;
	else
		return false;
}

bool Drawer::LoadFont(const char* aFontFile, const unsigned int &size)
{
	font = TTF_OpenFont(aFontFile, 24);
	/*if (font)
		return true;
	else
		return false;*/
	return font;
}