#pragma once
#include "Enemy.h"
#include "Observer.h"
class FlyingManthis : public Enemy, public Observer
{
public:

   enum Status
   {
      RIGHT    = 0,
      LEFT     = 1,
      ATTACK   = 1 << 1,
      HURT     = 1 << 2,
   };

   FlyingManthis( GameEntity * entity, double x, double y, double radius, double w, double h, int hitPoints = 60, int damage = 5 );
   ~FlyingManthis();

   int Update( int dt );
   void AlertAndUpdate();

    bool CreateShoot();
    inline int  GetDirection(){ return m_direction; }

    void AddAnimation( uint16_t label, std::shared_ptr< Animation >& animation );

    void ChangeHitPoints( int damage );
private:

   static const double deltaPhi;
   double m_angle;
   double m_radius;
   double m_xCenter;
   double m_yCenter;
   int    m_shootTime;
   int    m_shootAnimationTime;
   int    m_hurtTime;

   int    m_direction;
   bool   m_canCreateShoot;
   Timer  m_shootTimer;
   Timer  m_hurtTimer;

};

