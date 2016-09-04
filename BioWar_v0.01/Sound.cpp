#include "Sound.h"


Sound::Sound( std::string fileName, short channel ) :
   Audio( fileName ),
   m_channel( channel )
{
   m_chunk = SDLBase::LoadChunk( fileName );
}

void Sound::Play( short numberOfTimes )
{
#ifdef RELEASE
   m_channel = Mix_PlayChannel( m_channel, m_chunk, numberOfTimes );
#endif
}

void Sound::Stop()
{
   Mix_HaltChannel( m_channel );
}

Sound::~Sound()
{
   Mix_FreeChunk( m_chunk );
}
   