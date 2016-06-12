#include <iostream>
#include "thread_guard.h"

struct func
{
	int& i;
	func(int& i_) : i(i_) {}
	void operator() ()
	{
		std::cout << "线程已经启动了\n" << std::endl;
		for (unsigned j = 0; j < 1000; ++j)
		{
			i = i + j;
			std::cout << i << std::endl;
		}
	}
};

//异步执行线程操作
void oopsdetach()
{
	//构造基础对象
	int some_local_state = 0;
	func my_func(some_local_state);
	//构造线程
	std::thread my_thread(my_func);
	//对my_thread线程进行分离，个人按照异步进行了理解，其实这个时候，线程已经在运行了，不等待线程执行结束
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::cout << "要对子线程进行detach()了\n" << std::endl;
	my_thread.detach();
	//主线程暂停10毫秒，这句暂停可以去掉或者修改时间，去掉之后，由于main函数仅仅调用了这一个函数，会导致程序直接推出，无任何输出
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

//同步执行线程操作
//直接调用jion属于强制等待
void oopsjoin()
{
	//构造基础对象
	int some_local_state = 0;
	func my_func(some_local_state);
	//构造线程
	std::thread my_thread(my_func);
	//对my_thread进行等待，个人理解为同步，主线程等待子线程执行结束
	std::cout << "要对子线程进行join()了\n" << std::endl;
	my_thread.join();
}

//利用线程类对象析构时候，来调用join，阻止直接析构，等待线程执行结束
void oopsthread_guard()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "线程局部变量要被析构了\n" << std::endl;
}

int main()
{
	//oopsdetach();
	//oopsjoin();
	oopsthread_guard();
	std::cout << "主线程运行到最后了" << std::endl;
}