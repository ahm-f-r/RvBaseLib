#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gtest/gtest_prod.h>
#include "RvBaseObject.h"

using namespace std;
/*
// The fixture for testing class Foo.
class RvBaseObjectTest : public testing::Test {
  protected:
    // You can remove any or all of the following functions if their bodies would be empty.
    RvBaseObjectTest() {
      // You can do set-up work for each test here.
      prop0 = new RvBaseObject("uint64_t", 99);
      prop1 = new RvBaseProperty<bool>("bool", true);
      prop2 = new RvBaseProperty<string>("string", "hello");

      prop_b0 = new RvBaseProperty<bool>("kabool", true);
      prop_b1 = prop_b0;
      prop_b2 = new RvBaseProperty<bool>(*prop_b0);
    }

    ~RvBaseObjectTest() override {
      delete prop0;
      delete prop1;
      delete prop2;
      delete prop_b0;
      //delete prop_b1;
      delete prop_b2;
      // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    void SetUp() override {
      // Code here will be called immediately after the constructor (right
      // before each test).
    }

    void TearDown() override {
      if (mDebug) {
        cout << "RvBaseProperty<bool>::RefCount()     = " << prop1->RefCount() << endl;
        cout << "RvBaseProperty<uint64_t>::RefCount() = " << prop0->RefCount() << endl;
        cout << "RvBaseProperty<string>::RefCount()   = " << prop2->RefCount() << endl;
      }
      // Code here will be called immediately after each test (right
      // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.

    RvBaseProperty<uint64_t> * prop0;
    RvBaseProperty<bool>     * prop1;
    RvBaseProperty<string>   * prop2;

    RvBaseProperty<bool>     * prop_b0;
    RvBaseProperty<bool>     * prop_b1;
    RvBaseProperty<bool>     * prop_b2;

    bool mDebug {false};
};

TEST_F(RvBasePropertyTest, IsValid) {
  EXPECT_EQ(prop0->IsValid(), true);
  EXPECT_EQ(prop1->IsValid(), true);
  EXPECT_EQ(prop2->IsValid(), true);
}

TEST_F(RvBasePropertyTest, IsCleared) {
  prop0->ClearValid();
  prop1->ClearValid();
  prop2->ClearValid();
  EXPECT_EQ(prop0->IsValid(), false);
  EXPECT_EQ(prop1->IsValid(), false);
  EXPECT_EQ(prop2->IsValid(), false);
}

TEST_F(RvBasePropertyTest, CheckName) {
  prop0->Name("Hello");
  prop1->Name("Strange");
  prop2->Name("World");
  EXPECT_EQ(prop0->Name(), "Hello");
  EXPECT_EQ(prop1->Name(), "Strange");
  EXPECT_EQ(prop2->Name(), "World");
  EXPECT_FALSE(prop0->Name() == "H_llo");
  EXPECT_FALSE(prop1->Name() == "St_ange");
  EXPECT_FALSE(prop2->Name() == "Wo_ld");
}

TEST_F(RvBasePropertyTest, CheckValue) {
  prop0->Value(~0x0000000000000000);
  prop1->Value(prop2->Name() == "STRING");
  prop2->Value("99");
  EXPECT_EQ(prop0->Value(), 0xffffffffffffffff);
  EXPECT_TRUE(prop1->Value() == false);
  EXPECT_EQ(prop2->Value(), to_string(99));
}

TEST_F(RvBasePropertyTest, IsCopyOk) {
  EXPECT_TRUE(&(*prop_b0) == &(*prop_b1));
  EXPECT_TRUE(*prop_b0 == *prop_b1);
  EXPECT_TRUE(*prop_b0 == *prop_b2);
  EXPECT_FALSE(&(*prop_b0) == &(*prop_b2));
}

TEST_F(RvBasePropertyTest, CheckRefCount) {
  EXPECT_EQ(prop_b0->RefCount(), 3ull);
  EXPECT_EQ(prop_b1->RefCount(), 3ull);
  EXPECT_EQ(prop_b2->RefCount(), 3ull);
  EXPECT_EQ(  prop0->RefCount(), 1ull);
  EXPECT_EQ(  prop1->RefCount(), 3ull);
  EXPECT_EQ(  prop2->RefCount(), 1ull);
}
*/