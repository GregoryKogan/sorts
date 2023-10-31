#include "BubbleSorter_tests.hpp"

kogan::TestSuite bubble_sorter_test_suite("BubbleSorter");

TEST(random, bubble_sorter_test_suite) {
    auto sequence = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>());
    for (int i = 0; i < 10; ++i) sequence->append(rand() % 100);

    auto sorter = kogan::make_unique<kogan::BubbleSorter<int>>([](int a, int b) { return a - b; }, sequence);
    sorter->sort();

    ASSERT(sorter->is_sorted());
    ASSERT(sorter->get_comparisons() == 45);
}

TEST(empty, bubble_sorter_test_suite) {
    auto sequence = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>());

    auto sorter = kogan::make_unique<kogan::BubbleSorter<int>>([](int a, int b) { return a - b; }, sequence);
    sorter->sort();

    ASSERT(sequence->get_length() == 0);
    ASSERT(sorter->get_comparisons() == 0);
    ASSERT(sorter->get_swaps() == 0);
}

TEST(one_element, bubble_sorter_test_suite) {
    auto sequence = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>());
    sequence->append(1);

    auto sorter = kogan::make_unique<kogan::BubbleSorter<int>>([](int a, int b) { return a - b; }, sequence);
    sorter->sort();

    ASSERT(sequence->get_length() == 1);
    ASSERT(sequence->get(0) == 1);
    ASSERT(sorter->get_comparisons() == 0);
    ASSERT(sorter->get_swaps() == 0);
}

TEST(two_elements, bubble_sorter_test_suite) {
    auto sequence = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>());
    sequence->append(2);
    sequence->append(1);

    auto sorter = kogan::make_unique<kogan::BubbleSorter<int>>([](int a, int b) { return a - b; }, sequence);
    sorter->sort();

    ASSERT(sequence->get_length() == 2);
    ASSERT(sequence->get(0) == 1);
    ASSERT(sequence->get(1) == 2);
    ASSERT(sorter->get_comparisons() == 1);
    ASSERT(sorter->get_swaps() == 1);
}

TEST(sorted, bubble_sorter_test_suite) {
    auto sequence = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>());
    for (int i = 0; i < 10; ++i) sequence->append(i + 1);

    auto sorter = kogan::make_unique<kogan::BubbleSorter<int>>([](int a, int b) { return a - b; }, sequence);
    sorter->sort();

    for (int i = 0; i < 10; ++i) ASSERT(sequence->get(i) == i + 1);
    ASSERT(sorter->get_comparisons() == 45);
    ASSERT(sorter->get_swaps() == 0);
}

TEST(reverse_sorted, bubble_sorter_test_suite) {
    auto sequence = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>());
    for (int i = 0; i < 10; ++i) sequence->append(10 - i);

    auto sorter = kogan::make_unique<kogan::BubbleSorter<int>>([](int a, int b) { return a - b; }, sequence);
    sorter->sort();

    for (int i = 0; i < 10; ++i) ASSERT(sequence->get(i) == i + 1);
    ASSERT(sorter->get_comparisons() == 45);
    ASSERT(sorter->get_swaps() == 45);
}

TEST(comparison_limited, bubble_sorter_test_suite) {
    auto sequence = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>());
    for (int i = 0; i < 10; ++i) sequence->append(rand() % 100);

    auto sorter = kogan::make_unique<kogan::BubbleSorter<int>>([](int a, int b) { return a - b; }, sequence);
    sorter->make_limited_in_comparisons();
    sorter->add_available_comparisons(10);
    sorter->sort();
    sorter->add_available_comparisons(35);
    sorter->sort();

    ASSERT(sorter->is_sorted());
    ASSERT(sorter->get_comparisons() == 45);
}

TEST(swap_limited, bubble_sorter_test_suite) {
    auto sequence = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>());
    for (int i = 0; i < 10; ++i) sequence->append(rand() % 100);

    auto sorter = kogan::make_unique<kogan::BubbleSorter<int>>([](int a, int b) { return a - b; }, sequence);
    sorter->make_limited_in_swaps();
    sorter->add_available_swaps(10);
    sorter->sort();
    sorter->add_available_swaps(35);
    sorter->sort();

    ASSERT(sorter->is_sorted());
    ASSERT(sorter->get_swaps() <= 45);
}

kogan::TestSuite get_bubble_sorter_test_suite() { return bubble_sorter_test_suite; }