#include "UniquePtr_tests.hpp"

kogan::TestSuite unique_ptr_test_suite("UniquePtr");

struct TestObject {
    int value;
    TestObject() : value(0) {}
    TestObject(int value) : value(value) {}
};

TEST(default_constructor, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr;
    ASSERT(ptr.get() == nullptr);
}

TEST(default_constructor_array, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject[]> ptr;
    ASSERT(ptr.get() == nullptr);
}

TEST(constructor_from_pointer, unique_ptr_test_suite) {
    TestObject* obj = new TestObject(42);
    kogan::UniquePtr<TestObject> ptr(obj);
    ASSERT(ptr.get() == obj);
}

TEST(constructor_from_pointer_array, unique_ptr_test_suite) {
    TestObject* obj_arr = new TestObject[3]{1, 2, 3};
    kogan::UniquePtr<TestObject[]> ptr(obj_arr);
    ASSERT(ptr.get() == obj_arr);
    ASSERT(ptr[0].value == 1);
    ASSERT(ptr[1].value == 2);
    ASSERT(ptr[2].value == 3);
}

TEST(move_constructor, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr1(new TestObject(42));
    kogan::UniquePtr<TestObject> ptr2(std::move(ptr1));
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2.get()->value == 42);
}

TEST(move_constructor_array, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::UniquePtr<TestObject[]> ptr2(std::move(ptr1));
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2[0].value == 1);
    ASSERT(ptr2[1].value == 2);
    ASSERT(ptr2[2].value == 3);
}

TEST(move_assignment, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr1(new TestObject(42));
    kogan::UniquePtr<TestObject> ptr2;
    ptr2 = std::move(ptr1);
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2.get()->value == 42);
}

TEST(move_assignment_array, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::UniquePtr<TestObject[]> ptr2;
    ptr2 = std::move(ptr1);
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2[0].value == 1);
    ASSERT(ptr2[1].value == 2);
    ASSERT(ptr2[2].value == 3);
}

TEST(copy_constructor, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr1(new TestObject(42));
    // kogan::UniquePtr<TestObject> ptr2(ptr1);  // should not compile
}

TEST(copy_constructor_array, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    // kogan::UniquePtr<TestObject[]> ptr2(ptr1);  // should not compile
}

TEST(copy_assignment, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr1(new TestObject(42));
    kogan::UniquePtr<TestObject> ptr2;
    // ptr2 = ptr1;  // should not compile
}

TEST(copy_assignment_array, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::UniquePtr<TestObject[]> ptr2;
    // ptr2 = ptr1;  // should not compile
}

TEST(assignment_from_nullptr, unique_ptr_test_suite) {
    TestObject* obj = new TestObject(42);
    kogan::UniquePtr<TestObject> ptr(obj);
    ptr = nullptr;
    ASSERT(ptr.get() == nullptr);
}

TEST(assignment_from_nullptr_array, unique_ptr_test_suite) {
    TestObject* obj_arr = new TestObject[3]{1, 2, 3};
    kogan::UniquePtr<TestObject[]> ptr(obj_arr);
    ptr = nullptr;
    ASSERT(ptr.get() == nullptr);
}

TEST(equality_operator, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr1;
    kogan::UniquePtr<TestObject> ptr2;
    ASSERT(ptr1 == ptr2);
    ASSERT(ptr2 == ptr1);
    ASSERT(ptr1 == nullptr);
    ASSERT(nullptr == ptr1);
    ASSERT(ptr2 == nullptr);
    ASSERT(nullptr == ptr2);

    TestObject* obj = new TestObject(42);
    ptr1.reset(obj);
    ASSERT(ptr1 == ptr1);
    ASSERT(ptr1 != ptr2);
    ASSERT(ptr2 != ptr1);
    ASSERT(ptr1 != nullptr);
    ASSERT(nullptr != ptr1);
    ASSERT(ptr2 == nullptr);
    ASSERT(nullptr == ptr2);

    TestObject* new_obj = new TestObject(43);
    ptr2.reset(new_obj);
    ASSERT(ptr1 != ptr2);
    ASSERT(ptr2 != ptr1);
    ASSERT(ptr1 != nullptr);
    ASSERT(nullptr != ptr1);
    ASSERT(ptr2 != nullptr);
    ASSERT(nullptr != ptr2);

    ptr1 = nullptr;
    ASSERT(ptr1 != ptr2);
    ASSERT(ptr2 != ptr1);
    ASSERT(ptr1 == nullptr);
    ASSERT(nullptr == ptr1);
    ASSERT(ptr2 != nullptr);
    ASSERT(nullptr != ptr2);

    ptr2 = nullptr;
    ASSERT(ptr1 == ptr2);
    ASSERT(ptr2 == ptr1);
    ASSERT(ptr1 == nullptr);
    ASSERT(nullptr == ptr1);
    ASSERT(ptr2 == nullptr);
    ASSERT(nullptr == ptr2);
}

