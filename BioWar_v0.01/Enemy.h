#pragma once

#include "GameEntity.h"

class Enemy : public GameEntity
{
public:

   enum EnemyType
   {
      FlyingManthisType = 1,
      NembrothaType     = 2,
      RotiferaType      = 3,
      BossType          = 4
   };

   Enemy( double x, double y, double w, double h, int enemyType, int hitPoints = 30, int damage = 2, uint16_t weakness = -1 );
   virtual int  Update( int dt ) = 0;
   ~Enemy();

   int GetDamage(){ return m_damage; }
   int GetWeakness(){ return m_weakness; }
   int GetEnemyType(){ return m_enemyType; }

protected:
   int    m_enemyType;
   int    m_damage;
   double m_startXPos;
   double m_startYPos;
   int    m_weakness;
};

