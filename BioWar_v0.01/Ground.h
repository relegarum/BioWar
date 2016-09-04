#pragma once
#include "GameObject.h"
#include "TileMap.h"
#include "TileSetSingleFile.h"
class Ground : public GameObject
{
public:
   Ground( double x, double y, double w, double h );
   ~Ground();

   void Render( double cameraX, double cameraY );
   int Update( int dt );
private:
   TileSetSingleFile * m_tileSet;
   TileMap           * m_tileMap;

};

