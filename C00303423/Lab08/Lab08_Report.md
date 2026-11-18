# Lab 08 — Report

**Name:** Dhruv Dagar 
**Registration:** C00303423

Show your working throughout. A correct answer with no derivation earns little credit.

---

## Part 1 — Determination

### 1.1 Truth table

Fill in F from R1–R4, then mark T in each p column where that clause determines F (leave the others blank or write F).

| Row | m | A | B | C | D | F | p<sub>A</sub> | p<sub>B</sub> | p<sub>C</sub> | p<sub>D</sub> |
|:--:|:--:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| 1 | 15 | T | T | T | T | T | F  | F  | F  | F  |
| 2 | 14 | T | T | T | F | T | F  | T  | F  | F  |
| 3 | 13 | T | T | F | T | T | T  | T  | F  | F  |
| 4 | 12 | T | T | F | F | T | T  | T  | F  | F  |
| 5 | 11 | T | F | T | T | T | T  | F  | T  | T  |
| 6 | 10 | T | F | T | F | F | F  | T  | F  | T  |
| 7 | 9 | T | F | F | T |  F | F  | T  | T  | F  |
| 8 | 8 | T | F | F | F |  F | F  | T  | F  | F  |
| 9 | 7 | F | T | T | T |  T | F  | T  | T  | F  |
| 10 | 6 | F | T | T | F | T  | F  | T  | T  | F  |
| 11 | 5 | F | T | F | T | F  | T  | F  | T  | F  |
| 12 | 4 | F | T | F | F | F  | T  | F  | T  | F  |
| 13 | 3 | F | F | T | T | F |  T | T  | F  | F  |
| 14 | 2 | F | F | T | F | F  | F  | T  | F  | F  |
| 15 | 1 | F | F | F | T | F  | F |  F |  F |  F |
| 16 | 0 | F | F | F | F | F  | F  | F  | F  | F  |

### 1.2 Determination conditions (XOR method)

For each clause, show every step from p<sub>X</sub> = F<sub>X=true</sub> ⊕ F<sub>X=false</sub> to the simplified result.

**p<sub>A</sub>**

```
p_A = F(A=true) ⊕ F(A=false)
F(A=1) = B + CD + BC + BCD = B + CD
F(A=0) = BC
p_A = (B + CD) ⊕ BC
    If BC = 1: B + CD = 1, XOR = 0.
    If BC = 0: XOR = B + CD.
    = ¬(BC)·(B + CD)
    = B¬C + ¬B·C·D          (B=1 forces C=0; B=0 leaves CD)
```

**p<sub>B</sub>**

```
p_B = F(B=true) ⊕ F(B=false)
F(B=1) = A + ACD + C + ACD = A + C
F(B=0) = ACD
p_B = (A + C) ⊕ ACD
    If ACD = 1: A + C = 1, XOR = 0.
    If ACD = 0: XOR = A + C.
    = (A + C)(¬A + ¬C + ¬D)
    = A¬C + A¬D + ¬A·C + C¬D
    = (A ⊕ C) + A·C·¬D     (A¬D and C¬D together cover ACD̄)
```

**p<sub>C</sub>**

```
p_C = F(C=true) ⊕ F(C=false)
F(C=1) = AB + AD + B + ABD = B + AD
F(C=0) = AB
p_C = (B + AD) ⊕ AB
    If AB = 1: B + AD = 1, XOR = 0.
    If AB = 0: XOR = B + AD.
    = ¬(AB)(B + AD)
    = ¬A·B + A¬B·D
```

**p<sub>D</sub>**

```
p_D = F(D=true) ⊕ F(D=false)
F(D=1) = AB + AC + BC
F(D=0) = AB + BC
p_D differs only where AC = 1 and AB + BC = 0, i.e. A=1, C=1, B=0:
p_D = A¬B·C
```

### 1.3 Tabulation check

For each clause, list the pairs of rows that differ only in that clause and say whether F changes. Confirm that the rows where F changes are exactly the rows where your p<sub>X</sub> is true.

Clause	Pairs (X true row, X false row) : F values	Rows where F changes
A	(1,9) 1/1 no · (2,10) 1/1 no · (3,11) 1/0 yes · (4,12) 1/0 yes · (5,13) 1/0 yes · (6,14) 0/0 no · (7,15) 0/0 no · (8,16) 0/0 no	3,4,5,11,12,13
B	(1,5) 1/1 no · (2,6) 1/0 yes · (3,7) 1/0 yes · (4,8) 1/0 yes · (9,13) 1/0 yes · (10,14) 1/0 yes · (11,15) 0/0 no · (12,16) 0/0 no	2,3,4,6,7,8,9,10,13,14
C	(1,3) 1/1 no · (2,4) 1/1 no · (5,7) 1/0 yes · (6,8) 0/0 no · (9,11) 1/0 yes · (10,12) 1/0 yes · (13,15) 0/0 no · (14,16) 0/0 no	5,7,9,10,11,12
D	(1,2) 1/1 no · (3,4) 1/1 no · (5,6) 1/0 yes · (7,8) 0/0 no · (9,10) 1/1 no · (11,12) 0/0 no · (13,14) 0/0 no · (15,16) 0/0 no	5,6


