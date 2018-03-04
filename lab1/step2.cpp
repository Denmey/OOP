class A
{
public:
     A() {};
     A(A const& a) = delete; // Works in C++11 and higher
     A& operator=(A const& a) = delete;

private:
     // A(A const& a); // Works in C++03
     // A& operator=(A const& a);
};

int main()
{
     A a, b;
     b = a;
     return 0;
}
