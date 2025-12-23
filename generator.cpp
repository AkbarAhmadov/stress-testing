#include <bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
using namespace std;
unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937_64 rng(seed);

int get(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

string str(int n) {
    string res;
    for (int i = 0; i < n; i++) {
        char x = 'a';
        x += get(0, 'z' - 'a');
        res += x;
    }
    return res;
}

string str1(int n) {
    string res;
    for (int i = 0; i < n; i++) {
        char x = (get(1, 2) == 1 ? '.' : '*');
        res += x;
    }
    return res;
}

void print(vector <int> &v) {
    for (int i = 0; i < v.size() - 1; i++) cout << v[i] << ' ';
    cout << v.back();
}

void print_pair(vector <pair<int, int>> &v) {
    for (int i = 0; i < v.size()-1; i++) cout << v[i].ff << ' ' << v[i].ss << endl;
    cout << v[v.size()-1].ff << ' ' << v[v.size()-1].ss;
}

void printstr(vector <string> &v) {
    for (int i = 0; i < v.size() - 1; i++) cout << v[i] << endl;
    cout << v.back();
}

struct testcase{
    int n;
    vector <pair<int, int>> v;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int remn = 2;
    vector <testcase> test;
    int t = get(1, 1000);
    while (t--) {
        if (remn == 0) break;
        int n = get(remn, remn);
        remn -= n;
        vector <pair<int, int>> v(2*n);
        for (auto &i : v) i.ff = get(1, 10), i.ss = get(0, 1);
        testcase x;
        x.n = n, x.v = v;
        test.pb(x);
    }
    cout << test.size() << endl;
    for (int i = 0; i < test.size(); i++) {
        testcase x = test[i];
        cout << x.n << endl;
        print_pair(x.v);
        cout << endl;
    }

    return 0;
}