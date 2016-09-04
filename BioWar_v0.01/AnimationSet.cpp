#include "AnimationSet.h"


AnimationSet::AnimationSet( std::string filePath, int frameTime, uint16_t numberOfSprites, uint16_t numberOfRows ) :
   Animation( filePath, frameTime, numberOfSprites ),
   m_time( 0 ),
   m_frameTime( frameTime )
{
   m_clipRect.h = m_surface->h/numberOfRows;
   for( int i = 0; i < numberOfRows; ++i )
   {
      m_animationSet[ i ] = numberOfSprites;
   }
}

AnimationSet::AnimationSet( std::string filePath, int frameTime, uint16_t numberOfSprites, uint16_t numberOfRows, int alphaRed, int alphaGreen, int alphaBlue ) :
   Animation( filePath, frameTime, numberOfSprites, alphaRed, alphaGreen, alphaBlue ),
   m_time( 0 ),
   m_frameTime( frameTime )
{
   m_clipRect.h = m_surface->h/numberOfRows;
   for( int i = 0; i < numberOfRows; ++i )
   {
      m_animationSet[ i ] = numberOfSprites;
   }
}

void AnimationSet::ChangeRowSpritesNumber( uint16_t row, uint16_t numberOfSprites )
{
   m_animationSet[ row ] = numberOfSprites;
}

void AnimationSet::SetAnimationRow( uint16_t row )
{
   m_actualRow = row;
}

void AnimationSet::Update( int dt )
{
   m_time += dt;
   m_frameSkip = m_time/m_frameTime;
   m_time %= m_frameTime;

   auto y = m_clipRect.h*m_actualRow;
   auto x = m_clipRect.x + m_clipRect.w * m_frameSkip;
   if( x >= m_surface->w )
   {
      x = ( x - m_surface->w ) % m_surface->w;
   }

   Clip( x, y, m_clipRect.w, m_clipRect.h );
}

AnimationSet::~AnimationSet()
{
}


