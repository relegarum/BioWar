#pragma once
#include "Shoot.h"
#include <memory>

class MainCharacterShoot : public Shoot
{
public:

   enum ShotType 
   {
      Blue  = 0,
      Red   = 1,
      Green = 2
   };

   MainCharacterShoot( std::unique_ptr< AnimationSet >& animationSet, double x, double y, int damage, int direction, ShotType type = ShotType::Blue );
   ~MainCharacterShoot();

   int  Update( int dt );

   inline double GetStart(){ return m_start; }
   uint16_t GetType(){ return m_type; }

private:

   const double   m_shootSpeed;
   double         m_start;
   uint16_t       m_type;
};

