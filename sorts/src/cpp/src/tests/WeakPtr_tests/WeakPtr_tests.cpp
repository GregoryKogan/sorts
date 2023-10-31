#include "WeakPtr_tests.hpp"

kogan::TestSuite weak_ptr_test_suite("WeakPtr");

struct TestObject {
    int value;
    TestObject() : value(0) {}
    TestObject(int value) : value(value) {}
};

TEST(default_constructor, weak_ptr_test_suite) {
    kogan::WeakPtr<TestObject> ptr;
    ASSERT(ptr.use_count() == 0);

    auto shared = ptr.lock();
    ASSERT(shared.use_count() == 0);
    ASSERT(shared.get() == nullptr);
}

TEST(default_constructor_array, weak_ptr_test_suite) {
    kogan::WeakPtr<TestObject[]> ptr;
    ASSERT(ptr.use_count() == 0);

    auto shared = ptr.lock();
    ASSERT(shared.use_count() == 0);
    ASSERT(shared.get() == nullptr);
}

TEST(copy_constructor, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    kogan::WeakPtr<TestObject> ptr(shared);
    ASSERT(ptr.use_count() == 1);

    kogan::WeakPtr<TestObject> ptr2(ptr);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr.lock()->value == 42);
    ASSERT(ptr2.lock()->value == 42);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.use_count() == 1);
}

TEST(copy_constructor_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    ASSERT(ptr.use_count() == 1);

    kogan::WeakPtr<TestObject[]> ptr2(ptr);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr.lock()[0].value == 1);
    ASSERT(ptr.lock()[1].value == 2);
    ASSERT(ptr.lock()[2].value == 3);
    ASSERT(ptr2.lock()[0].value == 1);
    ASSERT(ptr2.lock()[1].value == 2);
    ASSERT(ptr2.lock()[2].value == 3);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.use_count() == 1);
}

TEST(constructor_from_shared_ptr, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    kogan::WeakPtr<TestObject> ptr(shared);
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr.lock()->value == 42);
    ASSERT(ptr.use_count() == 1);
}

TEST(constructor_from_shared_ptr_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr.lock()[0].value == 1);
    ASSERT(ptr.lock()[1].value == 2);
    ASSERT(ptr.lock()[2].value == 3);
    ASSERT(ptr.use_count() == 1);
}

TEST(move_constructor, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    kogan::WeakPtr<TestObject> ptr(shared);
    kogan::WeakPtr<TestObject> ptr2(std::move(ptr));
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.use_count() == 0);
    ASSERT(ptr.lock().get() == nullptr);
    ASSERT(ptr2.lock()->value == 42);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.use_count() == 0);
}

TEST(move_constructor_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    kogan::WeakPtr<TestObject[]> ptr2(std::move(ptr));
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.use_count() == 0);
    ASSERT(ptr.lock().get() == nullptr);
    ASSERT(ptr2.lock()[0].value == 1);
    ASSERT(ptr2.lock()[1].value == 2);
    ASSERT(ptr2.lock()[2].value == 3);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.use_count() == 0);
}

TEST(copy_assignment, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    kogan::WeakPtr<TestObject> ptr(shared);
    kogan::WeakPtr<TestObject> ptr2;
    ptr2 = ptr;
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr.lock()->value == 42);
    ASSERT(ptr2.lock()->value == 42);
}

TEST(copy_assignment_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    kogan::WeakPtr<TestObject[]> ptr2;
    ptr2 = ptr;
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr.lock()[0].value == 1);
    ASSERT(ptr.lock()[1].value == 2);
    ASSERT(ptr.lock()[2].value == 3);
    ASSERT(ptr2.lock()[0].value == 1);
    ASSERT(ptr2.lock()[1].value == 2);
    ASSERT(ptr2.lock()[2].value == 3);
}

