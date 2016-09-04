#include "StageOneState.h"
#include "MenuState.h"
#include "InputManager.h"
#include "AnimationSet.h"
#include "PauseState.h"

#include "GameOverState.h"
#include "CreditsState.h"

#include <algorithm>
StageOneState StageOneState::m_instance;
StageOneState * StageOneState::GetInstance()
{
   return &m_instance;
}

void StageOneState::Init()
{
   m_hurtingTimer.Start();
   m_stageTimer.Start();

   setupBackGround();
   setupMainCharacter();
   setupTileMap();
   setupObstacle();
   setupEnemies();
   setupHud();
   setupItens();

   m_ship = std::make_unique< Obstacle >( m_shipSprite.get(),
                                          m_mainCharacter->GetX() - m_shipSprite->GetClip().m_w / 2,
                                          ( *m_groundPool.begin() )->GetY() - m_shipSprite->GetClip().m_h,
                                          m_shipSprite->GetClip().m_w,
                                          m_shipSprite->GetClip().m_h );

   m_shooting1Sound = std::make_unique< Sound >( "sfx/Shot1.wav" );
   m_shooting2Sound = std::make_unique< Sound >( "sfx/Shot2.wav" );
   m_shooting3Sound = std::make_unique< Sound >( "sfx/Shot3.wav" );
   m_dyingSound = std::make_unique< Sound >( "sfx/W3L2Ndeath.wav" );

   m_hurtingSound = std::make_unique< Sound >( "sfx/keyboard_beep.wav" );
   m_gettingLifeSound = std::make_unique< Sound >( "sfx/get_HP_little.wav" );
   m_bossGrowl = std::make_unique< Sound >( "sfx/Boss_Growl.wav" );
   m_shootPool = {};

   //m_shootingAnimationLeft->RotoZoom( 180 );

   m_cameraX = 0;
   m_cameraY = 0;

   m_cameraSpeedX = 0;
   m_cameraSpeedY = 0;
   m_pauseTimer.Start();
   m_music = std::make_unique< Music >( "sfx/firstStageloop.ogg", 300, 700 );
   m_bossMusic = std::make_unique< Music >( "sfx/bossSongLoop.ogg", 700 );
   m_victoryMusic = std::make_unique< Music >( "sfx/victory.ogg" );
   m_music->Play( -1 );
}

void StageOneState::setupObstacle()
{
   m_initialRuinSprite = std::make_shared< Animation >( "img/icc_stage/initialRuin.png", FRAME_TIME, 1 );
   m_busSprite = std::make_shared< Animation >( "img/flower_stage/bus.png", FRAME_TIME, 1 );
   m_phoneCabinSprite = std::make_shared< Animation >( "img/icc_stage/phoneCabin.png", FRAME_TIME, 1 );
   m_trashSprite = std::make_shared< Animation >( "img/icc_stage/trash.png", FRAME_TIME, 1 );
   m_leftRuinSprite = std::make_shared< Animation >( "img/icc_stage/leftRuin.png", FRAME_TIME, 1 );
   m_rightRuinSprite = std::make_shared< Animation >( "img/icc_stage/rightRuin.png", FRAME_TIME, 1 );
   m_leftRuin2Sprite = std::make_shared< Animation >( "img/icc_stage/leftRuin2.png", FRAME_TIME, 1 );
   m_rightRuin2Sprite = std::make_shared< Animation >( "img/icc_stage/rightRuin2.png", FRAME_TIME, 1 );
   m_centralRuinSprite = std::make_shared< Animation >( "img/icc_stage/centerRuin.png", FRAME_TIME, 1 );
   m_obstacleTreeSprite = std::make_shared< Animation >( "img/catedral_stage/obstacleCatedralTree.png", FRAME_TIME, 1 );
   m_paranoaBusSprite = std::make_shared< Animation >( "img/catedral_stage/ObstaculoOnibus_Paranoa_xD.png", FRAME_TIME, 1 );
   m_carSprite = std::make_shared< Animation >( "img/flower_stage/car.png", FRAME_TIME, 1 );

   m_initialRuin = std::make_shared< Obstacle >( m_initialRuinSprite.get(),
                                                 0,
                                                 MAX_HEIGHT - m_initialRuinSprite->GetHeight() + 20,
                                                 m_initialRuinSprite->GetWidth(),
                                                 m_initialRuinSprite->GetHeight() );

   m_obstacleTree = std::make_shared< Obstacle >( m_obstacleTreeSprite.get(),
                                                 THIRD_SCENARIO_BEGIN + 15 * TILE_WIDHT,
                                                 m_baseGround - m_obstacleTreeSprite->GetHeight(),
                                                 m_obstacleTreeSprite->GetWidth(),
                                                 m_obstacleTreeSprite->GetHeight() );

   m_car = std::make_shared< Obstacle >( m_carSprite.get(),
                                         THIRD_SCENARIO_BEGIN + 20 * TILE_WIDHT,
                                         m_baseGround - m_carSprite->GetHeight(),
                                         m_carSprite->GetWidth(),
                                         m_carSprite->GetHeight() );

   m_paranoaBus =  std::make_shared< Obstacle >( m_paranoaBusSprite.get(),
                                                    m_car->GetX() + m_car->GetRectBox().m_w,
                                                    m_baseGround - m_paranoaBusSprite->GetHeight(),
                                                    m_paranoaBusSprite->GetWidth(),
                                                    m_paranoaBusSprite->GetHeight() );

   m_bus =  std::make_shared< Obstacle >( m_busSprite.get(),
                                             SECOND_SCENARIO_BEGIN + 15 * TILE_WIDHT,
                                             m_baseGround - m_busSprite->GetHeight(),
                                             m_busSprite->GetWidth(), m_busSprite->GetHeight() );

   m_trash =  std::make_shared< Obstacle >( m_trashSprite.get(),                                                  // Sprite
                                               m_bus->GetX() - m_trashSprite->GetWidth(),                      // Position Right Before Bus   
                                               m_baseGround - m_trashSprite->GetHeight(),  // Position Over Ground
                                               m_trashSprite->GetWidth(),                                      // Width
                                               m_trashSprite->GetHeight() );                                   // Height     

   m_trash2 =  std::make_shared< Obstacle >( m_trashSprite.get(),                                                  // Sprite
                                                m_bus->GetX() + m_busSprite->GetWidth(),                      // Position Right after Bus   
                                                m_baseGround - m_trashSprite->GetHeight(),  // Position Over Ground
                                                m_trashSprite->GetWidth(),                                      // Width
                                                m_trashSprite->GetHeight() );                                   // Height     

   m_phoneCabin =  std::make_shared< Obstacle >( m_phoneCabinSprite.get(),
                                                FIRST_GAP - TILE_WIDHT * 2,
                                                m_baseGround - m_phoneCabinSprite->GetHeight(),  // Position Over Ground
                                                m_phoneCabinSprite->GetWidth(),
                                                m_phoneCabinSprite->GetHeight() );

   m_leftRuin =  std::make_shared< Obstacle >( m_leftRuinSprite.get(),
                                                MAX_WIDTH * 2,
                                                m_baseGround - m_leftRuinSprite->GetHeight(),
                                                m_leftRuinSprite->GetWidth(),
                                                m_leftRuinSprite->GetWidth() );


   m_centerRuin =  std::make_shared< Obstacle >( m_centralRuinSprite.get(),
                                                    m_leftRuin->GetX() + m_leftRuinSprite->GetWidth(),
                                                    m_baseGround - m_centralRuinSprite->GetHeight(),
                                                    m_centralRuinSprite->GetWidth(),
                                                    m_centralRuinSprite->GetHeight() );

   m_rightRuin =  std::make_shared< Obstacle >( m_rightRuinSprite.get(),
                                                   m_centerRuin->GetX() + m_centralRuinSprite->GetWidth(),
                                                   m_baseGround - m_rightRuinSprite->GetHeight(),
                                                   m_leftRuinSprite->GetWidth(),
                                                   m_leftRuinSprite->GetHeight() );

   m_leftRuin2 =  std::make_shared< Obstacle >( m_leftRuin2Sprite.get(),
                                                   MAX_WIDTH * 4,
                                                   m_baseGround - m_leftRuin2Sprite->GetHeight(),
                                                   m_leftRuin2Sprite->GetWidth(),
                                                   m_leftRuin2Sprite->GetHeight() );

   m_rightRuin2 =  std::make_shared< Obstacle >( m_rightRuin2Sprite.get(),
                                                    m_leftRuin2->GetX() + m_leftRuin2Sprite->GetWidth(),
                                                    m_baseGround - m_rightRuin2Sprite->GetHeight(),
                                                    m_centralRuinSprite->GetWidth(),
                                                    m_centralRuinSprite->GetHeight() );



   m_obstaclePool.push_front( m_initialRuin );
   m_obstaclePool.push_front( m_car );
   m_obstaclePool.push_front( m_paranoaBus );
   m_obstaclePool.push_front( m_leftRuin2 );
   m_obstaclePool.push_front( m_centerRuin );
   m_obstaclePool.push_front( m_rightRuin2 );
   m_obstaclePool.push_front( m_leftRuin );
   m_obstaclePool.push_front( m_rightRuin );
   m_obstaclePool.push_front( m_phoneCabin );
   m_obstaclePool.push_front( m_bus );
   m_obstaclePool.push_front( m_obstacleTree );
   m_obstaclePool.push_front( m_trash );
   m_obstaclePool.push_front( m_trash2 );
}

