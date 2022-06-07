#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <functional>
#include <iostream>

namespace linq {
    namespace impl {

        template<typename T, typename Iter>
        class range_enumerator;

        template<typename T>
        class drop_enumerator;

        template<typename T>
        class take_enumerator;

        template<typename T, typename U, typename F>
        class select_enumerator;

        template<typename T, typename F>
        class until_enumerator;

        template<typename T, typename F>
        class where_enumerator;

        template<typename T>
        class enumerator {
        public:

            virtual T operator*() = 0; // Получает текущий элемент

            virtual void operator++() = 0; // Переход к следующему элементу

            virtual explicit operator bool() = 0; // Возвращает true, если есть текущий элемент

            auto drop(size_t count) {
                return drop_enumerator<T>(*this, count);
            }

            auto take(size_t count) {
                return take_enumerator<T>(*this, count);
            }

            template<typename U = T, typename F>
            auto select(F func) {
                return select_enumerator<U, T, F>(*this, std::move(func));
            }

            template<typename F>
            auto until(F func) {
                return until_enumerator<T, F>(*this, std::move(func));
            }

            auto until_eq(const T &t) {
                return until_enumerator(*this, [&](T x) { return x == t; });
            }

            template<typename F>
            auto where(F func) {
                return where_enumerator(*this, std::move(func));
            }

            auto where_neq(const T& t) {
                return where_enumerator(*this, [&](T x) { return x != t; });
            }

            std::vector<T> to_vector() {
                std::vector<T> v;
                for (; *this; ++(*this)) {
                    v.push_back(**this);
                }
                return v;
            }

            template<typename Iter>
            void copy_to(Iter it) {
                for (; *this; ++(*this), ++it) {
                    *it = **this;
                }
            }
        };

        template<typename T, typename Iter>
        class range_enumerator : public enumerator<T> {
        public:
            range_enumerator(Iter begin, Iter end): begin_(begin), end_(end) {}

            T operator*() override {
                return *begin_;
            }

            void operator++() override {
                begin_++;
            }

            explicit operator bool() override {
                return begin_ != end_;
            }

        private:
            Iter begin_, end_;
        };

        template<typename T>
        class thread_enumerator: public enumerator<T> {
        public:

            explicit thread_enumerator(enumerator<T>& parent): parent_(parent) {}

            T operator*() override {
                return *parent_;
            }

            void operator++() override {
                ++parent_;
            }

            explicit operator bool() override {
                return (bool)parent_;
            }

            enumerator<T>& parent_;
        };

        template<typename T>
        class drop_enumerator : public thread_enumerator<T> {
        public:
            drop_enumerator(enumerator<T>& parent, size_t count): thread_enumerator<T>(parent) {
                while (thread_enumerator<T>::parent_ && count--) {
                    ++thread_enumerator<T>::parent_;
                }
            }
        };

        template<typename T>
        class take_enumerator : public thread_enumerator<T> {
        public:
            take_enumerator(enumerator<T>& parent, size_t count): thread_enumerator<T>(parent), count_(count) {}

            explicit operator bool() override {
                return thread_enumerator<T>::parent_ && (bool)count_;
            }

            void operator++() override {
                count_--;
                ++thread_enumerator<T>::parent_;
            }

        private:
            size_t count_;
        };

        template<typename T, typename U, typename F>
        class select_enumerator : public enumerator<T> {
        public:
            select_enumerator(enumerator<U>& parent, F func) : parent_(parent), func_(std::move(func)), calculated_(false) {}

            T operator*() {
                if (calculated_) {
                    return predicate_;
                }
                calculated_ = true;
                return predicate_ = func_(*parent_);
            }

            void operator++() {
                calculated_ = false;
                ++parent_;
            }

            explicit operator bool() {
                return (bool)parent_;
            }

        private:
            enumerator<U>& parent_;
            F func_;
            bool calculated_;
            T predicate_;
        };

        template<typename T, typename F>
        class predict_enumerator: public thread_enumerator<T> {
        public:
            predict_enumerator(enumerator<T>& parent, F func) :
                    thread_enumerator<T>(parent), func_(std::move(func)), calculated_(false), predicate_(false) {}

            void operator++() override {
                calculated_ = false;
                ++thread_enumerator<T>::parent_;
            }

        protected:
            F func_;
            bool calculated_;
            bool predicate_;

            bool predict() {
                if (calculated_) {
                    return predicate_;
                }
                calculated_ = true;
                return predicate_ = func_(*thread_enumerator<T>::parent_);
            }
        };

        template<typename T, typename F>
        class until_enumerator : public predict_enumerator<T, F> {
        public:
            until_enumerator(enumerator<T> &parent, F predicate_) : predict_enumerator<T, F>(parent, predicate_) {}

            explicit operator bool() override {
                return thread_enumerator<T>::parent_ && !predict_enumerator<T, F>::predict();
            }

        };

        template<typename T, typename F>
        class where_enumerator : public predict_enumerator<T, F> {
        public:
            where_enumerator(enumerator<T> &parent, F predicate_) : predict_enumerator<T, F>(parent, predicate_) {
                move();
            }

            void operator++() override {
                predict_enumerator<T, F>::operator++();
                move();
            }

        private:
            void move() {
                while (thread_enumerator<T>::parent_ && !predict_enumerator<T, F>::predict()) {
                    predict_enumerator<T, F>::operator++();
                }
            }
        };

    } // namespace impl

    template<typename T>
    auto from(T begin, T end) {
        return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
    }

} // namespace linq

#endif
