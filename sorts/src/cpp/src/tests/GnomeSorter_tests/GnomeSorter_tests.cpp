#include "GnomeSorter_tests.hpp"

kogan::TestSuite gnome_sorter_test_suite("GnomeSorter");

TEST(random, gnome_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrArraySequence<int>());
  for (int i = 0; i < 10; ++i) { sequence->append(rand() % 100); }

  kogan::GnomeSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i) ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(sorted, gnome_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrArraySequence<int>());
  for (int i = 0; i < 10; ++i) { sequence->append(i); }

  kogan::GnomeSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i) ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(reversed, gnome_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrArraySequence<int>());
  for (int i = 10; i > 0; --i) { sequence->append(i); }

  kogan::GnomeSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i) ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(same, gnome_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrArraySequence<int>());
  for (int i = 0; i < 10; ++i) { sequence->append(1); }

  kogan::GnomeSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  for (int i = 0; i < sequence->get_length() - 1; ++i) ASSERT(sequence->get(i) <= sequence->get(i + 1));
}

TEST(empty, gnome_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrArraySequence<int>());

  kogan::GnomeSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  ASSERT(sequence->get_length() == 0);
}

TEST(one, gnome_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrArraySequence<int>());
  sequence->append(1);

  kogan::GnomeSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  ASSERT(sequence->get_length() == 1);
}

TEST(two, gnome_sorter_test_suite) {
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence =
      kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrArraySequence<int>());
  sequence->append(2);
  sequence->append(1);

  kogan::GnomeSorter<int> sorter([](int a, int b) { return a - b; }, sequence);

  sorter.sort();

  ASSERT(sequence->get_length() == 2);
  ASSERT(sequence->get(0) <= sequence->get(1));
}

kogan::TestSuite get_gnome_sorter_test_suite() { return gnome_sorter_test_suite; }