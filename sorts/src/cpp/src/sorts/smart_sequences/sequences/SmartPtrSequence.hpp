#ifndef LAB1_SMART_PTR_SEQUENCE_HPP
#define LAB1_SMART_PTR_SEQUENCE_HPP

#include <sstream>
#include <string>

#include "../smart_pointers/SharedPtr/SharedPtr.hpp"
#include "../smart_pointers/UniquePtr/UniquePtr.hpp"

namespace kogan {

template <class T>
class SmartPtrSequence {
   public:
    virtual ~SmartPtrSequence() = 0;

    virtual T get_first() const = 0;
    virtual T get_last() const = 0;
    virtual T get(int index) const = 0;
    virtual UniquePtr<SmartPtrSequence<T>> get_subsequence(int start_index, int end_index) const = 0;
    [[nodiscard]] virtual size_t get_length() const = 0;

    virtual void set(int index, T item) = 0;
    virtual void append(T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insert(int index, T item) = 0;
    virtual UniquePtr<SmartPtrSequence<T>> concat(SharedPtr<SmartPtrSequence<T>> sequence) const = 0;
    virtual void clear() = 0;
    virtual void remove(int index) = 0;

    virtual T &operator[](int index) = 0;

    [[nodiscard]] std::string to_string() const;

    friend std::ostream &operator<<(std::ostream &os, const SmartPtrSequence<T> &seq) {
        os << seq.to_string();
        return os;
    }
};

template <class T>
SmartPtrSequence<T>::~SmartPtrSequence() = default;

template <class T>
std::string SmartPtrSequence<T>::to_string() const {
    if (get_length() == 0) return "[]";

    std::ostringstream oss;
    oss << "[" << get_first();
    for (int i = 1; i < get_length(); ++i) oss << ", " << get(i);
    oss << "]";

    return oss.str();
}

}  // namespace kogan

#endif