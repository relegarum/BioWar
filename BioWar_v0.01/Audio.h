#pragma once
#include <string>

class Audio
{
public:
   Audio( std::string fileName );

   virtual void Play( short numberOfTimes ) = 0;
   virtual void Stop() = 0;

   ~Audio(void);
private:
   std::string m_fileName;
};

