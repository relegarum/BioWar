#include "FlyingManthisShoot.h"

FlyingManthisShoot::FlyingManthisShoot( std::unique_ptr< AnimationSet >& animationSet, double x, double y, int damage, int direction, double targetX, double targetY ) :
   Shoot( animationSet, x, y, damage, direction, 20, 20, 30 ),
   m_targetX( targetX ),
   m_targetY( targetY ),
   m_reachedTarget( false )
{
   m_animationSet->SetAnimationRow( 0 ); 
}


int FlyingManthisShoot::Update( int dt )
{
   m_animationSet->Update( dt );
   /*if( m_x > ( m_start + Limit ) )
      m_animationSet->SetAnimationRow( 1 );*/

   auto distanceX = m_targetX - m_x;
   auto distanceY = m_targetY - m_y;
   auto distance  = sqrt( distanceX * distanceX + distanceY * distanceY );
   
   auto speedY = ( 5.0*distanceY ) / distance;
   auto speedX = ( 5.0*distanceX ) / distance;

   m_x += speedX;
   m_y += speedY;

   auto positionX = static_cast< int >( std::abs( m_x - m_targetX ) );
   auto positionY = static_cast< int >( std::abs( m_y - m_targetY ) );
   if( ( positionX < 5 ) &&
       ( positionY < 5 ) )
   {
      m_reachedTarget = true;
   }

   return 0;

}
