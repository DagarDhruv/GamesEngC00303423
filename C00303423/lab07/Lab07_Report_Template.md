# Lab 07 — Report

**Name:** <Dhruv Dagar 
*StudentID:** <  C00303423  >

## Build and run

```
cmake -S . -B build
cmake --build build --target lab07_tests
./build/lab07_tests --gtest_color=yes
```

## My CACC rows

Fill in the pairs you added:

| Major | Row 1 (major = T) | Row 2 (major = F) |
|-------|-------------------|-------------------|
| G     |{T, F, T, T, T} → T|{T, F, T, F, T} → F|
| D     |{T, F, T, T, T} → T|{T, F, T, T, F} → F|

## Report (150–250 words)

Explain, in your own words, why the disjunction `(A ∨ B)` needs two determining pairs — one for A and one for B — instead of one shared pair. What value must the *minor* take to make the major "matter"?

In the predicate P = (A ∨ B) ∧ C ∧ G ∧ D, the clauses A and B are joined by OR, so each one only matters when the other is silent. A determines P only if flipping A flips the whole result. With B = T, the disjunction (A ∨ B) is already true no matter what A is, so changing A has no effect on P. The minor clause B must therefore be F for A to matter. By the same reasoning, A must be F for B to matter.
This is the disjunction trap. A single shared pair, such as A=T, B=T against A=F, B=F, changes both clauses at once, so we cannot tell which one caused P to change. A test that sets both to T would also pass even if the code ignored A or B completely, because the other one hides the fault. That is why we need two separate pairs: A=T,B=F versus A=F,B=F for A, and A=F,B=T versus A=F,B=F for B. The F,F row can be reused for both.
For the AND clauses C, G and D, the minors must all be T so that nothing else forces P to be false. For these I picked A=T, B=F, which makes (A ∨ B) true.


## Screenshots

* `screenshots/vscode.png`
* `screenshots/terminal.png`
