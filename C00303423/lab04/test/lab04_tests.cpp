// Lab 04 - Prime Path Coverage
// Name  : Dhruv Dagar
// StudentID: C00303423
//
// The unit under test is scanRegion( ) in src/region_scan.cpp. 
//
//
// Replace each FAIL( ) with real assertions. Add more TEST cases as you need
// them. A test "reaches" a node or edge by calling scanRegion( ) with a grid
// that forces execution down that part of the graph.

#include <gtest/gtest.h>
#include "region_scan.hpp"

// The following is an example test code provided as a starter code. 
// You can use the similar test format, and choosing the right assert from GoogleTest.
// Ideally, you should be able to write test cases for all FEASIBLE prime paths
// Just like we discussed in the lecture, Prime Path Coverage Subsumes Edge-Pair coverage, which in-turn subsumes Edge coverage.
// So in this lab, if all prime paths are covered (tests written for each), we automatically complete all the edges and the pairs.
TEST(ScanRegion, WorkedExample_PositiveMultipleOfThree) {
    Grid g = {{11, 11, 11}};
    EXPECT_EQ(scanRegion(g), 33);
}

// TODO(Task 2 - node coverage): add tests so that, between them, every node
// of the graph is executed at least once. One more grid alongside the worked
// example is enough. Think about which grid drives the false arm of the
// sum > 10 decision and the default arm of the switch.
TEST(ScanRegion, NodeCoverage_SecondTest) {
    Grid g = {{1}};
    EXPECT_EQ(scanRegion(g), -1);
}

// TODO(Task 3 - edge coverage): add the tests that cover the edges node
// coverage leaves out. The edge from the outer loop test straight to the code
// after the loops needs a grid the outer loop never enters.
TEST(ScanRegion, EdgeCoverage_EmptyRegion) {
    Grid g;  // zero rows
    EXPECT_EQ(scanRegion(g), 0);
}

// TODO(Task 4 - prime path tour): using the prime path list in the overview,
// add tests whose executions tour the feasible prime paths. Label each test
// with the prime path numbers it covers. Three of the listed prime paths are
// infeasible; you do not write tests for those, but you must explain in your
// report why they cannot be toured.


// P04, P05, P17
// One row with zero columns.
// Path: 1-2-3-4-6-2-7-9-10-11-13
TEST(ScanRegion, PrimePath_P04_P05_P17_SingleEmptyRow) {
    Grid g(1);  // one row, zero columns
    EXPECT_EQ(scanRegion(g), 0);
}

// P05, P06
// Two empty rows: 3-4-6-2-3 is toured.
// Path: 1-2-3-4-6-2-3-4-6-2-7-9-10-11-13
TEST(ScanRegion, PrimePath_P06_TwoEmptyRows) {
    Grid g(2);
    EXPECT_EQ(scanRegion(g), 0);
}

// P01, P02, P03, P07, P08, P09, P22
// 2x2 grid of ones: sum = 4, score = -4, 4 % 3 = 1 -> default.
// Path: 1-2-3-4-5-4-5-4-6-2-3-4-5-4-5-4-6-2-7-9-10-12-13
TEST(ScanRegion, PrimePath_P01_P02_P03_P07_P08_P09_P22_TwoByTwo) {
    Grid g = {{1, 1}, {1, 1}};
    EXPECT_EQ(scanRegion(g), -4);
}

// P10, P18
// Non-empty row followed by an empty row: 6-2-3-4-6 is toured, and the
// loop finishes on an empty row (3-4-6-2-7), sum = 1 -> 9 -> default (12).
// Path: 1-2-3-4-5-4-6-2-3-4-6-2-7-9-10-12-13
TEST(ScanRegion, PrimePath_P10_P18_RowThenEmptyRow_SmallNonMultiple) {
    Grid g(2);
    g[0] = {1};
    EXPECT_EQ(scanRegion(g), -1);
}

// P21
// Last row non-empty, sum <= 10, sum % 3 == 0.
// sum = 3, score = -3, adjust(-3) clamps to 0.
// Path: 1-2-3-4-5-4-6-2-7-9-10-11-13
TEST(ScanRegion, PrimePath_P21_NonEmptyLast_SmallMultipleOfThree) {
    Grid g = {{3}};
    EXPECT_EQ(scanRegion(g), 0);
}

// P20
// Last row non-empty, sum > 10, sum % 3 != 0.
// sum = 11, 11 % 3 = 2 -> default.
// Path: 1-2-3-4-5-4-6-2-7-8-10-12-13
TEST(ScanRegion, PrimePath_P20_NonEmptyLast_LargeNonMultiple) {
    Grid g = {{11}};
    EXPECT_EQ(scanRegion(g), 11);
}

// P16
// Last row empty, sum > 10, sum % 3 != 0.
// Path: 1-2-3-4-5-4-6-2-3-4-6-2-7-8-10-12-13
TEST(ScanRegion, PrimePath_P16_EmptyLast_LargeNonMultiple) {
    Grid g(2);
    g[0] = {11};
    EXPECT_EQ(scanRegion(g), 11);
}

// P15 (and P19 again)
// Last row empty, sum > 10, sum % 3 == 0 -> adjust(33) = 33.
// Path: 1-2-3-4-5-4-5-4-5-4-6-2-3-4-6-2-7-8-10-11-13
TEST(ScanRegion, PrimePath_P15_EmptyLast_LargeMultipleOfThree) {
    Grid g(2);
    g[0] = {11, 11, 11};
    EXPECT_EQ(scanRegion(g), 33);
}
