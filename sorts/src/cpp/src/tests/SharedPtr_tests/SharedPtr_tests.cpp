#include "SharedPtr_tests.hpp"

kogan::TestSuite shared_ptr_test_suite("SharedPtr");

struct TestObject {
    int value;
    TestObject() : value(0) {}
    TestObject(int value) : value(value) {}
};

TEST(default_constructor, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr;
    ASSERT(ptr.get() == nullptr);
    ASSERT(ptr.use_count() == 0);
}

TEST(default_constructor_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr;
    ASSERT(ptr.get() == nullptr);
    ASSERT(ptr.use_count() == 0);
}

TEST(constructor_from_pointer, shared_ptr_test_suite) {
    TestObject* obj = new TestObject(42);
    kogan::SharedPtr<TestObject> ptr(obj);
    ASSERT(ptr.get() == obj);
    ASSERT(ptr->value == 42);
    ASSERT(ptr.use_count() == 1);
}

TEST(constructor_from_pointer_array, shared_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> ptr(obj);
    ASSERT(ptr.get() == obj);
    ASSERT(ptr[0].value == 1);
    ASSERT(ptr[1].value == 2);
    ASSERT(ptr[2].value == 3);
    ASSERT(ptr.use_count() == 1);
}

TEST(copy_constructor, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1(new TestObject(42));
    kogan::SharedPtr<TestObject> ptr2(ptr1);
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
}

TEST(copy_constructor_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::SharedPtr<TestObject[]> ptr2(ptr1);
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
}

TEST(constructor_from_weak_ptr, shared_ptr_test_suite) {
    kogan::WeakPtr<TestObject> weak_ptr;
    ASSERT(weak_ptr.use_count() == 0);
    ASSERT(weak_ptr.expired());
    {
        auto ptr1 = kogan::make_shared<TestObject>(42);
        weak_ptr = ptr1;
        ASSERT(weak_ptr.use_count() == 1);
        ASSERT(weak_ptr.lock().get() == ptr1.get());
        kogan::SharedPtr<TestObject> ptr2(weak_ptr);
        ASSERT(ptr1.get() == ptr2.get());
        ASSERT(weak_ptr.lock().get() == ptr1.get());
        ASSERT(ptr1.use_count() == 2);
        ASSERT(ptr2.use_count() == 2);
        ASSERT(weak_ptr.use_count() == 2);
        ASSERT(!weak_ptr.expired());
        ASSERT(weak_ptr.lock()->value == 42);
        ASSERT(ptr1->value == 42);
        ASSERT(ptr2->value == 42);
    }
    ASSERT(weak_ptr.expired());
    ASSERT(weak_ptr.lock().get() == nullptr);
}

TEST(constructor_from_weak_ptr_array, shared_ptr_test_suite) {
    kogan::WeakPtr<TestObject[]> weak_ptr;
    ASSERT(weak_ptr.use_count() == 0);
    ASSERT(weak_ptr.expired());
    {
        kogan::SharedPtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
        weak_ptr = ptr1;
        ASSERT(weak_ptr.use_count() == 1);
        ASSERT(weak_ptr.lock().get() == ptr1.get());
        kogan::SharedPtr<TestObject[]> ptr2(weak_ptr);
        ASSERT(ptr1.get() == ptr2.get());
        ASSERT(weak_ptr.lock().get() == ptr1.get());
        ASSERT(ptr1.use_count() == 2);
        ASSERT(ptr2.use_count() == 2);
        ASSERT(weak_ptr.use_count() == 2);
        ASSERT(!weak_ptr.expired());
        ASSERT(weak_ptr.lock()[0].value == 1);
        ASSERT(weak_ptr.lock()[1].value == 2);
        ASSERT(weak_ptr.lock()[2].value == 3);
        ASSERT(ptr1[0].value == 1);
        ASSERT(ptr1[1].value == 2);
        ASSERT(ptr1[2].value == 3);
        ASSERT(ptr2[0].value == 1);
        ASSERT(ptr2[1].value == 2);
        ASSERT(ptr2[2].value == 3);
    }
    ASSERT(weak_ptr.expired());
    ASSERT(weak_ptr.lock().get() == nullptr);
}

TEST(move_constructor, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1(new TestObject(42));
    kogan::SharedPtr<TestObject> ptr2(std::move(ptr1));
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2->value == 42);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr1.use_count() == 0);
}