### 1.4 GACC, CACC and RACC pairs

 
p_X is true in the X-true row and in the X-false row. F is monotone in every clause, so whenever p_X holds F(X=T)=1 and F(X=F)=0. The two tests therefore always have different F values, which makes **CACC = GACC** here. RACC additionally forces the minor clauses to be identical.

| Clause | GACC pairs | CACC pairs | RACC pairs |
|:--:|---|---|---|
| A | {3,4,5} × {11,12,13} | {3,4,5} × {11,12,13} | (3,11), (4,12), (5,13) |
| B | {2,3,4,9,10} × {6,7,8,13,14} | {2,3,4,9,10} × {6,7,8,13,14} | (2,6), (3,7), (4,8), (9,13), (10,14) |
| C | {5,9,10} × {7,11,12} | {5,9,10} × {7,11,12} | (5,7), (9,11), (10,12) |
| D | {5} × {6} | {5} × {6} | (5,6) |

### 1.5 Chosen pairs

D has only one pair, (5,6), so I build around it. Row 5 appears in an A pair and a C pair, which gives (5,13) and (5,7). B has no pair inside {5,6,7,13}, so one extra row is unavoidable. (9,13) reuses row 13.
 
| Clause | RACC pair (row with X true, row with X false) | Minor clause values |
|:--:|:--:|---|
| A | (5, 13) | B=F, C=T, D=T |
| B | (9, 13) | A=F, C=T, D=T |
| C | (5, 7) | A=T, B=F, D=T |
| D | (5, 6) | A=T, B=F, C=T |
 
Resulting set of rows: { 5, 6, 7, 9, 13 } (m = 11, 10, 9, 7, 3) — size: **5** (the minimum possible for 4 clauses is n+1 = 5).
---

## Part 2 — Karnaugh maps

### 2.1 Minterms

| Requirement | Minterms |
|---|---|
| R1  A ∧ B | 12, 13, 14, 15 |
| R2  A ∧ C ∧ D | 11, 15 |
| R3  B ∧ C | 6, 7, 14, 15 |
| R4  A ∧ B ∧ C ∧ D | 15 |
 
Σm(F) = {6, 7, 11, 12, 13, 14, 15}

### 2.2 K-map of F

Mark each group. A screenshot or photo of a hand-drawn map is fine, but fill in the tables below as well.

 | AB \ CD | 00 | 01 | 11 | 10 |
|:--:|:--:|:--:|:--:|:--:|
| **00** | 0 | 0 | 0 | 0 |
| **01** | 0 | 0 | 1 (m7) | 1 (m6) |
| **11** | 1 (m12) | 1 (m13) | 1 (m15) | 1 (m14) |
| **10** | 0 | 0 | 1 (m11) | 0 |
 
| Group | Minterms | Implicant | Essential? |
|---|---|---|---|
| Row AB=11 | 12, 13, 14, 15 | A·B | Yes (only cover of m12, m13) |
| Block B=1, C=1 | 6, 7, 14, 15 | B·C | Yes (only cover of m6, m7) |
| Pair in column CD=11 | 11, 15 | A·C·D | Yes (only cover of m11) |
 
Minimal DNF: **F = AB + BC + ACD**
### 2.3 What disappeared

Which requirement was removed by minimisation, and why does removing it not change the behaviour? Can any remaining term be dropped?
R4 (A∧B∧C∧D, m15) disappeared. m15 already lies inside AB, BC and ACD, so it adds no true point and F does not change (absorption: AB + ABCD = AB). No remaining term can be dropped, because each has a minterm that only it covers (AB: m12, m13; BC: m6, m7; ACD: m11). All three are essential prime implicants.

### 2.4 K-map of F̄

| AB \ CD | 00 | 01 | 11 | 10 |
|:--:|:--:|:--:|:--:|:--:|
| **00** | 1 | 1 | 1 | 1 |
| **01** | 1 | 1 | 0 | 0 |
| **11** | 0 | 0 | 0 | 0 |
| **10** | 1 | 1 | 0 | 1 |
 
Groups: ¬A¬B {0,1,2,3}, ¬A¬C {0,1,4,5}, ¬B¬C {0,1,8,9}, ¬B¬D {0,2,8,10}. Each is essential (m3, m4/m5, m9, m10 respectively).
 
