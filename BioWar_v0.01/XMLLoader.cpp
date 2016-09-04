#include "XMLLoader.h"


XMLLoader *  XMLLoader::m_instance;

XMLLoader * XMLLoader::GetInstance()
{
   if( m_instance == NULL )
   {
      m_instance = new XMLLoader();
   }

   return m_instance;
}

XMLLoader::XMLLoader()
{
}

void XMLLoader::LoadFile( std::string filepath )
{
   tinyxml2::XMLDocument doc;
   doc.LoadFile( filepath.c_str() );
   tinyxml2::XMLElement * root = doc.FirstChildElement( "STAGE" );
   tinyxml2::XMLElement * enemies = root->FirstChildElement( "ENEMIES" );
   for( tinyxml2::XMLElement * enemy = enemies->FirstChildElement( "ENEMY" );
      enemy != NULL;
      enemy = enemy->NextSiblingElement( "ENEMY" ) )
   {
      for( tinyxml2::XMLElement * element = enemy->FirstChildElement();
         element != NULL;
         element = element->NextSiblingElement() )
      {
         std::cout << element->Name() << ": " << element->FirstChild()->Value() << std::endl;
      }
      std::cout << std::endl;
   }

}

std::vector< Enemy * > * XMLLoader::GetEnemyPool()
{
   return &m_enemyVector;
}

std::vector< Obstacle * > * XMLLoader::GetObstaclePool()
{
   return &m_obstacleVector;
}

XMLLoader::~XMLLoader()
{
}
