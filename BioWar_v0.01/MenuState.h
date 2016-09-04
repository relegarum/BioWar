#pragma once

#include "GameState.h"
#include "Button.h"
#include "Music.h"
#include <list>

class MenuState : public GameState
{
public:

   void Init();
   void CleanUp();

   void Pause();
   void Resume();

   void GainFocus( GameManager *manager );
   void HandleEvents( GameManager *manager );
   void Update( GameManager *manager );

   static MenuState * GetInstance();
protected:
   MenuState(){ }
private:
   Music * m_music;
   Sprite * m_background;
   Sprite * m_logo;
   std::list< Button * >  m_buttonList;
   static MenuState m_instance;
};

