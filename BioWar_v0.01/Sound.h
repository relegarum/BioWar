#pragma once
#include "Audio.h"
#include "SDLBase.h"
class Sound : public Audio
{
public:
   Sound( std::string fileName, short channel = -1 );
   void Play( short numberOfTimes = 0 );
   void Stop();

   ~Sound(void);
private:
   short       m_channel;
   Mix_Chunk * m_chunk;

};

