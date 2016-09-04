#pragma once
#include "enemy.h"
#include "Observer.h"

class Nembrotha : public Enemy
{
public:
   enum Status
   {
      RIGHT    = 0,
      LEFT     = 1,
      HURT     = 1 << 1,
   };

   Nembrotha( double x, double y, double w, double h, int hitPoints = 50, int damage = 7 );
   ~Nembrotha(void);

   int Update( int dt );
   void ChangeHitPoints( int damage );

private:


   int   m_hurtTime;
   Timer m_hurtTimer;
};