void StageOneState::setupHud()
{
   m_healthBar = std::make_shared< Animation >( "img/HUD/mainCharacterLifeBarHor.png", FRAME_TIME, 2 );
   m_healthBarEmpty = std::make_shared< Animation >( "img/HUD/mainCharacterLifeBarShellHor.png", FRAME_TIME, 2 );
   m_healthBar->SetFrame( 1 );
   m_healthBarEmpty->SetFrame( 1 );
   m_hud.swap( std::make_unique < HUD >( m_mainCharacter.get(), m_healthBarEmpty.get(), m_healthBar.get(), nullptr, nullptr, nullptr ) );



   m_bossHealthBar      = std::make_shared< Animation >( "img/HUD/bossHealthBar.png", FRAME_TIME, 2 );
   m_bossHealthBarEmpty = std::make_shared< Animation >( "img/HUD/bossHealthBarShell.png", FRAME_TIME, 2 );
   m_bossHealthBar->SetFrame( 1 );
   m_bossHealthBarEmpty->SetFrame( 1 );
   m_hudBoss.swap( std::make_unique < HUD >( m_boss.get(), m_bossHealthBarEmpty.get(), m_bossHealthBar.get(), nullptr, nullptr, nullptr ) );

   m_mainCharacter->AttachObserver( m_hud.get() );
   m_boss->AttachObserver( m_hudBoss.get() );
}
void StageOneState::setupEnemies()
{
   m_enemyPool = {};
   for( int i = 0; i < NUMBER_OF_NEMBROS; ++i )
   {
      std::shared_ptr< Animation > numbroDamageLeft     = std::make_shared< Animation >( "img/enemy/DAMAGEnembroLeft.png", FRAME_TIME, NUMBER_OF_NEMBRO_SPRITES );
      std::shared_ptr< Animation > numbroDamageRight    = std::make_shared< Animation >( "img/enemy/DAMAGEnembroRight.png", FRAME_TIME, NUMBER_OF_NEMBRO_SPRITES );
      std::shared_ptr< Animation > numbroAnimationLeft  = std::make_shared< Animation >( "img/enemy/nembroLeft.png", FRAME_TIME, NUMBER_OF_NEMBRO_SPRITES );
      std::shared_ptr< Animation > numbroAnimationRight = std::make_shared< Animation >( "img/enemy/nembroRight.png", FRAME_TIME, NUMBER_OF_NEMBRO_SPRITES, true );

      double posX;
      double posY;
      switch( i )
      {
      case 0:
      {
         posX = m_rightRuin->GetX() + m_rightRuin->GetRectBox().m_w + TILE_WIDHT * 3;
         posY = BASE_FLOOR - TILE_HEIGHT - 10;
      }
      break;
      case 1:
      {
         posX = m_bus->GetX() + m_bus->GetRectBox().m_w*0.5;
         posY = m_bus->GetY() - numbroAnimationLeft->GetHeight();

      }
      break;

      case 2:
      {
         posX = m_paranoaBus->GetX() + m_bus->GetRectBox().m_w*0.5;
         posY = m_paranoaBus->GetY() - numbroAnimationLeft->GetHeight();
      }
      case 3:
      {
         posX = THIRD_SCENARIO_BEGIN - 2 * MAX_WIDTH;
         posY = BASE_FLOOR - TILE_HEIGHT - 10;
      }
      break;
      default:
         posY = m_groundPool.front()->GetY() - numbroAnimationLeft->GetHeight();
         break;
      }

      std::unique_ptr< Enemy > enemy = std::make_unique < Nembrotha >( posX, posY, numbroAnimationLeft->GetClip().m_w*0.9, numbroAnimationLeft->GetClip().m_h*0.9, 30 );

      enemy->AddAnimation( Nembrotha::LEFT, numbroAnimationLeft );
      enemy->AddAnimation( Nembrotha::RIGHT, numbroAnimationRight );
      enemy->AddAnimation( Nembrotha::LEFT | Nembrotha::HURT, numbroDamageLeft );
      enemy->AddAnimation( Nembrotha::RIGHT | Nembrotha::HURT, numbroDamageRight );

      m_enemyPool.push_front( std::move( enemy ) );
   }

   for( int i = 0; i < NUMBER_OF_FLYING_MANTHIS; ++i )
   {
      auto manthisAnimationLeft              = std::make_shared< Animation >( "img/enemy/Flyingmantis_spritesheet_LEFT.png", FRAME_TIME, NUMBER_OF_FLYING_MANTHIS_SPRITES );
      auto manthisAnimationRight             = std::make_shared< Animation >( "img/enemy/Flyingmantis_spritesheet_RIGHT.png", FRAME_TIME, NUMBER_OF_FLYING_MANTHIS_SPRITES, true );
      auto manthisAnimationAttackLeft        = std::make_shared< Animation >( "img/enemy/AttackingMantis_LEFT_70cx60a.png", FRAME_TIME, NUMBER_OF_FLYING_MANTHIS_SPRITES );
      auto manthisAnimationAttackRight       = std::make_shared< Animation >( "img/enemy/AttackingMantis_RIGHT_70cx60a.png", FRAME_TIME, NUMBER_OF_FLYING_MANTHIS_SPRITES, true );
      auto manthisAnimationDamageRight       = std::make_shared< Animation >( "img/enemy/DAMAGEFlyingmantis_spritesheet_RIGHT.png", FRAME_TIME, NUMBER_OF_FLYING_MANTHIS_SPRITES, true );
      auto manthisAnimationDamageLeft        = std::make_shared< Animation >( "img/enemy/DAMAGEFlyingmantis_spritesheet_LEFT.png", FRAME_TIME, NUMBER_OF_FLYING_MANTHIS_SPRITES, true );
      auto manthisAnimationAttackDamageRight = std::make_shared< Animation >( "img/enemy/DAMAGEAttackingMantis_RIGHT_70x60.png", FRAME_TIME, NUMBER_OF_FLYING_MANTHIS_SPRITES, true );
      auto manthisAnimationAttackDamageLeft  = std::make_shared< Animation >( "img/enemy/DAMAGEAttackingMantis_LEFT_70x60.png", FRAME_TIME, NUMBER_OF_FLYING_MANTHIS_SPRITES, true );

      double posX;
      double posY = BASE_FLOOR - manthisAnimationRight->GetClip().m_h * 2;

      switch( i )
      {
      case 0:
      {
         posX = THIRD_SCENARIO_BEGIN - 2 * MAX_WIDTH;
      }
      break;
      case 1:
      {
         posX = m_paranoaBus->GetX() + m_paranoaBus->GetRectBox().m_w + 2 * TILE_WIDHT;
      }
      break;
      case 2:
      {
         posX = m_obstacleTree->GetX() + m_obstacleTree->GetRectBox().m_w*0.75;
      }
      break;
      default:
         break;
      }


      std::unique_ptr< FlyingManthis > flyingManthis = std::make_unique< FlyingManthis >( m_mainCharacter.get(), 
                                                                                          posX, 
                                                                                          posY, 
                                                                                          manthisAnimationLeft->GetClip().m_w*0.9, 
                                                                                          manthisAnimationLeft->GetClip().m_h*0.9, 
                                                                                          70 );


      flyingManthis->AddAnimation( FlyingManthis::LEFT, manthisAnimationLeft );
      flyingManthis->AddAnimation( FlyingManthis::RIGHT, manthisAnimationRight );

      flyingManthis->AddAnimation( FlyingManthis::LEFT | FlyingManthis::ATTACK, manthisAnimationAttackLeft );
      flyingManthis->AddAnimation( FlyingManthis::RIGHT | FlyingManthis::ATTACK, manthisAnimationAttackRight );

      flyingManthis->AddAnimation( FlyingManthis::LEFT | FlyingManthis::HURT, manthisAnimationDamageLeft );
      flyingManthis->AddAnimation( FlyingManthis::RIGHT | FlyingManthis::HURT, manthisAnimationDamageRight );

      flyingManthis->AddAnimation( FlyingManthis::LEFT | FlyingManthis::ATTACK | FlyingManthis::HURT, manthisAnimationAttackDamageLeft );
      flyingManthis->AddAnimation( FlyingManthis::RIGHT | FlyingManthis::ATTACK | FlyingManthis::HURT, manthisAnimationAttackDamageRight );


      //m_mainCharacter->AttachObserver( flyingManthis );

      m_enemyPool.push_front( std::move( flyingManthis ) );
   }

   for( int i = 0; i < NUMBER_OF_ROTIFERA; ++i )
   {
      auto rotiferaAnimationUp         = std::make_shared< Animation >( "img/enemy/rotiferaUP_34x56.png", FRAME_TIME, NUMBER_OF_ROTIFERA_SPRITES );
      auto rotiferaAnimationDown       = std::make_shared< Animation >( "img/enemy/rotiferaDOWN_34x56.png", FRAME_TIME, NUMBER_OF_ROTIFERA_SPRITES, true );
      auto rotiferaAnimationDamageUp   = std::make_shared< Animation >( "img/enemy/DAMAGErotiferaUP_34x56.png", FRAME_TIME, NUMBER_OF_ROTIFERA_SPRITES );
      auto rotiferaAnimationDamageDown = std::make_shared< Animation >( "img/enemy/DAMAGErotiferaDOWN_34x56.png", FRAME_TIME, NUMBER_OF_ROTIFERA_SPRITES, true );

      auto posX = 0.0;
      auto posY = BASE_FLOOR + TILE_HEIGHT*1.5;

      switch( i )
      {
      case 0:
         posX = FIRST_GAP + TILE_WIDHT*0.5 - rotiferaAnimationUp->GetClip().m_w*0.5;
         break;
      case 1:
         posX = SECOND_GAP + TILE_WIDHT*0.5 - rotiferaAnimationUp->GetClip().m_w*0.5;
         break;
      default:
         break;
      }

      std::unique_ptr< Rotifera > enemy = std::make_unique < Rotifera >( m_mainCharacter.get(),
                                                                         posX,
                                                                         posY,
                                                                         rotiferaAnimationDown->GetClip().m_w,
                                                                         rotiferaAnimationDown->GetClip().m_h );

      enemy->AddAnimation( Rotifera::UP, rotiferaAnimationUp );
      enemy->AddAnimation( Rotifera::DOWN, rotiferaAnimationDown );
      enemy->AddAnimation( Rotifera::UP | Rotifera::HURT, rotiferaAnimationDamageUp );
      enemy->AddAnimation( Rotifera::DOWN | Rotifera::HURT, rotiferaAnimationDamageDown );

      m_enemyPool.push_front( std::move( enemy ) );
   }

   auto bossLeft  = std::make_shared< Animation >( "img/enemy/Bossentradaeataque1LEFT_140x48.png", FRAME_TIME, 5, true );
   auto bossRight = std::make_shared< Animation >( "img/enemy/Bossentradaeataque1RIGHT_140x48.png", FRAME_TIME, 5 );

   m_boss.swap( std::make_unique< Boss >( m_mainCharacter.get(), 
                                          ( TOTAL_STAGE_WIDTH - FOURTH_SCENARIO_BEGIN ) / 2, 
                                          BASE_FLOOR - bossLeft->GetClip().m_h, 
                                          bossLeft->GetClip().m_w, 
                                          bossLeft->GetClip().m_h ) );
   m_boss->AddAnimation( Boss::LEFT, bossLeft );
   m_boss->AddAnimation( Boss::RIGHT, bossRight );
}
void StageOneState::setupItens()
{
   m_itemSprite = std::make_unique < Sprite >( "img/Vida.png" );

   for( int i = 0; i < NUMBER_OF_ITENS; ++i )
   {
      switch( i )
      {
      case 0:
      {
         m_itemPool.push_front( std::make_unique< Item >( m_itemSprite.get(),
                                                          m_bus->GetX() + m_busSprite->GetWidth() / 2, m_bus->GetY() - m_itemSprite->GetHeight(),
                                                          m_itemSprite->GetWidth(),
                                                          m_itemSprite->GetHeight(),
                                                          20 ) );
      }
      break;
      case 1:
      {
         m_itemPool.push_front( std::make_unique< Item >( m_itemSprite.get(),
                                                          m_phoneCabin->GetX() + m_phoneCabinSprite->GetWidth() / 2,
                                                          m_phoneCabin->GetY() - m_itemSprite->GetHeight(),
                                                          m_itemSprite->GetWidth(),
                                                          m_itemSprite->GetHeight(),
                                                          30 ) );
      }
      break;
      default:
         break;
      }
   }
}
void StageOneState::buildMap()
{

   m_tileSetMult->AddTile( "img/Tiles/01.png" );
   m_tileSetMult->AddTile( "img/Tiles/02.png" );
   m_tileSetMult->AddTile( "img/Tiles/03.png" );
   m_tileSetMult->AddTile( "img/Tiles/04.png" );
   m_tileSetMult->AddTile( "img/Tiles/05.png" );
   m_tileSetMult->AddTile( "img/Tiles/06.png" );
   m_tileSetMult->AddTile( "img/Tiles/07.png" );
   m_tileSetMult->AddTile( "img/Tiles/08.png" );
   m_tileSetMult->AddTile( "img/Tiles/09.png" );
   m_tileSetMult->AddTile( "img/Tiles/10.png" );
   m_tileSetMult->AddTile( "img/Tiles/11.png" );
   m_tileSetMult->AddTile( "img/Tiles/12.png" );
   m_tileSetMult->AddTile( "img/Tiles/13.png" );
   m_tileSetMult->AddTile( "img/Tiles/14.png" );
   m_tileSetMult->AddTile( "img/Tiles/15.png" );
   m_tileSetMult->AddTile( "img/Tiles/16.png" );
   m_tileSetMult->AddTile( "img/Tiles/17.png" );
   m_tileSetMult->AddTile( "img/Tiles/18.png" );
   m_tileSetMult->AddTile( "img/Tiles/19.png" );
   m_tileSetMult->AddTile( "img/Tiles/20.png" );
   m_tileSetMult->AddTile( "img/Tiles/21.png" );
   m_tileSetMult->AddTile( "img/Tiles/22.png" );
   m_tileSetMult->AddTile( "img/Tiles/23.png" );
   m_tileSetMult->AddTile( "img/Tiles/24.png" );
   m_tileSetMult->AddTile( "img/Tiles/25.png" );
   m_tileSetMult->AddTile( "img/Tiles/26.png" );
   m_tileSetMult->AddTile( "img/Tiles/27.png" );
   m_tileSetMult->AddTile( "img/Tiles/28.png" );
   m_tileSetMult->AddTile( "img/Tiles/29.png" );
   m_tileSetMult->AddTile( "img/Tiles/30.png" );
   m_tileSetMult->AddTile( "img/Tiles/31.png" );
   m_tileSetMult->AddTile( "img/Tiles/32.png" );
   m_tileSetMult->AddTile( "img/Tiles/33.png" );
   m_tileSetMult->AddTile( "img/Tiles/34.png" );
   m_tileSetMult->AddTile( "img/Tiles/35.png" );
   m_tileSetMult->AddTile( "img/Tiles/36.png" );
   m_tileSetMult->AddTile( "img/Tiles/37.png" );
   m_tileSetMult->AddTile( "img/Tiles/38.png" );
   m_tileSetMult->AddTile( "img/Tiles/39.png" );
   m_tileSetMult->AddTile( "img/Tiles/40.png" );
   m_tileSetMult->AddTile( "img/Tiles/41.png" );
   m_tileSetMult->AddTile( "img/Tiles/42.png" );
   m_tileSetMult->AddTile( "img/Tiles/43.png" );
   m_tileSetMult->AddTile( "img/Tiles/44.png" ); // Hole 1
   m_tileSetMult->AddTile( "img/Tiles/45.png" ); // Shadow Hole 1
   m_tileSetMult->AddTile( "img/Tiles/46.png" ); // Hole 2
   m_tileSetMult->AddTile( "img/Tiles/47.png" ); // Shadow Hole 2
   m_tileSetMult->AddTile( "img/Tiles/48.png" ); // Hole 3
   m_tileSetMult->AddTile( "img/Tiles/49.png" ); // Shadow Hole 3
   m_tileSetMult->AddTile( "img/Tiles/50.png" ); // Hole 4
   m_tileSetMult->AddTile( "img/Tiles/51.png" ); // Shadow Hole 4
   m_tileSetMult->AddTile( "img/Tiles/52.png" ); // BIG HOLE PT1
   m_tileSetMult->AddTile( "img/Tiles/53.png" ); // BIG HOLE PT1 SHADOW
   m_tileSetMult->AddTile( "img/Tiles/54.png" ); // BIG HOLE PT2
   m_tileSetMult->AddTile( "img/Tiles/55.png" ); // BIG HOLE PT2 SHADOW

   m_tileMap.swap( std::make_unique < TileMap >( "tileMap.txt", m_tileSetMult.get() ) );

   for( unsigned long i = 0; i < SCENARIO_TILE_NUMBER + 1; ++i )
   {
      if( i != INDEX_GAP_1 &&
         i != INDEX_BIG_GAP_1 &&
         i != ( INDEX_BIG_GAP_1 + 1 ) )
      {
         m_tileMap->at( i, 7 ) = rand() % 4;
      }
   }

   for( unsigned long i = SCENARIO_TILE_NUMBER + 1; i < SCENARIO_TILE_NUMBER * 2 + 1; ++i )
   {
      if( i != SCENARIO_TILE_NUMBER + 10 )
      {
         m_tileMap->at( i, 7 ) = 4 + rand() % 4;
      }
   }

   for( unsigned long i = SCENARIO_TILE_NUMBER * 2 + 1; i < SCENARIO_TILE_NUMBER * 3 + 1; ++i )
   {
      if( i != SCENARIO_TILE_NUMBER * 2 + 10 )
         m_tileMap->at( i, 7, 1 ) = 8 + rand() % 4;
   }

   for( unsigned long i = SCENARIO_TILE_NUMBER * 3; i < SCENARIO_TILE_NUMBER * 4; ++i )
   {
      m_tileMap->at( i, 7 ) = 12 + rand() % 4;
   }
}
void StageOneState::CleanUp()
{

   m_shootPool.clear();
   //delete m_shootPool;

   m_enemyPool.clear();
   //delete m_enemyPool;

   m_obstaclePool.clear();
   //delete m_groundPool;

   m_background.clear();

   m_music->Stop();
   m_bossMusic->Stop();
   m_stageTimer.Stop();
}
void StageOneState::setupTileMap()
{
   int entireStageWidth = 4 * SCENARIO_TILE_NUMBER*TILE_WIDHT + 9;

   m_groundPool = {};
   m_tileSetMult = std::make_unique < TileSetMultipleFiles >( TILE_WIDHT, TILE_HEIGHT );
   //m_tileMap = std::make_unique< TileMap( 70, 8, TILE_WIDHT, 1, m_tileSetMult );
   m_groundPool.push_front( std::make_shared< Ground >( 0, BASE_FLOOR, GAP_1, TILE_HEIGHT ) );
   m_groundPool.push_front( std::make_shared< Ground >( GAP_1 + TILE_WIDHT, BASE_FLOOR, BIG_GAP_1 - GAP_1 - TILE_WIDHT, TILE_HEIGHT ) );
   m_groundPool.push_front( std::make_shared< Ground >( BIG_GAP_1 + TILE_WIDHT * 2, BASE_FLOOR, FIRST_GAP - ( BIG_GAP_1 + TILE_WIDHT * 2 ), TILE_HEIGHT ) );
   m_groundPool.push_front( std::make_shared< Ground >( FIRST_GAP + TILE_WIDHT, BASE_FLOOR, SECOND_GAP - ( FIRST_GAP + TILE_WIDHT ), TILE_HEIGHT ) );
   m_groundPool.push_front( std::make_shared< Ground >( SECOND_GAP + TILE_WIDHT, BASE_FLOOR, TOTAL_STAGE_WIDTH - ( SECOND_GAP + TILE_WIDHT ), TILE_HEIGHT ) );

   m_baseGround = m_groundPool.front()->GetY() + 6;

   // TODO: MAYBE GROUND ALSO BECOME A SHARED...
   for( auto& itr : m_groundPool )
   {
      m_obstaclePool.push_front( itr );
   }


   buildMap();
}
void StageOneState::setupBackGround()
{
   m_shipSprite.swap( std::make_shared< Animation >( "img/shipSpriteSheep_128px.png", FRAME_TIME * 2, 10 ) );
   m_horizonSprite.swap( std::make_shared< Animation >( "img/Horizonte_290px_de_altura.png", FRAME_TIME, 1 ) );
   m_cityBackGroundSprite.swap( std::make_shared< Animation >( "img/flower_stage/Background_Cidade_240px_de_altura2.png", FRAME_TIME, 1 ) );
   m_dirtyFilter.swap( std::make_shared< Animation >( "img/dark_atmosphere.png", FRAME_TIME, 1 ) );
   m_savanahsFlowerSprite.swap( std::make_shared< Animation >( "img/flower_stage/teste.png", FRAME_TIME, 1 ) );
   m_cityBackGroundSprite2.swap( std::make_shared< Animation >( "img/tv_tower_stage/Ruinas.png", FRAME_TIME, 1 ) );
   m_tvTowerSprite.swap( std::make_shared< Animation >( "img/tv_tower_stage/TVtower_with_name_that_Alexandre_approves.png", FRAME_TIME, 1 ) );

   // UnB Sprites
   m_transictionSprite.swap( std::make_shared< Animation >( "img/icc_stage/checkPoint1.png", FRAME_TIME, 1 ) );
   m_transictionSprite2.swap( std::make_shared< Animation >( "img/flower_stage/checkPoint2.png", FRAME_TIME, 1 ) );
   m_transictionSprite3.swap( std::make_shared< Animation >( "img/catedral_stage/checkPoint3.png", FRAME_TIME, 1 ) );
   m_unbSprite.swap( std::make_shared< Animation >( "img/icc_stage/ICC_240px_de_altura.png", FRAME_TIME, 1 ) );
   m_museumAndCatedralSprite.swap( std::make_shared< Animation >( "img/catedral_stage/museumAndCatedral240px.png", FRAME_TIME, 1 ) );

   for( int i = 0; i < 9; ++i )
   {
      //m_background.push_back( new Obstacle( m_unbSprite, m_unbSprite->GetWidth()*i, 0, m_unbSprite->GetWidth(), m_unbSprite->GetHeight() ) );
      m_background.push_front( std::make_unique< Obstacle >( m_unbSprite.get(),
                                                             m_unbSprite->GetWidth()*i,
                                                             TILE_HEIGHT,
                                                             m_unbSprite->GetWidth(),
                                                             m_unbSprite->GetHeight() ) );
   }

   m_transiction = std::make_shared< Obstacle >( m_transictionSprite.get(), // Sprite
                                                     SECOND_SCENARIO_BEGIN + TILE_WIDHT, // Position Scenario 36 + Blank 1 + half blank - transiction
                                                     -TILE_HEIGHT,                        // Y Pos
                                                     m_transictionSprite->GetWidth(),    // width
                                                     m_transictionSprite->GetHeight() ); // Height

   m_transiction2 = std::make_shared< Obstacle >( m_transictionSprite2.get(), // Sprite
                                                      THIRD_SCENARIO_BEGIN, // Position Scenario 36 + Blank 1 + half blank - transiction
                                                      TILE_HEIGHT,                        // Y Pos
                                                      m_transictionSprite2->GetWidth(),    // width
                                                      m_transictionSprite2->GetHeight() ); // Height


   m_transiction3 = std::make_shared< Obstacle >( m_transictionSprite3.get(), // Sprite
      FOURTH_SCENARIO_BEGIN, // Position Scenario 36 + Blank 1 + half blank - transiction
      TILE_HEIGHT,                        // Y Pos
      m_transictionSprite3->GetWidth(),    // width
      m_transictionSprite3->GetHeight() ); // Height

      m_cityBackGround2 = std::make_unique< Obstacle >( m_cityBackGroundSprite2.get(), m_transiction3->GetX() + m_transiction2->GetRectBox().m_w / 2, MAX_HEIGHT - 3 * TILE_HEIGHT, m_cityBackGroundSprite2->GetWidth(), m_cityBackGroundSprite2->GetHeight() );
      m_cityBackGround = std::make_unique< Obstacle >( m_cityBackGroundSprite.get(), m_transiction->GetX() + m_transiction->GetRectBox().m_w / 2, TILE_HEIGHT, m_cityBackGroundSprite->GetWidth(), m_cityBackGroundSprite->GetHeight() );
      m_savanahsFlower = std::make_unique< Obstacle >( m_savanahsFlowerSprite.get(), m_transiction->GetX() + m_transictionSprite->GetWidth(), TILE_HEIGHT, m_savanahsFlowerSprite->GetWidth(), m_savanahsFlowerSprite->GetHeight() );
      m_museumAndCatedral = std::make_unique< Obstacle >( m_museumAndCatedralSprite.get(), FOURTH_SCENARIO_BEGIN + TILE_WIDHT*1.5, TILE_HEIGHT, m_museumAndCatedralSprite->GetWidth(), m_museumAndCatedralSprite->GetHeight() );
      m_tvTower = std::make_unique< Obstacle >( m_tvTowerSprite.get(), FOURTH_SCENARIO_BEGIN + TILE_WIDHT*1.5, TILE_HEIGHT, m_tvTowerSprite->GetWidth(), m_tvTowerSprite->GetHeight() );
      m_horizon1 = std::make_unique< Obstacle >( m_horizonSprite.get(), 0, 0, m_horizonSprite->GetWidth(), m_horizonSprite->GetWidth() );
      m_horizon2 = std::make_unique< Obstacle >( m_horizonSprite.get(), m_horizon1->GetX() + m_horizonSprite->GetWidth(), 0, m_horizonSprite->GetWidth(), m_horizonSprite->GetHeight() );
}

