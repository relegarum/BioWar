#include "FlyingManthis.h"
#include "MainCharacterShoot.h"

const double FlyingManthis::deltaPhi = 0.002;

FlyingManthis::FlyingManthis( GameEntity * subject, double x, double y, double radius, double w, double h, int hitPoints, int damage ) :
   Enemy( x, y, w, h, FlyingManthisType, hitPoints, damage, MainCharacterShoot::Red ),
   Observer( subject ),
   m_radius( radius ),
   m_xCenter( x ),
   m_yCenter( y ),
   m_angle( 0 ),
   m_canCreateShoot( false ),
   m_shootTime( 1000 ),
   m_hurtTime( 100 )
{
   m_shootTimer.Start();
   m_label = LEFT;
   m_y = m_y - m_box.m_h/2 + m_radius*sin( m_angle );
   m_x = m_x - m_box.m_w/2 +   m_radius*cos( m_angle );
}

bool FlyingManthis::CreateShoot()
{
   if( m_canCreateShoot )
   {
      m_canCreateShoot = false;
      return true;
   }
   return false;
}

void FlyingManthis::ChangeHitPoints( int damage )
{
   m_actualHitPoints -= damage;
   m_label  |= HURT;
   m_hurtTimer.Start();
}

void FlyingManthis::AddAnimation( uint16_t label, std::shared_ptr< Animation >& animation )
{
   m_animationMap[ label ] = animation;
   m_shootAnimationTime = animation->GetFrameTime()*animation->GetNumberOfSprites();
}

int FlyingManthis::Update( int dt )
{
   if( m_hurtTimer.GetTicks() > m_hurtTime )
   {
      if( m_label & HURT )
      {
         m_label &= ~(HURT);
      }
   }

   if( m_shootTimer.GetTicks() > m_shootAnimationTime )
   {
      if( m_label & ATTACK )
      {
         m_canCreateShoot = true;
         m_label &= ~(ATTACK);
      }
   }

   if( m_x > m_subject->GetX() )
   {
      m_direction = LEFT;
      m_label |= LEFT;
   }
   else
   {
      m_direction = RIGHT;
      m_label |= RIGHT;
   }

   if( std::abs( m_x - m_subject->GetX() ) < 200 )
   {
      if( m_shootTimer.GetTicks() > m_shootTime )
      {
         m_label |= ATTACK;
         m_shootTimer.Start();
      }
   }

   m_angle += deltaPhi*dt;
   m_y = m_yCenter - m_box.m_h/2 + m_radius*sin( m_angle );
   m_x = m_xCenter - m_box.m_w/2 +   m_radius*cos( m_angle );
   m_animationMap[ m_label ]->Update( dt );

   return 0;
}

void FlyingManthis::AlertAndUpdate()
{

}



FlyingManthis::~FlyingManthis(void)
{
}
