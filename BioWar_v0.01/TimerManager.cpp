#include "TimerManager.h"
#include <sstream>
#include <string>

TimerManager * TimerManager::m_instance;
const int TimerManager::FramesPerSecond =  30;
const bool TimerManager::Regulate = true;


TimerManager * TimerManager::GetInstance()
{
   if( m_instance == NULL )
      m_instance = new TimerManager();
 
   return m_instance;
}

void TimerManager::Free()
{
   if( m_instance != NULL )
      delete m_instance;
}

TimerManager::TimerManager() : m_frame( 0 )
{
   m_update.Start();
   m_fps.Start();
}

void TimerManager::RegulateFPS()
{
   if( Regulate && ( m_update.GetTicks() < 1000 / FramesPerSecond ) )
   {
      SDL_Delay( ( 1000 / FramesPerSecond ) - m_update.GetTicks() );
   }
   m_update.Start();
}

std::string TimerManager::GetFPS()
{
   //float fps;
   if( m_update.GetTicks() > 1000 )
   {
      //fps = ( m_frame / ( m_fps.GetTicks() ) / 1000.f );
      std::stringstream stream;
      int tick = ( m_fps.GetTicks() );

      stream << " " << ( m_frame / (tick / 1000.f) ) << " fps";
      
      std::string teste = stream.str();
      m_update.Start();
      return teste;
   }
   return std::string();
}

TimerManager::~TimerManager()
{
}
