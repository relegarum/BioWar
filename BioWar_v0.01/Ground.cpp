#include "Ground.h"


Ground::Ground( double x, double y, double w, double h ) :
   GameObject( x, y, w, h )
{
   /*m_tileSet = new TileSetSingleFile( "img/Tile_Map_Cidade_Teste.png", 72, 72 );
   m_tileMap = new TileMap( w, h, 72, 1, m_tileSet );

   for( int i = 0; i*72 < w; ++i )
   {
      m_tileMap->at(  i*72, 1 ) = + m_tileSet->GetColumns() + rand()%( m_tileSet->GetColumns() );
   }*/
}

void Ground::Render( double cameraX, double cameraY )
{
   //m_tileMap->Render( cameraX, cameraY );
}


int Ground::Update( int dt )
{
   return 0;
}

Ground::~Ground(void)
{
   //delete m_tileMap;
   //delete m_tileSet;
}
