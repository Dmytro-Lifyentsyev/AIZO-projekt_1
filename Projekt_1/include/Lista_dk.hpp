#pragma once

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
	// Operator [] dla Listy Dwukierunkowej - optymalizacja poprzez wybór kierunku przeszukiwania
	T& operator[](size_t index) {
		// Sprawdzamy, czy szybciej będzie iść od początku, czy od końca
		if (index < size / 2) {
			auto* current = head; // zaczynamy od początku
			for (size_t i = 0; i < index; ++i) {
				current = current->next; //przechodzi do nastepnego wezla
			}
			return current->data; //zwraca dane z aktualnego wezla

		}
		else {
			auto* current = tail; //	zaczynamy od końca
			for (size_t i = size - 1; i > index; --i) {
				current = current->prev; //przechodzi do poprzedniego wezla
			}
			return current->data;
		}
	}
};