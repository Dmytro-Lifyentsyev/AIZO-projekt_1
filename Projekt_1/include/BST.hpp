#pragma once
#include <stdexcept>

// implementacja struktury - Drzewo BST
template <typename T>
class BST {
private:
    struct Node {
        T data;
		Node* left; // Wskaznik na lewe dziecko
		Node* right; // Wskaznik na prawe dziecko
        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t size;

    // Rekurencyjne czyszczenie pamieci
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    // Rekurencyjne wstawianie 
    void insertNode(Node*& node, const T& val) {
		if (node == nullptr) { // Jesli jest puste miejsce, wstawiamy nowy wezel
            node = new Node(val);
        }
		else if (val <= node->data) { // Mniejsze lub rowne idzie na lewo
            insertNode(node->left, val);
        }
		else { // Wieksze idzie na prawo
            insertNode(node->right, val);
        }
    }

    //  Przejscie In-Order (Lewo-Korzen-Prawo)
    void findInOrder(Node* node, size_t targetIndex, size_t& currentIndex, Node*& result) {
        if (node == nullptr || result != nullptr) return;

        // Najpierw idziemy maksymalnie w lewo (do najmniejszych liczb)
        findInOrder(node->left, targetIndex, currentIndex, result);

        if (result == nullptr) {
            // Sprawdzamy obecny wezel
            if (currentIndex == targetIndex) {
                result = node;
                return;
            }
            currentIndex++;
            // Potem idziemy w prawo (do wiekszych)
            findInOrder(node->right, targetIndex, currentIndex, result);
        }
    }

public:
	BST() { // Konstruktor 
        root = nullptr;
        size = 0;
    }

	~BST() {// Destruktor
        destroyTree(root);
    }

    // insert = push_back
    void push_back(const T& value) {
        insertNode(root, value);
        size++;
    }

    size_t getSize() const { return size; }

    void reserve(size_t) { /* Drzewo rosnie dynamicznie, brak rezerwacji */ }

	// Operator indeksowania - zwraca element na podstawie indeksu w porzadku in-order
    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Indeks poza zakresem BST");

        Node* result = nullptr;
        size_t currentIndex = 0;
        findInOrder(root, index, currentIndex, result);
        return result->data;
    }
};