#include <iostream>
#include <thread>
#include <mutex>
#include <random>

class X
{
public:
	int m = 0;
	std::mutex some_mutex;
public:
	void do_lengthy_work(int k)
	{
		//每个线程中弄个随机数，让线程都随机停上几毫秒，打乱运行顺序
		std::random_device rd;
		std::this_thread::sleep_for(std::chrono::milliseconds(rd()%11));

		//然后加锁
		std::lock_guard<std::mutex> guard(some_mutex);
		m++;
		std::cout << "k=" <<k << "\tm=" << m << std::endl;
	}

	void do_another_thing(X& _OtherX, int& k)
	{
		//每个线程中弄个随机数，让线程都随机停上几毫秒，打乱运行顺序
		std::random_device rd;
		std::this_thread::sleep_for(std::chrono::milliseconds(rd() % 11));

		//锁住两个互斥量
		std::lock(_OtherX.some_mutex, some_mutex);
		//创建lock_guard对象，std::adopt_lock表示现成的锁，不创建新锁
		std::lock_guard<std::mutex> lock_a(_OtherX.some_mutex, std::adopt_lock);
		std::lock_guard<std::mutex> lock_b(some_mutex, std::adopt_lock); 
		m = m + 1;
		_OtherX.m = _OtherX.m + k;

		std::cout << "m=" << m << "\t_OtherX.m=" << _OtherX.m << std::endl;
	}
};

//运行结果预测：m的输出应该是顺序的，k的输出是随机的
void oopsMutex()
{
	X myX;
	for (int i = 0; i < 100;++i)
	{
		//循环开上N多的线程，并全部分离
		std::thread t(&X::do_lengthy_work, &myX, i);
		t.detach();
	}

	//主线程等待结束，不然就把myX析构了
	std::this_thread::sleep_for(std::chrono::milliseconds(60000));
}

//同时锁住多个锁
void oopsMoreMutex()
{
	X myX,myY;
	int k = 0;
	std::thread t(&X::do_another_thing, &myX, std::ref(myY), std::ref(k));

	//主线程等待结束，不然就把myX析构了
	std::this_thread::sleep_for(std::chrono::milliseconds(60000));
}

//层次锁的情况

//层级互斥结束
int main()
{
	//好吧，一下开几百个线程，机器不好确实就搞死了。
	//oopsMutex();
	oopsMoreMutex();
}
