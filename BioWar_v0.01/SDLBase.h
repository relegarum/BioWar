#ifndef SDL_BASE_H
#define SDL_BASE_H

#define RELEASE

#include "OS_Include.h"
#include "TimerManager.h"
#include <iostream>

#define MAX_HEIGHT 240  
#define MAX_WIDTH  320

class SDLBase
{
public:
	SDLBase();
	~SDLBase();

	static int			  InitSDL();
   static void         Quit();
	static SDL_Surface * GetScreen();
   static SDL_Joystick * GetJoystick();


   static void FullScreen();
   //IMAGES
	static SDL_Surface * LoadImage( std::string fileName );
   static SDL_Surface * LoadImage( std::string fileName, int alphaRed, int alphaGreen, int alphaBlue );
   static SDL_Surface * Clip( SDL_Surface * surface, SDL_Rect * clip );
   static SDL_Surface * RotoZoomSurface( SDL_Surface * source, double angle, double scaleX = 1.0f, double scaleY = 1.0f );
   // FONTS
   static TTF_Font    * LoadFont( std::string fontFileName, uint16_t size );
   static SDL_Surface * LoadFontSurface( TTF_Font * font, std::string &text, SDL_Color &color );
   // Musics
   static Mix_Music   * LoadMusic( std::string musicFileName );
   static Mix_Chunk   * LoadChunk( std::string chunkFileName );
   static void          PlayChunk( Mix_Chunk * chunk, int channel = -1, int times = 0 );

   static void		     RenderSurface( SDL_Surface * surface, SDL_Rect * clip = NULL, SDL_Rect * dst = NULL, SDL_Surface * father = NULL );
	static void		     RefreshScreen();

   // Phisics
   static bool         CheckCollision( SDL_Rect &one, SDL_Rect &other );
private:
	static SDL_Surface * s_screen;
   static SDL_Joystick * s_joystick;
};

#endif