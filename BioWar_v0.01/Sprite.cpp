#include "Sprite.h"

Sprite::Sprite() :
   m_surface( NULL ),
   m_surfaceRotoZoom( NULL ),
   m_angle( 0 ),
   m_scaleX( 1.0f ),
   m_scaleY( 1.0f )
{
}

Sprite::Sprite( const Sprite *other ) :
   m_surface( other->m_surface ),
   m_surfaceRotoZoom( other->m_surfaceRotoZoom ),
   m_angle( other->m_angle ),
   m_scaleX ( other->m_scaleX ),
   m_scaleY( other->m_scaleY )
{
}

Sprite::Sprite( std::string fileName ): 
   m_surface( NULL ),
   m_surfaceRotoZoom( NULL ),
   m_angle( 0 ),
   m_scaleX( 1.0f ),
   m_scaleY( 1.0f )
{
   Load( fileName );
}

Sprite::Sprite( std::string fileName, int alphaRed, int alphaGreen, int alphaBlue ):
   m_surface( NULL ),
   m_surfaceRotoZoom( NULL ),
   m_angle( 0 ),
   m_scaleX( 1.0f ),
   m_scaleY( 1.0f )
{
   Load( fileName , alphaRed, alphaGreen,  alphaBlue );
}


void Sprite::Load( std::string fileName )
{
   if( m_surface != NULL )
   {
      SDL_FreeSurface( m_surface );
   }

   m_surface = SDLBase::LoadImage( fileName );
   m_clipRect.x = 0;
   m_clipRect.y = 0;
   m_clipRect.w = m_surface->w;
   m_clipRect.h = m_surface->h;
}

void Sprite::Load( std::string fileName,int alphaRed, int alphaGreen, int alphaBlue )
{
   if( m_surface != NULL )
   {
      SDL_FreeSurface( m_surface );
   }

   m_surface = SDLBase::LoadImage( fileName, alphaRed, alphaGreen, alphaBlue );
   m_clipRect.x = 0;
   m_clipRect.y = 0;
   m_clipRect.w = m_surface->w;
   m_clipRect.h = m_surface->h;
}

void Sprite::Clip( int x, int y, int w, int h )
{
   m_clipRect.x = x;
   m_clipRect.y = y;
   m_clipRect.w = w;
   m_clipRect.h = h;

   if( m_surfaceRotoZoom != NULL ) 
   {
      RotoZoom( m_angle, m_scaleX, m_scaleY, true );
   }

}

void Sprite::Clip( const Rect< double >& rect )
{
   m_clipRect.x = rect.m_x;
   m_clipRect.y = rect.m_y;
   m_clipRect.h = rect.m_h;
   m_clipRect.w = rect.m_w;

   if( m_surfaceRotoZoom != NULL ) 
   {
      RotoZoom( m_angle, m_scaleX, m_scaleY, true );
   }
}

void Sprite::Render( int x, int y )
{
   SDL_Rect dst;
   dst.x = x;
   dst.y = y;

   if( m_surfaceRotoZoom == NULL )
   {
      SDLBase::RenderSurface( m_surface, &m_clipRect, &dst );
   }
   else
   {
      auto centerX = m_clipRect.w*0.5;
      auto centerY = m_clipRect.h*0.5;

      auto centerAdjX = m_surfaceRotoZoom->w*0.5;
      auto centerAdjY = m_surfaceRotoZoom->h*0.5;

      auto differenceX = centerX - centerAdjX;
      auto differenceY = centerY - centerAdjY;

      dst.x += differenceX;
      dst.y += differenceY;

      SDLBase::RenderSurface( m_surfaceRotoZoom, NULL, &dst );
   }

}

void Sprite::Update( int dt )
{
}

void Sprite::Restore()
{
   if( m_surfaceRotoZoom != NULL )
   {
      delete m_surfaceRotoZoom;
   }
}


void Sprite::RotoZoom( double angle, double scaleX, double scaleY, bool force )
{
   if( ( m_angle == angle   ) &&
       ( m_scaleX == scaleX ) &&
       ( m_scaleY == scaleY ) &&
       !force )
   {
      return;
   }

   if( m_surfaceRotoZoom != NULL )
   {
      SDL_FreeSurface( m_surfaceRotoZoom );
      m_surfaceRotoZoom = NULL;
   }

   m_angle = angle;
   m_scaleX = scaleX;
   m_scaleY = scaleY;
   
   SDL_Surface * surface = m_surface;
   if( ( m_clipRect.w != m_surface->w ) ||
       ( m_clipRect.h != m_surface->h ) )
   {
      SDL_Rect rect;
      rect = m_clipRect;
      surface = SDLBase::Clip( surface, &rect );
   }
   m_clipRect.w *= m_scaleX;
   m_clipRect.h *= m_scaleY;
   //m_surfaceRotoZoom = SDLBase::RotoZoomSurface( m_surface, angle, scaleX, scaleY );
   m_surfaceRotoZoom = SDLBase::RotoZoomSurface( surface, angle, scaleX, scaleY );
   SDL_FreeSurface( surface );
}

Rect< double > Sprite::GetClip()
{
   Rect< double > rect;
   rect.m_x = m_clipRect.x;
   rect.m_y = m_clipRect.y;
   rect.m_w = m_clipRect.w;
   rect.m_h = m_clipRect.h;
   return rect;
}

Sprite::~Sprite()
{
   SDL_FreeSurface( m_surface );
}
