#pragma once
#include <thread>

class thread_guard
{
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) :
		t(t_)
	{}
	~thread_guard()
	{
		if (t.joinable())
		{
			t.join();
		}
	}

	//阻止进行拷贝构造
	thread_guard(thread_guard const&) = delete; 
	thread_guard& operator=(thread_guard const&) = delete;
};

