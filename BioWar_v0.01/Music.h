#pragma once
#include "Audio.h"
#include "SDLBase.h"

class Music : public Audio
{
public:
   Music( std::string fileName, short fadeInTime = 0, short fadeOutTime = 0 );

   virtual void Play( short numberOfTimes );
   virtual void Stop();

   ~Music();

private:
   Mix_Music * m_music;
   short       m_fadeIntime;
   short       m_fadeOutTime;
};

