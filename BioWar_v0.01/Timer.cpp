#include "Timer.h"


Timer::Timer():
   m_startTicks( 0 ),
   m_pausedTicks( 0 ),
   m_paused( false ),
   m_started( false )
{
    
}


void Timer::Start()
{
   m_started = true;
   m_paused = false;

   m_startTicks = SDL_GetTicks();
}

void Timer::Stop()
{
   m_started = false;
   m_paused  = false;
}

int Timer::GetTicks()
{
   if( m_started == true )
   {
      if( m_paused == true )
      {
         return m_pausedTicks;
      }
      else
      {
         return SDL_GetTicks() - m_startTicks;
      }
   }
   else
   {
      return 0;
   }
}

void Timer::Pause()
{
   if( ( m_started == true ) &&
       ( m_paused == false ) )
   {
      m_paused = true;
      m_pausedTicks = SDL_GetTicks() -  m_startTicks;
   }
}

void Timer::UnPause()
{
   if( m_paused == true )
   {
      m_paused = false;
      m_startTicks = SDL_GetTicks() - m_pausedTicks;
      m_pausedTicks = 0;
   }
}

Timer::~Timer(void)
{
}
