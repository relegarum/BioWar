#include <iostream>
 
 class BaseClass
 {
 public:
     void Move() const { 
        std::cout << "BaseClass move one step\n"; 
     }
     void Move(int distance) const { 
        std::cout << "BaseClass move " << distance << " steps.\n"; 
     }
 protected:
     int itsAge;
     int itsWeight;
 };
 
 class DerivedClass : public BaseClass
 {
 public:
     void Move()const;
 };
 
 void DerivedClass::Move() const
 {
     std::cout << "In dog move...\n";
     BaseClass::Move(3);
 }
 
 int main()
 {
     BaseClass baseObject;
     DerivedClass derivedObject;
     baseObject.Move(2);
     derivedObject.BaseClass::Move(6);
     return 0;
 }