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
		//ÿ���߳���Ū������������̶߳����ͣ�ϼ����룬��������˳��
		std::random_device rd;
		std::this_thread::sleep_for(std::chrono::milliseconds(rd()%11));

		//Ȼ�����
		std::lock_guard<std::mutex> guard(some_mutex);
		m++;
		std::cout << "k=" <<k << "\tm=" << m << std::endl;
	}

	void do_another_thing(X& _OtherX, int& k)
	{
		//ÿ���߳���Ū������������̶߳����ͣ�ϼ����룬��������˳��
		std::random_device rd;
		std::this_thread::sleep_for(std::chrono::milliseconds(rd() % 11));

		//��ס����������
		std::lock(_OtherX.some_mutex, some_mutex);
		//����lock_guard����std::adopt_lock��ʾ�ֳɵ���������������
		std::lock_guard<std::mutex> lock_a(_OtherX.some_mutex, std::adopt_lock);
		std::lock_guard<std::mutex> lock_b(some_mutex, std::adopt_lock); 
		m = m + 1;
		_OtherX.m = _OtherX.m + k;

		std::cout << "m=" << m << "\t_OtherX.m=" << _OtherX.m << std::endl;
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

//ͬʱ��ס�����
void oopsMoreMutex()
{
	X myX,myY;
	int k = 0;
	std::thread t(&X::do_another_thing, &myX, std::ref(myY), std::ref(k));

	//���̵߳ȴ���������Ȼ�Ͱ�myX������
	std::this_thread::sleep_for(std::chrono::milliseconds(60000));
}

//����������

//�㼶�������
int main()
{
	//�ðɣ�һ�¿����ٸ��̣߳���������ȷʵ�͸����ˡ�
	//oopsMutex();
	oopsMoreMutex();
}