void StageOneState::setupMainCharacter()
{
   m_mainCharToTheRight.swap( std::make_shared< Animation >( "img/Sprites_W3L2N_andando_direita.png", FRAME_TIME, 11 ) );
   m_mainCharToTheLeft.swap( std::make_shared< Animation >( "img/Sprites_W3L2N_andando_esquerda.png", FRAME_TIME, 11, true ) );
   m_mainCharChargingRight.swap( std::make_shared< Animation >( "img/Sprites_W3L2N_arma_direita.png", FRAME_TIME, 11 ) );
   m_mainCharChargingLeft.swap( std::make_shared< Animation >( "img/Sprites_W3L2N_arma_esquerda.png", FRAME_TIME, 11, true ) );
   m_mainCharJumpingLeft.swap( std::make_shared< Animation >( "img/esquerda.png", FRAME_TIME, 4, true ) );
   m_mainCharJumpingRight.swap( std::make_shared< Animation >( "img/direita.png", FRAME_TIME, 4 ) );
   m_shootingJumpingLeft.swap( std::make_shared< Animation >( "img/saltos47x53esquerda.png", FRAME_TIME, 5, true ) );
   m_shootingJumpingRight.swap( std::make_shared< Animation >( "img/saltos47x53direita_teste.png", FRAME_TIME, 5 ) );

   m_mainCharDamageToTheRight = std::make_shared< Animation >( "img/Dano/correndodireitadano.png", FRAME_TIME, 11 );
   m_mainCharDamageToTheLeft = std::make_shared< Animation >( "img/Dano/correndoesquerdadano.png", FRAME_TIME, 11, true );
   m_mainCharDamageChargingRight = std::make_shared< Animation >( "img/Dano/correndocomarmadano.png", FRAME_TIME, 11 );
   m_mainCharDamageChargingLeft = std::make_shared< Animation >( "img/Dano/correndocomarmaesquerdadano.png", FRAME_TIME, 11, true );
   m_mainCharDamageJumpingLeft = std::make_shared< Animation >( "img/Dano/saltoesquerdadano.png", FRAME_TIME, 4, true );
   m_mainCharDamageJumpingRight = std::make_shared< Animation >( "img/Dano/saltodireitadano.png", FRAME_TIME, 4 );
   m_shootingDamageJumpingLeft = std::make_shared< Animation >( "img/Dano/saltos47x53esquerdadano.png", FRAME_TIME, 5, true );
   m_shootingDamageJumpingRight = std::make_shared< Animation >( "img/Dano/saltos47x53direitadano.png", FRAME_TIME, 5 );
   m_victoryAnimation = std::make_shared< Animation >( "img/posevitoria47x53.png", FRAME_TIME * 2, 2 );

   m_deathLeft.swap( std::make_shared< Animation >( "img/morrendoesquerda47x53.png", FRAME_TIME * 2, 4 ) );
   m_deathRight.swap( std::make_shared< Animation >( "img/morrendodireita47x53.png", FRAME_TIME * 2, 4, true ) );

   m_mainCharacter.swap( std::make_unique< MainCharacter >( MAX_WIDTH*0.5, -715, m_mainCharToTheLeft->GetClip().m_w*0.9, m_mainCharToTheLeft->GetClip().m_h*0.9, 160 ) );

   m_mainCharacter->AddAnimation( MainCharacter::LEFT, m_mainCharToTheLeft );
   m_mainCharacter->AddAnimation( MainCharacter::RIGHT, m_mainCharToTheRight );
   m_mainCharacter->AddAnimation( MainCharacter::LEFT | MainCharacter::SHOOTING, m_mainCharChargingLeft );
   m_mainCharacter->AddAnimation( MainCharacter::RIGHT | MainCharacter::SHOOTING, m_mainCharChargingRight );
   m_mainCharacter->AddAnimation( MainCharacter::LEFT | MainCharacter::JUMPING, m_mainCharJumpingLeft );
   m_mainCharacter->AddAnimation( MainCharacter::RIGHT | MainCharacter::JUMPING, m_mainCharJumpingRight );
   m_mainCharacter->AddAnimation( MainCharacter::LEFT | MainCharacter::JUMPING | MainCharacter::SHOOTING, m_shootingJumpingLeft );
   m_mainCharacter->AddAnimation( MainCharacter::RIGHT | MainCharacter::JUMPING | MainCharacter::SHOOTING, m_shootingJumpingRight );

   m_mainCharacter->AddAnimation( MainCharacter::LEFT | MainCharacter::HURTED, m_mainCharDamageToTheLeft );
   m_mainCharacter->AddAnimation( MainCharacter::RIGHT | MainCharacter::HURTED, m_mainCharDamageToTheRight );
   m_mainCharacter->AddAnimation( MainCharacter::LEFT | MainCharacter::HURTED | MainCharacter::SHOOTING, m_mainCharDamageChargingLeft );
   m_mainCharacter->AddAnimation( MainCharacter::RIGHT | MainCharacter::HURTED | MainCharacter::SHOOTING, m_mainCharDamageChargingRight );
   m_mainCharacter->AddAnimation( MainCharacter::LEFT | MainCharacter::HURTED | MainCharacter::JUMPING, m_mainCharDamageJumpingLeft );
   m_mainCharacter->AddAnimation( MainCharacter::RIGHT | MainCharacter::HURTED | MainCharacter::JUMPING, m_mainCharDamageJumpingRight );
   m_mainCharacter->AddAnimation( MainCharacter::LEFT | MainCharacter::HURTED | MainCharacter::JUMPING | MainCharacter::SHOOTING, m_shootingDamageJumpingLeft );
   m_mainCharacter->AddAnimation( MainCharacter::RIGHT | MainCharacter::HURTED | MainCharacter::JUMPING | MainCharacter::SHOOTING, m_shootingDamageJumpingRight );

   m_mainCharacter->AddAnimation( MainCharacter::LEFT | MainCharacter::DEATH, m_deathLeft );
   m_mainCharacter->AddAnimation( MainCharacter::RIGHT | MainCharacter::DEATH, m_deathRight );

   m_mainCharacter->AddAnimation( MainCharacter::LEFT | MainCharacter::DEATH | MainCharacter::HURTED, m_deathLeft );
   m_mainCharacter->AddAnimation( MainCharacter::RIGHT | MainCharacter::DEATH | MainCharacter::HURTED, m_deathRight );

   m_mainCharacter->AddAnimation( MainCharacter::VICTORY, m_victoryAnimation );

}

