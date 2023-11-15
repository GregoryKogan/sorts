#include "HeapSorter_tests.hpp"

kogan::TestSuite heap_sorter_test_suite("HeapSorter");

TEST(random, heap_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  for (int i = 0; i < 10; ++i) { sequence->append(rand() % 100); }

  kogan::HeapSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i)
    ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(sorted, heap_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  for (int i = 0; i < 10; ++i) { sequence->append(i); }

  kogan::HeapSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i)
    ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(reversed, heap_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  for (int i = 10; i > 0; --i) { sequence->append(i); }

  kogan::HeapSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i)
    ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(same, heap_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  for (int i = 0; i < 10; ++i) { sequence->append(1); }

  kogan::HeapSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i)
    ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(empty, heap_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());

  kogan::HeapSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  ASSERT(sequence->get_length() == 0);
}

TEST(one, heap_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  sequence->append(1);

  kogan::HeapSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  ASSERT(sequence->get_length() == 1);
}

TEST(two, heap_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  sequence->append(2);
  sequence->append(1);

  kogan::HeapSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  ASSERT(sequence->get_length() == 2);
  ASSERT(sequence->get(0) <= sequence->get(1));
}

kogan::TestSuite get_heap_sorter_test_suite() { return heap_sorter_test_suite; }