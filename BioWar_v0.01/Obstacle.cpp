#include "Obstacle.h"


Obstacle::Obstacle( Animation * sprite, double x, double y, double w, double h ) :
   GameObject( x, y, w, h ),
   m_animation( sprite )
{
}


Obstacle::~Obstacle(void)
{
}

int Obstacle::Update( int dt )
{
   m_animation->Update( dt );
   return 0;
}


void Obstacle::Render( double cameraX, double cameraY )
{
   m_animation->Render( m_x - cameraX, m_y - cameraY );
}