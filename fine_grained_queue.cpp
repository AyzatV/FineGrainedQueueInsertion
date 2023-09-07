#include "fine_grained_queue.h"

namespace avhw29
{
	FineGrainedQueue::FineGrainedQueue(int value)
	{
		this->head = new Node();
		this->head->value = value;
		this->head->next = nullptr;
		this->head->node_mutex = new std::mutex();
		this->queue_mutex = new std::mutex();
	}

	FineGrainedQueue::~FineGrainedQueue() { destroy(); }

	std::stringstream FineGrainedQueue::remove(int value)
	{
		std::stringstream info;
		Node* prev, * cur;
		
		queue_mutex->lock();
		// здесь должна быть обработка случая пустого списка
		prev = this->head;
		cur = prev->next;
		prev->node_mutex->lock();
		// здесь должна быть обработка случая удаления первого элемента
		queue_mutex->unlock();

		while (cur)
		{
			cur->node_mutex->lock();
			if (cur->value == value)
			{
				prev->next = cur->next;
				prev->node_mutex->unlock();
				cur->node_mutex->unlock();
				delete cur;
				info << "Узел со значением " << value << " удален" << std::endl;
				return info;
			}
			Node* old_prev = prev;
			prev = cur;
			cur = prev->next;
			old_prev->node_mutex->unlock();
		}
		prev->node_mutex->unlock();

		info << "Узел со значением " << value << " не найден" << std::endl;
		return info;
	}

	std::stringstream FineGrainedQueue::insert(int value, int pos)
	{
		std::stringstream info;
		if (pos > 0)
		{
			int act_pos = 0;
			Node* prev, * cur;

			queue_mutex->lock();
			// здесь должна быть обработка случая пустого списка
			prev = this->head;
			cur = prev->next;
			prev->node_mutex->lock();
			// здесь должна быть обработка случая вставки нулевого элемента
			queue_mutex->unlock();

			act_pos++;
			while (cur)
			{
				if (act_pos == pos) break;
				act_pos++;
				Node* old_prev = prev;
				prev = cur;
				prev->node_mutex->lock();
				cur = prev->next;
				old_prev->node_mutex->unlock();
			}
			// вставка нового узла
			Node* new_node = new Node();
			new_node->value = value;
			new_node->next = cur;
			new_node->node_mutex = new std::mutex();
			prev->next = new_node;
			prev->node_mutex->unlock();

			info << "Узел со значением " << value << " вставлен в позицию списка " << act_pos << std::endl;
		}
		else info << "Вставка значения в начало списка не предусмотрена" << std::endl;
		return info;
	}

	void FineGrainedQueue::destroy()
	{
		Node* prev, * cur;
		queue_mutex->lock();
		prev = this->head;
		while (prev)
		// если список не пустой
		{
			cur = prev->next;
			delete prev->node_mutex;
			delete prev;
			prev = cur;
		}
		queue_mutex->unlock();
		delete queue_mutex;
		queue_mutex = nullptr;
	}

}