void StageOneState::Pause()
{
   m_pauseTimer.Pause();
   m_stageTimer.Pause();
}

void StageOneState::Resume()
{
   m_pauseTimer.Start();
   m_stageTimer.UnPause();
}

void StageOneState::GainFocus( GameManager * manager )
{
   m_horizon1->Render( 0, 0 );
   m_horizon2->Render( 0, 0 );
   if( m_mainCharacter->GetX() >= SECOND_SCENARIO_BEGIN + 20 &&
      m_mainCharacter->GetX() < m_transiction2->GetX() + m_transictionSprite2->GetWidth()*0.60 )
   {
      m_savanahsFlower->Render( m_cameraX, m_cameraY );
      m_cityBackGround->Render( m_cameraX, m_cameraY );
   }

   if( m_mainCharacter->GetX() >= THIRD_SCENARIO_BEGIN + TILE_WIDHT*1.5 &&
      m_mainCharacter->GetX() < FOURTH_SCENARIO_BEGIN + TILE_WIDHT * 3 )
   {
      m_museumAndCatedral->Render( m_cameraX, m_cameraY );
   }

   if( m_mainCharacter->GetX() > FOURTH_SCENARIO_BEGIN + TILE_WIDHT * 3 )
   {
      //m_hudBoss->Render( MAX_WIDTH - 5, - 5 );
      m_cityBackGround2->Render( m_cameraX, m_cameraY );
      m_tvTower->Render( m_cameraX, m_cameraY );
   }

   for( auto& itr : m_background )
   {
      itr->Render( m_cameraX, m_cameraY );
   }
   m_dirtyFilter->Render( 0, 0 );

   m_tileMap->RenderLayer( 0, m_cameraX, m_cameraY );

   for( auto& obstacle : m_obstaclePool )
   {
      obstacle->Render( m_cameraX, m_cameraY );
   }
   m_ship->Render( m_cameraX, m_cameraY );
   m_mainCharacter->Render( m_cameraX, m_cameraY );

   for( auto& enemy : m_enemyPool )
   {
      enemy->Render( m_cameraX, m_cameraY );
   }

   m_tileMap->RenderLayer( 1, m_cameraX, m_cameraY );

   for( auto& shoot : m_shootPool )
   {
      shoot->Render( m_cameraX, m_cameraY );
   }


   for( auto& shoot : m_enemyShootPool )
   {
       shoot->Render( m_cameraX, m_cameraY );
   }

   if( m_boss != NULL )
   {
      m_boss->Render( m_cameraX, m_cameraY );
   }

   for( auto& item : m_itemPool )
   {
      item->Render( m_cameraX, m_cameraY );
   }
   m_transiction->Render( m_cameraX, m_cameraY );
   m_transiction2->Render( m_cameraX, m_cameraY );
   m_transiction3->Render( m_cameraX, m_cameraY );

   m_hud->Render( HUD_POS_X, HUD_POS_Y );

}

