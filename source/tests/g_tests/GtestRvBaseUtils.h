#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gtest/gtest_prod.h>
#include "RvBaseUtils.h"

using namespace std;

class RvBaseUtilsTest : public testing::Test {
  protected:
    RvBaseUtilsTest()           {}
   ~RvBaseUtilsTest() override  {}
    void SetUp() override       {}
    void TearDown() override    {}
    queue<string> target {};
    queue<string> object {};
};

TEST_F(RvBaseUtilsTest, NoMatch) {
  target = RvBaseScopeUtils::SplitScope("Mother.Child.GrandChild");
  object = RvBaseScopeUtils::SplitScope("Uncle.Cousin");
  EXPECT_FALSE(RvBaseScopeUtils::MatchScope(target, object));
}

TEST_F(RvBaseUtilsTest, ExactMatch) {
  target = RvBaseScopeUtils::SplitScope("Uncle.Cousin");
  object = RvBaseScopeUtils::SplitScope("Uncle.Cousin");
  EXPECT_TRUE(RvBaseScopeUtils::MatchScope(target, object));
}

TEST_F(RvBaseUtilsTest, PrefixMatch) {
  target = RvBaseScopeUtils::SplitScope("*.Cousin");
  object = RvBaseScopeUtils::SplitScope("Uncle.Cousin");
  EXPECT_TRUE(RvBaseScopeUtils::MatchScope(target, object));
}

TEST_F(RvBaseUtilsTest, PrefixNoMatch) {
  target = RvBaseScopeUtils::SplitScope("*.Cousin");
  object = RvBaseScopeUtils::SplitScope("Uncle.Aunty");
  EXPECT_FALSE(RvBaseScopeUtils::MatchScope(target, object));
}

TEST_F(RvBaseUtilsTest, SuffixMatch) {
  target = RvBaseScopeUtils::SplitScope("Uncle.Cousin.*");
  object = RvBaseScopeUtils::SplitScope("Uncle.Cousin.Nephew");
  EXPECT_TRUE(RvBaseScopeUtils::MatchScope(target, object));
}

TEST_F(RvBaseUtilsTest, SuffixNoMatch) {
  target = RvBaseScopeUtils::SplitScope("Uncle.Cousin.*");
  object = RvBaseScopeUtils::SplitScope("Uncle.Aunty.Nephew");
  EXPECT_FALSE(RvBaseScopeUtils::MatchScope(target, object));
}

TEST_F(RvBaseUtilsTest, PrefixAndSuffixMatch) {
  target = RvBaseScopeUtils::SplitScope("*.Cousin.Nephew.*");
  object = RvBaseScopeUtils::SplitScope("Uncle.Cousin.Nephew.GrandChild");
  EXPECT_TRUE(RvBaseScopeUtils::MatchScope(target, object));
}

TEST_F(RvBaseUtilsTest, PrefixAndSuffixNoMatch) {
  target = RvBaseScopeUtils::SplitScope("*.Cousin.Nephew.*");
  object = RvBaseScopeUtils::SplitScope("Uncle.Aunty.Nephew.GrandChild");
  EXPECT_FALSE(RvBaseScopeUtils::MatchScope(target, object));
}