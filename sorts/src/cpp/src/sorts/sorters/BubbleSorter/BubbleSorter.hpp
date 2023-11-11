#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T>
class BubbleSorter : public Sorter<T> {
   private:
    std::size_t i_ = 0;
    std::size_t j_ = 0;

   public:
    BubbleSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {}

    void sort_() override;
    void set_interesting_indexes_() noexcept override;
};

}  // namespace kogan

#include "BubbleSorter.tpp"