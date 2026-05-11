#pragma once
#include <stdexcept>

// implementacja struktury - Stos
template <typename T>
class Stos {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* topNode; 
    size_t size;

public:
	Stos() { // Konstruktor stosu
        topNode = nullptr;
        size = 0;
    }

	// Destruktor do zwalniania pamięci
    ~Stos() {
        Node* current = topNode;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

	// Dodawanie elementu na stos
    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        size++;
    }

	// Usuwanie elementu ze stosu
    void pop() {
        if (topNode != nullptr) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
            size--;
        }
    }

	// Pobieranie elementu z wierzchu stosu
    T& top() {
        if (topNode == nullptr) throw std::out_of_range("Stos jest pusty");
        return topNode->data;
    }

    void push_back(const T& value) { push(value); }
    size_t getSize() const { return size; }
    void reserve(size_t) {}

	// Operator indeksowania dla stosu (używany tylko dla zapisu w plik i do werefikacji, nie do sortowania)
    T& operator[](size_t index) {
		Node* current = topNode;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
};