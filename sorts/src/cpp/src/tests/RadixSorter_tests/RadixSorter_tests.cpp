#include "RadixSorter_tests.hpp"

kogan::TestSuite radix_sorter_test_suite("RadixSorter");

TEST(random, radix_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  for (int i = 0; i < 10; ++i) { sequence->append(rand() % 100); }

  kogan::RadixSorter sorter(sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i)
    ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(sorted, radix_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  for (int i = 0; i < 10; ++i) { sequence->append(i); }

  kogan::RadixSorter sorter(sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i)
    ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(reversed, radix_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  for (int i = 10; i > 0; --i) { sequence->append(i); }

  kogan::RadixSorter sorter(sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i)
    ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(same, radix_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  for (int i = 0; i < 10; ++i) { sequence->append(1); }

  kogan::RadixSorter sorter(sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i)
    ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(empty, radix_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());

  kogan::RadixSorter sorter(sequence);

  sorter.sort();

  ASSERT(sequence->get_length() == 0);
}

TEST(one, radix_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  sequence->append(1);

  kogan::RadixSorter sorter(sequence);

  sorter.sort();

  ASSERT(sequence->get_length() == 1);
}

TEST(two, radix_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
          new kogan::SmartPtrArraySequence<int>());
  sequence->append(2);
  sequence->append(1);

  kogan::RadixSorter sorter(sequence);

  sorter.sort();

  ASSERT(sequence->get_length() == 2);
  ASSERT(sequence->get(0) <= sequence->get(1));
}

kogan::TestSuite get_radix_sorter_test_suite() {
  return radix_sorter_test_suite;
}