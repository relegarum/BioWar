#pragma once
#include "Sprite.h"
#include <vector>

class TileSet
{
public:
   TileSet();
   ~TileSet();

   virtual void Render( int index, double posX, double posY ) = 0;

   inline unsigned long GetTileWidth(){ return m_width; }
   inline unsigned long GetTileHeight(){ return m_height; }

protected:
   unsigned long m_width;
   unsigned long m_height;
   unsigned long m_lines;
   unsigned long m_columns;
};

