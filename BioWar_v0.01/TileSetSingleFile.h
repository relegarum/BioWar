#pragma once
#include "tileset.h"
class TileSetSingleFile :
   public TileSet
{
public:
   TileSetSingleFile( std::string filePath, unsigned long tileWidth , unsigned long tileHeight );
   TileSetSingleFile( unsigned long lines, unsigned long columns, std::string filePath );
   
   ~TileSetSingleFile(void);
   
   void Render( int index, double posX, double posY );
   inline int GetColumns(){ return m_columns; }
   inline int GetLines(){ return m_lines; }
protected:
   Sprite * m_sprite;

};

