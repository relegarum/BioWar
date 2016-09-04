#pragma once
#include "GameState.h"
#include "Sprite.h"
#include "Animation.h"
#include "SubtitleReader.h"
#include "Text.h"
#include "Timer.h"
#include "Music.h"
#include "Sound.h"

#define NUMBER_OF_SCENES 18

class IntroState : public GameState
{
public:
   void Init();
   void CleanUp();

   void Pause();
   void Resume();

   void GainFocus( GameManager *manager );
   void HandleEvents( GameManager *manager );
   void Update( GameManager *manager );

   static IntroState * GetInstance();

protected:

   void loadScenes();
   void loadSubtitles();

   IntroState() { }
   static IntroState m_instance;

   Timer                     m_introTimer;
   Timer                     m_soundTimer;
   bool                      m_isText;

   unsigned long             m_index;
   unsigned long             m_actualImageIndex;
   unsigned long             m_actualTextIndex;
   unsigned long             m_haltTime;

   Music * m_music;
   Sound * m_messageSound;

   Sprite *                  m_blankSprite;
   std::vector< Sprite * > * m_scenePool;
   std::vector< std::vector< Text * > > *   m_subtitlesPool;

   Sprite *                  m_actualSprite;
   std::vector< Text * >     m_actualText;

   SubtitleReader *          m_subtitleReader;
};
