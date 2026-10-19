# Lab 06 — Report

**Full Name:** Dhruv Dagar
**Student ID:** C00303423

## Build, test, coverage

```
cmake -S . -B build
cmake --build build --target lab06_tests
./build/lab06_tests --gtest_color=yes

cmake -S . -B build-cov -DCMAKE_CXX_FLAGS="--coverage" \
                        -DCMAKE_EXE_LINKER_FLAGS="--coverage"
cmake --build build-cov --target lab06_tests
./build-cov/lab06_tests
gcov -b -r build-cov/CMakeFiles/discount.dir/src/discount.cpp.gcno > coverage_summary.txt
```

## Coverage criteria

Predicate-coverage rows used:  Row 1 (0,0,0)  false , Row 2 (0,0,1) true 
Clause-coverage rows used:  Rows 1 (0,0,0), 2 (0,0,1), 5 (1,0,0), 7 (1,1,0)
Tests reported / passed:  5 / 5

## Coverage summary (paste the tail of coverage_summary.txt)

Lines executed:100.00% of 2
Branches executed:100.00% of 4
Taken at least once:100.00% of 4
No calls
Creating 'discount.cpp.gcov'


## Report (250-500 words)

Explain the difference between Predicate Coverage and Clause Coverage. Give a pair of rows from the truth table that satisfies Predicate Coverage but not Clause Coverage, and say which clause is left unexercised. Then describe what gcov reported for `discount.cpp`: did your suite reach 100 % line coverage, 100 % branch coverage, or both, and what is the difference between those two numbers?

--
The predicate is P = (A AND B) OR C, where A is isMember, B is
spendOverThreshold and C is hasCoupon. Predicate Coverage only cares about the
final answer: P has to come out true in one test and false in another. Clause
Coverage looks at each of A, B and C on its own, and each one has to be true in
some test and false in some test.

The two aren't the same. Rows 1 (0,0,0) and 2 (0,0,1) give Predicate Coverage,
because row 1 makes P false and row 2 makes it true. But A is false in both
rows, so A never gets to be true, and Clause Coverage fails. B has the same
problem. Only C changes between the two rows.

To fix that I added rows 5 (1,0,0) and 7 (1,1,0). Now A, B and C are each true
in at least one row and false in at least one. These two rows also make the &&
and the || go both ways, which I needed for full branch coverage.

gcov reported 100% line coverage and 100% branch coverage for discount.cpp
(all 4 branches taken at least once). The predicate line ran 6 times, which
matches the 6 EXPECT calls in my 5 tests.

The difference is that line coverage only checks that a line ran. Branch
coverage checks that each decision went both ways. The whole predicate sits on
one line, so a single test like row 2 would already give 100% line coverage
while skipping most branches. Branch coverage is the stricter one, which is
why rows 5 and 7 mattered.

## Screenshots

* `screenshots/vscode.png`
* `screenshots/terminal.png`
