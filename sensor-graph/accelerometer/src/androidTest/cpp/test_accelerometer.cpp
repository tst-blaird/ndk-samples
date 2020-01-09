//
// Created by blaird on 1/9/2020.
//

#include <sensorgraph.h>
#include "gtest/gtest.h"

TEST(AccelerometerTester, first) {
    std::unique_ptr<sensorgraph> sg(new sensorgraph());
    ASSERT_TRUE(sg.get() != nullptr);
}
