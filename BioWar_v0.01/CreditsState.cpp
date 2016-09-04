#include "CreditsState.h"

#include "InputManager.h"
#include "MenuState.h"

CreditsState CreditsState::m_instance;

CreditsState * CreditsState::GetInstance()
{
   return &m_instance;
}

CreditsState::CreditsState() :
   musicFadeIn( 300 ),
   musicFadeOut( 300 )
{
}

void CreditsState::Init()
{
   m_quit = false;
   
   m_bg        = new Sprite( "img/victoryScreen_with_text240px.png" );
   m_music     = new Music( "sfx/Ending.ogg", musicFadeIn, musicFadeOut );

   m_music->Play( -1 );
}

void CreditsState::CleanUp()
{

   m_music->Stop();
   delete m_music;
   delete m_bg;  
}

void CreditsState::Pause()
{
}

void CreditsState::Resume()
{
}

void CreditsState::GainFocus( GameManager * manager )
{
   m_bg->Render( 0, 0 );

   SDLBase::RefreshScreen();
}

void CreditsState::HandleEvents( GameManager * manager )
{
   InputManager::GetInstance()->Update();
   if( InputManager::GetInstance()->QuitGame() ||
      InputManager::GetInstance()->IsKeyDown( SDLK_ESCAPE ) )
      m_quit = true;
   if( InputManager::GetInstance()->IsKeyDown( SDLK_SPACE ) )
      manager->ChangeState( MenuState::GetInstance() );
   if( m_quit )
      manager->QuitGame();
}

void CreditsState::Update( GameManager * manager )
{
}