TEST(copy_assignment_right_empty, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    kogan::WeakPtr<TestObject> ptr(shared);
    kogan::WeakPtr<TestObject> ptr2;
    ptr = ptr2;
    ASSERT(ptr2.use_count() == 0);
    ASSERT(ptr.use_count() == 0);
    ASSERT(ptr.lock().get() == nullptr);
    ASSERT(ptr2.lock().get() == nullptr);
}

TEST(copy_assignment_right_empty_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    kogan::WeakPtr<TestObject[]> ptr2;
    ptr = ptr2;
    ASSERT(ptr2.use_count() == 0);
    ASSERT(ptr.use_count() == 0);
    ASSERT(ptr.lock().get() == nullptr);
    ASSERT(ptr2.lock().get() == nullptr);
}

TEST(copy_assignment_both_empty, weak_ptr_test_suite) {
    kogan::WeakPtr<TestObject> ptr;
    kogan::WeakPtr<TestObject> ptr2;
    ptr2 = ptr;
    ASSERT(ptr2.use_count() == 0);
    ASSERT(ptr.use_count() == 0);
    ASSERT(ptr.lock().get() == nullptr);
    ASSERT(ptr2.lock().get() == nullptr);
}

TEST(copy_assignment_both_empty_array, weak_ptr_test_suite) {
    kogan::WeakPtr<TestObject[]> ptr;
    kogan::WeakPtr<TestObject[]> ptr2;
    ptr2 = ptr;
    ASSERT(ptr2.use_count() == 0);
    ASSERT(ptr.use_count() == 0);
    ASSERT(ptr.lock().get() == nullptr);
    ASSERT(ptr2.lock().get() == nullptr);
}

TEST(assignment_from_shared_ptr, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    kogan::WeakPtr<TestObject> ptr;
    ptr = shared;
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr.lock()->value == 42);
}

TEST(assignment_from_shared_ptr_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::WeakPtr<TestObject[]> ptr;
    ptr = shared;
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr.lock()[0].value == 1);
    ASSERT(ptr.lock()[1].value == 2);
    ASSERT(ptr.lock()[2].value == 3);
}

TEST(move_assignment, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    kogan::WeakPtr<TestObject> ptr(shared);
    kogan::WeakPtr<TestObject> ptr2;
    ptr2 = std::move(ptr);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.use_count() == 0);
    ASSERT(ptr.lock().get() == nullptr);
    ASSERT(ptr2.lock()->value == 42);
}

TEST(move_assignment_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    kogan::WeakPtr<TestObject[]> ptr2;
    ptr2 = std::move(ptr);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.use_count() == 0);
    ASSERT(ptr.lock().get() == nullptr);
    ASSERT(ptr2.lock()[0].value == 1);
    ASSERT(ptr2.lock()[1].value == 2);
    ASSERT(ptr2.lock()[2].value == 3);
}

TEST(assignment_from_nullptr, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    kogan::WeakPtr<TestObject> ptr(shared);
    ptr = nullptr;
    ASSERT(ptr.use_count() == 0);
    ASSERT(ptr.lock().get() == nullptr);
}

TEST(assignment_from_nullptr_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    ptr = nullptr;
    ASSERT(ptr.use_count() == 0);
    ASSERT(ptr.lock().get() == nullptr);
}

TEST(reset, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    kogan::WeakPtr<TestObject> ptr(shared);
    ptr.reset();
    ASSERT(ptr.use_count() == 0);
    ASSERT(ptr.lock().get() == nullptr);
}

TEST(reset_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    ptr.reset();
    ASSERT(ptr.use_count() == 0);
    ASSERT(ptr.lock().get() == nullptr);
}

TEST(swap, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    auto shared2 = kogan::make_shared<TestObject>(43);
    kogan::WeakPtr<TestObject> ptr(shared);
    kogan::WeakPtr<TestObject> ptr2(shared2);
    ptr.swap(ptr2);
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.lock()->value == 43);
    ASSERT(ptr2.lock()->value == 42);
}

