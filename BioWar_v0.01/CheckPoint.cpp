#include "CheckPoint.h"


CheckPoint * CheckPoint::m_instance;

CheckPoint::CheckPoint()
{
   m_file.open( "checkPoint.txt", std::fstream::in );
   read();
}


void CheckPoint::CheckPositions()
{
   double subjectPosX = m_subject->GetX();
   for( auto pos : m_positionMaps )
   {
      if( subjectPosX > m_lastCheckPoint )
      {
         if( subjectPosX > pos )
         {
            m_lastCheckPoint = pos;
            m_lastHitPoints = m_subject->GetHitPoints();
         }
      }
   }
}

CheckPoint * CheckPoint::GetInstance()
{
   if( m_instance != NULL )
   {
      m_instance = new CheckPoint();
   }

   return m_instance;
}

void CheckPoint::read()
{

   std::string line;
   if( std::getline( m_file, line ) )
      return;

   m_lastCheckPoint = atoi( line.c_str() );
   line.clear();

   if( std::getline( m_file, line ) )
      return;

   m_lastHitPoints = atoi( line.c_str() );
   line.clear();
}

void CheckPoint::AddPoints( double x )
{
   m_positionMaps.push_back( x );
}

CheckPoint::~CheckPoint(void)
{
   m_file.flush();
   m_file << m_lastCheckPoint << std::endl;
   m_file << m_lastHitPoints  << std::endl;
   m_file.close();
}
