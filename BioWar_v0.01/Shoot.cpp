#include "Shoot.h"


Shoot::Shoot( std::unique_ptr< AnimationSet >& animationSet, double x, double y, int damage, int direction, double width, double height, double limit ) :
   GameObject( x, y, animationSet->GetClip().m_w, animationSet->GetClip().m_h ),
   m_animationSet( std::move( animationSet ) ),
   m_damage( damage ),
   m_direction( direction ),
   m_start( x ),
   ShootHeight( height ),
   ShootWidth( width ),
   Limit( limit )
{
   m_animationSet->SetAnimationRow( 0 );
   m_box.m_h = ShootHeight;
   m_box.m_w = ShootWidth;
}


void Shoot::Render( double cameraX, double cameraY )
{
   m_animationSet->Render( m_x - cameraX, m_y - cameraY );
}
