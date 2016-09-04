#include "Text.h"

Text::Text( std::string fontFileName, std::string text, short red, short green, short blue, uint16_t size, int x, int y ) :
   m_textSurface( NULL ),
   m_text( text ),
   m_size( size ),
   m_fontFileName( fontFileName )
{
   m_box.x = x;
   m_box.y = y;

   m_color.r = red;
   m_color.g = green;
   m_color.b = blue;

   Load();
}


void Text::LoadFont( std::string fileName, uint16_t size )
{
   if( m_textSurface != NULL )
   {
      SDL_FreeSurface( m_textSurface );
   }

   TTF_Font * font = SDLBase::LoadFont( fileName, size );

   if( font == NULL )
   {
      std::cerr << "Erro no carregamento da fonte" << std::endl;
      return;
   }

   m_textSurface = SDLBase::LoadFontSurface( font, m_text, m_color );
}

void Text::Load()
{
   if( m_textSurface != NULL )
   {
      SDL_FreeSurface( m_textSurface );
   }

   m_font = SDLBase::LoadFont( m_fontFileName, m_size );
   m_textSurface = SDLBase::LoadFontSurface( m_font, m_text, m_color );
   if( m_textSurface == NULL )
   {
      std::cerr << "Erro no carregamento da SURFACE" << std::endl;
      return;
   }
   m_box.h = m_textSurface->h;
   m_box.w = m_textSurface->w;
}

void Text::Render( double cameraX, double cameraY )
{
   SDL_Rect dst;
   dst.x = m_box.x - cameraX;
   dst.y = m_box.y - cameraY;

   SDLBase::RenderSurface( m_textSurface, NULL, &dst );
}

Text::~Text(void)
{
   SDL_FreeSurface( m_textSurface );
}
