#include <iostream>
#include <utility>
#include "my_vector.hpp"

namespace product {

    class Product {
    public:
        Product(std::string name, int quantity, double price);
        Product(Product const &oth);
        ~Product() = default;

        Product& operator=(Product oth);

        bool operator==(const Product& oth);

        friend std::ostream & operator<<(std::ostream &os, const Product& p);
    private:
        std::string name_;
        int quantity_;
        double price_;
    };

    Product::Product(const Product &oth): Product(oth.name_, oth.quantity_, oth.price_) {}

    Product::Product(std::string name, int quantity, double price): name_(std::move(name)), quantity_(quantity), price_(price) {}

    Product& Product::operator=(Product oth) {
        std::swap(quantity_, oth.quantity_);
        std::swap(price_, oth.price_);
        std::swap(name_, oth.name_);
        return *this;
    }

    bool Product::operator==(const Product& oth) {
        return quantity_ == oth.quantity_ && price_ == oth.price_ && name_ == oth.name_;
    }

    std::ostream & operator<<(std::ostream &os, const Product& p) {
        return os << p.name_ << ' ' << p.quantity_ << ' ' << p.price_;
    }

}  // namespace product

namespace tests {
    template<typename T>
    void test_my_vector(T a, T b) {
        containers::my_vector<T> v;

        v.push_back(a);
        v.push_back(b);
        assert(v.size() == 2);
        assert(v.capacity() == 2);
        assert(v[0] == a);
        assert(v[1] == b);
        assert(!v.empty());

        containers::my_vector<T> u(v);
        assert(u.size() == 2);

        v.pop_back();
        assert(v.size() == 1);
        assert(v[0] == a);

        v.reserve(10);
        assert(v.capacity() == 16);

        v.clear();
        assert(v.size() == 0);
        assert(v.empty());

        std::swap(u[0], u[1]);
        v = u;
        assert(v.size() == 2);
        assert(v[0] == b);
        assert(v[1] == a);
    }

    template<typename T>
    void test_my_vector_default_constructible(T a, T b) {
        test_my_vector<T>(a, b);
        containers::my_vector<T> v(5);
        assert(v.size() == 5);
        assert(v.capacity() == 8);
        v[0] = a;
        assert(v[0] == a);
        v.resize(2);
        assert(v.size() == 2);
        assert(v.capacity() == 8);
    }
}

int main() {
	containers::my_vector<int> v;
	v.push_back(2);
	const int n{3};
	v.push_back(n);
	std::cout << v << std::endl;

    tests::test_my_vector<int>(5, 10);
    tests::test_my_vector<product::Product>(
            product::Product("asdf", 4, 12.0),
            product::Product("qwe", -1, 7.5));
    tests::test_my_vector_default_constructible<int>(0, -1);
    return 0;
}
