#include "TileMap.h"
#include <fstream>


TileMap::TileMap( unsigned long mapWidth, unsigned long mapHeight, unsigned long tileSize, unsigned short layers, TileSet * tileSet ) :
   m_mapHeight( mapHeight ),
   m_mapWidth( mapWidth ),
   m_mapLayers( layers ),
   m_tileSet( tileSet )
{
   m_tileMatrix = new std::vector<   std::vector< std::vector< int > > >
                      ( m_mapLayers, std::vector< std::vector< int > > // layers
                      ( m_mapHeight, std::vector< int >                // lines
                      ( m_mapWidth, -1 ) ) );                          // columns
}


TileMap::TileMap( std::string fileMapPath, TileSet * tileSet ) :
   m_tileSet( tileSet )
{
   Load( fileMapPath );
}

void TileMap::Load( std::string fileMapPath )
{
   std::string teste;
   std::fstream fileStream( fileMapPath.c_str(), std::fstream::in );
   if( fileStream )
   {

      std::string line;
      std::getline( fileStream, line );
      int pos    = 0;
      int antPos = 0;
      pos = line.find(",");
      m_mapHeight = atoi( line.substr( 0, pos ).c_str() );
      m_mapWidth  = atoi( line.substr( pos+1,  antPos = line.find(",", pos+1 ) ).c_str() );
      m_mapLayers = atoi( line.substr( antPos + 1, line.find( "\n", antPos + 1 ) ).c_str() );

      m_tileMatrix = new std::vector< std::vector< std::vector< int > > >
         ( m_mapLayers,  std::vector< std::vector< int> > // layers
         ( m_mapHeight,  std::vector< int >               // lines
         ( m_mapWidth, -1 ) ) );                         // columns

      for( int layer = 0; layer < m_mapLayers; ++layer )
      {
         std::string mapCoordinatesString;
         std::getline( fileStream, mapCoordinatesString );

         for( int coordY = 0; coordY < m_mapHeight; ++coordY )
         {
            std::getline( fileStream, mapCoordinatesString );

            int position = 0;
            for( int coordX = 0; coordX < m_mapWidth ; ++coordX )
            {
               int nextPos = mapCoordinatesString.find( ",", position );
               int value;

               if( coordX == 0 )
                  value = atoi( mapCoordinatesString.substr( position, nextPos ).c_str() );
               else
                  value = atoi( mapCoordinatesString.substr( position + 1, nextPos ).c_str() );

               (*m_tileMatrix)[ layer ][ coordY ][ coordX ] =  value - 1;

               position = mapCoordinatesString.find(",", position + 1);
            }
         }
      }
   }
   fileStream.close();
}

int& TileMap::at( int x, int y, int z )
{
   return m_tileMatrix->at( z ).at( y ).at( x );
}

void TileMap::Render( double cameraX, double cameraY )
{
   if( m_tileSet != NULL )
   {
      for( int z = 0; z < m_mapLayers; ++z)
      {
         for( int y = 0; y < m_mapHeight; ++y )
         {
            for( int x = 0; x < m_mapWidth; ++x )
            {
               if( m_tileMatrix->at(z).at(y).at(x) != -1 )
               {

                  m_tileSet->Render( m_tileMatrix->at(z).at(y).at(x), x*( m_tileSet->GetTileWidth() ) - cameraX , y*m_tileSet->GetTileHeight() - cameraY );
               }
            }
         }
      }
   }
}

void TileMap::RenderLayer( unsigned short layer, double cameraX, double cameraY )
{
   if( m_tileSet != NULL )
   {
      for( int y = 0; y < m_mapHeight; ++y )
      {
         for( int x = 0; x < m_mapWidth; ++x )
         {
            if( m_tileMatrix->at(layer).at(y).at(x) != -1 )
            {
               m_tileSet->Render( m_tileMatrix->at(layer).at(y).at(x), x*( m_tileSet->GetTileWidth() ) - cameraX , y*m_tileSet->GetTileHeight() - cameraY );
            }
         }
      }
   }
}

TileMap::~TileMap(void)
{
   delete m_tileMatrix;
}
