//#include "Siegfried.h"
//
//Siegfried::Siegfried( Sprite * sprite, float x, float y ) :
//   Object( sprite, x, y ),
//   Width( 64 ),
//   Height( 205 ),
//   m_offset( 0 ),
//   m_frame( 0 ),
//   m_status( RIGHT )
//{
//
//  
//   m_clipsRight[ 0 ].m_x = 98;
//   m_clipsRight[ 0 ].m_y = 456;
//   m_clipsRight[ 0 ].m_w = 32;
//   m_clipsRight[ 0 ].m_h = 36;
//
//   m_clipsRight[ 1 ].m_x = 130;
//   m_clipsRight[ 1 ].m_y = 456;
//   m_clipsRight[ 1 ].m_w = 22;
//   m_clipsRight[ 1 ].m_h = 36;
//
//   m_clipsRight[ 2 ].m_x = 152;
//   m_clipsRight[ 2 ].m_y = 456;
//   m_clipsRight[ 2 ].m_w = 22;
//   m_clipsRight[ 2 ].m_h = 36;
//
//   m_clipsRight[ 3 ].m_x = 174;
//   m_clipsRight[ 3 ].m_y = 456;
//   m_clipsRight[ 3 ].m_w = 33;
//   m_clipsRight[ 3 ].m_h = 36;
//
//   m_clipsRight[ 4 ].m_x = 207;
//   m_clipsRight[ 4 ].m_y = 456;
//   m_clipsRight[ 4 ].m_w = 35;
//   m_clipsRight[ 4 ].m_h = 36;
//
//   m_clipsRight[ 5 ].m_x = m_clipsRight[ 4 ].m_x + m_clipsRight[ 4 ].m_w;
//   m_clipsRight[ 5 ].m_y = 456;
//   m_clipsRight[ 5 ].m_w = 28;
//   m_clipsRight[ 5 ].m_h = 36;
//
//   m_clipsRight[ 6 ].m_x = m_clipsRight[ 5 ].m_x + m_clipsRight[ 5 ].m_w;
//   m_clipsRight[ 6 ].m_y = 456;
//   m_clipsRight[ 6 ].m_w = 24;
//   m_clipsRight[ 6 ].m_h = 36;
//
//   m_clipsRight[ 7 ].m_x = m_clipsRight[ 6 ].m_x + m_clipsRight[ 6 ].m_w;
//   m_clipsRight[ 7 ].m_y = 456;
//   m_clipsRight[ 7 ].m_w = 26;
//   m_clipsRight[ 7 ].m_h = 36;
//
//   m_clipsRight[ 8 ].m_x = m_clipsRight[ 7 ].m_x + m_clipsRight[ 7 ].m_w;
//   m_clipsRight[ 8 ].m_y = 456;
//   m_clipsRight[ 8 ].m_w = 31;
//   m_clipsRight[ 8 ].m_h = 36;
//
//   m_clipsRight[ 9 ].m_x = m_clipsRight[ 8 ].m_x + m_clipsRight[ 8 ].m_w;
//   m_clipsRight[ 9 ].m_y = 456;
//   m_clipsRight[ 9 ].m_w = 35;
//   m_clipsRight[ 9 ].m_h = 36;
//
//   m_clipsRight[ 10 ].m_x = m_clipsRight[ 9 ].m_x + m_clipsRight[ 9 ].m_w;
//   m_clipsRight[ 10 ].m_y = 456;
//   m_clipsRight[ 10 ].m_w = 30;
//   m_clipsRight[ 10 ].m_h = 36;
//   
//
//   m_clipsLeft[ 0 ].m_x = 98;
//   m_clipsLeft[ 0 ].m_y = 456;
//   m_clipsLeft[ 0 ].m_w = 32;
//   m_clipsLeft[ 0 ].m_h = 36;
//
//   m_clipsLeft[ 1 ].m_x = m_clipsLeft[ 0 ].m_x + m_clipsLeft[ 0 ].m_w;
//   m_clipsLeft[ 1 ].m_y = 456;
//   m_clipsLeft[ 1 ].m_w = 22;
//   m_clipsLeft[ 1 ].m_h = 36;
//
//   m_clipsLeft[ 2 ].m_x = m_clipsLeft[ 1 ].m_x + m_clipsLeft[ 1 ].m_w;;
//   m_clipsLeft[ 2 ].m_y = 456;
//   m_clipsLeft[ 2 ].m_w = 22;
//   m_clipsLeft[ 2 ].m_h = 36;
//
//   m_clipsLeft[ 3 ].m_x = m_clipsLeft[ 2 ].m_x + m_clipsLeft[ 2 ].m_w;
//   m_clipsLeft[ 3 ].m_y = 456;
//   m_clipsLeft[ 3 ].m_w = 33;
//   m_clipsLeft[ 3 ].m_h = 36;
//
//   m_clipsLeft[ 4 ].m_x = m_clipsLeft[ 3 ].m_x + m_clipsLeft[ 3 ].m_w;
//   m_clipsLeft[ 4 ].m_y = 456;
//   m_clipsLeft[ 4 ].m_w = 35;
//   m_clipsLeft[ 4 ].m_h = 36;
//
//   m_clipsLeft[ 5 ].m_x = m_clipsLeft[ 4 ].m_x + m_clipsLeft[ 4 ].m_w;
//   m_clipsLeft[ 5 ].m_y = 456;
//   m_clipsLeft[ 5 ].m_w = 28;
//   m_clipsLeft[ 5 ].m_h = 36;
//
//   m_clipsLeft[ 6 ].m_x = m_clipsLeft[ 5 ].m_x + m_clipsLeft[ 5 ].m_w;
//   m_clipsLeft[ 6 ].m_y = 456;
//   m_clipsLeft[ 6 ].m_w = 24;
//   m_clipsLeft[ 6 ].m_h = 36;
//
//   m_clipsLeft[ 7 ].m_x = m_clipsLeft[ 6 ].m_x + m_clipsLeft[ 6 ].m_w;
//   m_clipsLeft[ 7 ].m_y = 456;
//   m_clipsLeft[ 7 ].m_w = 26;
//   m_clipsLeft[ 7 ].m_h = 36;
//
//   m_clipsLeft[ 8 ].m_x = m_clipsLeft[ 7 ].m_x + m_clipsLeft[ 7 ].m_w;
//   m_clipsLeft[ 8 ].m_y = 456;
//   m_clipsLeft[ 8 ].m_w = 31;
//   m_clipsLeft[ 8 ].m_h = 36;
//
//   m_clipsLeft[ 9 ].m_x = m_clipsLeft[ 8 ].m_x + m_clipsLeft[ 8 ].m_w;
//   m_clipsLeft[ 9 ].m_y = 456;
//   m_clipsLeft[ 9 ].m_w = 35;
//   m_clipsLeft[ 9 ].m_h = 36;
//
//   m_clipsLeft[ 10 ].m_x = m_clipsLeft[ 9 ].m_x + m_clipsLeft[ 9 ].m_w;
//   m_clipsLeft[ 10 ].m_y = 456;
//   m_clipsLeft[ 10 ].m_w = 30;
//   m_clipsLeft[ 10 ].m_h = 36;
//
///*      for( int i = 0; i < NUMBER_OF_FRAMES; ++i )
//   {
//      m_clipsLeft[ i ].x = Width*i;
//      m_clipsLeft[ i ].y = Height;
//      m_clipsLeft[ i ].w = Width;
//      m_clipsLeft[ i ].h = Height;
//   }*/
//}
//
//void Siegfried::Render()
//{
//   if( m_velX < 0 )
//   {
//      m_status = LEFT;
//      ++m_frame;
//   }
//   else if( m_velX > 0 )
//   {
//      m_status = RIGHT;
//      ++m_frame;
//   }
//   else
//   {
//      m_frame = 0;
//   }
//
//   if( m_frame >= NUMBER_OF_FRAMES )
//      m_frame = 0;
//
//   if( m_status == RIGHT )
//   {
//      m_sprite->Clip( m_clipsRight[ m_frame ] );
//      m_sprite->Render( m_x, m_y );
//   }
//   else if( m_status == LEFT )
//   {
//      m_sprite->Clip( m_clipsLeft[ m_frame ] );
//      m_sprite->Render( m_x, m_y );
//   }
//}
//
//void Siegfried::Move()
//{
//   m_x += m_velX;
//   m_y += m_velY;
//}
//
//Siegfried::~Siegfried()
//{
//}