void StageOneState::HandleEvents( GameManager * manager )
{
   InputManager::GetInstance()->Update();
   m_mainCharacter->InputHandle();
   if( InputManager::GetInstance()->IsKeyDown( SDLK_ESCAPE ) )
   {
      manager->ChangeState( MenuState::GetInstance() );
      return;
   }

   if( InputManager::GetInstance()->IsKeyDown( SDLK_RETURN ) ||
      InputManager::GetInstance()->IsJoystickButtonDown( 9 ) )
   {
      if( m_pauseTimer.GetTicks() > 300 )
      {
         manager->PushState( PauseState::GetInstance() );
      }
   }

   if( InputManager::GetInstance()->QuitGame() )
   {
      manager->QuitGame();
   }
}

void StageOneState::checkCollision()
{   
   for( auto& obstacle : m_obstaclePool )
   {
      m_mainCharacter->HandleCollision( ( obstacle.get() ) );
   }

 
   for( auto& enemy : m_enemyPool )
   {
      if( m_mainCharacter->CollidesWithEntity( enemy.get() ) )
      {
         m_mainCharacter->ChangeHitPoints( enemy->GetDamage() );;
         if( m_hurtingTimer.GetTicks() > HURTING_GAP &&
            m_mainCharacter->GetHitPoints() > 0 )
         {
            m_hurtingSound->Play();
            m_hurtingTimer.Start();
         }
      }
   }

   // Shooting collide with enemy
   for( auto& shootItr = m_shootPool.begin();
        shootItr != m_shootPool.end();
        ++shootItr )
   {
      auto& shoot = *shootItr;
      for( auto& enemy : m_enemyPool )
      {
         if( enemy->CollidesWith( shoot.get() ) )
         {
            auto multiplier = 1.0;
            if( enemy->GetWeakness() ==  shoot->GetType() )
            {
               multiplier = 2;
            }

            enemy->ChangeHitPoints( shoot->GetDamage()*multiplier );
            m_shootPool.erase( shootItr );
            break;
         }
      }

      if( m_boss != NULL )
      {
         if( shoot->CollidesWith( m_boss.get() ) )
         {
            m_boss->ChangeHitPoints( shoot->GetDamage() );
            m_shootPool.erase( shootItr );
            break;
         }
      }
   }

   for( auto itr = m_enemyShootPool.begin();
        itr != m_enemyShootPool.end();
        ++itr)
   {
      if( m_mainCharacter->CollidesWith( itr->get() ) )
      {
         m_mainCharacter->ChangeHitPoints( ( *itr )->GetDamage() );
         m_enemyShootPool.erase( itr );
         break;
      }
   }

   for( auto itemItr = m_itemPool.begin();
        itemItr != m_itemPool.end();
        ++itemItr )
   {
      if( m_mainCharacter->CollidesWith( itemItr->get() ) )
      {
         m_gettingLifeSound->Play();
         m_mainCharacter->ChangeHitPoints( -( ( *itemItr )->GetAmmountOfHealth() ) );
         m_itemPool.erase( itemItr );
         break;
      }
   }
}

