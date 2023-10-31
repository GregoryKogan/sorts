#ifndef BASE_SORTER_HPP
#define BASE_SORTER_HPP

#include "../../libs/exception_lib/exceptions/OutOfComparisonsException/OutOfComparisonsException.hpp"
#include "../../libs/exception_lib/exceptions/OutOfSwapsException/OutOfSwapsException.hpp"
#include "../smart_sequences/sequences/SmartPtrSequence.hpp"

namespace kogan {

template <class T>
class Sorter {
   protected:
    u_int32_t comparisons_ = 0;
    u_int32_t swaps_ = 0;

    bool limited_in_comparisons_ = false;
    bool limited_in_swaps_ = false;
    u_int32_t available_comparisons_ = 0;
    u_int32_t available_swaps_ = 0;

    int (*cmp_)(T, T);
    SharedPtr<SmartPtrSequence<T>> sequence_;

   public:
    Sorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence);

    virtual ~Sorter() = default;

    // Observers
    [[nodiscard]] bool is_sorted() const noexcept;
    [[nodiscard]] u_int32_t get_comparisons() const noexcept;
    [[nodiscard]] u_int32_t get_swaps() const noexcept;
    [[nodiscard]] u_int32_t get_available_comparisons() const noexcept;
    [[nodiscard]] u_int32_t get_available_swaps() const noexcept;
    [[nodiscard]] bool is_limited_in_comparisons() const noexcept;
    [[nodiscard]] bool is_limited_in_swaps() const noexcept;

    // Modifiers
    void add_available_comparisons(u_int32_t available_comparisons) noexcept;
    void add_available_swaps(u_int32_t available_swaps) noexcept;
    void make_limited_in_comparisons() noexcept;
    void make_limited_in_swaps() noexcept;
    void make_unlimited_in_comparisons() noexcept;
    void make_unlimited_in_swaps() noexcept;

    void sort();

   protected:
    virtual void sort_() = 0;
    int cmp_wrapper_(T a, T b);
    void swap_(int i, int j);
};

}  // namespace kogan

#include "BaseSorter.hh"

#endif