#pragma once
#include "Animation.h"
#include <map>
#include <memory>

class AnimationSet : public Animation
{
public:
   AnimationSet( std::string filePath, int frameTime, uint16_t numberOfSprite, uint16_t numberOfRows );
   AnimationSet( std::string filePath, int frameTime, uint16_t numberOfSprites, uint16_t numberOfRows, int alphaRed, int alphaGreen, int alphaBlue );
   ~AnimationSet();

   void Update( int dt );
   void SetAnimationRow( uint16_t row );
   void ChangeRowSpritesNumber( uint16_t row, uint16_t numberOfSprites );

private:
   uint16_t m_numberOfRows;
   std::map< uint16_t, uint16_t > m_animationSet;
   int m_frameSkip;
   int m_frameTime;
   int m_time;
   int m_actualRow;
};

