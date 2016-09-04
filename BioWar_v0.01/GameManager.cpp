#include "GameManager.h"
#include "MenuState.h"
#include "TimerManager.h"

void GameManager::Run()
{
   ChangeState( MenuState::GetInstance() );
   render();
   while( m_isRunning )
   {
      handleEvents();
      update();
      render();
   }

}

void GameManager::QuitGame()
{
   m_isRunning = false;
}



void GameManager::ChangeState( GameState * state )
{
   if( !m_states.empty() )
   {
      m_states.back()->CleanUp();
      m_states.pop_back();
   }

   m_states.push_back( state );
   m_states.back()->Init();
}

void GameManager::PushState( GameState * state )
{
   if( !m_states.empty() )
   {
      m_states.back()->Pause();
   }
   if( state !=  NULL )
   {
      m_states.push_back( state );
      m_states.back()->Init();
   }
}

void GameManager::PopState()
{
   if( !m_states.empty() )
   {
      m_states.back()->CleanUp();
      m_states.pop_back();
   }

   if( !m_states.empty() )
   {
      m_states.back()->Resume();
   }
}

int GameManager::StackSize()
{
   return m_states.size();
}

void GameManager::handleEvents()
{
   m_states.back()->HandleEvents( this );
}

void GameManager::update()
{
   m_states.back()->Update( this );
}

void GameManager::render()
{
   m_states.back()->GainFocus( this );
   SDLBase::RefreshScreen();
   (++TimerManager::GetInstance()->m_frame );
   TimerManager::GetInstance()->RegulateFPS();
}

GameManager::GameManager()
{
   SDLBase::InitSDL();
}


GameManager::~GameManager()
{
   while( !m_states.empty() )
   {
      m_states.back()->CleanUp();
      m_states.pop_back();
   }

   SDLBase::Quit();
}