Minimal DNF: **F̄ = ¬A¬B + ¬A¬C + ¬B¬C + ¬B¬D**
 
(Check by De Morgan: F̄ = (¬A+¬B)(¬B+¬C)(¬A+¬C+¬D) = ¬B + ¬A¬C, times the third factor, gives the same four terms.)

### 2.5 Unique true points

| Expression | Implicant | Unique true points (minterm and row) |
|---|---|---|
| F | AB | m12 (row 4), m13 (row 3) |
| F | BC | m6 (row 10), m7 (row 9) |
| F | ACD | m11 (row 5) |
| F̄ | ¬A¬B | m3 (row 13) |
| F̄ | ¬A¬C | m4 (row 12), m5 (row 11) |
| F̄ | ¬B¬C | m9 (row 7) |
| F̄ | ¬B¬D | m10 (row 6) |

### 2.6 Near false points
Flip one literal; the other literals stay true; F must be false there.
 
| Implicant of F | Literal flipped | Near false points (minterm and row) |
|---|---|---|
| AB | A → ¬A B | m4 (row 12), m5 (row 11) |
| AB | B → A ¬B | m8 (row 8), m9 (row 7), m10 (row 6) |
| BC | B → ¬B C | m2 (row 14), m3 (row 13), m10 (row 6) |
| BC | C → B ¬C | m4 (row 12), m5 (row 11) |
| ACD | A → ¬A C D | m3 (row 13) |
| ACD | C → A ¬C D | m9 (row 7) |
| ACD | D → A C ¬D | m10 (row 6) |
 
### 2.7 CUTPNFP set

Each NFP differs from its UTP in exactly the flipped literal. I chose pairs so that points are shared between rows.
 
| Implicant | Literal | Unique true point | Near false point |
|---|---|---|---|
| AB | A | m13 (1101, row 3) | m5 (0101, row 11) |
| AB | B | m13 (1101, row 3) | m9 (1001, row 7) |
| BC | B | m7 (0111, row 9) | m3 (0011, row 13) |
| BC | C | m7 (0111, row 9) | m5 (0101, row 11) |
| ACD | A | m11 (1011, row 5) | m3 (0011, row 13) |
| ACD | C | m11 (1011, row 5) | m9 (1001, row 7) |
| ACD | D | m11 (1011, row 5) | m10 (1010, row 6) |
 
Resulting set: { rows 3, 5, 6, 7, 9, 11, 13 } = { m13, m11, m10, m9, m7, m5, m3 } — size: **7**

## Part 3 — Test suites

Expected F comes from the truth table in 1.1 (R1–R4), not from the code.
 
| Test row label | Suite | Row | m | A B C D | Expected F | Came from |
|---|---|:--:|:--:|:--:|:--:|---|
| row5_A_true_C_true_D_true | Determination | 5 | 11 | T F T T | 1 | A, C, D true rows |
| row6_D_false | Determination | 6 | 10 | T F T F | 0 | D false row |
| row7_C_false | Determination | 7 | 9 | T F F T | 0 | C false row |
| row9_B_true | Determination | 9 | 7 | F T T T | 1 | B true row |
| row13_A_false_B_false | Determination | 13 | 3 | F F T T | 0 | A false and B false row |
| row3_UTP_AB | DNF | 3 | 13 | T T F T | 1 | UTP of AB |
| row5_UTP_ACD | DNF | 5 | 11 | T F T T | 1 | UTP of ACD |
| row6_NFP_ACD_flipD | DNF | 6 | 10 | T F T F | 0 | NFP of ACD (D flipped) |
| row7_NFP_ACD_flipC | DNF | 7 | 9 | T F F T | 0 | NFP of ACD (C) and AB (B) |
| row9_UTP_BC | DNF | 9 | 7 | F T T T | 1 | UTP of BC |
| row11_NFP_flipA_flipC | DNF | 11 | 5 | F T F T | 0 | NFP of AB (A) and BC (C) |
| row13_NFP_flipB_flipA | DNF | 13 | 3 | F F T T | 0 | NFP of BC (B) and ACD (A) |
 
Number of tests: Determination = 5 , DNF = 7 , all passing? <fill in after your run>
 
---

## Part 4 — Automation

* Command used to run your script:
* What your oracle is, and why it is independent of the C++ code:
* Summary of the run against the starter (how many conditions failed):
* Summary of the final run:

Paste the table your script printed for the final run here.

---

## Part 5 — Comparison of the two methods (300–500 words)

Which conditions does each suite use that the other does not? What kind of fault in `evaluateSmokePurge()` could pass every test in the Determination suite but fail the DNF suite? Give a concrete faulty expression and show, using your conditions table, which row exposes it. Which suite would you keep if you could only keep one, and why?

---

## Screenshots

* `screenshots/vscode.png`
* `screenshots/terminal.png`
