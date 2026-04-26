#pragma once
#include <cstddef>

template <typename T>
class List {
private:
	struct Node { 
		T data; //pole przechowujace dane
		Node* next;

		Node(const T& value) { //konstruktor wezla
			data = value; 
			next = nullptr;
		}
	};
	Node* head;
	Node* tail;
	size_t size;

public:
	List() { //konstruktor listy
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	~List() { 
		Node* current = head;
		while (current != nullptr) {
			Node* nextNode = current->next; //przechowuje wskaznik na nastepny wezl
			delete current; //usuwa aktualny wezel
			current = nextNode; //przechodzi do nastepnego wezla
		}
	}

	void push_back(const T& value) {
		Node* newNode = new Node(value); //tworzy nowy wezel z podana wartoscia
		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			tail->next = newNode; //ustawia wskaznik next ostatniego wezla na nowy wezel
			tail = newNode; //aktualizuje wskaznik tail na nowy wezel
		}
		size++;
	}

	size_t getSize() const {
		return size;
	}
};