#!/usr/bin/env python3
"""Lab 08 automation: drive hvac_cli through all 16 conditions, compare with an
oracle written from R1-R4 (independent of the C++), write results/conditions.csv
and append to run_log.txt, then run ctest.

Usage:  python3 scripts/run_checks.py [--cli build/hvac_cli] [--label "starter"]
"""
import argparse, csv, datetime, pathlib, subprocess, sys

DET = {5, 6, 7, 9, 13}
DNF = {3, 5, 6, 7, 9, 11, 13}

def oracle(a, b, c, d):
    r1 = a and b
    r2 = a and c and d
    r3 = b and c
    r4 = a and b and c and d
    return int(bool(r1 or r2 or r3 or r4))

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--cli", default="build/hvac_cli")
    ap.add_argument("--label", default="run")
    ap.add_argument("--no-ctest", action="store_true")
    args = ap.parse_args()

    rows, out = [], []
    for row in range(1, 17):
        m = 16 - row
        a, b, c, d = (m >> 3) & 1, (m >> 2) & 1, (m >> 1) & 1, m & 1
        exp = oracle(a, b, c, d)
        res = subprocess.run([args.cli, str(a), str(b), str(c), str(d)],
                             capture_output=True, text=True)
        try:
            act = int(res.stdout.strip())
        except ValueError:
            act = -1
        ok = act == exp
        rows.append([row, m, a, b, c, d, exp, act, "PASS" if ok else "FAIL",
                     "x" if row in DET else "", "x" if row in DNF else ""])

    hdr = ["row", "m", "A", "B", "C", "D", "expected", "actual", "result",
           "Determination", "DNF"]
    pathlib.Path("results").mkdir(exist_ok=True)
    with open("results/conditions.csv", "w", newline="") as f:
        w = csv.writer(f); w.writerow(hdr); w.writerows(rows)

    fails = sum(1 for r in rows if r[8] == "FAIL")
    out.append(f"=== {datetime.datetime.now():%Y-%m-%d %H:%M:%S}  [{args.label}] ===")
    out.append("row  m  A B C D  exp act  result  Det DNF")
    for r in rows:
        out.append(f"{r[0]:>3} {r[1]:>2}  {r[2]} {r[3]} {r[4]} {r[5]}   {r[6]}   {r[7]:>2}  {r[8]}   {r[9]:^3} {r[10]:^3}")
    out.append(f"conditions failed: {fails} / 16")

    if not args.no_ctest:
        ct = subprocess.run(["ctest", "--test-dir", "build", "--output-on-failure"],
                            capture_output=True, text=True)
        out.append(ct.stdout.strip()); out.append(ct.stderr.strip())
        out.append(f"ctest exit code: {ct.returncode}")
        fails += ct.returncode != 0

    text = "\n".join(s for s in out if s) + "\n"
    print(text)
    with open("run_log.txt", "a") as f:
        f.write(text + "\n")
    sys.exit(1 if fails else 0)

if __name__ == "__main__":
    main()