TEST(move_constructor_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::SharedPtr<TestObject[]> ptr2(std::move(ptr1));
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2[0].value == 1);
    ASSERT(ptr2[1].value == 2);
    ASSERT(ptr2[2].value == 3);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr1.use_count() == 0);
}

TEST(copy_assignment, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1(new TestObject(42));
    kogan::SharedPtr<TestObject> ptr2;
    ptr2 = ptr1;
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(ptr1->value == 42);
}

TEST(copy_assignment_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::SharedPtr<TestObject[]> ptr2;
    ptr2 = ptr1;
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(ptr1[0].value == 1);
    ASSERT(ptr1[1].value == 2);
    ASSERT(ptr1[2].value == 3);
}

TEST(move_assignment, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1(new TestObject(42));
    kogan::SharedPtr<TestObject> ptr2;
    ptr2 = std::move(ptr1);
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2.get()->value == 42);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr1.use_count() == 0);
}

TEST(move_assignment_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::SharedPtr<TestObject[]> ptr2;
    ptr2 = std::move(ptr1);
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2[0].value == 1);
    ASSERT(ptr2[1].value == 2);
    ASSERT(ptr2[2].value == 3);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr1.use_count() == 0);
}

TEST(reset, shared_ptr_test_suite) {
    kogan::SharedPtr<int> ptr1(new int(42));
    kogan::SharedPtr<int> ptr2(ptr1);
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(*ptr1 == 42);
    ASSERT(*ptr2 == 42);

    ptr2.reset(new int(43));
    ASSERT(ptr1.use_count() == 1);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(*ptr1 == 42);
    ASSERT(*ptr2 == 43);
}

TEST(reset_array, shared_ptr_test_suite) {
    kogan::SharedPtr<int[]> ptr1(new int[3]{1, 2, 3});
    kogan::SharedPtr<int[]> ptr2(ptr1);
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(ptr1[0] == 1);
    ASSERT(ptr1[1] == 2);
    ASSERT(ptr1[2] == 3);
    ASSERT(ptr2[0] == 1);
    ASSERT(ptr2[1] == 2);
    ASSERT(ptr2[2] == 3);

    ptr2.reset(new int[3]{4, 5, 6});
    ASSERT(ptr1.use_count() == 1);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr1[0] == 1);
    ASSERT(ptr1[1] == 2);
    ASSERT(ptr1[2] == 3);
    ASSERT(ptr2[0] == 4);
    ASSERT(ptr2[1] == 5);
    ASSERT(ptr2[2] == 6);
}

TEST(reset_nullptr, shared_ptr_test_suite) {
    kogan::SharedPtr<int> ptr1(new int(42));
    kogan::SharedPtr<int> ptr2(ptr1);
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(*ptr1 == 42);
    ASSERT(*ptr2 == 42);

    ptr2.reset(nullptr);
    ASSERT(ptr1.use_count() == 1);
    ASSERT(ptr2.use_count() == 0);
    ASSERT(*ptr1 == 42);
    ASSERT(ptr2.get() == nullptr);
    ASSERT(!ptr2);
    ASSERT(ptr1);
}

TEST(reset_nullptr_array, shared_ptr_test_suite) {
    kogan::SharedPtr<int[]> ptr1(new int[3]{1, 2, 3});
    kogan::SharedPtr<int[]> ptr2(ptr1);
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(ptr1[0] == 1);
    ASSERT(ptr1[1] == 2);
    ASSERT(ptr1[2] == 3);
    ASSERT(ptr2[0] == 1);
    ASSERT(ptr2[1] == 2);
    ASSERT(ptr2[2] == 3);

    ptr2.reset(nullptr);
    ASSERT(ptr1.use_count() == 1);
    ASSERT(ptr2.use_count() == 0);
    ASSERT(ptr1[0] == 1);
    ASSERT(ptr1[1] == 2);
    ASSERT(ptr1[2] == 3);
    ASSERT(ptr2.get() == nullptr);
    ASSERT(!ptr2);
    ASSERT(ptr1);
}

TEST(reset_empty, shared_ptr_test_suite) {
    kogan::SharedPtr<int> ptr1(new int(42));
    kogan::SharedPtr<int> ptr2(ptr1);
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(*ptr1 == 42);
    ASSERT(*ptr2 == 42);

    ptr2.reset();
    ASSERT(ptr1.use_count() == 1);
    ASSERT(ptr2.use_count() == 0);
    ASSERT(*ptr1 == 42);
    ASSERT(ptr2.get() == nullptr);
    ASSERT(!ptr2);
    ASSERT(ptr1);
}

