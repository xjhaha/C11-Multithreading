#include <iostream>
#include <thread>

void f(int i)
{
	std::cout << i << std::endl;
}

void oopsPara(int some_param)
{
	std::thread t(f, some_param);//传递一般的参数，尽量不要传递指针
	t.join();
}

void f2(int & k)
{
	std::cout << k << std::endl;
	k++;
}

void oopsRefPara(int & some_param)
{
	std::thread t(f2, std::ref(some_param)); // 传递引用参数，使用std::ref，否则，传递的是一个拷贝对象的引用
	t.join();
}

class X
{
public:
	void do_lengthy_work(int& k)
	{
		std::cout << k << std::endl;
		k++;
	}
};

void oopsObject(int & some_param)
{
	X myX;//创建类的一个实例
	//对这个类的一个public函数进行线程运行，绑定函数，绑定对象，再送入参数
	std::thread t(&X::do_lengthy_work, &myX, std::ref(some_param)); // 2
	t.join();
}

int main()
{
	int k = 1;
	oopsPara(k);
	std::cout << "运行完之后的K值" << k << std::endl;

	k = 2;
	oopsRefPara(k);
	std::cout << "运行完之后的K值" << k << std::endl;

	k = 3;
	oopsObject(k);
	std::cout << "运行完之后的K值" << k << std::endl;
}