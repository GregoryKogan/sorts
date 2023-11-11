#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T>
class InsertionSorter : public Sorter<T> {
   private:
    std::size_t i_ = 1;
    std::size_t j_ = 1;

   public:
    InsertionSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {}

    void sort_() override;
    void set_interesting_indexes_() noexcept override;
};

}  // namespace kogan

#include "InsertionSorter.tpp"