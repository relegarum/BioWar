#pragma once
#include "GameObject.h"
#include "AnimationSet.h"
#include <memory>

class Shoot : public GameObject
{
public:

   enum Direction
   {
      RIGHT = 0,
      LEFT  = 1
   };

   Shoot( std::unique_ptr< AnimationSet >& animationSet, double x, double y, int damage, int direction, double width, double height, double limit );
   ~Shoot() = default;

   int  Update( int dt ) = 0;
   void Render( double cameraX, double cameraY );

   inline double GetStart(){ return m_start; }
   int GetDamage(){ return m_damage; }

protected:
   const double        ShootWidth;
   const double        ShootHeight;
   const unsigned long Limit;

   std::unique_ptr< AnimationSet > m_animationSet;
   int            m_direction;
   double         m_start;
   int            m_damage;
};

