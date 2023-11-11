#include "SelectionSorter_tests.hpp"

kogan::TestSuite selection_sorter_test_suite("SelectionSorter");

TEST(random, selection_sorter_test_suite) {
  auto sequence = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
      new kogan::SmartPtrLinkedListSequence<int>());
  for (int i = 0; i < 10; ++i)
    sequence->append(rand() % 100);

  auto sorter = kogan::make_unique<kogan::SelectionSorter<int>>(
      [](int a, int b) { return a - b; }, sequence);
  sorter->sort();

  ASSERT(sorter->is_sorted());
}

TEST(limited_in_comparisons, selection_sorter_test_suite) {
  auto sequence = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
      new kogan::SmartPtrLinkedListSequence<int>());
  for (int i = 0; i < 10; ++i)
    sequence->append(rand() % 100);

  auto sorter = kogan::make_unique<kogan::SelectionSorter<int>>(
      [](int a, int b) { return a - b; }, sequence);
  sorter->make_limited_in_comparisons();
  sorter->add_available_comparisons(10);
  sorter->sort();
  sorter->make_unlimited_in_comparisons();
  sorter->sort();

  ASSERT(sorter->is_sorted());
}

TEST(limited_in_swaps, selection_sorter_test_suite) {
  auto sequence = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
      new kogan::SmartPtrLinkedListSequence<int>());
  for (int i = 0; i < 10; ++i)
    sequence->append(rand() % 100);

  auto sorter = kogan::make_unique<kogan::SelectionSorter<int>>(
      [](int a, int b) { return a - b; }, sequence);
  sorter->make_limited_in_swaps();
  sorter->add_available_swaps(10);
  sorter->sort();
  sorter->make_unlimited_in_swaps();
  sorter->sort();

  ASSERT(sorter->is_sorted());
}

kogan::TestSuite get_selection_sorter_test_suite() {
  return selection_sorter_test_suite;
}