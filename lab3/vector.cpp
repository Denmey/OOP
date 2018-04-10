#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik
{
  template <typename Type>
  class vector
  {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0)
    {
	    // std::cout << "Called count constructor" << std::endl;
      // implement this
	 Type *tmp = new Type[count];
	 m_first = tmp;
	 m_last = tmp + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
	    // std::cout << "Called iterators constructor" << std::endl;
      // implement this
	 Type *tmp = new Type[last-first];
	 std::copy(first, last, tmp);
	 m_first = tmp;
	 m_last = m_first + (last-first);
    }

    vector(std::initializer_list<Type> init)
    {
	    // std::cout << "Called init_list constructor" << std::endl;
      // implement this
	 Type *tmp = new Type[init.size()];
	 std::copy(init.begin(), init.end(), tmp);
	 m_first = tmp;
	 m_last = tmp + init.size();
    }

    vector(const vector& other) : vector(other.begin(), other.end())
    {
	    // std::cout << "Called copy constructor" << std::endl;
      // implement this
    }

    vector(vector&& other)
    {
      // implement this
	 // std::cout << "Called move constructor" << std::endl;
	 m_first = other.m_first;
	 m_last = other.m_last;
	 other.m_first = nullptr;
	 other.m_last = nullptr;
    }

    ~vector()
    {
	 // std::cout << "Called destructor" << std::endl;
      // implement this
	 delete [] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
      // implement this
	 if (&other == this) return *this;
	 // std::cout << "Called operator=" << std::endl;
	 vector tmp{other};
	 delete [] m_first;
	 m_first = tmp.m_first;
	 m_last = tmp.m_last;
	 tmp.m_first = nullptr;
	 tmp.m_last = nullptr;
	 return *this;
    }

    vector& operator=(vector&& other)
    {
      // implement this
	 if (&other == this) return *this;
	 // std::cout << "Called move operator=" << std::endl;
	 delete [] m_first;
	 m_first = other.m_first;
	 m_last = other.m_last;
	 other.m_first = nullptr;
	 other.m_last = nullptr;
	 return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      // implement this
	 vector tmp{first, last};
	 delete [] m_first;
	 m_first = tmp.m_first;
	 m_last = tmp.m_last;
	 tmp.m_first = nullptr;
	 tmp.m_last = nullptr;
    }

    // resize methods
    void resize(size_t count)
    {
      // implement this
	 Type* tmp = new Type[count];
	 delete [] m_first;
	 m_first = tmp;
	 m_last = tmp + count;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      // implement this
	 return erase(pos, pos+1);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      // implement this
      if (first == m_last) return m_last;
      // assert(first < last);
      // assert((first>=m_first) && (first < m_last));
      // assert((last<=m_last) && (last>m_first));
      size_t diff = last - first ;
      size_t tmp_size = size() - diff;
      size_t ret_pos = first - m_first;
      Type* tmp = new Type[tmp_size];
      for (size_t i = 0; i != ret_pos; ++i)
      {
        tmp[i] = this->at(i);
      }
      for (size_t i = ret_pos+diff; i != size(); ++i)
      {
        tmp[i-diff] = this->at(i);
      }

      delete [] m_first;
      m_first = tmp;
      m_last = tmp + tmp_size;
      tmp = nullptr;
      return m_first + ret_pos;
    }


    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      return insert(pos, &value, 1+&value);
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      // implement this
      size_t in_size = last - first;
      size_t int_pos = pos - m_first;
      size_t new_size = size() + in_size;
      Type* tmp = new Type[new_size];
      for (size_t i = 0; i < int_pos; ++i)
      {
        tmp[i] = this->at(i);
      }
      for (size_t i = int_pos; i < int_pos + in_size; ++i)
      {
        tmp[i] = *(first+i-int_pos);
      }
      for (size_t i = int_pos + in_size; i < new_size; ++i)
      {
        tmp[i] = this->at(i-in_size);
      }
      delete [] m_first;
      m_first = tmp;
      m_last = tmp + new_size;
      return begin() + int_pos;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      // implement this
      size_t new_size = size() + 1;
      Type* tmp = new Type[new_size];
      std::copy(m_first, m_last, tmp);
      tmp[size()] = value;
      delete [] m_first;
      m_first = tmp;
      m_last = tmp + new_size;
    }


    //at methods
    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    //*end methods
    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    //size method
    size_t size() const
    {
      return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
      return m_first == m_last;
    }
    void print()
    {
	    for (auto i : *this)
		    std::cout << i << " ";
	    std::cout << std::endl;
    }
  private:
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik


int main()
{
	{
		stepik::vector<int> a(10);
		for(size_t i = 0; i < a.size(); ++i)
		{
			a.at(i) = i;
		}

		stepik::vector<int> b{a}, c{a.begin(), a.end()};
		std::cout << "First vector: ";
		a.print();
		std::cout << "Second(copy constructor): ";
		b.print();
		std::cout << "Third(constructor with iterators): ";
		c.print();

		stepik::vector<int> d;
		// operator=
		std::cout << "Assignment operator: ";
		d = c;
		d.print();

		// move operator=
		b.at(5) = 6;
		d = std::move(b);
		std::cout << "Move assignment operator: ";
		d.print();
		d.assign(c.begin(), c.begin()+5);
		std::cout << "Assign function: ";
		d.print();
	}
	{
		stepik::vector<int> a(4);
		std::cout << "Resizing vector: ";
		a.resize(10);
		a.print();
		std::cout << "Erasing  first element: ";
		a.erase(a.begin());
		a.print();
	}
  // step3
  {
    std::cout << "Step3" << std::endl;
    stepik::vector<int> a{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    std::cout << "Deleting first 3 elements: " << std::endl;
    a.erase(a.begin(), a.begin()+3);
    a.print();
    std::cout << "Deleting last 3 elements: " << std::endl;
    a.erase(a.end()-3, a.end());
    a.print();
    std::cout << "Deleting 2, 3 elements: " << std::endl;
    a.erase(a.begin()+1, a.begin()+3);
    a.print();
    std::cout << "Pushing back 7:" << std::endl;
    a.push_back(7);
    a.print();
    std::cout << "Inesrting in 2 77:" << std::endl;
    stepik::vector<int>::iterator i = a.insert(a.begin()+1,77);
    a.print();
    std::cout << "Returned: " << *i << std::endl;
    std::cout << "Inserting {1, 2, 3} in (end-1):" << std::endl;
    stepik::vector<int> b{1,2,3};
    a.insert(a.end()-1, b.begin(), b.end());
    a.print();
    std::cout << "Inserting {1, 2, 3} in begin:" << std::endl;
    i = a.insert(a.begin(), b.begin(), b.end());
    a.print();
    std::cout << "Returned: " << *i << std::endl;
    stepik::vector<int> c(0);
    std::cout << "Printing c:" << std::endl;
    c.print();
    std::cout << "Printing c after inserting {1, 2, 3}:" << std::endl;
    i = c.insert(c.end(), b.begin(), b.end());
    c.print();
    std::cout << "Returned: " << *i << std::endl;
  }
	return 0;
}
