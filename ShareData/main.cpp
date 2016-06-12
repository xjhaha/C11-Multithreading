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
		//ÿ���߳���Ū������������̶߳����ͣ�ϼ����룬��������˳��
		std::random_device rd;
		std::this_thread::sleep_for(std::chrono::milliseconds(rd()%11));

		//Ȼ�����
		std::lock_guard<std::mutex> guard(some_mutex);
		m++;
		std::cout << "k=" <<k << "\tm=" << m << std::endl;
	}
};

//���н��Ԥ�⣺m�����Ӧ����˳��ģ�k������������
void oopsMutex()
{
	X myX;
	for (int i = 0; i < 100;++i)
	{
		//ѭ������N����̣߳���ȫ������
		std::thread t(&X::do_lengthy_work, &myX, i);
		t.detach();
	}

	//���̵߳ȴ���������Ȼ�Ͱ�myX������
	std::this_thread::sleep_for(std::chrono::milliseconds(60000));
}

int main()
{
	oopsMutex();
}