TEST(equality_operator_array, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject[]> ptr1;
    kogan::UniquePtr<TestObject[]> ptr2;
    ASSERT(ptr1 == ptr2);
    ASSERT(ptr2 == ptr1);
    ASSERT(ptr1 == nullptr);
    ASSERT(nullptr == ptr1);
    ASSERT(ptr2 == nullptr);
    ASSERT(nullptr == ptr2);

    TestObject* obj_arr = new TestObject[3]{1, 2, 3};
    ptr1.reset(obj_arr);
    ASSERT(ptr1 == ptr1);
    ASSERT(ptr1 != ptr2);
    ASSERT(ptr2 != ptr1);
    ASSERT(ptr1 != nullptr);
    ASSERT(nullptr != ptr1);
    ASSERT(ptr2 == nullptr);
    ASSERT(nullptr == ptr2);

    TestObject* new_obj_arr = new TestObject[2]{4, 5};
    ptr2.reset(new_obj_arr);
    ASSERT(ptr1 != ptr2);
    ASSERT(ptr2 != ptr1);
    ASSERT(ptr1 != nullptr);
    ASSERT(nullptr != ptr1);
    ASSERT(ptr2 != nullptr);
    ASSERT(nullptr != ptr2);

    ptr1 = nullptr;
    ASSERT(ptr1 != ptr2);
    ASSERT(ptr2 != ptr1);
    ASSERT(ptr1 == nullptr);
    ASSERT(nullptr == ptr1);
    ASSERT(ptr2 != nullptr);
    ASSERT(nullptr != ptr2);

    ptr2 = nullptr;
    ASSERT(ptr1 == ptr2);
    ASSERT(ptr2 == ptr1);
    ASSERT(ptr1 == nullptr);
    ASSERT(nullptr == ptr1);
    ASSERT(ptr2 == nullptr);
    ASSERT(nullptr == ptr2);
}

TEST(make_unique, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr = kogan::make_unique<TestObject>(42);
    ASSERT(ptr.get()->value == 42);
}

TEST(make_unique_with_custom_constructor, unique_ptr_test_suite) {
    kogan::UniquePtr<std::string> ptr = kogan::make_unique<std::string>("Hello World!");
    ASSERT(ptr->compare("Hello World!") == 0);
}

TEST(make_unique_with_multiple_arguments, unique_ptr_test_suite) {
    std::vector<int> expected = {1, 2, 3};
    kogan::UniquePtr<std::vector<int>> ptr = kogan::make_unique<std::vector<int>>(expected.begin(), expected.end());
    ASSERT(*ptr == expected);
}

TEST(make_unique_array, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject[]> ptr = kogan::make_unique<TestObject[]>(3);
    ptr[0].value = 1;
    ptr[1].value = 2;
    ptr[2].value = 3;
    ASSERT(ptr[0].value == 1);
    ASSERT(ptr[1].value == 2);
    ASSERT(ptr[2].value == 3);
}

TEST(release, unique_ptr_test_suite) {
    TestObject* obj = new TestObject(42);
    kogan::UniquePtr<TestObject> ptr(obj);
    TestObject* released_obj = ptr.release();
    ASSERT(ptr.get() == nullptr);
    ASSERT(released_obj == obj);
    delete released_obj;
}

TEST(release_array, unique_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::UniquePtr<TestObject[]> ptr(obj);
    TestObject* released_obj = ptr.release();
    ASSERT(ptr.get() == nullptr);
    ASSERT(released_obj == obj);
    delete[] released_obj;
}

TEST(reset, unique_ptr_test_suite) {
    TestObject* obj1 = new TestObject(42);
    TestObject* obj2 = new TestObject(43);
    kogan::UniquePtr<TestObject> ptr(obj1);
    ptr.reset(obj2);
    ASSERT(ptr.get() == obj2);
}

