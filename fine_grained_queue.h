#pragma once
#include <iostream>
#include <sstream>
#include <mutex>
//#include <queue>

namespace avhw29
{
	struct Node
	{
		int value;
		Node* next;
		std::mutex* node_mutex;
	};

	class FineGrainedQueue
	{
	private:
		Node* head;
		std::mutex* queue_mutex;
		void destroy();

	public:
		FineGrainedQueue(int value);
		~FineGrainedQueue();

		std::stringstream remove(int value);
		std::stringstream insert(int value, int pos);
	};
}