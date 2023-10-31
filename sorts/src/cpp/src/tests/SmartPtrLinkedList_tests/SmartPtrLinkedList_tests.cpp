#include "SmartPtrLinkedList_tests.hpp"

kogan::TestSuite smart_ptr_linked_list_test_suite("SmartPtrLinkedList");

TEST(default_constructor, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    ASSERT(list.get_length() == 0);
}

TEST(array_constructor, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list(data, 5);
    ASSERT(list.get_length() == 5);
    ASSERT(list[0] == 1);
    ASSERT(list[1] == 2);
    ASSERT(list[2] == 3);
    ASSERT(list[3] == 4);
    ASSERT(list[4] == 5);
}

TEST(copy_constructor, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list1(data, 5);

    kogan::SmartPtrLinkedList<int> list2(list1);
    ASSERT(list2.get_length() == 5);
    ASSERT(list1.get_length() == 5);
    ASSERT(list2[0] == 1);
    ASSERT(list1[0] == 1);
    list2[0] = 42;
    ASSERT(list2[0] == 42);
    ASSERT(list1[0] == 1);
    ASSERT(list2[1] == 2);
    ASSERT(list2[2] == 3);
    ASSERT(list2[3] == 4);
    ASSERT(list2[4] == 5);
}

TEST(get, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list(data, 5);
    ASSERT(list.get(0) == 1);
    ASSERT(list.get(1) == 2);
    ASSERT(list.get(2) == 3);
    ASSERT(list.get(3) == 4);
    ASSERT(list.get(4) == 5);
}

TEST(get_single, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    list.append(42);
    ASSERT(list.get(0) == 42);
    ASSERT(list.get_length() == 1);
}

TEST(get_negative_index, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    kogan::SmartPtrLinkedList<int> list(data, 5);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.get(-1);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_big_index, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    kogan::SmartPtrLinkedList<int> list(data, 5);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.get(5);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_first, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list(data, 5);
    ASSERT(list.get_first() == 1);
}

TEST(get_first_single, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    list.append(42);
    ASSERT(list.get_first() == 42);
}

TEST(get_first_empty, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    bool emptyContainerExceptionThrown = false;
    try {
        list.get_first();
    } catch (kogan::EmptyContainerException &e) {
        emptyContainerExceptionThrown = true;
    }
    ASSERT(emptyContainerExceptionThrown);
}

TEST(get_last, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list(data, 5);
    ASSERT(list.get_last() == 5);
}

TEST(get_last_single, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    list.append(42);
    ASSERT(list.get_last() == 42);
}

TEST(get_last_empty, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    bool emptyContainerExceptionThrown = false;
    try {
        list.get_last();
    } catch (kogan::EmptyContainerException &e) {
        emptyContainerExceptionThrown = true;
    }
    ASSERT(emptyContainerExceptionThrown);
}

TEST(get_length, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    kogan::SmartPtrLinkedList<int> list(data, 5);
    ASSERT(list.get_length() == 5);
    list.append(42);
    ASSERT(list.get_length() == 6);
    list.remove(0);
    ASSERT(list.get_length() == 5);
    list.remove(4);
    ASSERT(list.get_length() == 4);
    list.clear();
    ASSERT(list.get_length() == 0);
    list.prepend(42);
    ASSERT(list.get_length() == 1);
}

TEST(set, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    kogan::SmartPtrLinkedList<int> list(data, 5);
    list.set(0, 42);
    ASSERT(list.get(0) == 42);
    list.set(1, 42);
    ASSERT(list.get(1) == 42);
    list.set(2, 42);
    ASSERT(list.get(2) == 42);
    list.set(3, 42);
    ASSERT(list.get(3) == 42);
    list.set(4, 42);
    ASSERT(list.get(4) == 42);
}

TEST(set_single, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    list.append(42);
    list.set(0, 43);
    ASSERT(list.get(0) == 43);
}

