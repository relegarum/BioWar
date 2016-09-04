#include "Nembrotha.h"
#include "MainCharacterShoot.h"


Nembrotha::Nembrotha( double x, double y, double w, double h, int hitPoints, int damage ) :
   Enemy( x, y, w, h, NembrothaType, hitPoints, damage, MainCharacterShoot::Green ),
   m_hurtTime( 100 )
{
   m_label = LEFT;
   m_velX = 0.15;
}


Nembrotha::~Nembrotha(void)
{
}


void Nembrotha::ChangeHitPoints( int damage )
{
   m_actualHitPoints -= damage;
   m_label |= HURT;
   m_hurtTimer.Start();
}


int Nembrotha::Update( int dt )
{
   if( ( m_startXPos + m_box.m_w*2 ) < m_x ||
       ( ( m_startXPos - m_box.m_w*2 ) > m_x ) )
   {
      m_velX *= -1;
   }

   if( m_hurtTimer.GetTicks() > m_hurtTime )
   {
      if( m_label & HURT )
      {
         m_label &= ~(HURT);
         m_hurtTimer.Stop();
      }
   }

   m_label = ( m_velX > 0 )?RIGHT:LEFT;

   m_x += m_velX*dt;
   m_animationMap[ m_label ]->Update( dt );

   return 0;
}