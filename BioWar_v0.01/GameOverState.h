#pragma once

#include "GameState.h"
#include <list>
#include "Sprite.h"
#include "Text.h"
#include "Music.h"

class GameOverState : public GameState
{
public:

   void Init();
   void CleanUp();

   void Pause();
   void Resume();

   void GainFocus( GameManager *manager );
   void HandleEvents( GameManager *manager );
   void Update( GameManager *manager );

   static GameOverState  * GetInstance();
protected:
   GameOverState();
   ~GameOverState();
private:
   bool                  m_quit;
   static GameOverState  m_instance;
   
   Music *          m_music;
   Text *           m_text;
   Sprite *         m_bg;
   Sprite *         m_image;
   const unsigned short  musicFadeIn;
   const unsigned short  musicFadeOut;
   const unsigned short  textSize;
};