TEST(swap_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    TestObject* obj2 = new TestObject[3]{4, 5, 6};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::SharedPtr<TestObject[]> shared2(obj2);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    kogan::WeakPtr<TestObject[]> ptr2(shared2);
    ptr.swap(ptr2);
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.lock()[0].value == 4);
    ASSERT(ptr.lock()[1].value == 5);
    ASSERT(ptr.lock()[2].value == 6);
    ASSERT(ptr2.lock()[0].value == 1);
    ASSERT(ptr2.lock()[1].value == 2);
    ASSERT(ptr2.lock()[2].value == 3);
}

TEST(swap_function, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    auto shared2 = kogan::make_shared<TestObject>(43);
    kogan::WeakPtr<TestObject> ptr(shared);
    kogan::WeakPtr<TestObject> ptr2(shared2);
    swap(ptr, ptr2);
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.lock()->value == 43);
    ASSERT(ptr2.lock()->value == 42);
}

TEST(swap_function_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    TestObject* obj2 = new TestObject[3]{4, 5, 6};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::SharedPtr<TestObject[]> shared2(obj2);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    kogan::WeakPtr<TestObject[]> ptr2(shared2);
    swap(ptr, ptr2);
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr.lock()[0].value == 4);
    ASSERT(ptr.lock()[1].value == 5);
    ASSERT(ptr.lock()[2].value == 6);
    ASSERT(ptr2.lock()[0].value == 1);
    ASSERT(ptr2.lock()[1].value == 2);
    ASSERT(ptr2.lock()[2].value == 3);
}

TEST(use_count, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    kogan::WeakPtr<TestObject> ptr(shared);
    ASSERT(ptr.use_count() == 1);
    auto shared2 = ptr.lock();
    ASSERT(ptr.use_count() == 2);
    ASSERT(shared.use_count() == 2);
    ASSERT(shared2.use_count() == 2);
}

TEST(use_count_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    ASSERT(ptr.use_count() == 1);
    auto shared2 = ptr.lock();
    ASSERT(ptr.use_count() == 2);
    ASSERT(shared.use_count() == 2);
    ASSERT(shared2.use_count() == 2);
}

TEST(expired, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    kogan::WeakPtr<TestObject> ptr(shared);
    ASSERT(!ptr.expired());
    auto shared2 = ptr.lock();
    ASSERT(!ptr.expired());
    ASSERT(shared.use_count() == 2);
    ASSERT(shared2.use_count() == 2);
    shared.reset();
    ASSERT(!ptr.expired());
    ASSERT(shared.use_count() == 0);
    ASSERT(shared2.use_count() == 1);
    shared2.reset();
    ASSERT(ptr.expired());
    ASSERT(shared.use_count() == 0);
    ASSERT(shared2.use_count() == 0);
}

TEST(expired_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    ASSERT(!ptr.expired());
    auto shared2 = ptr.lock();
    ASSERT(!ptr.expired());
    ASSERT(shared.use_count() == 2);
    ASSERT(shared2.use_count() == 2);
    shared.reset();
    ASSERT(!ptr.expired());
    ASSERT(shared.use_count() == 0);
    ASSERT(shared2.use_count() == 1);
    shared2.reset();
    ASSERT(ptr.expired());
    ASSERT(shared.use_count() == 0);
    ASSERT(shared2.use_count() == 0);
}

TEST(lock, weak_ptr_test_suite) {
    auto shared = kogan::make_shared<TestObject>(42);
    kogan::WeakPtr<TestObject> ptr(shared);
    auto shared2 = ptr.lock();
    ASSERT(shared.use_count() == 2);
    ASSERT(shared2.use_count() == 2);
    ASSERT(shared2->value == 42);
}

TEST(lock_array, weak_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> shared(obj);
    kogan::WeakPtr<TestObject[]> ptr(shared);
    auto shared2 = ptr.lock();
    ASSERT(shared.use_count() == 2);
    ASSERT(shared2.use_count() == 2);
    ASSERT(shared2[0].value == 1);
    ASSERT(shared2[1].value == 2);
    ASSERT(shared2[2].value == 3);
}

kogan::TestSuite get_weak_ptr_test_suite() { return weak_ptr_test_suite; }