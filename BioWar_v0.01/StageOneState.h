#pragma once
#include "GameState.h"
#include "Square.h"
#include "MainCharacter.h"
#include "TileSetSingleFile.h"
#include "TileSetMultipleFiles.h"
#include "TileMap.h"
#include "Ground.h"
#include "Music.h"
#include "Sound.h"
#include "Nembrotha.h"
#include "FlyingManthis.h"
#include "Rotifera.h"
#include "Obstacle.h"
#include "HUD.h"
#include "Item.h"
#include "Shoot.h"
#include "MainCharacterShoot.h"
#include "FlyingManthisShoot.h"
#include "Boss.h"
#include <list>

#define TILE_WIDHT  72
#define TILE_HEIGHT 36
#define SCENARIO_TILE_NUMBER 36
#define SCROLL      3.5f
#define NUMBER_OF_STAGE_TILES 35
#define NUMBER_OF_NEMBROS 4
#define NUMBER_OF_NEMBRO_SPRITES 12
#define NUMBER_OF_ROTIFERA 2
#define NUMBER_OF_ROTIFERA_SPRITES 4
#define NUMBER_OF_FLYING_MANTHIS 3
#define NUMBER_OF_FLYING_MANTHIS_SPRITES 4
#define FRAME_TIME 60
#define NUMBER_OF_SHOOT_COLUMNS 4
#define NUMBER_OF_SHOOT_ROWS 2
#define NUMBER_OF_ITENS 2
#define HURTING_GAP 200
#define SHOT_DAMAGE 5
#define HUD_POS_X 5
#define HUD_POS_Y -5

#define FIRST_SCENARIO_BEGIN  0
#define SECOND_SCENARIO_BEGIN FIRST_SCENARIO_BEGIN  + SCENARIO_TILE_NUMBER*TILE_WIDHT
#define THIRD_SCENARIO_BEGIN  SECOND_SCENARIO_BEGIN + SCENARIO_TILE_NUMBER*TILE_WIDHT
#define FOURTH_SCENARIO_BEGIN THIRD_SCENARIO_BEGIN  + SCENARIO_TILE_NUMBER*TILE_WIDHT

#define FIRST_GAP SECOND_SCENARIO_BEGIN + 10*TILE_WIDHT
#define SECOND_GAP THIRD_SCENARIO_BEGIN + 10*TILE_WIDHT

#define INDEX_GAP_1 22
#define INDEX_BIG_GAP_1 (INDEX_GAP_1 + 7)

#define GAP_1 INDEX_GAP_1*TILE_WIDHT
#define BIG_GAP_1 INDEX_BIG_GAP_1*TILE_WIDHT



#define BASE_FLOOR MAX_HEIGHT  +7
#define TOTAL_STAGE_WIDTH 4*SCENARIO_TILE_NUMBER*TILE_WIDHT
class StageOneState : public GameState
{
public:
   void Init();
   void CleanUp();

   void Pause();
   void Resume();


   void GainFocus( GameManager * manager );
   void HandleEvents( GameManager * manager );
   void Update( GameManager * manager );

   static StageOneState * GetInstance();

protected:
   StageOneState() {};
   void checkCollision();
   void buildMap();

   void setupEnemies();
   void setupMainCharacter();
   void setupBackGround();
   void setupTileMap();
   void setupHud();
   void setupObstacle();
   void setupItens();

   void createFlyingManthisShoot( FlyingManthis * enemy, double targetX, double targetY );
   void createBossShoot( Boss * enemy, double targetX, double targetY );
   void createW3L2NShoot( short shootForce );

   static StageOneState m_instance;

   double m_cameraX;
   double m_cameraY;
   double m_cameraSpeedX;
   double m_cameraSpeedY;

   int    m_baseGround;

   //AnimationSet * m_mainCharacterAnimation;
   std::shared_ptr< Animation > m_mainCharToTheRight;
   std::shared_ptr< Animation > m_mainCharToTheLeft;
   std::shared_ptr< Animation > m_mainCharJumpingRight;
   std::shared_ptr< Animation > m_mainCharJumpingLeft;
   std::shared_ptr< Animation > m_mainCharChargingRight;
   std::shared_ptr< Animation > m_mainCharChargingLeft;
   std::shared_ptr< AnimationSet > m_shootingAnimationRight;
   std::shared_ptr< AnimationSet > m_shootingAnimationLeft;
   std::shared_ptr< Animation > m_shootingJumpingLeft;
   std::shared_ptr< Animation > m_shootingJumpingRight;
   std::shared_ptr< Animation > m_mainCharDamageToTheRight;
   std::shared_ptr< Animation > m_mainCharDamageToTheLeft;
   std::shared_ptr< Animation > m_mainCharDamageChargingRight;
   std::shared_ptr< Animation > m_mainCharDamageChargingLeft;
   std::shared_ptr< Animation > m_mainCharDamageJumpingLeft;
   std::shared_ptr< Animation > m_mainCharDamageJumpingRight;
   std::shared_ptr< Animation > m_shootingDamageJumpingLeft;
   std::shared_ptr< Animation > m_shootingDamageJumpingRight;
   std::shared_ptr< Animation > m_victoryAnimation;

   std::shared_ptr< Animation > m_deathLeft;
   std::shared_ptr< Animation > m_deathRight;

