#pragma once
#include <cstddef>

template <typename T>
class List_dk {
private:
	struct Node {
		T data;
		Node* next;
		Node* prev;

		Node(const T& value) {
			data = value;
			next = nullptr;
			prev = nullptr;
		}
	};
	Node* head;
	Node* tail;
	size_t size;

public:
	List_dk() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	~List_dk() {
		Node* current = head;
		while (current != nullptr) {
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		}
	}

	void push_back(const T& value) {
		Node* newNode = new Node(value);
		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			tail->next = newNode; //ustawia wskaznik next ostatniego wezla na nowy wezel
			newNode->prev = tail; //ustawia wskaznik prev nowego wezla na aktualny tail
			tail = newNode; //aktualizuje wskaznik tail na nowy wezel
		}
		size++;
	}

	size_t getSize() const {
		return size;
	}
};