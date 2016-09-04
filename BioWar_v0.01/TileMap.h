#pragma once
#include "TileSet.h"
#include <map>

class TileMap
{
public:
   TileMap( unsigned long mapWidth, unsigned long mapHeight, unsigned long tileSize, unsigned short layers  = 1, TileSet * tileSet = NULL );
   TileMap( std::string fileMapPath, TileSet * tileSet = NULL );

   int& at( int x, int y, int z = 0 );

   void Load( std::string fileMapPath );
   void Render( double cameraX = 0.0, double cameraY = 0.0 );
   void RenderLayer( unsigned short layer, double cameraX =  0.0, double cameraY = 0.0 );

   inline void SetTileSet( TileSet * tileSet ){ m_tileSet = tileSet; }

   inline unsigned long GetWidth(){   return m_mapWidth; }
   inline unsigned long GetHeight(){  return m_mapHeight; }
   inline unsigned short GetLayers(){ return m_mapLayers; }

   ~TileMap(void);

private:
   unsigned long  m_mapWidth;
   unsigned long  m_mapHeight;
   unsigned short m_mapLayers;

   TileSet * m_tileSet;
   std::vector< std::vector< std::vector < int > > > * m_tileMatrix;
};

