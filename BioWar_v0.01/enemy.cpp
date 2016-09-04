#include "Enemy.h"


Enemy::Enemy( double x, double y, double w, double h, int enemyType, int hitPoints, int damage, uint16_t weakness ) :
   GameEntity( x, y, w, h, hitPoints, GameEntity::EnemyId ),
   m_enemyType( enemyType ),
   m_startXPos( x ),
   m_damage( damage ),
   m_weakness( weakness )
{
}

Enemy::~Enemy()
{
}

