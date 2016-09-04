#pragma once
#include "Observer.h"
#include "Text.h"
#include "MainCharacter.h"
#include "Rect.h"


#define PROPORTION_TO_DANGER 0.40
class HUD : public Observer
{
public:
   HUD::HUD( GameEntity* mainChar,
             Animation* healthBarShell, 
             Animation* healthBar, 
             Sprite* lifeIcon, 
             Sprite* lifeStatusIcon, 
             Text* text, 
             bool inverted = false );
   ~HUD();

   void Update( int dt );
   void AlertAndUpdate();
   void Render( double posX, double posY );
private:
   Rect< double > m_rect;
   Rect< double > m_posRect;
   Animation * m_healthBarShell;
   Animation * m_healthBar;
   Sprite * m_lifeIcon;
   Sprite * m_lifeStatusIcon;
   Text   * m_text;

   bool m_isInverted;

   bool m_blink;
   double m_proportion;
};

