#include <iostream>
#include <thread>
#include <mutex>
#include <random>

class X
{
private:
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

int main()
{
	oopsMutex();
}
