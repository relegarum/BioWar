#include "Rotifera.h"
#include "MainCharacterShoot.h"

Rotifera::Rotifera( GameEntity *entity, double x, double y, double w, double h, int hitPoints, int damage ):
   Enemy( x, y, w, h, RotiferaType, hitPoints, damage, MainCharacterShoot::Blue ),
   Observer( entity ),
   m_jumpTime( 300 ),
   m_waitTime( 300 ),
   m_hurtTime( 100 )
{
   m_waitTimer.Start();
   m_startYPos = y;
   m_label = UP;
}


Rotifera::~Rotifera(void)
{
}


void Rotifera::AlertAndUpdate()
{


}

void Rotifera::ChangeHitPoints( int damage )
{
   m_actualHitPoints -= damage;
   m_label |= HURT;
   m_hurtTimer.Start();
}

int Rotifera::Update( int dt )
{
   if( m_hurtTimer.GetTicks() > m_hurtTime )
   {
      if( m_label & HURT )
      {
         m_label &= ~(HURT);
         m_hurtTimer.Stop();
      }
   }

   if( std::abs( m_subject->GetX() + m_subject->GetRectBox().m_w - m_x ) < m_subject->GetRectBox().m_w*2 )
   {
      m_allowedToMove = true;
   }
   else
   {
      if( m_allowedToMove && std::abs( m_subject->GetX() + m_subject->GetRectBox().m_w - m_x ) > m_subject->GetRectBox().m_w*5 )
      {
         m_allowedToMove = false;
         m_y = m_startYPos;
      }
   }

   if( m_allowedToMove )
   {
      if( m_y < ( m_startYPos - m_box.m_h*3 )  )
      {
         if( m_label == UP )
         {
            m_label = DOWN;
            m_velY *= -0.5;
         }
      }
      else if( m_y > m_startYPos )
      {
         m_waitTimer.Start();
         m_jumpTimer.Stop();
         m_velY = 0;
         m_y = m_startYPos;
         m_label = UP;
      }
      else
      {
         if( m_label == UP )
            m_velY  = -0.4;
      }

      m_y += m_velY*dt;
      m_animationMap[ m_label ]->Update( dt );
   }


   return 0;
}