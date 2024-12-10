#ifndef ARR_H
#define ARR_H

#include <string>
#include <sstream>
using std::ostream, std::string, std::out_of_range;

template <typename T>
class arr {
protected:
    T* data;
    size_t size;
    size_t capacity;

    void realoc(){
        size_t newCapacity;
        if (capacity == 0){
            newCapacity = 1;
        }
        else {
            newCapacity = capacity * 2;
        }
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        if (data) {
            delete[] data;
        }
        data = newData;
        capacity = newCapacity;
    }

public:
    friend class Set;
    friend class hashMap;
    friend struct unoConditionPass;
    arr() : data(nullptr), size(0), capacity(0) {}

    arr(size_t length) : size(length), capacity(length) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = T();
        }
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            realoc(); // Увеличиваем вместимость, если нужно
        }
        data[size++] = value; // Добавляем значение и увеличиваем размер
    }

    [[nodiscard]] size_t get_size() const {
        return size;
    }
    void erase(){
        if (size == 0) {
            throw std::out_of_range("Array is empty");
        }
        --size;
    }

    void del(const size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1]; // Сдвигаем элементы влево
        }
        size--;
    }
    void clear() {
        delete this->data;
        this-> capacity = 0;
        this->size = 0;
        this->realoc();
    }

    void sort(){
        for (size_t i = 0; i < size - 1; ++i) {
            for (size_t j = 0; j < size - 1 - i; ++j) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]); // Меняем местами
                }
            }
        }
    }

    void resize(const size_t newSize) {
        if (newSize > capacity) {
            T* newData = new T[newSize];
            for (size_t i = 0; i < size && i < newSize; ++i) {
                newData[i] = data[i];
            }
            for (size_t i = size; i < newSize; ++i) {
                newData[i] = T();
            }
            delete[] data;
            data = newData;
            capacity = newSize;
        }
        size = newSize;
    }

    size_t find(const T& value) const {
        for (int i = 0; i < this->size; ++i){
            if (this->data[i] == value) return i;
        }
        return -1;
    }

    friend ostream& operator<<(ostream& os, const arr& arr) {
        os << "[";
        for (size_t i = 0; i < arr.size; ++i) {
            os << arr.data[i];
            if (i < arr.size - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

};


arr<string> splitToArr(const string &input, char delimiter = ' ');
arr<string> splitToArr(const string& input, const string& delimiter);
string unsplit(const arr<string>& array, char delimiter = ' ');

#endif // ARR_H
