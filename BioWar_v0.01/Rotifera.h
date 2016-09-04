#pragma once
#include "enemy.h"
#include "Observer.h"
#include "Shoot.h"
#include "Timer.h"

class Rotifera : public Enemy, public Observer
{
public:
   enum Status
   {
      UP    = 0,
      DOWN  = 1,
      HURT  = 1 << 1 
   };

   Rotifera( GameEntity *entity, double x, double y, double w, double h, int hitPoints = 150, int damage = 15 );
   ~Rotifera(void);

   int Update( int dt );
   void AlertAndUpdate();

   void ChangeHitPoints( int damage );
  

private:
   bool  m_allowedToMove;
   int   m_jumpTime;
   int   m_waitTime;
   int   m_hurtTime;


   Timer m_jumpTimer;
   Timer m_waitTimer;
   Timer m_hurtTimer;

};

