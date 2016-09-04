//#include "Square.h"
//
//
//Square::Square( Sprite * sprite, double x, double y ): 
//   Object( sprite, x, y )
//{
//   m_box.x = x;
//   m_box.y = y;
//   m_box.h = sprite->GetHeight();
//   m_box.w = sprite->GetWidth();
//}
//
//
//void Square::Move()
//{
//   m_x = m_box.x += m_velX;
//   m_y = m_box.y += m_velY;
//   
//}
//
//
//void Square::AdjustPosition()
//{
//   m_box.x -= m_velX;
//   m_box.y -= m_velY;
//}