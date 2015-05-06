#include <iostream>
#include <vector>
#include <functional>
using namespace std;
 
class A {
public:
   A() : m_a(0) {}
   void run1() 
   {
   	m_a++;
   	funcs.push_back([=](){std::cout << "run1 " << m_a << std::endl;});
   	auto f1 = std::bind(A::funk, m_a);
   	funcs.push_back(f1);
   	m_a++;
   }
   void run2() 
   {
   	m_a++;
   	funcs.push_back([&](){std::cout << "run1 " << m_a << std::endl;});
   	funcs.push_back(std::bind(A::funk, m_a));
   	m_a++;
   }
   void run3() 
   {
   	m_a++;
   	funcs.push_back([=](){std::cout << "run1 " << m_a << std::endl;});
   	funcs.push_back(std::bind(A::funk, m_a));
   	m_a++;
   }
   void run4() 
   {
   	for (int s=0;s < funcs.size(); s++)
   	{
   		funcs[s]();
   	}
 
   }
   static void funk(int a) {std::cout  << "funk " << a << std::endl;}
   private:
 
   int m_a;
   std::vector<std::function<void()>> funcs;
};
 
int main() {
	A a;
	a.run1();
	a.run2();
	a.run3();
	a.run4();
	return 0;
}
