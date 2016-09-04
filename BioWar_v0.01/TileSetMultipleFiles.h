#pragma once
#include "tileset.h"
class TileSetMultipleFiles : public TileSet
{
public:
   TileSetMultipleFiles( unsigned long tileWidth, unsigned long tileHeight );
   ~TileSetMultipleFiles(void);

   void AddTile( std::string filePath );
   virtual void Render( int index, double posX, double posY );

private:
   std::vector< Sprite * > * m_tileVector;
};

