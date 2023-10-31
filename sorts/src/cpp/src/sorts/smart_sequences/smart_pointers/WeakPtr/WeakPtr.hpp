#ifndef LAB1_WEAK_PTR_DECLARATION_HPP
#define LAB1_WEAK_PTR_DECLARATION_HPP

#include "../ControlBlock/ControlBlock.hpp"

namespace kogan {

template <class T>
class SharedPtr;

template <class T>
class WeakPtr {
   private:
    ControlBlock<T>* control_block_;
    void update_reference(ControlBlock<T>* new_control_block);

    friend class SharedPtr<T>;  // to access control_block_

   public:
    WeakPtr() noexcept;                           // default constructor
    WeakPtr(const WeakPtr& other) noexcept;       // copy constructor
    explicit WeakPtr(const SharedPtr<T>& other) noexcept;  // constructor from SharedPtr
    WeakPtr(WeakPtr&& other) noexcept;            // move constructor

    ~WeakPtr();

    WeakPtr<T>& operator=(const WeakPtr<T>& other) noexcept;    // copy assignment
    WeakPtr<T>& operator=(const SharedPtr<T>& other) noexcept;  // assignment from SharedPtr
    WeakPtr<T>& operator=(WeakPtr<T>&& other) noexcept;         // move assignment
    WeakPtr<T>& operator=(std::nullptr_t) noexcept;             // assignment from nullptr

    void reset() noexcept;                  // release the reference to the managed object
    void swap(WeakPtr<T>& other) noexcept;  // swaps the managed objects

    [[nodiscard]] unsigned int use_count() const noexcept;  // returns the number of SharedPtr objects that manage the object
    [[nodiscard]] bool expired() const noexcept;            // checks whether the referenced object was already deleted
    SharedPtr<T> lock() const noexcept;       // returns a SharedPtr of the managed object

    friend void swap(WeakPtr<T>& lhs, WeakPtr<T>& rhs) noexcept { lhs.swap(rhs); }
};

template <class T>
class WeakPtr<T[]> {  // specialization for arrays
   private:
    ControlBlock<T[]>* control_block_;
    void update_reference(ControlBlock<T[]>* new_control_block);

    friend class SharedPtr<T[]>;

   public:
    WeakPtr() noexcept;
    WeakPtr(const WeakPtr& other) noexcept;
    explicit WeakPtr(const SharedPtr<T[]>& other) noexcept;
    WeakPtr(WeakPtr&& other) noexcept;

    ~WeakPtr();

    WeakPtr<T[]>& operator=(const WeakPtr<T[]>& other) noexcept;
    WeakPtr<T[]>& operator=(const SharedPtr<T[]>& other) noexcept;
    WeakPtr<T[]>& operator=(WeakPtr<T[]>&& other) noexcept;
    WeakPtr<T[]>& operator=(std::nullptr_t) noexcept;

    void reset() noexcept;
    void swap(WeakPtr<T[]>& other) noexcept;

    [[nodiscard]] unsigned int use_count() const noexcept;
    [[nodiscard]] bool expired() const noexcept;
    SharedPtr<T[]> lock() const noexcept;

    friend void swap(WeakPtr<T[]>& lhs, WeakPtr<T[]>& rhs) noexcept { lhs.swap(rhs); }
};

}  // namespace kogan

#include "WeakPtr.hh"

#endif