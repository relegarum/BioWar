#ifndef SPRITE_H
#define SPRITE_H

#include "SDLBase.h"
#include "Rect.h"

class Sprite
{
public:
   Sprite( std::string fileName );
   Sprite( std::string fileName, int alphaRed, int alphaGreen, int alphaBlue );
   Sprite( const Sprite *other );
   Sprite();
   ~Sprite();

   void Load( std::string fileName );
   void Load( std::string fileName, int alphaRed, int alphaGreen, int alphaBlue );
   void Clip( int x, int y, int w, int h );
   void Clip( const Rect< double > &rect );
   void Render( int x, int y );
   Rect< double > GetClip();

   inline int GetHeight(){ return m_surface->h; }
   inline int GetWidth(){ return m_surface->w; }

   virtual void Update( int dt );

   void         RotoZoom( double angle, double scaleX = 1.0f, double scaleY = 1.0f, bool force = false );
   void         Restore();


protected:
   SDL_Surface * m_surface;
   SDL_Rect      m_clipRect;

   SDL_Surface * m_surfaceRotoZoom;
   double        m_angle;
   double        m_scaleX;
   double        m_scaleY;
};

#endif 