#ifndef TEXT_H
#define TEXT_H

#include "SDLBase.h"

class Text
{
public:
   Text( std::string fontFileName, std::string text, short red = 0, short green = 0, short blue = 0, uint16_t size = 10, int x = 0, int y = 0 );
   Text( TTF_Font *font, std::string &text, uint16_t size = 28 );
   ~Text();

   void LoadFont( std::string fileName, uint16_t size );
   void Load();
   void Render( double cameraX = 0.0, double cameraY = 0.0 );
   
   inline std::string   GetText(){ return m_text; }
   inline SDL_Surface * GetSurface(){ return m_textSurface; }
   inline SDL_Color     GetColor(){ return m_color; }
   inline uint16_t      GetSize(){ return m_size; }
   inline SDL_Rect      GetBox(){ return m_box; }

   inline void SetText( std::string &text ){ m_text = text; }
   inline void SetColor( SDL_Color &color ){ m_color = color; }
   inline void SetStyle( short style ){ m_style = style; }
   inline void SetSize( short size ){ m_size = size; }
   inline void SetPos( int x, int y ){ m_box.x = x; m_box.y = y; }

protected:
   SDL_Surface * m_textSurface;
   TTF_Font    * m_font;
   std::string   m_text;
   std::string   m_fontFileName;
   short         m_size;
   short         m_style;
   SDL_Color     m_color;
   SDL_Rect      m_box;
};

#endif 