TEST(reset_empty_array, shared_ptr_test_suite) {
    kogan::SharedPtr<int[]> ptr1(new int[3]{1, 2, 3});
    kogan::SharedPtr<int[]> ptr2(ptr1);
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(ptr1[0] == 1);
    ASSERT(ptr1[1] == 2);
    ASSERT(ptr1[2] == 3);
    ASSERT(ptr2[0] == 1);
    ASSERT(ptr2[1] == 2);
    ASSERT(ptr2[2] == 3);

    ptr2.reset();
    ASSERT(ptr1.use_count() == 1);
    ASSERT(ptr2.use_count() == 0);
    ASSERT(ptr1[0] == 1);
    ASSERT(ptr1[1] == 2);
    ASSERT(ptr1[2] == 3);
    ASSERT(ptr2.get() == nullptr);
    ASSERT(!ptr2);
    ASSERT(ptr1);
}

TEST(assignment_from_nullptr, shared_ptr_test_suite) {
    kogan::SharedPtr<int> ptr1(new int(42));
    kogan::SharedPtr<int> ptr2(ptr1);
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(*ptr1 == 42);
    ASSERT(*ptr2 == 42);

    ptr2 = nullptr;
    ASSERT(ptr1.use_count() == 1);
    ASSERT(ptr2.use_count() == 0);
    ASSERT(*ptr1 == 42);
    ASSERT(ptr2.get() == nullptr);
    ASSERT(!ptr2);
    ASSERT(ptr1);
}

TEST(assignment_from_nullptr_array, shared_ptr_test_suite) {
    kogan::SharedPtr<int[]> ptr1(new int[3]{1, 2, 3});
    kogan::SharedPtr<int[]> ptr2(ptr1);
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(ptr1[0] == 1);
    ASSERT(ptr1[1] == 2);
    ASSERT(ptr1[2] == 3);
    ASSERT(ptr2[0] == 1);
    ASSERT(ptr2[1] == 2);
    ASSERT(ptr2[2] == 3);

    ptr2 = nullptr;
    ASSERT(ptr1.use_count() == 1);
    ASSERT(ptr2.use_count() == 0);
    ASSERT(ptr1[0] == 1);
    ASSERT(ptr1[1] == 2);
    ASSERT(ptr1[2] == 3);
    ASSERT(ptr2.get() == nullptr);
    ASSERT(!ptr2);
    ASSERT(ptr1);
}

TEST(swap, shared_ptr_test_suite) {
    auto ptr1 = kogan::make_shared<TestObject>(42);
    auto ptr2 = kogan::make_shared<TestObject>(43);

    ptr1.swap(ptr2);
    ASSERT(ptr1->value == 43);
    ASSERT(ptr2->value == 42);
    ASSERT(ptr1.use_count() == 1);
    ASSERT(ptr2.use_count() == 1);

    ptr1.reset();
    ptr1.swap(ptr2);
    ASSERT(ptr1->value == 42);
    ASSERT(ptr2.use_count() == 0);
    ASSERT(ptr1.use_count() == 1);
}

TEST(swap_array, shared_ptr_test_suite) {
    auto ptr1 = kogan::make_shared<TestObject[]>(3);
    auto ptr2 = kogan::make_shared<TestObject[]>(3);
    for (int i = 0; i < 3; ++i) {
        ptr1[i].value = i + 1;
        ptr2[i].value = i + 4;
    }

    ptr1.swap(ptr2);
    ASSERT(ptr1[0].value == 4);
    ASSERT(ptr1[1].value == 5);
    ASSERT(ptr1[2].value == 6);
    ASSERT(ptr2[0].value == 1);
    ASSERT(ptr2[1].value == 2);
    ASSERT(ptr2[2].value == 3);
    ASSERT(ptr1.use_count() == 1);
    ASSERT(ptr2.use_count() == 1);

    ptr1.reset();
    ptr1.swap(ptr2);
    ASSERT(ptr1[0].value == 1);
    ASSERT(ptr1[1].value == 2);
    ASSERT(ptr1[2].value == 3);
    ASSERT(ptr2.use_count() == 0);
    ASSERT(ptr1.use_count() == 1);
}

