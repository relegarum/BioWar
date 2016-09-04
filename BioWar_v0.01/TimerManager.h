#pragma once
#include "Timer.h"
#include <string>

class TimerManager
{
public:
   static TimerManager * GetInstance();
   static void Free();

   void RegulateFPS();
   std::string GetFPS();
   int m_frame;

private:
   TimerManager();
   ~TimerManager();

   static TimerManager * m_instance;
   static const int FramesPerSecond;
   static const bool Regulate;

   Timer    m_fps;
   Timer    m_update;
};

