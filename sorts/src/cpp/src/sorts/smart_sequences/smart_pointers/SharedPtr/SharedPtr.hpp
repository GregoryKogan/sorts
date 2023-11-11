#pragma once

#include <utility>

#include "../../../../libs/exception_lib/exceptions/EmptyPointerException/EmptyPointerException.hpp"
#include "../ControlBlock/ControlBlock.hpp"
#include "../WeakPtr/WeakPtr.hpp"

namespace kogan {

template <class T>
class SharedPtr {
   private:
    ControlBlock<T>* control_block_;
    void update_reference(ControlBlock<T>* new_control_block);

    friend class WeakPtr<T>;  // to access control_block_

   public:
    SharedPtr() noexcept;                        // default constructor
    explicit SharedPtr(T* ptr) noexcept;         // constructor from pointer
    SharedPtr(const SharedPtr& other) noexcept;  // copy constructor
    SharedPtr(const WeakPtr<T>& other);          // constructor from WeakPtr
    SharedPtr(SharedPtr&& other) noexcept;       // move constructor

    ~SharedPtr();

    SharedPtr<T>& operator=(const SharedPtr<T>& other) noexcept;  // copy assignment
    SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept;       // move assignment
    SharedPtr<T>& operator=(std::nullptr_t) noexcept;             // assignment from nullptr

    void reset(T* ptr = nullptr) noexcept;    // replace the managed object
    void swap(SharedPtr<T>& other) noexcept;  // swaps the managed objects

    T* get() const noexcept;                  // get pointer
    T* operator->() const noexcept;           // get pointer and use operator ->
    T& operator*() const noexcept;            // get reference
    unsigned int use_count() const noexcept;  // get reference counter
    bool unique() const noexcept;             // check if unique
    explicit operator bool() const noexcept;  // check if pointer is not null

    friend bool operator==(const SharedPtr<T>& x, const SharedPtr<T>& y) { return x.get() == y.get(); }
    friend bool operator!=(const SharedPtr<T>& x, const SharedPtr<T>& y) { return !(x == y); }
    friend bool operator==(const SharedPtr<T>& x, std::nullptr_t) noexcept { return !x; }
    friend bool operator==(std::nullptr_t, const SharedPtr<T>& x) noexcept { return !x; }
    friend bool operator!=(const SharedPtr<T>& x, std::nullptr_t) noexcept { return (bool)x; }
    friend bool operator!=(std::nullptr_t, const SharedPtr<T>& x) noexcept { return (bool)x; }

    friend void swap(SharedPtr<T>& lhs, SharedPtr<T>& rhs) noexcept { lhs.swap(rhs); }
};

template <class T>
class SharedPtr<T[]> {  // specialization for arrays
   private:
    ControlBlock<T[]>* control_block_;
    void update_reference(ControlBlock<T[]>* new_control_block);

    friend class WeakPtr<T[]>;

   public:
    SharedPtr() noexcept;
    explicit SharedPtr(T* ptr) noexcept;
    SharedPtr(const SharedPtr& other) noexcept;
    SharedPtr(SharedPtr&& other) noexcept;

    ~SharedPtr();

    SharedPtr<T[]>& operator=(const SharedPtr<T[]>& other) noexcept;
    SharedPtr<T[]>& operator=(SharedPtr<T[]>&& other) noexcept;
    SharedPtr(const WeakPtr<T[]>& other);
    SharedPtr<T[]>& operator=(std::nullptr_t) noexcept;

    void reset(T* ptr = nullptr) noexcept;
    void swap(SharedPtr<T[]>& other) noexcept;

    T* get() const noexcept;
    T& operator[](std::size_t index) const;  // array subscript operator
    unsigned int use_count() const noexcept;
    bool unique() const noexcept;
    explicit operator bool() const noexcept;

    friend bool operator==(const SharedPtr<T[]>& x, const SharedPtr<T[]>& y) { return x.get() == y.get(); }
    friend bool operator!=(const SharedPtr<T[]>& x, const SharedPtr<T[]>& y) { return !(x == y); }
    friend bool operator==(const SharedPtr<T[]>& x, std::nullptr_t) noexcept { return !x; }
    friend bool operator==(std::nullptr_t, const SharedPtr<T[]>& x) noexcept { return !x; }
    friend bool operator!=(const SharedPtr<T[]>& x, std::nullptr_t) noexcept { return (bool)x; }
    friend bool operator!=(std::nullptr_t, const SharedPtr<T[]>& x) noexcept { return (bool)x; }

    friend void swap(SharedPtr<T[]>& lhs, SharedPtr<T[]>& rhs) noexcept { lhs.swap(rhs); }
};

template <class T, class... Args>
typename std::enable_if<!std::is_array<T>::value, SharedPtr<T>>::type make_shared(
    Args&&... args);  // make_shared for non-array types

template <class T>
typename std::enable_if<std::is_array<T>::value, SharedPtr<T>>::type make_shared(
    std::size_t size);  // make_shared for array types

}  // namespace kogan

#include "SharedPtr.tpp"