TEST(swap_function, shared_ptr_test_suite) {
    auto ptr1 = kogan::make_shared<TestObject>(42);
    auto ptr2 = kogan::make_shared<TestObject>(43);

    swap(ptr1, ptr2);
    ASSERT(ptr1->value == 43);
    ASSERT(ptr2->value == 42);
    ASSERT(ptr1.use_count() == 1);
    ASSERT(ptr2.use_count() == 1);

    ptr1.reset();
    swap(ptr1, ptr2);
    ASSERT(ptr1->value == 42);
    ASSERT(ptr2.use_count() == 0);
    ASSERT(ptr1.use_count() == 1);
}

TEST(swap_function_array, shared_ptr_test_suite) {
    auto ptr1 = kogan::make_shared<TestObject[]>(3);
    auto ptr2 = kogan::make_shared<TestObject[]>(3);
    for (int i = 0; i < 3; ++i) {
        ptr1[i].value = i + 1;
        ptr2[i].value = i + 4;
    }

    swap(ptr1, ptr2);
    ASSERT(ptr1[0].value == 4);
    ASSERT(ptr1[1].value == 5);
    ASSERT(ptr1[2].value == 6);
    ASSERT(ptr2[0].value == 1);
    ASSERT(ptr2[1].value == 2);
    ASSERT(ptr2[2].value == 3);
    ASSERT(ptr1.use_count() == 1);
    ASSERT(ptr2.use_count() == 1);

    ptr1.reset();
    swap(ptr1, ptr2);
    ASSERT(ptr1[0].value == 1);
    ASSERT(ptr1[1].value == 2);
    ASSERT(ptr1[2].value == 3);
    ASSERT(ptr2.use_count() == 0);
    ASSERT(ptr1.use_count() == 1);
}

TEST(unique, shared_ptr_test_suite) {
    auto ptr1 = kogan::make_shared<TestObject>(42);
    ASSERT(ptr1.unique());
    kogan::SharedPtr<TestObject> ptr2(ptr1);
    ASSERT(!ptr1.unique());
    ASSERT(!ptr2.unique());
}

TEST(unique_array, shared_ptr_test_suite) {
    auto ptr1 = kogan::make_shared<TestObject[]>(3);
    ASSERT(ptr1.unique());
    kogan::SharedPtr<TestObject[]> ptr2(ptr1);
    ASSERT(!ptr1.unique());
    ASSERT(!ptr2.unique());
}

TEST(equality_operator, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1(new TestObject(42));
    kogan::SharedPtr<TestObject> ptr2(ptr1);
    kogan::SharedPtr<TestObject> ptr3(new TestObject(42));
    ASSERT(ptr1 == ptr2);
    ASSERT(ptr1 != ptr3);
    ASSERT(ptr2 != ptr3);
    ASSERT(ptr1 == ptr1);
    ASSERT(ptr2 == ptr2);
    ASSERT(ptr3 == ptr3);

    kogan::SharedPtr<TestObject> ptr4;
    kogan::SharedPtr<TestObject> ptr5;
    ASSERT(ptr4 == ptr5);
    ASSERT(ptr4 == nullptr);
    ASSERT(nullptr == ptr4);
    ASSERT(ptr5 == nullptr);
    ASSERT(nullptr == ptr5);
    ASSERT(ptr4 == ptr4);
    ASSERT(ptr5 == ptr5);
    ASSERT(ptr4 != ptr1);
    ASSERT(ptr5 != ptr1);
    ASSERT(ptr1 != ptr4);
    ASSERT(ptr1 != ptr5);

    kogan::SharedPtr<TestObject> ptr6(new TestObject(42));
    ASSERT(ptr6 != ptr1);
    ASSERT(ptr1 != ptr6);
    ASSERT(ptr6 != ptr4);
    ASSERT(ptr4 != ptr6);
    ASSERT(ptr6 != nullptr);
    ASSERT(nullptr != ptr6);

    ptr6 = nullptr;
    ASSERT(ptr6 == nullptr);
    ASSERT(nullptr == ptr6);
    ASSERT(ptr6 == ptr6);
    ASSERT(ptr6 != ptr1);
    ASSERT(ptr1 != ptr6);
    ASSERT(ptr6 == ptr4);
    ASSERT(ptr4 == ptr6);
}