void StageOneState::Update( GameManager * manager )
{
   //#ifdef RELEASE
   unsigned long dt = m_stageTimer.GetTicks();
   //#else
   //   unsigned long dt = 33;
   //#endif
   static double lastXPos = m_mainCharacter->GetX();

   if( m_mainCharacter->GetY() + m_mainCharacter->GetRectBox().m_h*0.5 < MAX_HEIGHT - TILE_HEIGHT*0.5 )
   {
      m_cameraY = m_mainCharacter->GetY() + m_mainCharacter->GetRectBox().m_h*0.5 - ( MAX_HEIGHT - 70 );
   }
   m_ship->Update( dt );

   if( m_mainCharacter->GetX() > m_unbSprite->GetWidth() - MAX_WIDTH*0.5 &&
      m_mainCharacter->GetX() < TOTAL_STAGE_WIDTH - MAX_WIDTH*0.5 )
   {
      m_cameraX = m_mainCharacter->GetX() + m_mainCharacter->GetRectBox().m_w*0.5 - MAX_WIDTH*0.5;
   }
   m_mainCharacter->Update( dt );
   m_hud->Update( dt );
   if( m_mainCharacter->GetX() > SECOND_SCENARIO_BEGIN )
   {
      m_savanahsFlower->SetX( SECOND_SCENARIO_BEGIN + 3 * TILE_WIDHT + MAX_WIDTH*( m_mainCharacter->GetX() - ( SECOND_SCENARIO_BEGIN + 3 * TILE_HEIGHT ) ) * 7 / ( SCENARIO_TILE_NUMBER * 72 ) );
      m_cityBackGround->SetX( SECOND_SCENARIO_BEGIN + MAX_WIDTH*( m_mainCharacter->GetX() - ( SECOND_SCENARIO_BEGIN + 3 * TILE_HEIGHT ) ) * 5 / ( SCENARIO_TILE_NUMBER * 72 ) );
   }

   if( m_mainCharacter->GetX() > THIRD_SCENARIO_BEGIN )
   {
      m_museumAndCatedral->SetX( THIRD_SCENARIO_BEGIN + TILE_WIDHT + MAX_WIDTH*( m_mainCharacter->GetX() - ( THIRD_SCENARIO_BEGIN + 3 * TILE_HEIGHT ) ) * 5 / ( SCENARIO_TILE_NUMBER * 72 ) );
   }

   if( m_mainCharacter->GetX() > FOURTH_SCENARIO_BEGIN &&
      m_mainCharacter->GetX() < TOTAL_STAGE_WIDTH - MAX_WIDTH*0.5 - m_mainCharacter->GetRectBox().m_w*0.5 )
   {
      static bool firstTime = true;
      if( firstTime )
      {
         m_music->Stop();
         m_bossGrowl->Play();
         m_bossMusic->Play( -1 );
         firstTime = false;
      }
      m_cityBackGround2->SetX( FOURTH_SCENARIO_BEGIN + MAX_WIDTH*( m_mainCharacter->GetX() - ( FOURTH_SCENARIO_BEGIN + 3 * TILE_HEIGHT ) ) * 7 / ( SCENARIO_TILE_NUMBER * 72 ) );
      m_tvTower->SetX( FOURTH_SCENARIO_BEGIN + MAX_WIDTH*( m_mainCharacter->GetX() - ( FOURTH_SCENARIO_BEGIN + 3 * TILE_HEIGHT ) )*7.5 / ( SCENARIO_TILE_NUMBER * 72 ) );
   }

   for( auto& enemyItr = m_enemyPool.begin();
        enemyItr != m_enemyPool.end();
        ++enemyItr )
   {
      if( ( *enemyItr )->GetHitPoints() <= 0 )
      {
         m_enemyPool.erase( enemyItr );
      }
      else
      {
         ( *enemyItr )->Update( dt );
         if( ( *enemyItr )->GetEnemyType() == Enemy::FlyingManthisType )
         {
            FlyingManthis * enemy = static_cast< FlyingManthis * >( enemyItr->get() );
            if( enemy->CreateShoot() )
            {
               createFlyingManthisShoot( enemy, m_mainCharacter->GetX(), m_mainCharacter->GetY() );
            }
         }
      }
   }

   if( m_boss != NULL )
   {
      m_boss->Update( dt );

      if( m_boss->GetHitPoints() <= 0 )
      {
         m_boss.release();
         m_mainCharacter->RAUL();
         m_victoryMusic->Play( 1 );
      }
      else
      {
         if( m_boss->CreateShoot() )
         {
            createBossShoot( m_boss.get(), m_mainCharacter->GetX(), m_mainCharacter->GetY() );
         }
      }
   }


   for( auto& itr = m_shootPool.begin();
        itr != m_shootPool.end();
        ++itr )
   {
      ( *itr )->Update( dt );
      if( ( *itr )->GetX() > ( *itr )->GetStart() + ( *itr )->GetRectBox().m_w * 20 )
      {
         m_shootPool.erase( itr );
      }

      if( itr == m_shootPool.end() )
      {
         break;
      }
   }

   for( auto& itr = m_enemyShootPool.begin();
      itr != m_enemyShootPool.end();
      ++itr )
   {
      ( *itr )->Update( dt );
      if( ( *itr )->HasReachedTarget() )
      {
         m_enemyShootPool.erase( itr );
      }
   }

   short shootForce = m_mainCharacter->CreateShoot();
   if( shootForce != MainCharacter::NOSHOOT )
   {
      createW3L2NShoot( shootForce );
   }
   m_stageTimer.Start();
   checkCollision();


   if( m_mainCharacter->GetHitPoints() <= 0 )
   {
      m_dyingSound->Play();
   }

   if( m_mainCharacter->Finish() )
   {
      manager->ChangeState( CreditsState::GetInstance() );
      return;
   }

   if( m_mainCharacter->Loose() ||
      ( m_mainCharacter->GetY() > BASE_FLOOR + m_mainCharacter->GetRectBox().m_h / 2 ) )
   {
      manager->ChangeState( GameOverState::GetInstance() );
      return;
   }
}

