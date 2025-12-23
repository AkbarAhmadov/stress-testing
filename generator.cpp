/*

* Get random number in interval [L, R] --> get(L, R)
* Get random string with size n --> str(n)
* Print the vector with integer type v --> print(v)
* Print the vector with pair integer type v --> print_pair(v)

*/
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
        res.pb(x);
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

struct testcase{
    int n;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    

    return 0;
}
