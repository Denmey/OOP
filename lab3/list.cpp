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
	class list; //forward declaration

	template <class Type>
	class list_iterator
	{
	public:
		typedef ptrdiff_t difference_type;
		typedef Type value_type;
		typedef Type* pointer;
		typedef Type& reference;
		typedef size_t size_type;
		typedef std::forward_iterator_tag iterator_category;

		list_iterator()
		: m_node(NULL)
		{
		}

		list_iterator(const list_iterator& other)
		: m_node(other.m_node)
		{
		}

		list_iterator& operator = (const list_iterator& other)
		{
		// implement this
			m_node = other.m_node;
			return *this;
		}

		bool operator == (const list_iterator& other) const
		{
		// implement this
			return m_node == other.m_node;
		}

		bool operator != (const list_iterator& other) const
		{
		// implement this
			return m_node != other.m_node;
		}

		reference operator * ()
		{
		// implement this
			return m_node->value;
		}

		pointer operator -> ()
		{
		// implement this
			return &(operator*());
		}

		list_iterator& operator ++ ()
		{
		// implement this
			m_node = m_node->next;
			return *this;
		}

		list_iterator operator ++ (int)
		{
		// implement this
			list_iterator tmp{*this};
			m_node = m_node->next;
			return tmp;
		}

	private:
		friend class list<Type>;

		list_iterator(node<Type>* p)
		: m_node(p)
		{
		}

		node<Type>* m_node;
	};

	template <class Type>
	class list
	{
	public:
		typedef Type value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef list_iterator<Type> iterator;

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

		list::iterator begin()
		{
			return iterator(m_head);
		}

		list::iterator end()
		{
			return iterator();
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

		iterator insert(iterator pos, const Type& value)
		{
			// implement this
			if (pos.m_node == m_head)
			{
				push_front(value);
				return m_head;
			}
			if (!pos.m_node)
			{
				push_back(value);
				return m_tail;
			}
			node<Type>* ptr = new node<Type>(value, pos.m_node, pos.m_node->prev);
			pos.m_node->prev->next = ptr;
			pos.m_node->prev = ptr;
			return ptr;
		}
//TODO
		iterator erase(iterator pos)
		{
			// implement this
			if (pos == m_head)
			{
				pop_front();
				return m_head;
			}
			if (pos == m_tail)
			{
				pop_back();
				return m_tail;
			}
			node<Type>* tmp = pos.m_node;
			pos.m_node = pos.m_node->next;
			pos.m_node->prev = pos.m_node->prev->prev;
			pos.m_node->prev->next = pos.m_node; // ! m_head
			delete tmp;
			return pos;
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
	auto x = a.begin();
	std::cout << "Dereferencing iterator at first element: " << *(x++) << ", second: " << *x << std::endl;
	x = a.begin();
	std::cout << "After assigning iterator to first element: " << *x << std::endl;
	a.clear();
	std::cout << "After clearing list, it's size: " << a.size() << std::endl;
	a.print();
	x = a.insert(a.begin(), 1);
	a.insert(a.begin(), 0);
	std::cout << "After inserting elements '0' and '1': ";
	a.print();
	std::cout << "After inserting element before '1': ";
	a.insert(x, 2);
	a.print();
	std::cout << "After erasing middle element: ";
	a.erase(++a.begin());
	a.print();
}
