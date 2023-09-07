#include <Windows.h>
#include "fine_grained_queue.h"

using namespace avhw29;

int main()
{
	SetConsoleOutputCP(1251);	// для вывода кириллицы

	auto fgq = new FineGrainedQueue(0);
	// вставка новых 9 узлов
	for (int i = 1; i < 10; i++) std::cout << fgq->insert(i, i).str() << std::endl;
	delete fgq;

	system("Pause");
	return 0;
}