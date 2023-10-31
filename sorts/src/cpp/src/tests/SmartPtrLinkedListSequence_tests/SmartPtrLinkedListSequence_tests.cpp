#include "SmartPtrLinkedListSequence_tests.hpp"

kogan::TestSuite smart_ptr_linked_list_sequence_test_suite("SmartPtrLinkedListSequence");

TEST(array_constructor, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SharedPtr<int[]> values = kogan::make_shared<int[]>(10);
    for (int i = 0; i < 10; ++i) values[i] = i + 1;

    kogan::SmartPtrLinkedListSequence<int> seq(values, 10);

    ASSERT(seq.get_length() == 10);
    ASSERT(seq[0] == 1);
    ASSERT(seq[2] == 3);
    ASSERT(seq[9] == 10);
}

TEST(empty_constructor, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;

    ASSERT(seq.get_length() == 0);
}

TEST(sequence_constructor, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SharedPtr<int[]> values = kogan::make_shared<int[]>(10);
    for (int i = 0; i < 10; ++i) values[i] = i + 1;

    kogan::SmartPtrLinkedListSequence<int> init_seq(values, 10);
    kogan::SmartPtrLinkedListSequence<int> seq(init_seq);

    ASSERT(seq.get_length() == init_seq.get_length());
    ASSERT(seq.get_length() == 10);
    ASSERT(seq[0] == 1);
    ASSERT(seq[2] == 3);
    ASSERT(seq[9] == 10);
    ASSERT(seq[0] == init_seq[0]);
    ASSERT(seq[2] == init_seq[2]);
    ASSERT(seq[9] == init_seq[9]);
}

TEST(get_first, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    ASSERT(seq.get_first() == seq[0]);
    ASSERT(seq.get_first() == 1);
}

TEST(get_first_single_item, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    seq.append(1);

    ASSERT(seq.get_first() == seq[0]);
    ASSERT(seq.get_first() == 1);
}

TEST(get_last, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    ASSERT(seq.get_last() == seq[seq.get_length() - 1]);
    ASSERT(seq.get_last() == 10);
}

TEST(get_last_single_item, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    seq.append(1);

    ASSERT(seq.get_last() == seq[seq.get_length() - 1]);
    ASSERT(seq.get_last() == 1);
}

TEST(get, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    ASSERT(seq.get(0) == 1);
    ASSERT(seq.get(0) == seq[0]);
    ASSERT(seq.get(0) == seq.get_first());
    ASSERT(seq.get(seq.get_length() - 1) == 10);
    ASSERT(seq.get(seq.get_length() - 1) == seq[seq.get_length() - 1]);
    ASSERT(seq.get(seq.get_length() - 1) == seq.get_last());
}

TEST(get_single_item, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    seq.append(1);

    ASSERT(seq.get(0) == 1);
    ASSERT(seq.get(0) == seq[0]);
    ASSERT(seq.get(0) == seq.get_first());
    ASSERT(seq.get(0) == seq.get_last());
}

TEST(get_negative_index_IndexOutOfRangeException, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.get(-1);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_big_index_IndexOutOfRangeException, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.get(10);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_subsequence, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    kogan::UniquePtr<kogan::SmartPtrSequence<int>> sub_seq_35 = seq.get_subsequence(3, 5);
    ASSERT(sub_seq_35->get_length() == 3);
    ASSERT((*sub_seq_35)[0] == seq[3]);
    ASSERT((*sub_seq_35)[2] == seq[5]);
}

TEST(get_subsequence_max_bounds, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    kogan::UniquePtr<kogan::SmartPtrSequence<int>> sub_seq_09 = seq.get_subsequence(0, 9);
    ASSERT(sub_seq_09->get_length() == 10);
    ASSERT((*sub_seq_09)[0] == seq[0]);
    ASSERT((*sub_seq_09)[9] == seq[9]);
}

TEST(get_subsequence_InvalidArgumentException, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    bool invalidArgumentExceptionThrown = false;
    try {
        seq.get_subsequence(5, 3);
    } catch (kogan::InvalidArgumentException &e) {
        invalidArgumentExceptionThrown = true;
    }
    ASSERT(invalidArgumentExceptionThrown);
}

TEST(get_subsequence_negative_index_IndexOutOfRangeException, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.get_subsequence(-1, 5);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_subsequence_big_index_IndexOutOfRangeException, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.get_subsequence(3, 10);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_length, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    ASSERT(seq.get_length() == 10);

    kogan::SmartPtrLinkedListSequence<int> seq_empty;
    ASSERT(seq_empty.get_length() == 0);
}

TEST(set, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    for (int i = 0; i < 10; ++i) seq.set(i, 10 - i);

    ASSERT(seq[0] == 10);
    ASSERT(seq[9] == 1);

    seq.set(0, -34);
    ASSERT(seq[0] == -34);
}

