#include <iostream>
#include <thread>

void SingleThread()
{
	std::cout << "Hello World\n" << std::endl;
}

void MultiThread()
{
	std::thread t(SingleThread); 
	t.join(); 
}

int main()
{
	MultiThread();
	//SingleThread();	
}