#include "../sorts/smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "../sorts/sorters/BaseSorter.hpp"
#include "../sorts/sorters/BubbleSorter/BubbleSorter.hpp"
#include "../sorts/sorters/CocktailSorter/CocktailSorter.hpp"
#include "../sorts/sorters/CombSorter/CombSorter.hpp"
#include "../sorts/sorters/CountingSorter/CountingSorter.hpp"
#include "../sorts/sorters/CycleSorter/CycleSorter.hpp"
#include "../sorts/sorters/GnomeSorter/GnomeSorter.hpp"
#include "../sorts/sorters/HeapSorter/HeapSorter.hpp"
#include "../sorts/sorters/InsertionSorter/InsertionSorter.hpp"
#include "../sorts/sorters/IterativeMergeSorter/IterativeMergeSorter.hpp"
#include "../sorts/sorters/IterativeQuickSorter/IterativeQuickSorter.hpp"
#include "../sorts/sorters/MergeSorter/MergeSorter.hpp"
#include "../sorts/sorters/OddEvenSorter/OddEvenSorter.hpp"
#include "../sorts/sorters/QuickSorter/QuickSorter.hpp"
#include "../sorts/sorters/RadixSorter/RadixSorter.hpp"
#include "../sorts/sorters/SelectionSorter/SelectionSorter.hpp"
#include "../sorts/sorters/ShellSorter/ShellSorter.hpp"
#include "../sorts/sorters/StoogeSorter/StoogeSorter.hpp"

#include <chrono>
#include <iostream>
#include <vector>

enum class SortAlgorithm {
  BUBBLE,
  SELECTION,
  INSERTION,
  MERGE,
  ITER_MERGE,
  QUICK,
  ITER_QUICK,
  HEAP,
  COUNT,
  COCKTAIL,
  RADIX,
  SHELL,
  GNOME,
  ODD_EVEN,
  COMB,
  CYCLE
};

class SorterBenchmark {
  kogan::UniquePtr<kogan::Sorter<int>> sorter_;
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence_;
  SortAlgorithm algorithm_;

  void copy_sequence_(const kogan::SharedPtr<kogan::SmartPtrSequence<int>> &sequence) noexcept {
    sequence_ = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrArraySequence<int>());
    for (int i = 0; i < sequence->get_length(); ++i) sequence_->append(sequence->get(i));
  }

  void init_sorter() noexcept {
    switch (algorithm_) {
    case SortAlgorithm::BUBBLE:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::BubbleSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::SELECTION:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::SelectionSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::INSERTION:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::InsertionSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::MERGE:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::MergeSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::ITER_MERGE:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::IterativeMergeSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::QUICK:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::QuickSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::ITER_QUICK:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::IterativeQuickSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::HEAP:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::HeapSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::COUNT:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(new kogan::CountingSorter(sequence_));
      break;
    case SortAlgorithm::COCKTAIL:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::CocktailSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::RADIX: sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(new kogan::RadixSorter(sequence_)); break;
    case SortAlgorithm::SHELL:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::ShellSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::GNOME:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::GnomeSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::ODD_EVEN:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::OddEvenSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::COMB:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::CombSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    case SortAlgorithm::CYCLE:
      sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
          new kogan::CycleSorter<int>([](int a, int b) { return a - b; }, sequence_));
      break;
    }
  }

public:
  SorterBenchmark(const SortAlgorithm &algorithm,
                  const kogan::SharedPtr<kogan::SmartPtrSequence<int>> &sequence) noexcept
      : algorithm_(algorithm) {
    copy_sequence_(sequence);
    init_sorter();
  }

  void run() noexcept { sorter_->sort(); }

  bool is_sorted() const noexcept {
    for (int i = 0; i < sequence_->get_length() - 1; ++i)
      if (sequence_->get(i) > sequence_->get(i + 1)) return false;
    return true;
  }

  void set_sequence(const kogan::SharedPtr<kogan::SmartPtrSequence<int>> &sequence) noexcept {
    copy_sequence_(sequence);
    init_sorter();
  }

  std::string get_algorithm_name() {
    switch (algorithm_) {
    case SortAlgorithm::BUBBLE: return "Bubble Sort";
    case SortAlgorithm::SELECTION: return "Selection Sort";
    case SortAlgorithm::INSERTION: return "Insertion Sort";
    case SortAlgorithm::MERGE: return "Merge Sort";
    case SortAlgorithm::ITER_MERGE: return "Iterative Merge Sort";
    case SortAlgorithm::QUICK: return "Quick Sort";
    case SortAlgorithm::ITER_QUICK: return "Iterative Quick Sort";
    case SortAlgorithm::HEAP: return "Heap Sort";
    case SortAlgorithm::COUNT: return "Counting Sort";
    case SortAlgorithm::COCKTAIL: return "Cocktail Sort";
    case SortAlgorithm::RADIX: return "Radix Sort";
    case SortAlgorithm::SHELL: return "Shell Sort";
    case SortAlgorithm::GNOME: return "Gnome Sort";
    case SortAlgorithm::ODD_EVEN: return "Odd Even Sort";
    case SortAlgorithm::COMB: return "Comb Sort";
    case SortAlgorithm::CYCLE: return "Cycle Sort";
    }
  }
};

class Benchmark {
  std::vector<SorterBenchmark> benchmarks_;
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence_;

  void generate_sequence_(u_int32_t length) noexcept {
    sequence_ = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrArraySequence<int>());
    for (int i = 0; i < length; ++i) sequence_->append(rand() % length);
  }

public:
  Benchmark() {
    generate_sequence_(10);
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::BUBBLE, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::SELECTION, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::INSERTION, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::MERGE, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::ITER_MERGE, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::QUICK, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::ITER_QUICK, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::HEAP, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::COUNT, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::COCKTAIL, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::RADIX, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::SHELL, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::GNOME, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::ODD_EVEN, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::COMB, sequence_));
    benchmarks_.push_back(SorterBenchmark(SortAlgorithm::CYCLE, sequence_));
  }

  void run() noexcept {
    std::cout << "Sequence length,Bubble Sort,Selection Sort,Insertion Sort,Merge Sort,Iterative Merge Sort,Quick "
                 "Sort,Iterative Quick Sort,Heap Sort,Counting Sort,Cocktail Sort,Radix Sort,Shell Sort,Gnome "
                 "Sort,Odd Even Sort,Comb Sort,Cycle Sort"
              << std::endl;

    for (u_int32_t sequence_length = 500; sequence_length <= 10000; sequence_length += 500) {
      generate_sequence_(sequence_length);

      std::cout << sequence_length << ",";

      for (int i = 0; i < benchmarks_.size(); ++i) {
        if (benchmarks_[i].get_algorithm_name() == "Stooge Sort" && sequence_length > 1000) {
          std::cout << "N/A" << (i == benchmarks_.size() - 1 ? "\n" : ",");
          continue;
        }

        auto sum_time = 0;
        for (int average = 0; average < 10; ++average) {
          benchmarks_[i].set_sequence(sequence_);
          auto start = std::chrono::high_resolution_clock::now();
          benchmarks_[i].run();
          auto end = std::chrono::high_resolution_clock::now();
          auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
          sum_time += duration;
          if (!benchmarks_[i].is_sorted()) std::cout << "NOT SORTED" << std::endl;
        }

        auto average_time = sum_time / 10;
        std::cout << average_time << (i == benchmarks_.size() - 1 ? "\n" : ",");
      }
    }
  }
};

int main() {
  Benchmark benchmark;
  benchmark.run();
  return 0;
}