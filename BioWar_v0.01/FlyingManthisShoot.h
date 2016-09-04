#pragma once
#include "shoot.h"
class FlyingManthisShoot : public Shoot
{
public:
   FlyingManthisShoot( std::unique_ptr< AnimationSet >& animationSet, double x, double y, int damage, int direction, double targetX, double targetY );
   ~FlyingManthisShoot() = default;

   int Update( int dt );

   inline bool HasReachedTarget(){ return m_reachedTarget; }

protected:
   double m_targetX;
   double m_targetY;

   bool m_reachedTarget;
};

