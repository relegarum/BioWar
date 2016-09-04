#pragma once
#include "tinyxml2.h"
#include "Enemy.h"
#include "Obstacle.h"
#include <vector>

class XMLLoader
{
public:

   static XMLLoader * GetInstance();

   void LoadFile( std::string filepath );
   std::vector< Enemy * > * GetEnemyPool();
   std::vector< Obstacle * > * GetObstaclePool();

private:
   static XMLLoader * m_instance;
   XMLLoader();
   ~XMLLoader();

   std::vector< Enemy * > m_enemyVector;
   std::vector< Obstacle * > m_obstacleVector;
};

