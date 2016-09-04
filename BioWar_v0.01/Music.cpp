#include "Music.h"


Music::Music( std::string fileName, short fadeInTime, short fadeOutTime ) :
   Audio( fileName ),
   m_fadeIntime( fadeInTime ),
   m_fadeOutTime( fadeOutTime )
{
   m_music = SDLBase::LoadMusic( fileName );
}

void Music::Play( short numberOfTimes )
{
#ifdef RELEASE
   if( m_fadeIntime == 0 )
   {
      if( Mix_PlayMusic( m_music, numberOfTimes ) == -1 )
         std::cerr << Mix_GetError() << std::endl;
   }
   else
   {
      if( Mix_FadeInMusic( m_music, numberOfTimes, m_fadeIntime ) == -1 )
         std::cerr << Mix_GetError() << std::endl;
   }
#endif
}


void Music::Stop()
{
   Mix_FadeOutMusic( m_fadeOutTime );
}

Music::~Music(void)
{
   Mix_HaltMusic();
   Mix_FreeMusic( m_music );
}
