#pragma once
#include "GameEntity.h"
#include <fstream>
#include <vector>

class CheckPoint 
{
public:

   void SetEntity( GameEntity * entity ){ m_subject = entity; };
   void CheckPositions();
   void AddPoints( double x );

   static CheckPoint * GetInstance();

   double GetStartPosition(){ return m_lastCheckPoint; }
   double GetStartHitPoints(){ return m_lastHitPoints; }

protected:
   CheckPoint();
   ~CheckPoint(void);

   void read();

   GameEntity * m_subject;
   std::fstream m_file;
   std::vector< double > m_positionMaps;
   double m_lastCheckPoint;
   double m_lastHitPoints;


   static CheckPoint * m_instance;
};

