#include <Windows.h>
#include <thread>
#include "fine_grained_queue.h"

using namespace avhw29;

int main()
{
	SetConsoleOutputCP(1251);	// ��� ������ ���������

	auto fgq = new FineGrainedQueue(0);
	// ������� ����� 9 �����
	for (int i = 1; i < 10; i++) std::cout << fgq->insert(i, 10).str() << std::endl;
	
	// ������ � ������������ ������� �������� � ������� �����
	std::thread t1([fgq]() {for (int i = 1; i < 10; i++) std::cout << fgq->remove(i).str() << std::endl; });
	std::thread t2([fgq]() {for (int i = 10; i < 20; i++) std::cout << fgq->insert(i, 20).str() << std::endl; });
	
	t1.join();
	t2.join();
	delete fgq;

	system("Pause");
	return 0;
}