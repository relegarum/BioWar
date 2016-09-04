#pragma once
#include "GameState.h"
#include "Music.h"
class CreditsState : public GameState
{
public:
   void Init();
   void CleanUp();

   void Pause();
   void Resume();

   void GainFocus( GameManager * manager );
   void HandleEvents( GameManager * manager );
   void Update( GameManager * manager );

   static CreditsState * GetInstance();

protected:
   CreditsState();

   static CreditsState m_instance;
   bool m_quit;

   Music *          m_music;
   Sprite *         m_bg;
   const unsigned short  musicFadeIn;
   const unsigned short  musicFadeOut;
};

