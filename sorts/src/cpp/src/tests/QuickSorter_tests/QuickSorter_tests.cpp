#include "QuickSorter_tests.hpp"

kogan::TestSuite quick_sorter_test_suite("QuickSorter");

TEST(random, quick_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  for (int i = 0; i < 10; ++i) { sequence->append(rand() % 100); }

  kogan::QuickSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i)
    ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(sorted, quick_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  for (int i = 0; i < 10; ++i) { sequence->append(i); }

  kogan::QuickSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i)
    ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(reversed, quick_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  for (int i = 10; i > 0; --i) { sequence->append(i); }

  kogan::QuickSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i)
    ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(same, quick_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  for (int i = 0; i < 10; ++i) { sequence->append(1); }

  kogan::QuickSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i)
    ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(empty, quick_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());

  kogan::QuickSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  ASSERT(sequence->get_length() == 0);
}

TEST(one, quick_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  sequence->append(1);

  kogan::QuickSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  ASSERT(sequence->get_length() == 1);
}

TEST(two, quick_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  sequence->append(2);
  sequence->append(1);

  kogan::QuickSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  ASSERT(sequence->get_length() == 2);
  ASSERT(sequence->get(0) <= sequence->get(1));
}

kogan::TestSuite get_quick_sorter_test_suite() {
  return quick_sorter_test_suite;
}