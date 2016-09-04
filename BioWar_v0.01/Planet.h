#pragma once

#include "Sprite.h"
class Planet 
{
public:
   Planet( Sprite *sprite, float hitPoints, float x, float y );
   ~Planet();

   // Planet Methods
   bool WasHit( int x, int y );
   void Render();

   inline int GetXPosition(){ return m_x; }
   inline int GetYPosition(){ return m_y; }
   inline Sprite * GetSprite(){ return m_sprite; };
   float    m_hitPoints;

private:
   float    m_x;
   float    m_y;
   Sprite * m_sprite;

};