void StageOneState::createFlyingManthisShoot( FlyingManthis * enemy, double targetX, double targetY )
{
   double widthOffSetToShoot;
   double heightOffsetToShoot = enemy->GetY() + enemy->GetRectBox().m_h*0.25;
   auto animationSet = std::make_unique< AnimationSet >( "img/Shoots/Mantisprojectile_spritesheet_15x15.png", FRAME_TIME, NUMBER_OF_SHOOT_COLUMNS, 1 );

   if( enemy->GetDirection() == MainCharacter::RIGHT )
   {
      widthOffSetToShoot = enemy->GetX() + enemy->GetRectBox().m_w;

   }
   else
   {
      widthOffSetToShoot = enemy->GetX();
   }

   m_enemyShootPool.push_back( std::make_unique< FlyingManthisShoot >( animationSet,
      widthOffSetToShoot,
      heightOffsetToShoot,
      SHOT_DAMAGE,
      enemy->GetDirection(),
      targetX,
      targetY ) );
}


void StageOneState::createBossShoot( Boss * enemy, double targetX, double targetY )
{
   double widthOffSetToShoot;
   double heightOffsetToShoot = enemy->GetY() + enemy->GetRectBox().m_h*0.75;
   auto animationSet = std::make_unique < AnimationSet >( "img/Shoots/enemyShootSet.png", FRAME_TIME, NUMBER_OF_SHOOT_COLUMNS, 2 );

   if( enemy->GetDirection() == Boss::RIGHT )
   {
      widthOffSetToShoot = enemy->GetX() + enemy->GetRectBox().m_w;

   }
   else if( enemy->GetDirection() == Boss::LEFT )
   {
      widthOffSetToShoot = enemy->GetX();
   }

   m_enemyShootPool.push_back( std::make_unique< FlyingManthisShoot >( animationSet,
      widthOffSetToShoot,
      heightOffsetToShoot,
      SHOT_DAMAGE,
      enemy->GetDirection(),
      targetX,
      targetY ) );
}

