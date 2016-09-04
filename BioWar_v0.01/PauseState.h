#pragma once
#include "gamestate.h"
#include "Text.h"
#include "Sprite.h"

class PauseState : public GameState
{
public:
   void Init();
   void CleanUp();

   void Pause();
   void Resume();

   void GainFocus( GameManager *manager );
   void HandleEvents( GameManager *manager );
   void Update( GameManager *manager );

   static PauseState * GetInstance();

protected:
   PauseState() { }
   static PauseState m_instance;

   Sprite * m_bg;
   Text   * m_text;
   Timer  m_stageTimer;
};

