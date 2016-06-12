#include <iostream>
#include "thread_guard.h"

struct func
{
	int& i;
	func(int& i_) : i(i_) {}
	void operator() ()
	{
		std::cout << "�߳��Ѿ�������\n" << std::endl;
		for (unsigned j = 0; j < 1000; ++j)
		{
			i = i + j;
			std::cout << i << std::endl;
		}
	}
};

//�첽ִ���̲߳���
void oopsdetach()
{
	//�����������
	int some_local_state = 0;
	func my_func(some_local_state);
	//�����߳�
	std::thread my_thread(my_func);
	//��my_thread�߳̽��з��룬���˰����첽��������⣬��ʵ���ʱ���߳��Ѿ��������ˣ����ȴ��߳�ִ�н���
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::cout << "Ҫ�����߳̽���detach()��\n" << std::endl;
	my_thread.detach();
	//���߳���ͣ10���룬�����ͣ����ȥ�������޸�ʱ�䣬ȥ��֮������main����������������һ���������ᵼ�³���ֱ���Ƴ������κ����
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

//ͬ��ִ���̲߳���
//ֱ�ӵ���jion����ǿ�Ƶȴ�
void oopsjoin()
{
	//�����������
	int some_local_state = 0;
	func my_func(some_local_state);
	//�����߳�
	std::thread my_thread(my_func);
	//��my_thread���еȴ����������Ϊͬ�������̵߳ȴ����߳�ִ�н���
	std::cout << "Ҫ�����߳̽���join()��\n" << std::endl;
	my_thread.join();
}

//�����߳����������ʱ��������join����ֱֹ���������ȴ��߳�ִ�н���
void oopsthread_guard()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "�ֲ߳̾�����Ҫ��������\n" << std::endl;
}

int main()
{
	//oopsdetach();
	//oopsjoin();
	oopsthread_guard();
	std::cout << "���߳����е������" << std::endl;
}