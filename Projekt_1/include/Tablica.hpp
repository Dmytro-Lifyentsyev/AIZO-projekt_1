#pragma once
// implementacja struktury - Tablica
template <typename T>
class Tablica {
private:
	T* data;  //wskaźnik na dynamiczną tablicę       
	size_t capacity; //aktualna pojemność tablicy
	size_t size;    //aktualna liczba elementów w tablicy

	void resize() { //funkcja do zmiany rozmiaru tablicy
		T* newData = new T[capacity * 2]; 
        for (size_t i = 0; i < size; i++) { 
            newData[i] = data[i];
        }
		delete[] data; 
		data = newData; 
		capacity = capacity * 2; 
    }

public:
	Tablica(size_t initialCapacity = 1) { //konstruktor z domyślną pojemnością
		size = 0; 
		capacity = initialCapacity; 
		data = new T[capacity];
    }
	// Destruktor do zwalniania pamięci
    ~Tablica() {
		delete[] data;
    }
	// Funkcja do rezerwowania określonej pojemności tablicy
    void reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            T* newData = new T[newCapacity]; 
            for (size_t i = 0; i < size; i++) {
                newData[i] = data[i]; 
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }
	// Funkcja do dodawania elementów na koniec tablicy
    void push_back(const T& value) {
        if (size == capacity)
			resize(); 
		data[size] = value; 
		size++; 
    }
	// Funkcja do pobierania aktualnej liczby elementów w tablicy
    size_t getSize() const {
        return size;
    }

	T& operator[](size_t index) { //operator indeksowania do odczytu i zapisu
        return data[index];
    }
};