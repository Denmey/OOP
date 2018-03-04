#include <iostream>

struct Base
{
     Base()
     {
          std::cout << "Called Base constructor" << std::endl;
     }
     ~Base()
     {
          std::cout << "Called Base destructor" << std::endl;
     }
};

struct Property1
{
     Property1()
     {
          std::cout << "Called Property1 constructor" << std::endl;
     }
     ~Property1()
     {
          std::cout << "Called Property1 destructor" << std::endl;
     }
};

struct Property2
{
     Property2()
     {
          std::cout << "Called Property2 constructor" << std::endl;
     }
     ~Property2()
     {
          std::cout << "Called Property2 destructor" << std::endl;
     }
};

class Derived : public Base
{
     Property1 m_property1;
     Property2 m_property2;
public:
     Derived()
     {
          std::cout << "Called Derived constructor" << std::endl;
     }
     ~Derived()
     {
          std::cout << "Called Derived destructor" << std::endl;
     }
};


int main()
{
     Derived test;
     
     return 0;
}
