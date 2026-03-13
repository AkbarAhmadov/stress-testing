# Stress Tester

A competitive programming stress testing tool that automatically finds failing test cases by comparing two solutions against randomly generated inputs.

## How It Works

```
generator.cpp  →  input  →  correct.cpp  ──┐
                                            ├── compare → STOP if different
                         →  hack.cpp     ──┘
```

The generator produces random test cases. Both solutions run on each input, and if their outputs differ, the process stops and saves the failing case for you to inspect.

## Files

| File | Description |
|------|-------------|
| `generator.cpp` | Generates random test inputs. **You write this.** |
| `correct.cpp` | Your reference / brute-force solution |
| `hack.cpp` | The solution you want to test |
| `stress_tester.py` | The main runner script |

## Setup

### 1. Write `generator.cpp`

The generator prints a random test case to stdout. A starter template with helper utilities is provided:

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
using namespace std;

unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937_64 rng(seed);

// Random integer in [l, r]
int get(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

// Random lowercase string of length n
string str(int n) {
    string res;
    for (int i = 0; i < n; i++) {
        char x = 'a';
        x += get(0, 'z' - 'a');
        res.pb(x);
    }
    return res;
}

// Print integer vector (space-separated, no trailing space)
void print(vector<int> &v) {
    for (int i = 0; i < v.size() - 1; i++) cout << v[i] << ' ';
    cout << v.back();
}

// Print vector of pairs (one pair per line)
void print_pair(vector<pair<int,int>> &v) {
    for (int i = 0; i < v.size() - 1; i++) cout << v[i].ff << ' ' << v[i].ss << "\n";
    cout << v.back().ff << ' ' << v.back().ss;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example: generate n and an array of n integers
    int n = get(1, 10);
    cout << n << "\n";
    for (int i = 0; i < n; i++)
        cout << get(1, 100) << " \n"[i == n - 1];

    return 0;
}
```

### 2. Add your solutions

- `correct.cpp` — a correct solution (brute force is fine)
- `hack.cpp` — the solution you want to verify

### 3. Run

```bash
python3 stress_tester.py
```

Or with custom options:

```bash
python3 stress_tester.py --max 200000 --timeout 2 --progress 100
```

## Options

| Flag | Default | Description |
|------|---------|-------------|
| `--max N` | `1000000` | Maximum number of test cases to run |
| `--timeout T` | `2.0` | Time limit per solution in seconds |
| `--progress N` | `100` | Print a status message every N tests |
| `--correct-src FILE` | `correct.cpp` | Path to the correct solution |
| `--hack-src FILE` | `hack.cpp` | Path to the solution being tested |
| `--gen-src FILE` | `generator.cpp` | Path to the generator |
| `--keep-files` | off | Keep temporary binaries after a difference is found |

## Output

When a difference is found (or a timeout / crash occurs), the tool saves these files automatically:

| File | Contents |
|------|----------|
| `found_input.txt` | The failing input |
| `found_correct_output.txt` | Output from `correct.cpp` |
| `found_hack_output.txt` | Output from `hack.cpp` |
| `found_correct_stderr.txt` | Stderr from `correct.cpp` |
| `found_hack_stderr.txt` | Stderr from `hack.cpp` |

Prefixes change depending on the stop reason: `found_*`, `timeout_*`, or `runtime_error_*`.

## Requirements

- Python 3
- `g++` with C++17 support