TEST(set_negative_index_IndexOutOfRangeException, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.set(-1, 0);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(set_big_index_IndexOutOfRangeException, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.set(10, 0);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(append, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    ASSERT(seq.get_length() == 10);
    ASSERT(seq[0] == 1);
    ASSERT(seq[4] == 5);
    ASSERT(seq[9] == 10);

    seq.append(-72);
    ASSERT(seq.get_length() == 11);
    ASSERT(seq[0] == 1);
    ASSERT(seq[4] == 5);
    ASSERT(seq[9] == 10);
    ASSERT(seq[10] == -72);
}

TEST(prepend, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.prepend(i + 1);

    ASSERT(seq.get_length() == 10);
    ASSERT(seq[0] == 10);
    ASSERT(seq[4] == 6);
    ASSERT(seq[9] == 1);

    seq.prepend(-72);
    ASSERT(seq.get_length() == 11);
    ASSERT(seq[1] == 10);
    ASSERT(seq[5] == 6);
    ASSERT(seq[10] == 1);
    ASSERT(seq[0] == -72);
}

TEST(insert, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    seq.insert(0, 0);
    ASSERT(seq[0] == 0);

    seq.insert(11, 11);
    ASSERT(seq[11] == 11);

    seq.insert(5, -42);
    ASSERT(seq[5] == -42);
    ASSERT(seq[4] == 4);
    ASSERT(seq[6] == 5);
}

TEST(insert_negative_index_IndexOutOfRangeException, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.insert(-1, 0);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(insert_big_index_IndexOutOfRangeException, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.insert(11, 0);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(concat, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq1;
    kogan::SharedPtr<kogan::SmartPtrSequence<int>> seq2 =
        kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>());
    for (int i = 0; i < 10; ++i) {
        seq1.append(i + 1);
        seq2->append(i + 11);
    }

    kogan::UniquePtr<kogan::SmartPtrSequence<int>> con12 = seq1.concat(seq2);
    ASSERT(con12->get_length() == seq1.get_length() + seq2->get_length());
    ASSERT(con12->get_length() == 20);
    ASSERT((*con12)[0] == 1);
    ASSERT((*con12)[9] == 10);
    ASSERT((*con12)[10] == 11);
    ASSERT((*con12)[19] == 20);
}

TEST(concat_empty_tail, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq1;
    for (int i = 0; i < 10; ++i) seq1.append(i + 1);

    kogan::SharedPtr<kogan::SmartPtrSequence<int>> seq_empty =
        kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>());
    kogan::UniquePtr<kogan::SmartPtrSequence<int>> con1e = seq1.concat(seq_empty);
    ASSERT(con1e->get_length() == seq1.get_length() + seq_empty->get_length());
    ASSERT(con1e->get_length() == 10);
    ASSERT((*con1e)[0] == 1);
    ASSERT((*con1e)[9] == 10);
}

TEST(concat_empty_head, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SharedPtr<kogan::SmartPtrSequence<int>> seq2 =
        kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>());
    for (int i = 0; i < 10; ++i) seq2->append(i + 11);

    kogan::SharedPtr<kogan::SmartPtrSequence<int>> seq_empty =
        kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>());
    kogan::UniquePtr<kogan::SmartPtrSequence<int>> cone2 = seq_empty->concat(seq2);
    ASSERT(cone2->get_length() == seq_empty->get_length() + seq2->get_length());
    ASSERT(cone2->get_length() == 10);
    ASSERT((*cone2)[0] == 11);
    ASSERT((*cone2)[9] == 20);
}

TEST(clear, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    seq.clear();
    ASSERT(seq.get_length() == 0);
}

TEST(clear_empty, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;

    seq.clear();
    ASSERT(seq.get_length() == 0);
}

TEST(remove, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    seq.remove(5);
    ASSERT(seq.get_length() == 9);
    ASSERT(seq[0] == 1);
    ASSERT(seq[4] == 5);
    ASSERT(seq[5] == 7);
    ASSERT(seq[8] == 10);
}

TEST(remove_first, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    seq.remove(0);
    ASSERT(seq.get_length() == 9);
    ASSERT(seq[0] == 2);
    ASSERT(seq[8] == 10);
}

TEST(remove_last, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    seq.remove(9);
    ASSERT(seq.get_length() == 9);
    ASSERT(seq[0] == 1);
    ASSERT(seq[8] == 9);
}

TEST(remove_single_item, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    seq.append(42);

    seq.remove(0);
    ASSERT(seq.get_length() == 0);
}

TEST(remove_big_index_IndexOutOfRangeException, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.remove(10);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(remove_negative_index_IndexOutOfRangeException, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.remove(-1);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(remove_empty_IndexOutOfRangeException, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.remove(0);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(operator_square_brackets, smart_ptr_linked_list_sequence_test_suite) {
    kogan::SmartPtrLinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i) seq.append(i + 1);

    ASSERT(seq[0] == 1);
    ASSERT(seq[9] == 10);

    seq[0] = 42;
    ASSERT(seq[0] == 42);

    seq[9] = 42;
    ASSERT(seq[9] == 42);
}

kogan::TestSuite get_smart_ptr_linked_list_sequence_test_suite() { return smart_ptr_linked_list_sequence_test_suite; }