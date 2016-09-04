//#ifndef SQUARE_H
//#define SQUARE_H
//
//#include "Object.h"
//#include <list>
//class Square : public Object
//{
//public:
//   Square( Sprite * sprite, double x, double y );
//
//   void Move();
//   void AdjustPosition();
//
//   inline SDL_Rect GetBox(){ return m_box; }
//   inline void SetBox( SDL_Rect &box ) { m_box = box; }
//
//protected:
//   SDL_Rect m_box;
//   std::list< SDL_Rect* > m_visibleObstacles;
//   double   m_velX, m_velY;
//};
//
//#endif