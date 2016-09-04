#include "TileSetSingleFile.h"


TileSetSingleFile::TileSetSingleFile( std::string filePath, unsigned long tileWidth , unsigned long tileHeight ) 
{
   m_sprite  = new Sprite( filePath );
   m_width   = tileWidth;
   m_height  = tileHeight;
   m_columns = m_sprite->GetWidth() / tileWidth;
   m_lines   = m_sprite->GetHeight() / tileHeight;
}


TileSetSingleFile::TileSetSingleFile( unsigned long lines, unsigned long columns, std::string filePath )
{
   m_sprite  = new Sprite( filePath );
   m_columns = columns;
   m_lines   = lines;
   m_width   = m_sprite->GetWidth() / m_columns;
   m_height  = m_sprite->GetHeight() / m_lines;
}

void TileSetSingleFile::Render( int index, double posX, double posY )
{
   long indexX = index % m_columns;
   long indexY = index / m_columns;

   m_sprite->Clip( indexX*m_width, indexY*m_height, m_width, m_height );
   m_sprite->Render( posX, posY );
}

TileSetSingleFile::~TileSetSingleFile(void)
{
   delete m_sprite;
}
