#include <iostream>
#include <thread>

void f(int i)
{
	std::cout << i << std::endl;
}

void oopsPara(int some_param)
{
	std::thread t(f, some_param);//����һ��Ĳ�����������Ҫ����ָ��
	t.join();
}

void f2(int & k)
{
	std::cout << k << std::endl;
	k++;
}

void oopsRefPara(int & some_param)
{
	std::thread t(f2, std::ref(some_param)); // �������ò�����ʹ��std::ref�����򣬴��ݵ���һ���������������
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
	X myX;//�������һ��ʵ��
	//��������һ��public���������߳����У��󶨺������󶨶������������
	std::thread t(&X::do_lengthy_work, &myX, std::ref(some_param)); // 2
	t.join();
}

int main()
{
	int k = 1;
	oopsPara(k);
	std::cout << "������֮���Kֵ" << k << std::endl;

	k = 2;
	oopsRefPara(k);
	std::cout << "������֮���Kֵ" << k << std::endl;

	k = 3;
	oopsObject(k);
	std::cout << "������֮���Kֵ" << k << std::endl;
}