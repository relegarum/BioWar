#include "StageFactory.h"


StageFactory::StageFactory(void)
{
}


Enemy * StageFactory::CreateEnemy( tinyxml2::XMLElement * enemy )
{

   tinyxml2::XMLElement * xmlElementType   = enemy->FirstChildElement( "TYPE" );
   tinyxml2::XMLElement * xmlElementHealth = enemy->FirstChildElement( "HEALTH" );
   tinyxml2::XMLElement * xmlElementDamage = enemy->FirstChildElement( "DAMAGE" );
   tinyxml2::XMLElement * xmlElementPosx   = enemy->FirstChildElement( "POSX" );
   tinyxml2::XMLElement * xmlElementPosy   = enemy->FirstChildElement( "POSY" );

   if( xmlElementType == NULL )
      return NULL;

   int type = atoi( xmlElementType->FirstChild()->ToText()->Value() );

   switch( type )
   {
      case Enemy::EnemyType::FlyingManthisType:
         break;
      case Enemy::EnemyType::NembrothaType:
         break;
      case Enemy::EnemyType::RotiferaType:
         break;
      default:
         break;
   }
}

Obstacle * StageFactory::CreateObstacle( tinyxml2::XMLElement * enemy )
{
   return NULL;
}