TEST(set_negative_index, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    kogan::SmartPtrLinkedList<int> list(data, 5);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.set(-1, 42);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(set_big_index, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    kogan::SmartPtrLinkedList<int> list(data, 5);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.set(5, 42);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(set_empty, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.set(0, 42);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(append, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    list.append(42);
    ASSERT(list.get_length() == 1);
    ASSERT(list.get(0) == 42);
    list.append(43);
    ASSERT(list.get_length() == 2);
    ASSERT(list.get(0) == 42);
    ASSERT(list.get(1) == 43);
    list.append(44);
    ASSERT(list.get_length() == 3);
    ASSERT(list.get(0) == 42);
    ASSERT(list.get(1) == 43);
    ASSERT(list.get(2) == 44);
}

TEST(prepend, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    list.prepend(42);
    ASSERT(list.get_length() == 1);
    ASSERT(list.get(0) == 42);
    list.prepend(43);
    ASSERT(list.get_length() == 2);
    ASSERT(list.get(0) == 43);
    ASSERT(list.get(1) == 42);
    list.prepend(44);
    ASSERT(list.get_length() == 3);
    ASSERT(list.get(0) == 44);
    ASSERT(list.get(1) == 43);
    ASSERT(list.get(2) == 42);
}

TEST(insert, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list(data, 5);
    list.insert(0, 42);
    ASSERT(list.get_length() == 6);
    ASSERT(list.get(0) == 42);
    ASSERT(list.get(1) == 1);
    ASSERT(list.get(2) == 2);
    ASSERT(list.get(3) == 3);
    ASSERT(list.get(4) == 4);
    ASSERT(list.get(5) == 5);
    list.insert(1, 43);
    ASSERT(list.get_length() == 7);
    ASSERT(list.get(0) == 42);
    ASSERT(list.get(1) == 43);
    ASSERT(list.get(2) == 1);
    ASSERT(list.get(3) == 2);
    ASSERT(list.get(4) == 3);
    ASSERT(list.get(5) == 4);
    ASSERT(list.get(6) == 5);
    list.insert(6, 44);
    ASSERT(list.get_length() == 8);
    ASSERT(list.get(0) == 42);
    ASSERT(list.get(1) == 43);
    ASSERT(list.get(2) == 1);
    ASSERT(list.get(3) == 2);
    ASSERT(list.get(4) == 3);
    ASSERT(list.get(5) == 4);
    ASSERT(list.get(6) == 44);
    ASSERT(list.get(7) == 5);
    list.insert(8, 45);
    ASSERT(list.get_length() == 9);
    ASSERT(list.get(0) == 42);
    ASSERT(list.get(1) == 43);
    ASSERT(list.get(2) == 1);
    ASSERT(list.get(3) == 2);
    ASSERT(list.get(4) == 3);
    ASSERT(list.get(5) == 4);
    ASSERT(list.get(6) == 44);
    ASSERT(list.get(7) == 5);
    ASSERT(list.get(8) == 45);
}

TEST(insert_single, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    list.insert(0, 42);
    ASSERT(list.get_length() == 1);
    ASSERT(list.get(0) == 42);
}

TEST(insert_negative_index, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.insert(-1, 42);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(insert_big_index, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.insert(1, 42);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(remove, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list(data, 5);
    list.remove(0);
    ASSERT(list.get_length() == 4);
    ASSERT(list.get(0) == 2);
    ASSERT(list.get(1) == 3);
    ASSERT(list.get(2) == 4);
    ASSERT(list.get(3) == 5);
    list.remove(2);
    ASSERT(list.get_length() == 3);
    ASSERT(list.get(0) == 2);
    ASSERT(list.get(1) == 3);
    ASSERT(list.get(2) == 5);
    list.remove(2);
    ASSERT(list.get_length() == 2);
    ASSERT(list.get(0) == 2);
    ASSERT(list.get(1) == 3);
    list.remove(1);
    ASSERT(list.get_length() == 1);
    ASSERT(list.get(0) == 2);
    list.remove(0);
    ASSERT(list.get_length() == 0);
}

TEST(remove_single, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    list.append(42);
    list.remove(0);
    ASSERT(list.get_length() == 0);
}

TEST(remove_negative_index, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.remove(-1);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(remove_big_index, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.remove(0);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(remove_empty, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.remove(0);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(clear, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    kogan::SmartPtrLinkedList<int> list(data, 5);
    list.clear();
    ASSERT(list.get_length() == 0);
}

TEST(clear_empty, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    list.clear();
    ASSERT(list.get_length() == 0);
}

TEST(clear_single, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    list.append(42);
    list.clear();
    ASSERT(list.get_length() == 0);
}

TEST(get_sublist, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list(data, 5);

    auto sublist = list.get_sublist(0, 4);
    ASSERT(sublist.get_length() == 5);
    ASSERT(sublist.get(0) == 1);
    ASSERT(sublist.get(1) == 2);
    ASSERT(sublist.get(2) == 3);
    ASSERT(sublist.get(3) == 4);
    ASSERT(sublist.get(4) == 5);

    sublist = list.get_sublist(1, 3);
    ASSERT(sublist.get_length() == 3);
    ASSERT(sublist.get(0) == 2);
    ASSERT(sublist.get(1) == 3);
    ASSERT(sublist.get(2) == 4);

    sublist = list.get_sublist(2, 2);
    ASSERT(sublist.get_length() == 1);
    ASSERT(sublist.get(0) == 3);

    sublist = list.get_sublist(4, 4);
    ASSERT(sublist.get_length() == 1);
    ASSERT(sublist.get(0) == 5);
}

TEST(get_sublist_single, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    list.append(42);

    auto sublist = list.get_sublist(0, 0);
    ASSERT(sublist.get_length() == 1);
    ASSERT(sublist.get(0) == 42);
}

TEST(get_sublist_negative_start_index, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.get_sublist(-1, 0);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_sublist_negative_end_index, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.get_sublist(0, -1);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_sublist_big_start_index, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.get_sublist(1, 0);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_sublist_big_end_index, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list;
    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.get_sublist(0, 1);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_sublist_end_index_less_than_start_index, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list(data, 5);

    bool invalidArgumentExceptionThrown = false;
    try {
        list.get_sublist(1, 0);
    } catch (kogan::InvalidArgumentException &e) {
        invalidArgumentExceptionThrown = true;
    }
    ASSERT(invalidArgumentExceptionThrown);
}

TEST(concat, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list1(data, 5);

    for (int i = 0; i < 5; ++i) data[i] = i + 6;
    kogan::SmartPtrLinkedList<int> list2(data, 5);

    auto list3 = list1.concat(list2);
    ASSERT(list3.get_length() == 10);
    ASSERT(list3.get(0) == 1);
    ASSERT(list3.get(1) == 2);
    ASSERT(list3.get(2) == 3);
    ASSERT(list3.get(3) == 4);
    ASSERT(list3.get(4) == 5);
    ASSERT(list3.get(5) == 6);
    ASSERT(list3.get(6) == 7);
    ASSERT(list3.get(7) == 8);
    ASSERT(list3.get(8) == 9);
    ASSERT(list3.get(9) == 10);
}

TEST(concat_empty, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list1;
    kogan::SmartPtrLinkedList<int> list2;
    auto list3 = list1.concat(list2);
    ASSERT(list3.get_length() == 0);
}

TEST(concat_empty_first, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list1;
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list2(data, 5);
    auto list3 = list1.concat(list2);
    ASSERT(list3.get_length() == 5);
    ASSERT(list3.get(0) == 1);
    ASSERT(list3.get(1) == 2);
    ASSERT(list3.get(2) == 3);
    ASSERT(list3.get(3) == 4);
    ASSERT(list3.get(4) == 5);
}

TEST(concat_empty_second, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list1;
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list2(data, 5);
    auto list3 = list2.concat(list1);
    ASSERT(list3.get_length() == 5);
    ASSERT(list3.get(0) == 1);
    ASSERT(list3.get(1) == 2);
    ASSERT(list3.get(2) == 3);
    ASSERT(list3.get(3) == 4);
    ASSERT(list3.get(4) == 5);
}

TEST(concat_single, smart_ptr_linked_list_test_suite) {
    kogan::SmartPtrLinkedList<int> list1;
    list1.append(42);
    kogan::SmartPtrLinkedList<int> list2;
    list2.append(43);
    auto list3 = list1.concat(list2);
    ASSERT(list3.get_length() == 2);
    ASSERT(list3.get(0) == 42);
    ASSERT(list3.get(1) == 43);
    ASSERT(list1.get_length() == 1);
    ASSERT(list2.get_length() == 1);
    ASSERT(list1.get(0) == 42);
    ASSERT(list2.get(0) == 43);
}

TEST(operator_square_brackets, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list(data, 5);
    ASSERT(list[0] == 1);
    ASSERT(list[1] == 2);
    ASSERT(list[2] == 3);
    ASSERT(list[3] == 4);
    ASSERT(list[4] == 5);
    list[0] = 42;
    ASSERT(list[0] == 42);
    ASSERT(list[1] == 2);
    ASSERT(list[2] == 3);
    ASSERT(list[3] == 4);
    ASSERT(list[4] == 5);
}

TEST(copy_assignment, smart_ptr_linked_list_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrLinkedList<int> list1(data, 5);

    auto list2 = list1;
    ASSERT(list1.get_length() == list2.get_length());
    ASSERT(list1.get_length() == 5);
    ASSERT(list1[0] == list2[0]);
    ASSERT(list1[0] == 1);
    ASSERT(list1[4] == list2[4]);
    ASSERT(list1[4] == 5);

    kogan::SmartPtrLinkedList<int> list3;
    list2 = list3;
    ASSERT(list2.get_length() == list3.get_length());
    ASSERT(list2.get_length() == 0);
    ASSERT(list1.get_length() == 5);
}

kogan::TestSuite get_smart_ptr_linked_list_test_suite() { return smart_ptr_linked_list_test_suite; }