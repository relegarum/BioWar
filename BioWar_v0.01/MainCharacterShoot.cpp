#include "MainCharacterShoot.h"


MainCharacterShoot::MainCharacterShoot( std::unique_ptr< AnimationSet >& animationSet, double x, double y, int damage, int direction, ShotType type )
   : Shoot( animationSet, x, y, damage, direction, 17, 10, 20 ),
   m_start( x ),
   m_type( type ),
   m_shootSpeed( 0.3 )
{
   m_animationSet->SetAnimationRow( 0 );
   m_box.m_h = ShootHeight;
   m_box.m_w = ShootWidth;
}

MainCharacterShoot::~MainCharacterShoot()
{
}

int MainCharacterShoot::Update( int dt )
{
   m_animationSet->Update( dt );
   if( m_direction == RIGHT )
   {
      m_x += m_shootSpeed*dt;
      if( m_x > m_start + Limit )
      {
          m_animationSet->SetAnimationRow( 1 );
      }
   }
   else
   {
      m_x -= m_shootSpeed*dt;
      if( m_x < m_start - Limit )
      {
          m_animationSet->SetAnimationRow( 1 );
      }
   }  
   
   return 0;
}
