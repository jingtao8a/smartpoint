#include <iostream>
#include <cstdlib>
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

class A{
	public:
		mystl::Weak_Ptr<A> pos;
		~A()
		{
			std::cout << "xigou A" << std::endl;
		}
};

void test()
{
	mystl::Shared_Ptr<A> pos1(new A());
	mystl::Shared_Ptr<A> pos2(new A());
	pos1->pos = pos2;
	pos2->pos = pos1;
}

int main()
{
	test();
	std::system("pause");
	return 0;	
}