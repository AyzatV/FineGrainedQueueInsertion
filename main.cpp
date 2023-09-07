#include <Windows.h>
#include "fine_grained_queue.h"

using namespace avhw29;

int main()
{
	SetConsoleOutputCP(1251);	// ��� ������ ���������

	auto fgq = new FineGrainedQueue(0);
	// ������� ����� 9 �����
	for (int i = 1; i < 10; i++) std::cout << fgq->insert(i, i).str() << std::endl;
	delete fgq;

	system("Pause");
	return 0;
}