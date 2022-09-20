#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <stdexcept>
#include <cstddef>
#include <bitset>
#include <climits>

namespace lab_13 {

    template<typename T, std::size_t N>
    class my_array {
    public:
        T& at(std::size_t index) {
            if (index >= N) {
                throw std::out_of_range("index out of range");
            }
            return data[index];
        }

        T const & at(std::size_t index) const {
            if (index >= N) {
                throw std::out_of_range("index out of range");
            }
            return data[index];
        }

        T& operator[] (std::size_t index) {
            return data[index];
        }

        T const & operator[] (std::size_t index) const {
            return data[index];
        }

        [[nodiscard]] bool empty() const {
            return N == 0;
        }

        [[nodiscard]] size_t size() const {
            return N;
        }

        void fill(const T& val) {
            for (T* it = data; it - data < N; it++) {
                *it = val;
            }
        }

    private:
        T data[N];
    };

    template<std::size_t N>
    class my_array<bool, N> {
    public:

        class Iterator {
        public:
            Iterator(char& data, size_t index): data(data), index(index) {}

            operator bool() const {return data & mask(1);}

            Iterator& operator=(bool bit) {
                data = (data & ~(data & mask(bit)) | mask(bit));
                return *this;
            }

            Iterator& operator=(Iterator it) {
                std::swap(data, it.data);
                std::swap(index, it.index);
                return *this;
            }

        private:
            [[nodiscard]] char mask(bool bit) const {
                return bit << index;
            }

            char& data;
            size_t index;
        };

        Iterator at(std::size_t index) {
            if (index >= N) {
                throw std::out_of_range("index out of range");
            }
            return Iterator(data[index / CHAR_BIT], index % CHAR_BIT);
        }

        [[nodiscard]] bool at(std::size_t index) const {
            if (index >= N) {
                throw std::out_of_range("index out of range");
            }
            return get(index);
        }

        Iterator operator[] (std::size_t index) {
            return Iterator(data[index / CHAR_BIT], index % CHAR_BIT);
        }

        bool operator[] (std::size_t index) const {
            return get(index);
        }

        [[nodiscard]] bool empty() const {
            return N == 0;
        }

        [[nodiscard]] size_t size() const {
            return N;
        }

        void fill(bool val) {
            for (size_t i = 0; i < N; i++) {
                at(i) = val;
            }
        }

    private:
        [[nodiscard]] bool get(size_t index) const {
            return data[index / CHAR_BIT] & (1 << (index % CHAR_BIT));
        }

        static const size_t M = N ? ((N - 1) / CHAR_BIT + 1) : 0;
        char data[M];
    };

}  // namespace lab_13

#endif  // MY_ARRAY_H_
