#pragma once

#include <algorithm>

#include "../../../../libs/exception_lib/exceptions/IndexOutOfRangeException/IndexOutOfRangeException.hpp"
#include "../../smart_pointers/SharedPtr/SharedPtr.hpp"

namespace kogan {

template <class T>
class SmartPtrDynamicArray {
   private:
    std::size_t length_;
    SharedPtr<T[]> data_;

   public:
    SmartPtrDynamicArray();
    explicit SmartPtrDynamicArray(int length);
    SmartPtrDynamicArray(SharedPtr<T[]> data, int length);
    SmartPtrDynamicArray(const SmartPtrDynamicArray<T>& other);

    T get(int index) const;
    [[nodiscard]] std::size_t get_length() const noexcept;

    void set(int index, T value);
    void resize(int new_length);

    T& operator[](int index);

    SmartPtrDynamicArray& operator=(const SmartPtrDynamicArray& other) noexcept {
        if (this != &other) {
            length_ = other.length_;
            data_ = make_shared<T[]>(length_);
            for (std::size_t i = 0; i < length_; ++i) set(i, other.get(i));
        }
        return *this;
    }
};

}  // namespace kogan

#include "SmartPtrDynamicArray.tpp"