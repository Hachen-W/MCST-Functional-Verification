#include <iostream>
#include <vector>
#include <cstdint>



class BitVector {
private:
    std::vector<uint64_t> storage;
    size_t bit_size;  // Общая разрядность вектора

public:
    template <typename T>
    BitVector(size_t bits, const T* array) : bit_size(bits) {
        size_t capacity = bits == 0 ? 0 : (bits - 1) / 64 + 1;
        storage.resize(capacity, 0);

        size_t bits_per_element = sizeof(T) * 8;
        for (size_t i = 0; i < bits; ++i) {
            // Проверяем бит в array
            if (((array[i / bits_per_element] >> (i % bits_per_element)) & 1) == 1) {
                // Записываем бит в storage
                storage[i / 64] |= (1ULL << (i % 64));
            }
        }
    }

    size_t size() const {
        return bit_size;
    }

    void set_bit_field(size_t offset, const BitVector& src) {
        for (size_t i = 0; i < src.bit_size; ++i) {
            // Читаем биты src
            if (((src.storage[i / 64] >> (i % 64)) & 1) == 1) {
                // Записываем в текущий вектор с учётом смещения
                storage[(i + offset) / 64] |= (1ULL << ((i + offset) % 64));
            }
        }
    }

    template <typename T>
    void set_bit_field(size_t offset, size_t length, T value) {
        for (size_t i = 0; i < length; ++i) {
            if (((value >> i) & 1) == 1) {
                storage[(i + offset) / 64] |= (1ULL << ((i + offset) % 64));
            }
        }
    }

    bool get_bit(size_t index) const {
        return ((storage[index / 64] >> (index % 64)) & 1) == 1;
    }

    void set_bit(size_t index, bool value) {
        if (value) {
            // Устанавливаем бит в 1
            storage[index / 64] |= (1ULL << (index % 64));
        } else {
            // Сбрасываем бит в 0
            storage[index / 64] &= ~(1ULL << (index % 64));
        }
    }

    template <typename T>
    T get_bit_field_to_integral(size_t offset, size_t length) const {
        T result = 0;
        for (size_t i = 0; i < length; ++i) {
            bool bit = get_bit(offset + i);
            
            // Если бит равен 1, переносим его в result
            if (bit)
                result |= (static_cast<T>(1) << i);
        }
        return result;
    }
};
