#include "Boss.h"


Boss::Boss( GameEntity * entity, double x, double y, double w, double h, int hitPoints, int damage ) :
   Enemy( x, y, w, h, BossType, hitPoints, damage ),
   Observer( entity ),
   m_noRollingTime( 700 ),
   m_missilingTime( 1000 ),
   m_shottingTime( 3000 ),
   m_rollVelX( 0.5 ),
   m_reachedRollTarget( false ),
   m_rollTargetDefined( false ),
   m_createMissil( false ),
   m_createShoot( false )
{
   m_shottingTimer.Start();
   m_label = LEFT;
   m_behavior = Behavior::SHOOTING;
   m_velX = 0.15;

}


Boss::~Boss(void)
{
}

int  Boss::Update( int dt )
{
   switch (m_behavior)
   {
   case Boss::Behavior::SHOOTING:
      {
         updateShooting( dt );
      }
      break;
   case Boss::Behavior::ROLL:
      updateRoll( dt );
      break;
   case Boss::Behavior::MISSILING:
      updateMissiling( dt );
      break;
   default:
      break;
   }

   return 0;
}

void Boss::AlertAndUpdate()
{
   double proportionMainChar = m_subject->GetHitPoints()/m_subject->GetMaxPoints();
   double proportionBoss     = m_actualHitPoints/m_maxHitPoints;
   
   if( proportionMainChar < 0.5 &&
       proportionBoss > proportionMainChar )
   {
      m_rollVelX *=0.75;
      m_missilingTime *= 1.25;
      m_shottingTime *= 1.25;
   }
   else if( proportionBoss > 0.25 )
   {
      m_rollVelX *=1.25;
      m_missilingTime *= 0.80;
      m_shottingTime *= 0.80;
   }

}

void Boss::updateRoll( int dt )
{

   if( m_noRollingTimer.GetTicks() > m_noRollingTime )
   {

      if( !m_rollTargetDefined )
      {

         m_targetRoll = m_subject->GetX();

      }

      if( std::abs( m_x - m_targetRoll ) > 5 )
      {
         m_label |= ROLLING;
         m_x += m_rollVelX*dt;
         m_animationMap[ m_label ]->Update( dt );
      }
      else
      {
         m_label &= ~(ROLLING);
         m_reachedRollTarget = true;
         m_rollTargetDefined = false;
         m_noRollingTimer.Start();
      }

      double velX = 0.0;
      if( ( m_targetRoll - m_x ) > 0 )
      {
         m_label |= RIGHT;
         velX += std::abs( m_rollVelX );
      }
      else
      {
         m_label  |= LEFT;
         velX -= std::abs( m_rollVelX );
      }
      m_rollVelX = velX;
   }
}


void Boss::ChangeHitPoints( double damage )
{
   m_actualHitPoints -= damage;
   for( auto itr : m_observerPool )
   {
      if( itr != NULL )
         itr->AlertAndUpdate();
   }
}

void Boss::AttachObserver( Observer * observer )
{
   m_observerPool.push_back( observer );
}

bool Boss::CreateMissil()
{
   bool returnValue = m_createMissil;
   m_createMissil = false;
   return returnValue;
}

bool Boss::CreateShoot()
{
   bool returnValue = m_createShoot;
   m_createShoot = false;
   return returnValue;
}

void Boss::updateShooting( int dt )
{
   if( ( m_startXPos + m_box.m_w*2 ) < m_x ||
       ( ( m_startXPos - m_box.m_w*2 ) > m_x ) )
   {
      m_velX *= -1;
   }

   m_label = ( m_velX > 0 )?RIGHT:LEFT;
   m_direction = m_label;

   m_x += m_velX*dt;
   m_animationMap[ m_label ]->Update( dt );

   if( m_shottingTimer.GetTicks() > m_shottingTime )
   {
      if( std::abs( m_subject->GetX() - m_x ) < MAX_WIDTH )
      {
         m_createShoot = true;
         m_shottingTimer.Start();
      }
   }
}

void Boss::updateMissiling( int dt )
{
}