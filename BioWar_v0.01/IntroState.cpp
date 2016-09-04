#include "IntroState.h"
#include "StageOneState.h"
#include "InputManager.h"

IntroState IntroState::m_instance;
IntroState * IntroState::GetInstance()
{
   return &m_instance;
}

void IntroState::Init()
{
   m_scenePool = new std::vector< Sprite * >();
   m_subtitlesPool = new std::vector< std::vector< Text * > >();
   loadScenes();
   loadSubtitles();
   m_index = 0;
   m_haltTime = 0;
   m_music = new Music( "sfx/cataclysm.ogg", 200 );
   m_messageSound = new Sound( "sfx/keyboard_beep.wav" );
   m_introTimer.Start();
   m_soundTimer.Start();
   m_music->Play( -1 );
}

void IntroState::CleanUp()
{
   m_music->Stop();
   for( auto itr = m_scenePool->begin(); itr != m_scenePool->end(); ++itr )
   {
      Sprite * scene = (*itr);
      delete scene;
      m_scenePool->erase( itr );
   }

   /*for( auto itr = m_subtitlesPool->begin(); itr != m_subtitlesPool->end(); ++itr )
   {
      Text * text = (*itr);
      delete text;
      m_subtitlesPool->erase( itr );
   }*/

   delete m_music;
   delete m_messageSound;
   delete m_blankSprite;
   delete m_subtitleReader;
   delete m_subtitlesPool;
   delete m_scenePool;
}

void IntroState::loadScenes()
{
   
   m_blankSprite = new Sprite( "img/scenes/Result/Empty.png" );
   m_actualSprite = m_blankSprite;
   for( int i = 1; i <= NUMBER_OF_SCENES; ++i )
   {
      std:: string filename = "img/scenes/Result/";
      if( i < 10 )
         filename += "0" + std::to_string( i ) + ".png";
      else
         filename += std::to_string( i ) + ".png";
      
      m_scenePool->push_back( new Sprite( filename ) );
   }
}

void IntroState::loadSubtitles()
{

   //#1fc7e1 - COR azul
   m_subtitleReader = new SubtitleReader( "subtitles/OpeningSubtitles.txt" );
   for( size_t i = 0; i < m_subtitleReader->GetSubtitles().size(); ++i )
   {
      if( m_subtitleReader->GetLine( i ).first != -1 )
      {
         std::vector< Text * > sceneLines;
         for( size_t line = 0; line < m_subtitleReader->GetLine( i ).second.size(); ++line )
         {
            sceneLines.push_back( new Text( "fonts/Vdj.ttf", m_subtitleReader->GetLine( i ).second[ line ], 0x1f, 0xc7, 0xe1, 9 ) ); //#1FC7E1 - COR azul
         }
         m_subtitlesPool->push_back( sceneLines );
      }
   }
}

void IntroState::Pause()
{
   m_introTimer.Pause();
   m_music->Stop();
}

void IntroState::Resume()
{
   m_music->Play( -1 );
   m_introTimer.UnPause();
}

void IntroState::GainFocus( GameManager * manager )
{
   if( m_isText )
   {     
      if( m_soundTimer.GetTicks() > rand()%200 )
      {
         m_messageSound->Play();
         m_soundTimer.Start();
      }
      m_blankSprite->Render( 0, 0 ); 
      for( auto itr : m_actualText )
      {
         itr->Render( 0,  0 );
      }
   }
   else
   {
      m_actualSprite->Render( 0, 0 );
   }
}

void IntroState::HandleEvents( GameManager * manager )
{
   InputManager::GetInstance()->Update();
   if( InputManager::GetInstance()->IsKeyDown( SDLK_ESCAPE ) ||
      InputManager::GetInstance()->IsJoystickButtonDown( 9 ) )
   {
      manager->ChangeState( StageOneState::GetInstance() );
   }
}

void IntroState::Update( GameManager * manager )
{
   if( m_introTimer.GetTicks() > m_haltTime )
   {
      if( m_index < m_subtitleReader->GetSubtitles().size() )
      {

         if( m_subtitleReader->GetSubtitles().at( m_index ).first != -1 )
         {
            m_isText = true;
            m_actualText = m_subtitlesPool->at( m_actualTextIndex );
            int y = MAX_HEIGHT/2 - ((*m_actualText.begin())->GetBox().h )*(m_actualText.size());
            int biggerSize = 0;
            for( auto& itr : m_actualText ) // C++11
            {
               int x = MAX_WIDTH/2 - itr->GetBox().w/2;;
               itr->SetPos( x,  y );
               y += itr->GetBox().h*(1.5);
            }
            ++m_actualTextIndex;
         }
         else
         {
            m_isText = false;
            m_actualSprite = m_scenePool->at( m_actualImageIndex );
            ++m_actualImageIndex;
         }

         if( m_index < m_subtitleReader->GetSubtitles().size() )
         {
            if( m_subtitleReader->GetSubtitles().at( m_index ).first != -1 )
               m_haltTime = m_subtitleReader->GetSubtitles().at( m_index ).first;
            else
               m_haltTime = 3000;
         }
         ++m_index;
         m_introTimer.Start();
      }
      else
      {
         manager->ChangeState( StageOneState::GetInstance() );
      }
   }
}

