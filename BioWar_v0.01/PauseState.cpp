#include "PauseState.h"
#include "MenuState.h"
#include "InputManager.h"


PauseState PauseState::m_instance;
PauseState * PauseState::GetInstance()
{
   return &m_instance;
}

void PauseState::Init()
{
   m_bg = new Sprite( "img/bioWarbg_320x240.png" );
   m_text = new Text( "fonts/04B_03__.ttf", 
                      "Press \"Enter\" to return to game or press \"Escape\" to return to Menu",
                      0xFF,
                      0xFF,
                      0xFF,
                      8 );
   m_text->SetPos( MAX_WIDTH*0.5 - m_text->GetBox().w*0.5, MAX_HEIGHT*0.5 - m_text->GetBox().h*0.5 );
   m_stageTimer.Start();
}

void PauseState::CleanUp()
{
   delete m_text;
   delete m_bg;
}

void PauseState::Pause()
{
   m_stageTimer.Pause();
}

void PauseState::Resume()
{
   m_stageTimer.Start();
}

void PauseState::GainFocus( GameManager * manager )
{
   m_bg->Render( 0, 0 );
   m_text->Render( 0, 0 );
}

void PauseState::HandleEvents( GameManager * manager )
{
   if( m_stageTimer.GetTicks() > 300 )
   {
      InputManager::GetInstance()->Update();
      if( InputManager::GetInstance()->IsKeyDown( SDLK_RETURN ) ||
         InputManager::GetInstance()->IsJoystickButtonDown( 9 ) )
      {
         if( manager->StackSize() > 1 )
            manager->PopState();
      }

      if( InputManager::GetInstance()->IsKeyDown( SDLK_ESCAPE ) ||
         InputManager::GetInstance()->IsJoystickButtonDown( 8 ) )
      {
         manager->PopState();
         manager->ChangeState( MenuState::GetInstance() );
      }
   }
}

void PauseState::Update( GameManager * manager )
{
}