void StageOneState::createW3L2NShoot( short shootForce )
{
   double widthOffSetToShoot;
   double heightOffsetToShoot;
   std::unique_ptr< AnimationSet > shootingAnimation = nullptr;
   double damage = SHOT_DAMAGE;
   switch( m_mainCharacter->ShootType() )
   {
   case MainCharacterShoot::Green:
   {
      if( shootForce == MainCharacter::SIMPLE )
      {
         shootingAnimation = std::make_unique< AnimationSet >( "img/Shoots/greenShootSet.png",
            FRAME_TIME,
            NUMBER_OF_SHOOT_COLUMNS,
            NUMBER_OF_SHOOT_ROWS );
      }
      else if( shootForce == MainCharacter::CHARGED )
      {
         shootingAnimation = std::make_unique< AnimationSet >( "img/Shoots/Charge_3_Alexandre_ta_bom_assim_ponto_de_interrogacao.png",
            FRAME_TIME,
            NUMBER_OF_SHOOT_COLUMNS,
            NUMBER_OF_SHOOT_ROWS );
         damage *= 10;
      }
      m_shooting1Sound->Play();
   }
   break;
   case MainCharacterShoot::Blue:
   {
      if( shootForce == MainCharacter::SIMPLE )
      {
         shootingAnimation = std::make_unique< AnimationSet >( "img/Shoots/ShootSet.png",
            FRAME_TIME,
            NUMBER_OF_SHOOT_COLUMNS,
            NUMBER_OF_SHOOT_ROWS );
      }
      else if( shootForce == MainCharacter::CHARGED )
      {
         shootingAnimation = std::make_unique< AnimationSet >( "img/Shoots/blueChargedShootAnimationSet.png",
                                                               FRAME_TIME,
                                                               NUMBER_OF_SHOOT_COLUMNS,
                                                               NUMBER_OF_SHOOT_ROWS );
         damage *= 10;
      }
      m_shooting2Sound->Play();
   }
   break;
   case MainCharacterShoot::Red:
   {
      if( shootForce == MainCharacter::SIMPLE )
      {
         shootingAnimation = std::make_unique< AnimationSet >( "img/Shoots/redShootSet.png",
                                                               FRAME_TIME,
                                                               NUMBER_OF_SHOOT_COLUMNS,
                                                               NUMBER_OF_SHOOT_ROWS );
      }
      else if( shootForce == MainCharacter::CHARGED )
      {
         shootingAnimation = std::make_unique< AnimationSet >( "img/Shoots/redChargedShootAnimationSetNew.png",
                                                               FRAME_TIME,
                                                               NUMBER_OF_SHOOT_COLUMNS,
                                                               NUMBER_OF_SHOOT_ROWS );
         damage *= 10;
      }
      m_shooting3Sound->Play();
   }
   break;
   default:
      break;
   }
   if( m_mainCharacter->GetDirection() == MainCharacter::RIGHT )
   {
      widthOffSetToShoot = m_mainCharacter->GetRectBox().m_w*( 1.2 );

   }
   else
   {
      widthOffSetToShoot = m_mainCharacter->GetRectBox().m_w*( -0.5 );
      shootingAnimation->RotoZoom( 180 );
   }

   if( m_mainCharacter->GetIsJumping() )
   {
      heightOffsetToShoot = 0.20;
   }
   else
   {
      heightOffsetToShoot = 0.55;
   }

   m_shootPool.push_front( std::make_unique< MainCharacterShoot >( shootingAnimation,
                                                                   m_mainCharacter->GetX() + widthOffSetToShoot,
                                                                   m_mainCharacter->GetY() + m_mainCharacter->GetRectBox().m_h*heightOffsetToShoot,
                                                                   damage,
                                                                   m_mainCharacter->GetDirection(),
                                                                   static_cast< MainCharacterShoot::ShotType >( m_mainCharacter->ShootType() ) ) );

}