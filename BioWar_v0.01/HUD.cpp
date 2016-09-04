#include "HUD.h"


HUD::HUD( GameEntity* mainChar, Animation* healthBarShell, Animation* healthBar,Sprite* lifeIcon, Sprite* lifeStatusIcon, Text* text, bool inveted ) 
   : Observer( mainChar ),
   m_healthBar( healthBar ),
   m_healthBarShell( healthBarShell ),
   m_lifeIcon( lifeIcon ),
   m_lifeStatusIcon( lifeStatusIcon ),
   m_blink( false ),
   m_isInverted( inveted )
{
   m_rect = m_healthBar->GetClip();
}


void HUD::Render( double posX, double posY )
{
   m_healthBarShell->Render( posX,posY );
   m_healthBar->Render( posX, posY );
}


void HUD::Update( int dt )
{
   if( m_blink )
   {
      //m_healthBar->Update( dt );
      m_healthBarShell->Update( dt );
   }
   else
   {
      m_healthBarShell->SetFrame( 1 );
   }
}

void HUD::AlertAndUpdate()
{

   Rect< double > rect = m_rect;
   float maxPoints    = m_subject->GetMaxPoints();
   float actualPoints = m_subject->GetHitPoints();
   double proportion = (actualPoints/maxPoints);
   rect.m_w           = m_rect.m_w*(proportion);

   

   if( proportion < PROPORTION_TO_DANGER )
   {
      m_proportion = proportion;
      m_blink = true;
   }
   else
   {
      m_blink = false;
   }

   if( m_isInverted )
   {
      rect.m_x += m_rect.m_w*proportion;
   }


   m_healthBar->Clip( rect );
}

HUD::~HUD()
{
}
