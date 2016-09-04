#include "MainCharacter.h"
#include "InputManager.h"
#include "AnimationSet.h"
#include "MainCharacterShoot.h"

MainCharacter::MainCharacter( double x, double y, double w, double h, int hitPoints ) :
   GameEntity( x, y, w, h, hitPoints, W3L2NId ),
   m_frame( 0 ),
   m_velX( 0 ),
   m_velY( 0 ),
   m_jumping( false ),
   m_jumpAcceleration( 30 ),
   m_falling( true ),
   m_createShoot( false ),
   m_gettinHurt( false ),
   m_shotType( MainCharacterShoot::Blue ),
   JumpingBaseSpeed( 12 ),
   High( JumpingBaseSpeed*JumpingBaseSpeed*(0.5)*m_jumpAcceleration ),
   HurtSpeed( -12 ),
   HurtHigh( HurtSpeed*HurtSpeed*(0.5)*m_jumpAcceleration ),
   m_hurtingTime( 500 )
{
   m_shootForce = NOSHOOT;
   m_shootingTimer.Start();
   m_changingWeaponTimer.Start();

   m_box.m_x += w*0.9;
   m_box.m_w -= w*0.5;
   m_label = RIGHT;
}

void MainCharacter::RAUL()
{
   m_label = VICTORY;
   m_victoryTimer.Start();
}

bool MainCharacter::Finish()
{
   if( m_victoryTimer.GetTicks() >  3000 )
   {
      return true;
   }
   return false;
}


bool MainCharacter::Loose()
{
   if( m_deathTimer.GetTicks() > 2000 )
   {
      return true;
   }
   return false;
}

//Implementação
double MainCharacter::GetVelX() const
{
   return m_velX;
}

void MainCharacter::SetVelX( const double velX )
{
   m_velX = velX;
}
double MainCharacter::GetVelY() const
{
   return m_velY;
}

void MainCharacter::AttachObserver( Observer * observer )
{
   m_observerPool.push_back( observer );
}

void MainCharacter::SetVelY( const double velY )
{
   m_velY = velY;
}
//Fim da implementação 

void MainCharacter::SetFalling( bool falling )
{
   m_falling = falling;
}

void MainCharacter::ChangeHitPoints( int damage )
{
   if( m_label & DEATH )
   {
      return;
   }

   m_actualHitPoints -= damage;
   if( m_actualHitPoints > m_maxHitPoints )
   {
      m_actualHitPoints = m_maxHitPoints;
   }
   
   if( m_actualHitPoints < 0 )
   {
      if( m_label & LEFT )
         m_label = LEFT;
      else
         m_label = RIGHT;

      m_label |= DEATH;

      m_deathTimer.Start();
   }


   for( auto itr : m_observerPool )
   {
      if( itr != NULL )
         itr->AlertAndUpdate();
      else
         DetachObserver( itr );
   }

   if( ( damage > 0 ) &&
       ( m_gettinHurt == false ) &&
       m_actualHitPoints > 0 )
   {
      m_label |= HURTED;
      m_hurtingTimer.Start();
      m_gettinHurt = true;
      if( m_velX != 0 )
      {
         if( m_velX > 0 )
         {
            m_velX = -0.25;
            m_velY = HurtSpeed;
         }
         else
         {
            m_velX = 0.25;
            m_velY = HurtSpeed;
         }
      }
      else
      {
         if( m_label & LEFT )
         {
            m_velX = -0.25;
         }
         else 
         {
            m_velX = 0.25;
         }
      }
   }
}

void MainCharacter::InputHandle()
{
   if( m_label == VICTORY )
   {
      return;
   }

   if( InputManager::GetInstance()->IsKeyDown( SDLK_SPACE ) ||
      InputManager::GetInstance()->IsJoystickButtonDown( 2 ) )
   {
      if( m_velY == 0 )
      {
         m_jumping = true;
         m_velY = -JumpingBaseSpeed;
      }
   }
   if( !m_gettinHurt )
   {
      if( InputManager::GetInstance()->IsKeyPressed( SDLK_LEFT ) ||
         InputManager::GetInstance()->IsKeyPressed( SDLK_a ) ||
         InputManager::GetInstance()->IsJoystickHatPressed( SDL_HAT_LEFT ) ) 
      {
         m_velX = -0.25;
         m_label = LEFT;
      }
      else if( InputManager::GetInstance()->IsKeyPressed( SDLK_RIGHT ) ||
         InputManager::GetInstance()->IsKeyPressed( SDLK_d ) ||
         InputManager::GetInstance()->IsJoystickHatPressed( SDL_HAT_RIGHT ) )
      {
         m_velX = 0.25;
         m_label = RIGHT;
      }
      else
      {
         m_velX = 0;
      }
   }

   if( InputManager::GetInstance()->IsKeyDown( SDLK_h ) ||
      InputManager::GetInstance()->IsJoystickButtonPressed( 7 ) )
   {
      if( m_changingWeaponTimer.GetTicks() > 300 )
      {
         ++m_shotType;
         if( m_shotType > MainCharacterShoot::Green )
            m_shotType = MainCharacterShoot::Blue;

         m_changingWeaponTimer.Start();
      }
   }

   if( InputManager::GetInstance()->IsKeyPressed( SDLK_j ) ||
      InputManager::GetInstance()->IsJoystickButtonPressed( 3 ) )
   {
      if( !m_chargeTimer.IsStarted() )
         m_chargeTimer.Start();

      m_label |= SHOOTING;
   }
   else
   {
      if( m_chargeTimer.IsStarted() )
      {
         if( m_chargeTimer.GetTicks() < 500 )
         {
            m_shootForce = SIMPLE;
         }
         else
         {
            m_shootForce = CHARGED;
         }
         m_chargeTimer.Stop();
      }
      m_label &= ~(SHOOTING);
   }
}