TEST(reset_array, unique_ptr_test_suite) {
    TestObject* obj1 = new TestObject[3]{1, 2, 3};
    TestObject* obj2 = new TestObject[2]{4, 5};
    kogan::UniquePtr<TestObject[]> ptr(obj1);
    ptr.reset(obj2);
    ASSERT(ptr.get() == obj2);
    ASSERT(ptr[0].value == 4);
    ASSERT(ptr[1].value == 5);
}

TEST(reset_with_nullptr, unique_ptr_test_suite) {
    auto ptr = kogan::make_unique<TestObject>(42);
    ptr.reset(nullptr);
    ASSERT(ptr.get() == nullptr);
}

TEST(reset_with_nullptr_array, unique_ptr_test_suite) {
    auto ptr = kogan::make_unique<TestObject[]>(3);
    ptr.reset(nullptr);
    ASSERT(ptr.get() == nullptr);
}

TEST(swap, unique_ptr_test_suite) {
    TestObject* obj1 = new TestObject(42);
    TestObject* obj2 = new TestObject(43);
    kogan::UniquePtr<TestObject> ptr1(obj1);
    kogan::UniquePtr<TestObject> ptr2(obj2);
    ptr1.swap(ptr2);
    ASSERT(ptr1.get() == obj2);
    ASSERT(ptr2.get() == obj1);
}

TEST(swap_array, unique_ptr_test_suite) {
    TestObject* obj_arr1 = new TestObject[3]{1, 2, 3};
    TestObject* obj_arr2 = new TestObject[2]{4, 5};
    kogan::UniquePtr<TestObject[]> ptr1(obj_arr1);
    kogan::UniquePtr<TestObject[]> ptr2(obj_arr2);
    ptr1.swap(ptr2);
    ASSERT(ptr1.get() == obj_arr2);
    ASSERT(ptr2.get() == obj_arr1);
    ASSERT(ptr1[0].value == 4);
    ASSERT(ptr1[1].value == 5);
    ASSERT(ptr2[0].value == 1);
    ASSERT(ptr2[1].value == 2);
    ASSERT(ptr2[2].value == 3);
}

TEST(swap_function, unique_ptr_test_suite) {
    TestObject* obj1 = new TestObject(42);
    TestObject* obj2 = new TestObject(43);
    kogan::UniquePtr<TestObject> ptr1(obj1);
    kogan::UniquePtr<TestObject> ptr2(obj2);
    swap(ptr1, ptr2);
    ASSERT(ptr1.get() == obj2);
    ASSERT(ptr2.get() == obj1);
}

TEST(swap_function_array, unique_ptr_test_suite) {
    TestObject* obj_arr1 = new TestObject[3]{1, 2, 3};
    TestObject* obj_arr2 = new TestObject[2]{4, 5};
    kogan::UniquePtr<TestObject[]> ptr1(obj_arr1);
    kogan::UniquePtr<TestObject[]> ptr2(obj_arr2);
    swap(ptr1, ptr2);
    ASSERT(ptr1.get() == obj_arr2);
    ASSERT(ptr2.get() == obj_arr1);
    ASSERT(ptr1[0].value == 4);
    ASSERT(ptr1[1].value == 5);
    ASSERT(ptr2[0].value == 1);
    ASSERT(ptr2[1].value == 2);
    ASSERT(ptr2[2].value == 3);
}

TEST(operator_bool, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr1;
    kogan::UniquePtr<TestObject> ptr2(new TestObject(42));
    ASSERT(!ptr1);
    ASSERT(ptr2);
}

TEST(operator_bool_array, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject[]> ptr1;
    kogan::UniquePtr<TestObject[]> ptr2(new TestObject[3]{1, 2, 3});
    ASSERT(!ptr1);
    ASSERT(ptr2);
}

TEST(get, unique_ptr_test_suite) {
    TestObject* obj = new TestObject(42);
    kogan::UniquePtr<TestObject> ptr(obj);
    ASSERT(ptr.get() == obj);
}

TEST(get_array, unique_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::UniquePtr<TestObject[]> ptr(obj);
    ASSERT(ptr.get() == obj);
}

TEST(operator_arrow, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr(new TestObject(42));
    ASSERT(ptr->value == 42);
}

TEST(operator_star, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr(new TestObject(42));
    ASSERT((*ptr).value == 42);
}

TEST(operator_bracket_array, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject[]> ptr(new TestObject[3]{1, 2, 3});
    ASSERT(ptr[0].value == 1);
    ASSERT(ptr[1].value == 2);
    ASSERT(ptr[2].value == 3);
}

kogan::TestSuite get_unique_ptr_test_suite() { return unique_ptr_test_suite; }
