#include <iostream>
#include <iomanip>

const int KEY_SIZE = 8;
const int LEN = 2049;
const int SIZE_OF_MAS = 33;
const int HEX = 16;
const int BIT = 4;
const char ZERO = '0';
const char NINE = '9';
const char A = 'a';
const char F = 'f';
const int MAX_KEY = 0xffff;

template <typename T>
class TVector {
private:
    T* data;
    long long size;
    long long capacity;
public:
    TVector() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }
    TVector(const long long newSize) {
        size = newSize;
        capacity = newSize;
        data = new T[size];
    }
    ~TVector() {
        delete[] data;
    }
    long long Size() const {
        return size;
    }
    T& operator[] (const long long index) {
        return data[index];
    }
    void Add(const T& elem) {
        if (capacity == 0) {
            capacity = 1;
            data = new T[capacity];
        }
        if (size == capacity) {
            capacity *= 2;
            T* newData = new T[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size] = elem;
        ++size;
    }
};
struct TTypeToSort {
    int key[KEY_SIZE];
    char value[LEN];
};
void RadixSort (TVector<TTypeToSort> &vector) {
    TVector<long long> count(MAX_KEY + 1);
    for (int i = KEY_SIZE - 1; i >= 0; --i) {
        long long size = vector.Size();
        for (int j = 0; j <= MAX_KEY; ++j) {
            count[j] = 0;
        }
        for (long long j = 0; j < size; ++j) {
            ++count[vector[j].key[i]];
        }
        for (int j = 1; j <= MAX_KEY; ++j) {
            count[j] += count[j - 1];
        }
        TVector<TTypeToSort> result(size);
        for (long long j = size - 1; j >= 0; --j) {
            result[count[vector[j].key[i]] - 1] = vector[j];
            --count[vector[j].key[i]];
        }
        for (long long j = 0; j < size; ++j) {
            vector[j] = result[j];
        }
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    TVector<TTypeToSort> vector;
    TTypeToSort current;
    char mas[SIZE_OF_MAS];
    while (std::cin >> mas >> current.value) {
        for (int i = 0; i < KEY_SIZE; i++) {
            int hex = 1;
            current.key[i] = 0;
            for (int j = BIT - 1; j >= 0; --j) {
                if ((mas[i * BIT + j] >= ZERO) && (mas[i * BIT + j] <= NINE)) {
                    current.key[i] += (mas[i * BIT + j] - ZERO) * hex;
                }
                if ((mas[i * BIT + j] >= A) && (mas[i * BIT + j] <= F)) {
                    current.key[i] += (mas[i * BIT + j] - A + 10) * hex;
                }
                hex *= HEX;
            }
        }
        vector.Add(current);
    }
    long long size = vector.Size();
    RadixSort(vector);
    for (long long i = 0; i < size; ++i) {
        for (int j = 0; j < KEY_SIZE; ++j) {
            std::cout << std::hex << std::setw(BIT) << std::setfill(ZERO) << vector[i].key[j];
        }
        std::cout << ' ' << vector[i].value << '\n';
    }
}