TEST(equality_operator_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::SharedPtr<TestObject[]> ptr2(ptr1);
    kogan::SharedPtr<TestObject[]> ptr3(new TestObject[3]{1, 2, 3});
    ASSERT(ptr1 == ptr2);
    ASSERT(ptr1 != ptr3);
    ASSERT(ptr2 != ptr3);
    ASSERT(ptr1 == ptr1);
    ASSERT(ptr2 == ptr2);
    ASSERT(ptr3 == ptr3);

    kogan::SharedPtr<TestObject[]> ptr4;
    kogan::SharedPtr<TestObject[]> ptr5;
    ASSERT(ptr4 == ptr5);
    ASSERT(ptr4 == nullptr);
    ASSERT(nullptr == ptr4);
    ASSERT(ptr5 == nullptr);
    ASSERT(nullptr == ptr5);
    ASSERT(ptr4 == ptr4);
    ASSERT(ptr5 == ptr5);
    ASSERT(ptr4 != ptr1);
    ASSERT(ptr5 != ptr1);
    ASSERT(ptr1 != ptr4);
    ASSERT(ptr1 != ptr5);

    kogan::SharedPtr<TestObject[]> ptr6(new TestObject[3]{1, 2, 3});
    ASSERT(ptr6 != ptr1);
    ASSERT(ptr1 != ptr6);
    ASSERT(ptr6 != ptr4);
    ASSERT(ptr4 != ptr6);
    ASSERT(ptr6 != nullptr);
    ASSERT(nullptr != ptr6);

    ptr6 = nullptr;
    ASSERT(ptr6 == nullptr);
    ASSERT(nullptr == ptr6);
    ASSERT(ptr6 == ptr6);
    ASSERT(ptr6 != ptr1);
    ASSERT(ptr1 != ptr6);
    ASSERT(ptr6 == ptr4);
    ASSERT(ptr4 == ptr6);
}

TEST(make_shared, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr = kogan::make_shared<TestObject>(42);
    ASSERT(ptr.get()->value == 42);
    ASSERT(ptr.use_count() == 1);
}

TEST(make_shared_with_custom_constructor, shared_ptr_test_suite) {
    kogan::SharedPtr<std::string> ptr = kogan::make_shared<std::string>("Hello World!");
    ASSERT(ptr->compare("Hello World!") == 0);
    ASSERT(ptr.use_count() == 1);
}

TEST(make_shared_with_multiple_arguments, shared_ptr_test_suite) {
    std::vector<int> expected = {1, 2, 3};
    kogan::SharedPtr<std::vector<int>> ptr = kogan::make_shared<std::vector<int>>(expected.begin(), expected.end());
    ASSERT(*ptr == expected);
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr->size() == 3);
    ASSERT(ptr->at(0) == 1);
    ASSERT(ptr->at(1) == 2);
    ASSERT(ptr->at(2) == 3);
}

TEST(make_shared_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr = kogan::make_shared<TestObject[]>(3);
    ptr[0].value = 1;
    ptr[1].value = 2;
    ptr[2].value = 3;
    ASSERT(ptr[0].value == 1);
    ASSERT(ptr[1].value == 2);
    ASSERT(ptr[2].value == 3);
    ASSERT(ptr.use_count() == 1);
}

TEST(operator_bool, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1;
    kogan::SharedPtr<TestObject> ptr2(new TestObject(42));
    ASSERT(!ptr1);
    ASSERT(ptr2);
}

TEST(operator_bool_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1;
    kogan::SharedPtr<TestObject[]> ptr2(new TestObject[3]{1, 2, 3});
    ASSERT(!ptr1);
    ASSERT(ptr2);
}

TEST(get, shared_ptr_test_suite) {
    TestObject* obj = new TestObject(42);
    kogan::SharedPtr<TestObject> ptr(obj);
    ASSERT(ptr.get() == obj);
}

TEST(get_array, shared_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> ptr(obj);
    ASSERT(ptr.get() == obj);
}

TEST(operator_arrow, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr(new TestObject(42));
    ASSERT(ptr->value == 42);
}

TEST(operator_star, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr(new TestObject(42));
    ASSERT((*ptr).value == 42);
}

TEST(use_count, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1(new TestObject(42));
    kogan::SharedPtr<TestObject> ptr2(ptr1);
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    kogan::SharedPtr<TestObject> ptr3(std::move(ptr1));
    ASSERT(ptr1.use_count() == 0);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(ptr3.use_count() == 2);
}

TEST(use_count_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::SharedPtr<TestObject[]> ptr2(ptr1);
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    kogan::SharedPtr<TestObject[]> ptr3(std::move(ptr1));
    ASSERT(ptr1.use_count() == 0);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(ptr3.use_count() == 2);
}

kogan::TestSuite get_shared_ptr_test_suite() { return shared_ptr_test_suite; }
