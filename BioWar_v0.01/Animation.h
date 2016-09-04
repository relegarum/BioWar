#pragma once
#include "Sprite.h"
class Animation : public Sprite
{
public:
   Animation( std::string filePath, int frameTime, int numberOfSprites, bool inverted = false  );
   Animation( std::string filePath, int frameTime, int numberOfSprites, int alphaRed, int alphaGreen, int alphaBlue, bool inverted = false );
   ~Animation();

   void Update( int dt );

   inline void SetInverted( bool value ){ m_inverted = value; }
   void SetFrame( int frame );
   void SetFrameTime( int time );
   int  GetFrameTime();
   int  GetNumberOfSprites(){ return m_numberOfSprites; }

protected:
   bool     m_inverted;
   int      m_numberOfSprites;
   int      m_time;
   int      m_frameSkip;
   int      m_frameTime;
   SDL_Rect m_box;
};

