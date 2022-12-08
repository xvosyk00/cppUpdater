//
// Created by pavel on 12/6/22.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/VersionDb.hpp"

using ::testing::Matcher;
using ::testing::Return;
using ::testing::_;

TEST(versionDbTest, parseCurrentVersion){
  {
    std::stringstream input{"2 3 4 0"};
    VersionDb versionDb{input};
    ASSERT_EQ(versionDb.getVersion(), (Version{2, 3, 4}));
  }
  {
    std::stringstream input{"0 0 1 0 \n 2 3 4 0"};
    VersionDb versionDb{input};
    ASSERT_EQ(versionDb.getVersion(), (Version{2, 3, 4}));
  }
  {
    std::stringstream input{"0 0 1 0 \n 0 0 2 0 \n 1 2 3 0"};
    VersionDb versionDb{input};
    ASSERT_EQ(versionDb.getVersion(), (Version{1, 2, 3}));
  }
}

TEST(versionDbTest, parseChanges){
  {
    std::stringstream input{"2 3 4  1  file1 0"};
    VersionDb versionDb{input};
    auto& c = versionDb.getChanges({0,0,0});
    ASSERT_EQ(c.size(), 1);
    EXPECT_EQ(c[0].filename, "file1");
    EXPECT_EQ(static_cast<int>(c[0].action), 0);
  }
  {
    std::stringstream input{"2 3 4  3  file1 0 file2 1 file3 1"};
    VersionDb versionDb{input};
    auto& c = versionDb.getChanges({0,0,0});
    ASSERT_EQ(c.size(), 3);
    EXPECT_EQ(c[0].filename, "file1");
    EXPECT_EQ(static_cast<int>(c[0].action), 0);
    EXPECT_EQ(c[1].filename, "file2");
    EXPECT_EQ(static_cast<int>(c[1].action), 1);
    EXPECT_EQ(c[2].filename, "file3");
    EXPECT_EQ(static_cast<int>(c[2].action), 1);
  }
}

TEST(versionDbTest, parseChangesMultipleVersions) {
  std::stringstream input{"0 0 1  1  file1 0 \n 2 3 4  1  file2 0"};
  VersionDb versionDb{input};
  auto &c = versionDb.getChanges({0, 0, 1});
  ASSERT_EQ(c.size(), 1);
  EXPECT_EQ(c[0].filename, "file2");
  EXPECT_EQ(static_cast<int>(c[0].action), 0);

  auto &c2 = versionDb.getChanges({0, 0, 0});
  ASSERT_EQ(c2.size(), 2);
  EXPECT_EQ(c2[0].filename, "file2");
  EXPECT_EQ(static_cast<int>(c2[0].action), 0);
  EXPECT_EQ(c2[1].filename, "file1");
  EXPECT_EQ(static_cast<int>(c2[1].action), 0);
}