   std::unique_ptr< MainCharacter > m_mainCharacter;
   std::shared_ptr< Animation     > m_lifeBar;

   // Street sprites
   std::shared_ptr< Animation > m_horizonSprite;
   std::shared_ptr< Animation > m_dirtyFilter;
   std::shared_ptr< Animation > m_cityBackGroundSprite;
   std::shared_ptr< Animation > m_savanahsFlowerSprite;
   std::shared_ptr< Animation > m_shipSprite;
   std::shared_ptr< Animation > m_museumAndCatedralSprite;
   std::shared_ptr< Animation > m_cityBackGroundSprite2;
   std::shared_ptr< Animation > m_tvTowerSprite;

   std::shared_ptr< Obstacle > m_cityBackGround2;
   std::shared_ptr< Obstacle > m_tvTower;
   std::shared_ptr< Obstacle > m_museumAndCatedral;
   std::shared_ptr< Obstacle > m_cityBackGround;
   std::shared_ptr< Obstacle > m_savanahsFlower;
   std::shared_ptr< Obstacle > m_ship;

   // UnB Sprites
   std::shared_ptr< Animation > m_transictionSprite;
   std::shared_ptr< Animation > m_transictionSprite2;
   std::shared_ptr< Animation > m_transictionSprite3;
   std::shared_ptr< Animation > m_unbSprite;
   std::shared_ptr< Animation > m_initialRuinSprite;
   std::list< std::shared_ptr< Obstacle > > m_background;

   // Obstacles
   std::shared_ptr< Animation > m_busSprite;
   std::shared_ptr< Animation > m_phoneCabinSprite;
   std::shared_ptr< Animation > m_trashSprite;
   std::shared_ptr< Animation > m_centralRuinSprite;
   std::shared_ptr< Animation > m_leftRuinSprite;
   std::shared_ptr< Animation > m_rightRuinSprite;
   std::shared_ptr< Animation > m_leftRuin2Sprite;
   std::shared_ptr< Animation > m_rightRuin2Sprite;
   
   std::shared_ptr< Animation > m_carSprite;
   std::shared_ptr< Animation > m_obstacleTreeSprite;
   std::shared_ptr< Animation > m_paranoaBusSprite;

   std::shared_ptr< Obstacle > m_car;
   std::shared_ptr< Obstacle > m_paranoaBus;
   std::shared_ptr< Obstacle > m_obstacleTree;

   std::shared_ptr< Obstacle > m_initialRuin;
   std::shared_ptr< Obstacle > m_bus;
   std::shared_ptr< Obstacle > m_phoneCabin;
   std::shared_ptr< Obstacle > m_trash;
   std::shared_ptr< Obstacle > m_trash2;
   std::shared_ptr< Obstacle > m_transiction;
   std::shared_ptr< Obstacle > m_transiction2;
   std::shared_ptr< Obstacle > m_transiction3;
   std::shared_ptr< Obstacle > m_horizon1;
   std::shared_ptr< Obstacle > m_horizon2;
   std::shared_ptr< Obstacle > m_leftRuin;
   std::shared_ptr< Obstacle > m_rightRuin;
   std::shared_ptr< Obstacle > m_leftRuin2;
   std::shared_ptr< Obstacle > m_rightRuin2;
   std::shared_ptr< Obstacle > m_centerRuin;

   std::unique_ptr< Boss > m_boss;

   std::unique_ptr< HUD       > m_hud;
   std::unique_ptr< HUD       > m_hudBoss;
   std::shared_ptr< Animation > m_healthBar;
   std::shared_ptr< Animation > m_healthBarEmpty;
   std::shared_ptr< Animation > m_bossHealthBar;
   std::shared_ptr< Animation > m_bossHealthBarEmpty;
   std::unique_ptr< Sprite    > m_itemSprite;


   std::unique_ptr< Music > m_music;
   std::unique_ptr< Music > m_bossMusic;
   std::unique_ptr< Music > m_victoryMusic;
   std::unique_ptr< Sound > m_shooting1Sound;
   std::unique_ptr< Sound > m_shooting2Sound;
   std::unique_ptr< Sound > m_shooting3Sound;
   std::unique_ptr< Sound > m_hurtingSound;
   std::unique_ptr< Sound > m_gettingLifeSound;
   std::unique_ptr< Sound > m_dyingSound;
   std::unique_ptr< Sound > m_bossGrowl;
   std::unique_ptr< Sound > m_dyingMonsterSound;

   Timer       m_pauseTimer;
   Timer       m_stageTimer;
   Timer       m_hurtingTimer;
   uint16_t    m_lastTime;

   std::unique_ptr< TileSetSingleFile > m_tileSet;
   std::unique_ptr< TileSetMultipleFiles > m_tileSetMult;
   std::unique_ptr< TileMap >   m_tileMap;

   Ground *                  m_base;
   std::list< std::shared_ptr< Ground > >              m_groundPool;
   std::list< std::shared_ptr< GameObject > >          m_obstaclePool;
   std::list< std::unique_ptr< Enemy > >               m_enemyPool; 
   std::list< std::unique_ptr< MainCharacterShoot > >  m_shootPool;
   std::list< std::unique_ptr< FlyingManthisShoot > >  m_enemyShootPool;
   std::list< std::unique_ptr< FlyingManthisShoot > >  m_bossShootPool;
   std::list< std::unique_ptr< Item > >                m_itemPool;
};

