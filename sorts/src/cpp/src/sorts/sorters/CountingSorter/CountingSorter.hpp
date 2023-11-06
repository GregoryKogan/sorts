#ifndef COUNTING_SORTER_HPP
#define COUNTING_SORTER_HPP

#include "../BaseSorter.hpp"

namespace kogan {

template <class T>
class CountingSorter : public Sorter<T> {
   private:
    T max_value_ = 0;
    SmartPtrArraySequence<int> counting_array_;
    SmartPtrArraySequence<T> output_array_;

    bool max_value_found_ = false;
    int i_ = 0;

   public:
    CountingSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {}

    void sort_() override;
    void set_interesting_indexes_() noexcept override;
};

}  // namespace kogan

#include "CountingSorter.hh"

#endif