#ifndef LAB1_UNIQUE_PTR_HPP
#define LAB1_UNIQUE_PTR_HPP

#include <utility>

namespace kogan {

template <class T>
class UniquePtr {
   private:
    T* ptr_;

   public:
    UniquePtr() noexcept;                   // default constructor
    explicit UniquePtr(T* ptr) noexcept;    // constructor from pointer
    UniquePtr(const UniquePtr&) = delete;   // copy constructor is deleted
    UniquePtr(UniquePtr&& other) noexcept;  // move constructor

    ~UniquePtr();

    UniquePtr<T>& operator=(const UniquePtr<T>&) = delete;   // copy assignment is deleted
    UniquePtr<T>& operator=(UniquePtr<T>&& other) noexcept;  // move assignment
    UniquePtr<T>& operator=(std::nullptr_t) noexcept;        // assignment from nullptr

    T* release() noexcept;                    // release ownership
    void reset(T* ptr = nullptr) noexcept;    // delete old and set new pointer
    void swap(UniquePtr<T>& other) noexcept;  // swaps the managed objects

    T* get() const noexcept;                  // get pointer
    explicit operator bool() const noexcept;  // checks if there is an associated managed object

    T* operator->() const noexcept;  // get pointer and use operator ->
    T& operator*() const noexcept;   // get reference

    friend bool operator==(const UniquePtr<T>& x, const UniquePtr<T>& y) { return x.get() == y.get(); }
    friend bool operator!=(const UniquePtr<T>& x, const UniquePtr<T>& y) { return !(x == y); }
    friend bool operator==(const UniquePtr<T>& x, std::nullptr_t) noexcept { return !x; }
    friend bool operator==(std::nullptr_t, const UniquePtr<T>& x) noexcept { return !x; }
    friend bool operator!=(const UniquePtr<T>& x, std::nullptr_t) noexcept { return (bool)x; }
    friend bool operator!=(std::nullptr_t, const UniquePtr<T>& x) noexcept { return (bool)x; }

    friend void swap(UniquePtr<T>& lhs, UniquePtr<T>& rhs) noexcept { lhs.swap(rhs); }
};

template <class T>
class UniquePtr<T[]> {  // specialization for arrays
   private:
    T* ptr_;

   public:
    UniquePtr() noexcept;
    explicit UniquePtr(T* ptr) noexcept;
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& other) noexcept;

    ~UniquePtr();

    UniquePtr<T[]>& operator=(const UniquePtr<T[]>&) = delete;
    UniquePtr<T[]>& operator=(UniquePtr<T[]>&& other) noexcept;
    UniquePtr<T[]>& operator=(std::nullptr_t) noexcept;

    T* release() noexcept;
    void reset(T* ptr = nullptr) noexcept;
    void swap(UniquePtr<T[]>& other) noexcept;

    T* get() const noexcept;
    explicit operator bool() const noexcept;

    T& operator[](std::size_t index) const;  // array subscript operator

    friend bool operator==(const UniquePtr<T[]>& x, const UniquePtr<T[]>& y) { return x.get() == y.get(); }
    friend bool operator!=(const UniquePtr<T[]>& x, const UniquePtr<T[]>& y) { return !(x == y); }
    friend bool operator==(const UniquePtr<T[]>& x, std::nullptr_t) noexcept { return !x; }
    friend bool operator==(std::nullptr_t, const UniquePtr<T[]>& x) noexcept { return !x; }
    friend bool operator!=(const UniquePtr<T[]>& x, std::nullptr_t) noexcept { return (bool)x; }
    friend bool operator!=(std::nullptr_t, const UniquePtr<T[]>& x) noexcept { return (bool)x; }

    friend void swap(UniquePtr<T[]>& lhs, UniquePtr<T[]>& rhs) noexcept { lhs.swap(rhs); }
};

template <class T, class... Args>
typename std::enable_if<!std::is_array<T>::value, UniquePtr<T>>::type make_unique(
    Args&&... args);  // make_unique for non-array types

template <class T>
typename std::enable_if<std::is_array<T>::value, UniquePtr<T>>::type make_unique(
    std::size_t size);  // make_unique for array types

}  // namespace kogan

#include "UniquePtr.hh"

#endif