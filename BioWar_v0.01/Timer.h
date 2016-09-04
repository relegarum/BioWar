#pragma once
#include <SDL_timer.h>
class Timer
{
public:
   Timer();
   ~Timer();

   void Start();
   void Stop();
   void Pause();
   void UnPause();

   int GetTicks();

   inline bool IsStarted(){ return m_started; }
   inline bool IsPaused(){ return m_paused; }

private:
   int m_startTicks;
   int m_pausedTicks;

   bool m_paused;
   bool m_started;
};

