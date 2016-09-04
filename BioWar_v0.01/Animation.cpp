#include "Animation.h"


Animation::Animation( std::string filePath, int frameTime, int numberOfSprites, bool inverted ) :
   Sprite( filePath ),
   m_numberOfSprites( numberOfSprites ),
   m_frameTime( frameTime ),
   m_inverted( inverted ),
   m_time( 0 )
{
   m_clipRect.h = m_surface->h;
   m_clipRect.w = m_surface->w/numberOfSprites;
   m_clipRect.x = 0;
   m_clipRect.y = 0;
}


Animation::Animation( std::string filePath, int frameTime, int numberOfSprites, int alphaRed, int alphaGreen, int alphaBlue, bool inverted ) :
   Sprite( filePath, alphaRed, alphaGreen, alphaBlue ),
   m_numberOfSprites( numberOfSprites ),
   m_frameTime( frameTime ),
   m_inverted( inverted ),
   m_time( 0 )
{
   m_clipRect.h = m_surface->h;
   m_clipRect.w = m_surface->w/numberOfSprites;
   m_clipRect.x = 0;
   m_clipRect.y = 0;
}

Animation::~Animation()
{
}


void Animation::Update( int dt )
{
   m_time += dt;
   m_frameSkip = m_time/m_frameTime;
   m_time %= m_frameTime;
   
   int x;
   if( !m_inverted )
   {
      x = m_clipRect.x + m_clipRect.w*m_frameSkip;
      if( x >= m_surface->w )
         x = ( x - m_surface->w ) % m_surface->w;
   }
   else
   {
      x = m_clipRect.x - m_clipRect.w*( m_frameSkip );
      if( x < 0 )
         x = m_surface->w + x;
   }

   Clip( x, m_clipRect.y, m_clipRect.w, m_clipRect.h );
}

void Animation::SetFrame( int frame )
{

   int x;
   if( !m_inverted )
      x = m_clipRect.w*frame;
   else
      x = m_surface->w - m_clipRect.w*( frame + 1 );

   Clip( x, m_clipRect.y, m_clipRect.w, m_clipRect.h );
}

void Animation::SetFrameTime( int time )
{
   if( time <= 0 )
      return;

   m_frameTime = time;
}

int  Animation::GetFrameTime()
{
   return m_frameTime;
}