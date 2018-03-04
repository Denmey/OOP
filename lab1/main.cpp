#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
     // (default) constructor
     Array(const size_t size = 0)
          : m_size(size)
          , m_array(m_size ? new T[m_size]() : nullptr)
     {
          std::cout << "Constructor from " << this << std::endl;
     }

     ~Array()
     {
          std::cout << "Destructor from " << this << std::endl;
          if (m_array) delete [] m_array;
     }

     const size_t size() const
     {
          return m_size;
     }

     T& operator [](const size_t index)
     {
          assert(index < m_size);

          return m_array[index];
     }

     Array(const Array &A)
     {
          std::cout << "Copy constructor from " << this << " with " << &A << " argument" << std::endl;
          // try
          {
               m_size = A.m_size;
               if (m_size)
               {
                    m_array = new T[m_size];
                    std::copy(A.m_array, A.m_array+m_size, m_array);
               }
          }
          // catch(...)
          // {
          //      std::cout << "Got exception in copy constructor from " << this << " with " << &A << " argument" << std::endl;
          //      m_size = 0;
          //      if (m_array)
          //           delete [] m_array;
          //      m_array=nullptr;
          //      throw;
          // }
     }

     Array(Array && A)
     {
          m_size = A.m_size;
          m_array = A.m_array;
          A.m_size = 0;
          A.m_array = nullptr;
     }

     Array &operator=(const Array& A)
     {
          std::cout << "Assignment operator from " << this << " with " << &A << " argument" << std::endl;
          if (this==&A)
               return *this;

          size_t tmp_size;
          T* tmp_array;

          try
          {
               tmp_size = A.m_size;
               if (tmp_size)
               {
                    tmp_array = new T[tmp_size];

                    std::copy(A.m_array, A.m_array+tmp_size, tmp_array);

                    if (m_array) delete [] m_array;
                    m_array = tmp_array;
                    m_size = tmp_size;
               }
          }
          catch(...)
          {
               std::cout << "Got exception in assignment operator from " << this << " with " << &A << " argument" << std::endl;
               if (tmp_array)
                    delete [] tmp_array;
               throw;
          }
          return *this;
     }

private:
     size_t m_size;
     T* m_array;
};

class TestClass
{
public:
     TestClass() = default;
     TestClass(int a)
     {
          test = a;
     }
     TestClass& operator=(const TestClass& A)
     {
          throw 0;
     }
private:
     int test;
};

void print(Array<int>& A)
{
     for (size_t i = 0; i < A.size(); ++i)
          std::cout << A[i] << " ";
     std::cout << std::endl;
}

int main()
{
     Array<int>* ptr;
     // Test for assignment operator:
     {
          std::cout << "Testing assignment operator: " << std::endl;
          Array<int> A(10), B;
          for (size_t i = 0; i < A.size(); ++i)
               A[i]=i;
          B = A;

          print(A);
          print(B); // Should print same lines √

          for (size_t i = 0; i < B.size(); ++i)
               B[B.size()-i-1]=i;

          print(A);
          print(B); // Should print different lines √
          ptr = &B;

          std::cout << "Testing exception: " << std::endl;
          Array<TestClass> Aexc(10), Bexc;
          Bexc = Aexc;

     }
     print(*ptr); // Should print unknown thing

     // Test for copy constructor:
     {
          std::cout << std::endl << "Testing copy constructor: " << std::endl;
          Array<int> A(10);
          for (size_t i = 0; i < A.size(); ++i)
               A[i]=i;
          Array<int> B(A);

          print(A);
          print(B); // Should print same lines √

          for (size_t i = 0; i < B.size(); ++i)
               B[B.size()-i-1]=i;

          print(A);
          print(B); // Should print different lines √
          ptr = &B;

          // How to test exceptions?
     }
     print(*ptr); // Should print unknown thing

     // Test for move constructor:


    std::cout << "Check!" << std::endl;
    return 0;
}
