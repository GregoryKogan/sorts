#include "SharedPtr_tests/SharedPtr_tests.hpp"
#include "UniquePtr_tests/UniquePtr_tests.hpp"
#include "WeakPtr_tests/WeakPtr_tests.hpp"

#include "SmartPtrArraySequence_tests/SmartPtrArraySequence_tests.hpp"
#include "SmartPtrDynamicArray_tests/SmartPtrDynamicArray_tests.hpp"
#include "SmartPtrLinkedListSequence_tests/SmartPtrLinkedListSequence_tests.hpp"
#include "SmartPtrLinkedList_tests/SmartPtrLinkedList_tests.hpp"

#include "BubbleSorter_tests/BubbleSorter_tests.hpp"
#include "CocktailSorter_tests/CocktailSorter_tests.hpp"
#include "CombSorter_tests/CombSorter_tests.hpp"
#include "CountingSorter_tests/CountingSorter_tests.hpp"
#include "GnomeSorter_tests/GnomeSorter_tests.hpp"
#include "HeapSorter_tests/HeapSorter_tests.hpp"
#include "InsertionSorter_tests/InsertionSorter_tests.hpp"
#include "IterativeMergeSorter_tests/IterativeMergeSorter_tests.hpp"
#include "IterativeQuickSorter_tests/IterativeQuickSorter_tests.hpp"
#include "MergeSorter_tests/MergeSorter_tests.hpp"
#include "OddEvenSorter_tests/OddEvenSorter_tests.hpp"
#include "QuickSorter_tests/QuickSorter_tests.hpp"
#include "RadixSorter_tests/RadixSorter_tests.hpp"
#include "SelectionSorter_tests/SelectionSorter_tests.hpp"
#include "ShellSorter_tests/ShellSorter_tests.hpp"
#include "StoogeSorter_tests/StoogeSorter_tests.hpp"

int main() {
  std::vector<kogan::TestSuite> suites = {
      get_unique_ptr_test_suite(),
      get_shared_ptr_test_suite(),
      get_weak_ptr_test_suite(),

      get_smart_ptr_dynamic_array_test_suite(),
      get_smart_ptr_linked_list_test_suite(),

      get_smart_ptr_array_sequence_test_suite(),
      get_smart_ptr_linked_list_sequence_test_suite(),

      get_bubble_sorter_test_suite(),
      get_cocktail_sorter_test_suite(),
      get_counting_sorter_test_suite(),
      get_gnome_sorter_test_suite(),
      get_heap_sorter_test_suite(),
      get_insertion_sorter_test_suite(),
      get_iterative_merge_sorter_test_suite(),
      get_iterative_quick_sorter_test_suite(),
      get_merge_sorter_test_suite(),
      get_quick_sorter_test_suite(),
      get_radix_sorter_test_suite(),
      get_selection_sorter_test_suite(),
      get_shell_sorter_test_suite(),
      get_odd_even_sorter_test_suite(),
      get_comb_sorter_test_suite(),
      get_stooge_sorter_test_suite(),
  };

  kogan::Tester tester(suites);
  tester.test();

  return 0;
}