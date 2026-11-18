// Lab 08 - GoogleTest suites. Expected values come from the specification
// (R1-R4) worked out by hand in the report, NOT from the C++ code.
#include <gtest/gtest.h>
#include "hvac_controller.hpp"

struct Case {
    const char* label;   // what this row is for
    int row;             // truth-table row (1 = TTTT, 16 = FFFF)
    bool a, b, c, d;
    bool expected;       // F from R1-R4
};

static std::string caseName(const ::testing::TestParamInfo<Case>& info) {
    return std::string("row") + std::to_string(info.param.row) + "_" + info.param.label;
}

// ---------------- Suite 1: Determination (RACC pairs) ----------------
// A: (5,13)  B: (9,13)  C: (5,7)  D: (5,6)  -> rows {5,6,7,9,13}
class Determination : public ::testing::TestWithParam<Case> {};
TEST_P(Determination, MatchesSpec) {
    const Case& t = GetParam();
    HVACController ctl;
    EXPECT_EQ(ctl.evaluateSmokePurge(t.a, t.b, t.c, t.d), t.expected) << t.label;
}
INSTANTIATE_TEST_SUITE_P(Rows, Determination, ::testing::Values(
    Case{"A_true_C_true_D_true", 5,  true,  false, true,  true,  true },
    Case{"D_false",              6,  true,  false, true,  false, false},
    Case{"C_false",              7,  true,  false, false, true,  false},
    Case{"B_true",               9,  false, true,  true,  true,  true },
    Case{"A_false_B_false",      13, false, false, true,  true,  false}
), caseName);

// ---------------- Suite 2: DNF (CUTPNFP on F = AB + BC + ACD) ----------------
// rows {3,5,6,7,9,11,13}
class DNF : public ::testing::TestWithParam<Case> {};
TEST_P(DNF, MatchesSpec) {
    const Case& t = GetParam();
    HVACController ctl;
    EXPECT_EQ(ctl.evaluateSmokePurge(t.a, t.b, t.c, t.d), t.expected) << t.label;
}
INSTANTIATE_TEST_SUITE_P(Rows, DNF, ::testing::Values(
    Case{"UTP_AB",         3,  true,  true,  false, true,  true },
    Case{"UTP_ACD",        5,  true,  false, true,  true,  true },
    Case{"NFP_ACD_flipD",  6,  true,  false, true,  false, false},
    Case{"NFP_ACD_flipC",  7,  true,  false, false, true,  false},
    Case{"UTP_BC",         9,  false, true,  true,  true,  true },
    Case{"NFP_flipA_flipC",11, false, true,  false, true,  false},
    Case{"NFP_flipB_flipA",13, false, false, true,  true,  false}
), caseName);
