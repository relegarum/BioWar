#include "Planet.h"


Planet::Planet( Sprite *sprite, float hitPoints, float x, float y ): m_sprite( sprite ),
   m_hitPoints( hitPoints ),
   m_x( x ),
   m_y( y )
{
}

Planet::~Planet()
{
}

// Planet Methods
bool Planet::WasHit( int x, int y )
{
   return true;
}

void Planet::Render()
{
   m_sprite->Render( m_x, m_y );
}
