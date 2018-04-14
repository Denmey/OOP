#include <iostream>
#define DEBUG
#include <memory>
#include <stdexcept>

namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    explicit shared_ptr(T *ptr = 0)
    {
	 m_ptr = ptr;
	 if (m_ptr)
	 {
		 #ifdef DEBUG
		 	std::cout << "Assigning " << ptr << " to new shared_ptr" << std::endl;
		 #endif
		 m_count = new long(1);
		 if (!m_count) throw std::bad_alloc{};
	 }
    }

    ~shared_ptr() noexcept
    {
	 if (m_ptr)
	 {
		 --(*m_count);
		 if ((*m_count) == 0)
		 {
		 	delete m_ptr;
			delete m_count;
		}
	 }
    }

    shared_ptr(const shared_ptr & other) noexcept
    {
	 m_ptr = other.m_ptr;
	 m_count = other.m_count;
	 if (m_ptr)
		 ++(*m_count);
    }

    shared_ptr& operator=(const shared_ptr & other) noexcept
    {
	 if (this == &other) return *this;
	 if (m_ptr)
	 {
		 --(*m_count);
		 if((*m_count)==0)
		 {
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
	 if (m_ptr) return true;
	 return false;
    }

    T* get() const noexcept
    {
	 return m_ptr;
    }

    long use_count() const noexcept
    {
	 if (!m_count) return 0;
	 return *m_count;
    }

    T& operator*() const noexcept
    {
	 return *m_ptr;
    }

    T* operator->() const noexcept
    {
	 return m_ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
	 T *tmp_ptr = m_ptr;
	 long *tmp_count = m_count;
	 m_ptr = x.m_ptr;
	 m_count = x.m_count;
	 x.m_ptr = tmp_ptr;
	 x.m_count = tmp_count;
    }

    void reset(T *ptr = 0)
    {
	 if (m_ptr)
	 {
		 --(*m_count);
		 if ((*m_count)==0)
		 {
			delete m_ptr;
			delete m_count;
			m_ptr = nullptr;
			m_count = nullptr;
		}
	 }
	 m_ptr = ptr;
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
	{
		int* p = new int(3);
		std::cout << "Pointer: " << p << " " << *p << std::endl;
		stepik::shared_ptr<int> a(p);
		stepik::shared_ptr<int> b{a};
		stepik::shared_ptr<int> c;
		std::cout << "Shared ptr initialized by pointer: " << a.get() << std::endl
				<< "Value: " << *a << std::endl
				<< "Count: " << a.use_count;
		std::cout << "Shared ptr initialized by another shared: " << b.get() << std::endl
				<< "Value: " << *b << std::endl
				<< "Count: " << b.use_count;

		b = a;
	}
	std::cout << p << std::endl;
	return 0;
}
