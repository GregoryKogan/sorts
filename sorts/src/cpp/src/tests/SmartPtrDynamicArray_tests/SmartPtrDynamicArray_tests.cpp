#include "SmartPtrDynamicArray_tests.hpp"

kogan::TestSuite smart_ptr_dynamic_array_test_suite("SmartPtrDynamicArray");

TEST(default_constructor, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr;
    ASSERT(arr.get_length() == 0);
}

TEST(length_constructor, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr(5);
    ASSERT(arr.get_length() == 5);
}

TEST(array_constructor, smart_ptr_dynamic_array_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrDynamicArray<int> arr(data, 5);
    ASSERT(arr.get_length() == 5);
    ASSERT(arr[0] == 1);
    ASSERT(arr[1] == 2);
    ASSERT(arr[2] == 3);
    ASSERT(arr[3] == 4);
    ASSERT(arr[4] == 5);
}

TEST(copy_constructor, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr1(5);
    for (int i = 0; i < 5; ++i) arr1[i] = i + 1;
    kogan::SmartPtrDynamicArray<int> arr2(arr1);
    ASSERT(arr2.get_length() == 5);
    ASSERT(arr1.get_length() == 5);
    ASSERT(arr2[0] == 1);
    ASSERT(arr1[0] == 1);
    arr2[0] = 42;
    ASSERT(arr2[0] == 42);
    ASSERT(arr1[0] == 1);
    ASSERT(arr2[1] == 2);
    ASSERT(arr2[2] == 3);
    ASSERT(arr2[3] == 4);
    ASSERT(arr2[4] == 5);
}

TEST(get, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr(5);
    for (int i = 0; i < 5; ++i) arr[i] = i + 1;
    ASSERT(arr.get(0) == 1);
    ASSERT(arr.get(1) == 2);
    ASSERT(arr.get(2) == 3);
    ASSERT(arr.get(3) == 4);
    ASSERT(arr.get(4) == 5);
}

TEST(get_single, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr(1);
    arr[0] = 42;
    ASSERT(arr.get(0) == 42);
    ASSERT(arr.get_length() == 1);
}

TEST(get_negative_index, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr(5);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        arr.get(-1);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_big_index, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr(5);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        arr.get(5);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_length, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr(5);
    ASSERT(arr.get_length() == 5);

    arr.resize(10);
    ASSERT(arr.get_length() == 10);

    kogan::SmartPtrDynamicArray<int> empty_arr;
    ASSERT(empty_arr.get_length() == 0);
}

TEST(set, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr(5);
    for (int i = 0; i < 5; ++i) arr[i] = i + 1;
    arr.set(0, 42);
    ASSERT(arr.get(0) == 42);
    ASSERT(arr.get(1) == 2);
    ASSERT(arr.get(2) == 3);
    ASSERT(arr.get(3) == 4);
    ASSERT(arr.get(4) == 5);
    arr.set(4, -42);
    ASSERT(arr.get(0) == 42);
    ASSERT(arr.get(1) == 2);
    ASSERT(arr.get(2) == 3);
    ASSERT(arr.get(3) == 4);
    ASSERT(arr.get(4) == -42);
}

TEST(set_negative_index, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr(5);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        arr.set(-1, 42);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(set_big_index, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr(5);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        arr.set(5, 42);
    } catch (kogan::IndexOutOfRangeException &e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(resize, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr(5);
    for (int i = 0; i < 5; ++i) arr[i] = i + 1;

    ASSERT(arr.get_length() == 5);

    arr.resize(10);
    ASSERT(arr.get_length() == 10);
    ASSERT(arr.get(0) == 1);
    ASSERT(arr.get(1) == 2);
    ASSERT(arr.get(2) == 3);
    ASSERT(arr.get(3) == 4);
    ASSERT(arr.get(4) == 5);

    arr.resize(3);
    ASSERT(arr.get_length() == 3);
    ASSERT(arr.get(0) == 1);
    ASSERT(arr.get(1) == 2);
    ASSERT(arr.get(2) == 3);

    arr.resize(3);
    ASSERT(arr.get_length() == 3);
    ASSERT(arr.get(0) == 1);
    ASSERT(arr.get(1) == 2);
    ASSERT(arr.get(2) == 3);

    arr.resize(0);
    ASSERT(arr.get_length() == 0);

    arr.resize(1);
    ASSERT(arr.get_length() == 1);
}

TEST(resize_negative_length, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr(5);

    bool InvalidArgumentExceptionThrown = false;
    try {
        arr.resize(-1);
    } catch (kogan::InvalidArgumentException &e) {
        InvalidArgumentExceptionThrown = true;
    }
    ASSERT(InvalidArgumentExceptionThrown);
}

TEST(operator_brackets, smart_ptr_dynamic_array_test_suite) {
    kogan::SmartPtrDynamicArray<int> arr(5);
    for (int i = 0; i < 5; ++i) arr[i] = i + 1;
    ASSERT(arr[0] == 1);
    ASSERT(arr[1] == 2);
    ASSERT(arr[2] == 3);
    ASSERT(arr[3] == 4);
    ASSERT(arr[4] == 5);
    arr[0] = 42;
    ASSERT(arr[0] == 42);
    ASSERT(arr[1] == 2);
    ASSERT(arr[2] == 3);
    ASSERT(arr[3] == 4);
    ASSERT(arr[4] == 5);
}

TEST(copy_assignment, smart_ptr_dynamic_array_test_suite) {
    auto data = kogan::make_shared<int[]>(5);
    for (int i = 0; i < 5; ++i) data[i] = i + 1;
    kogan::SmartPtrDynamicArray<int> arr1(data, 5);

    auto arr2 = arr1;
    ASSERT(arr1.get_length() == arr2.get_length());
    ASSERT(arr1.get_length() == 5);
    ASSERT(arr1[0] == arr2[0]);
    ASSERT(arr1[0] == 1);
    ASSERT(arr1[4] == arr2[4]);
    ASSERT(arr1[4] == 5);

    kogan::SmartPtrDynamicArray<int> arr3;
    arr2 = arr3;
    ASSERT(arr2.get_length() == arr3.get_length());
    ASSERT(arr2.get_length() == 0);
    ASSERT(arr1.get_length() == 5);
}

kogan::TestSuite get_smart_ptr_dynamic_array_test_suite() { return smart_ptr_dynamic_array_test_suite; }