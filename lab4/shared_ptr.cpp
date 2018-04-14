#include <iostream>
#define DEBUG
// #define DEBUG2
#include <memory>
#include <stdexcept>

namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    explicit shared_ptr(T *ptr = nullptr)
    {
	 m_ptr = ptr;
	 m_count = nullptr;
	 if (m_ptr)
	 {
		 #ifdef DEBUG
		 	std::cout << "Constructing new shared " << this << " from ptr " << ptr << std::endl;
		 #endif
		 m_count = new long(1);
		 if (!m_count) throw std::bad_alloc{};
	 }
    }

    ~shared_ptr() noexcept
    {
	 #ifdef DEBUG
	 	std::cout << "Destroying shared_ptr " << this << std::endl;
	 #endif
	 if (m_ptr)
	 {
		 --(*m_count);
		 if ((*m_count) == 0)
		 {
			#ifdef DEBUG
				std::cout << "Counter is zero, deleting owned object " << m_ptr << std::endl;
			#endif
		 	delete m_ptr;
			delete m_count;
		}
	 }
    }

    shared_ptr(const shared_ptr & other) noexcept
    {
	 #ifdef DEBUG
	 	std::cout << "Constructing shared_ptr " << this << " from shared_ptr " << &other << std::endl;
	 #endif
	 m_ptr = other.m_ptr;
	 m_count = other.m_count;
	 if (m_ptr)
		 ++(*m_count);
    }

    shared_ptr& operator=(const shared_ptr & other) noexcept
    {
	 #ifdef DEBUG
	 	std::cout << "Assigning shared ptrs: " << this << " = " << &other << std::endl;
	 #endif
	 if (this == &other) return *this;
	 if (m_ptr)
	 {
		 --(*m_count);
		 if((*m_count)==0)
		 {
			#ifdef DEBUG
 				std::cout << "Counter is zero, deleting owned object " << m_ptr << std::endl;
 			#endif
		 	delete m_ptr;
			delete m_count;
			m_ptr = nullptr;
			m_count = nullptr;
		 }
	 }
	 m_ptr = other.m_ptr;
	 m_count = other.m_count;
	 if (m_ptr)
		 ++(*m_count);
	 return *this;
    }

    explicit operator bool() const noexcept
    {
     #ifdef DEBUG2
     std::cout << "Bool called " << this << std::endl;
     #endif
	 if (m_ptr) return true;
	 return false;
    }

    T* get() const noexcept
    {
     #ifdef DEBUG2
     std::cout << "Get called " << this << std::endl;
     #endif
	 return m_ptr;
    }

    long use_count() const noexcept
    {
     #ifdef DEBUG2
     std::cout << "Count called " << this << std::endl;
     #endif
	 if (!m_count) return 0;
	 return *m_count;
    }

    T& operator*() const noexcept
    {
     #ifdef DEBUG2
     std::cout << "* called " << this << std::endl;
     #endif
	 return *m_ptr;
    }

    T* operator->() const noexcept
    {
     #ifdef DEBUG2
     std::cout << "-> called " << this << std::endl;
     #endif
	 return m_ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
	 #ifdef DEBUG2
	 	std::cout << "Swapping shared ptrs " << this << " and " << &x << std::endl;
	 #endif
	 T *tmp_ptr = m_ptr;
	 long *tmp_count = m_count;
	 m_ptr = x.m_ptr;
	 m_count = x.m_count;
	 x.m_ptr = tmp_ptr;
	 x.m_count = tmp_count;
    }

    void reset(T *ptr = nullptr)
    {
	 #ifdef DEBUG
	 	std::cout << "Resetting shared_ptr " << this << " from " << m_ptr << " to " << ptr << std::endl;
	 #endif
	 if (m_ptr)
	 {
		 --(*m_count);
		 if ((*m_count)==0)
		 {
			#ifdef DEBUG
				std::cout << "Counter is zero, deleting owned object " << m_ptr << std::endl;
			#endif
			delete m_ptr;
			delete m_count;
			m_ptr = nullptr;
			m_count = nullptr;
		}
	 }
	 m_ptr = ptr;
	 m_count = nullptr;
	 if (m_ptr)
	 {
	 	m_count = new long(1);
		if (!m_count) throw std::bad_alloc{};
	 }
    }

  private:
    // data members
    T *m_ptr;
    long *m_count;
  };
} // namespace stepik

int main()
{
	std::cout << "Step1--------------------" << std::endl;
	int* p = new int(3);
	{
		std::cout << "Pointer: " << p << " " << *p << std::endl;
		stepik::shared_ptr<int>* a = new stepik::shared_ptr<int>(p);

		std::cout << "Shared ptr initialized by pointer: " << a->get() << std::endl
				<< "Value: " << **a << std::endl
				<< "Count: " << a->use_count() << std::endl
				<< "Bool: " << bool(*a) << std::endl;
		stepik::shared_ptr<int> b{*a};
		stepik::shared_ptr<int> c;
		std::cout << "Shared ptr initialized by another shared: " << b.get() << std::endl
				<< "Value: " << *b << std::endl
				<< "Count: " << b.use_count() << std::endl
				<< "Bool: " << bool(b) << std::endl;
		std::cout << "Empty shared ptr: " << c.get() << std::endl
				<< "Count: " << c.use_count() << std::endl
				<< "Bool: " << bool(c) << std::endl;
		c = *a;
		std::cout << "After assigning shrd ptr first to empty: " << c.get() << std::endl
				<< "Value: " << *c << std::endl
				<< "Count: " << c.use_count() << std::endl
				<< "Bool: " << bool(c) << std::endl;
		c.reset();
		std::cout << "After resetting shared to nullptr: " << c.get() << std::endl
				// << "Value: " << *c << std::endl
				<< "Count: " << c.use_count() << std::endl
				<< "Bool: " << bool(c) << std::endl;
		a->swap(c);
		std::cout << "After swapping shared ptrs: " << c.get() << std::endl
				<< "Value: " << *c << std::endl
				<< "Count: " << c.use_count() << std::endl
				<< "Bool: " << bool(c) << std::endl;
		// c.~shared_ptr();
		std::cout << "After destroying shared ptr: " << c.get() << std::endl
				// << "Value: " << *c << std::endl
				<< "Count: " << c.use_count() << std::endl
				<< "Bool: " << bool(c) << std::endl;

	}
	std::cout << "Shared ptrs destroyed, pointer: " << p << " " << *p << std::endl;
	return 0;
}