unsigned short MainCharacter::ShootType()
{
   return m_shotType;
}

int MainCharacter::Update( int dt )
{
   if( m_label == VICTORY ||
       ( m_label & DEATH ) )
   {
      m_animationMap [ m_label ]->Update( dt );
      return 0;
   }

   m_x += m_velX*dt;

   if( m_hurtingTimer.GetTicks() > m_hurtingTime )
   {
      if( m_label & HURTED )
         m_label &= ~(HURTED);
   }

   if( m_gettinHurt )
   {
      if( m_velY == 0 )
      {
         m_gettinHurt = false;
         m_velX = 0;
      }
   }

   if( m_falling )
   {

      m_velY += m_jumpAcceleration*dt*0.001;
      m_y += m_velY;
   }



   if( m_jumping )
   {
      m_label |= JUMPING;
      if( m_velY < JumpingBaseSpeed && m_velY > JumpingBaseSpeed*0.75 )
      {
         m_animationMap[ m_label ]->SetFrame( 0 );
      }
      if( m_velY < JumpingBaseSpeed*0.75 && m_velY > JumpingBaseSpeed*0.5 )
      {
         m_animationMap[ m_label ]->SetFrame( 1 );
      }
      else if( m_velY < JumpingBaseSpeed*0.5 && m_velY > JumpingBaseSpeed*0.5 )
      {
         m_animationMap[ m_label ]->SetFrame( 2 );
      }
      else if( m_velY < JumpingBaseSpeed*0.25 && m_velY > 0 )
      {
         m_animationMap[ m_label ]->SetFrame( 3 );
      }
   }
   else
   {
      m_label &= ~(JUMPING);

      if( m_velX != 0 )
         m_animationMap[ m_label ]->Update( dt );
      else
         m_animationMap[ m_label ]->SetFrame( 0 );
   }
 
   return 0;
}

void MainCharacter::DetachObserver( Observer * observer )
{
   auto itr =  std::find( m_observerPool.begin(), m_observerPool.end(), observer );
   if( itr != m_observerPool.end() )
      m_observerPool.erase( itr );
}

int MainCharacter::GetDirection()
{
   if( m_label & LEFT )
   {
      return LEFT;
   }
   else
   {
      return RIGHT;
   }
}

bool MainCharacter::GetIsJumping()
{
   if( m_label & JUMPING )
   {
      return true;
   }
   else
   {
      return false;
   }
}

short MainCharacter::CreateShoot()
{
   short valueToReturn = m_shootForce;
   m_shootForce = NOSHOOT;
   return valueToReturn;
}

void MainCharacter::SetJumpAcceleration( double acc )
{
   m_jumpAcceleration = acc;
}

void MainCharacter::HandleCollision()
{
   if( m_exceedBot > 0 )
   {
      m_jumping = false;
      m_velY = 0;
      m_y   -= m_exceedBot;
   }

}

void MainCharacter::HandleCollision( GameObject * object )
{
   if( CollidesWith( object ) )
   {
      if( m_exceedBot > 0 )
      {
         m_jumping = false;
         m_velY = 0;
         m_y   -= m_exceedBot;
      }
      if( m_exceedTop > 0 )
      {
         m_y -= m_exceedTop;
      }
      if( CollidesWith( object ) )
      {
         if( m_exceedRight > 0 )
         {
            if( m_velX > 0 )
               m_x -= m_exceedRight;
         }
         if( m_exceedLeft < 0 )
         {
            if( m_velX < 0 )
               m_x -= m_exceedLeft;
         }
      }
   }

   m_exceedLeft  = 0;
   m_exceedBot   = 0;
   m_exceedRight = 0;
   m_exceedTop   = 0;
}

bool MainCharacter::CollidesWith( GameObject *  other )
{
   int leftObject   = m_x;
   int rightObject  = m_x + m_box.m_w;
   int topObject    = m_y;
   int bottomObject = m_y + m_box.m_h;

   int leftOther   = other->GetX();
   int rightOther  = other->GetX() + other->GetRectBox().m_w;
   int topOther    = other->GetY();
   int bottomOther = other->GetY() + other->GetRectBox().m_h;

   if( bottomObject <= topOther )
      return false;
   if( topObject >= bottomOther )
      return false;
   if( rightObject <= leftOther )
      return false;
   if( leftObject >= rightOther )
      return false;
   

   m_exceedLeft  = leftObject - rightOther;
   m_exceedBot   = bottomObject - topOther;
   m_exceedRight = rightObject - leftOther;
   m_exceedTop   = topObject - bottomOther;

   return true;
}

bool MainCharacter::CollidesWithEntity( GameEntity *other )
{
   int leftObject   = m_x;
   int rightObject  = m_x + m_box.m_w;
   int topObject    = m_y;
   int bottomObject = m_y + m_box.m_h;

   int leftOther   = other->GetX();
   int rightOther  = other->GetX() + other->GetRectBox().m_w;
   int topOther    = other->GetY();
   int bottomOther = other->GetY() + other->GetRectBox().m_h;

   if( bottomObject <= topOther )
      return false;
   if( topObject >= bottomOther )
      return false;
   if( rightObject <= leftOther )
      return false;
   if( leftObject >= rightOther )
      return false;

   if( other->GetId() != EnemyId )
   {
      m_exceedLeft  = leftObject - rightOther;
      m_exceedBot   = bottomObject - topOther;
      m_exceedRight = rightObject - leftOther;
      m_exceedTop   = topObject - bottomOther;
   }

   return true;
}


MainCharacter::~MainCharacter()
{
}
