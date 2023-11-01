#ifndef SELECTION_SORTER_HPP
#define SELECTION_SORTER_HPP

#include "../BaseSorter.hpp"

namespace kogan {

template <class T>
class SelectionSorter : public Sorter<T> {
   private:
    std::size_t i_ = 0;
    std::size_t j_ = i_ + 1;
    std::size_t min_index_ = 0;

   public:
    SelectionSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {}

    void sort_() override;
    void set_interesting_indexes_() noexcept override;
};

}  // namespace kogan

#include "SelectionSorter.hh"

#endif