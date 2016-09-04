#pragma once
#include "Enemy.h"
#include "Obstacle.h"
#include "tinyxml2.h"

class StageFactory
{
public:
   static Enemy * CreateEnemy( tinyxml2::XMLElement * enemy );
   static Obstacle * CreateObstacle( tinyxml2::XMLElement * obstacle );

protected:

   StageFactory();
};

