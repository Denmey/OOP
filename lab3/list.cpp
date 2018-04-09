#include <iostream>
#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

namespace stepik
{
  template <class Type>
  struct node
  {
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
      : value(value), next(next), prev(prev)
    {
    }
  };

  template <class Type>
  class list
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;

    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

    ~list()
    {
      // implement this
      node<Type>* p = m_head;
      while (p != m_tail)
      {
        p = p->next;
        delete p->prev;
      }
      delete p;
    }

    list(const list& other)
    {
      // implement this
      node<Type> *ptr = other.m_head;
      if (ptr)
      {
        m_tail = m_head = new node<Type>(ptr->value, nullptr, nullptr);
      }
      for(size_t i = 1; i < other.size(); ++i)
      {
        ptr = ptr->next;
        m_tail->next = new node<Type>(ptr->value, nullptr, m_tail);
        m_tail = m_tail->next;
      }
    }

    list(list&& other)
    {
      // implement this
      m_head = other.m_head;
      m_tail = other.m_tail;
      other.m_head = nullptr;
      other.m_tail = nullptr;
    }

    list& operator= (const list& other)
    {
      // implement this
	 if (this==&other) return *this;
      list tmp{other};
      node<Type> *t1 = m_head;
      node<Type> *t2 = m_tail;
      m_head = tmp.m_head;
      m_tail = tmp.m_tail;
      tmp.m_head = t1;
      tmp.m_tail = t2;
	 return *this;
    }

    void push_back(const value_type& value)
    {
	 // implement this
	 if (m_head == m_tail)
	 {
	   if (m_head == nullptr)
	     m_head = m_tail = new node<Type>(value, nullptr, nullptr);
	   else
	     m_head->next = m_tail = new node<Type>(value, nullptr, m_head);
	 }
	 else
	 {
	   m_tail->next = new node<Type>(value, nullptr, m_tail);
	   m_tail = m_tail->next;
	 }
    }

    void push_front(const value_type& value)
    {
      // implement this
	 if (m_head == m_tail)
	 {
		if (!m_head)
			m_head = m_tail = new node<Type>(value, nullptr, nullptr);
		else
			m_tail->prev = m_head = new node<Type>(value, m_head, nullptr);
	 }
	 else
	 {
		 m_head->prev = new node<Type>(value, m_head, nullptr);
		 m_head = m_head->prev;
	 }
    }

    reference front()
    {
      // implement this
      return m_head->value;
    }

    const_reference front() const
    {
      // implement this
      return m_head->value;
    }

    reference back()
    {
      // implement this
      return m_tail->value;
    }

    const_reference back() const
    {
      // implement this
      return m_tail->value;
    }

    void pop_front()
    {
      // implement this
	 if(m_head==m_tail)
	 {
		 delete m_head;
		 m_head = m_tail = nullptr;
	 }
	 else
	 {
	      m_head = m_head->next;
	      delete m_head->prev;
	      m_head->prev = nullptr;
	 }
    }

    void pop_back()
    {
      // implement this
	 if(m_head==m_tail)
	 {
		 delete m_head;
		 m_head = m_tail = nullptr;
	 }
	 else
	 {
	      m_tail = m_tail->prev;
		 delete m_tail->next;
		 m_tail->next = nullptr;
	 }
    }

    void clear()
    {
      // implement this
      node<Type>* p = m_head;
      while (p != m_tail)
      {
	   p = p->next;
	   delete p->prev;
      }
      delete p;
      m_head = nullptr;
      m_tail = nullptr;
    }

    bool empty() const
    {
      // implement this
      return (!m_head);
    }

    size_t size() const
    {
      // implement this
      if (empty()) return 0;
      node<Type>* p = m_head;
      size_t i = 0;
      while (p != m_tail)
      {
        p=p->next;
        ++i;
      }
      ++i;
      return i;
    }
    void print()
    {
      if (!m_head) return;
      node<Type>* p = m_head;
      while (p != m_tail)
      {
        std::cout << p->value << " ";
        p = p->next;
      }
      std::cout << p->value << std::endl;
    }
  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik

int main()
{
  stepik::list<int> a;
  a.push_back(3);
  a.push_back(5);
  a.push_back(7);
  a.push_front(1);
  std::cout << "After pushing 1, 3, 5, 7 in empty list: " << std::endl;
  a.print();
  std::cout << "It's front: " << a.front() << std::endl;
  std::cout << "It's size: " << a.size() << std::endl;
  stepik::list<int> b{a};
  std::cout << "Copy of this list: ";
  b.print();
  std::cout << "Move copy of first list: ";
  stepik::list<int> c{std::move(a)};
  c.print();
  std::cout << "Size of first list: " << a.size() << std::endl;
  std::cout << "After assignment to first list: ";
  a=b;
  a.print();
  std::cout << "After popping back in first list: ";
  a.pop_back();
  a.print();
  a.clear();
  std::cout << "After clearing list, it's size: " << a.size() << std::endl;
  a.print();
}
