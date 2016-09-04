#include "TileSetMultipleFiles.h"


TileSetMultipleFiles::TileSetMultipleFiles( unsigned long  tileWidth, unsigned long tileHeight ) 
{
   m_tileVector = new std::vector< Sprite * >();
   m_height  = tileHeight;
   m_width   = tileWidth;
   m_lines   = 0;
   m_columns = 0; 
}


TileSetMultipleFiles::~TileSetMultipleFiles(void)
{
   delete m_tileVector;
}

void TileSetMultipleFiles::AddTile( std::string filePath )
{
   Sprite * sprite = new Sprite( filePath );
   m_tileVector->push_back( sprite );
}

void TileSetMultipleFiles::Render( int index, double posX, double posY )
{
   m_tileVector->at( index )->Render( posX, posY );
}