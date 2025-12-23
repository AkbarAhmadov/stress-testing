#include<bits/stdc++.h>
using namespace std;

signed main(){
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector < int > p(n), s(n);
		vector < int > q(n), t(n);
		map < int , multiset < int > > g;
		vector < pair < int , int > > y;
		for(int i = 0; i < n; i++){
			cin >> p[i] >> s[i];
			g[s[i]].insert(p[i]);
		}
		for(int i = 0; i < n; i++){
			cin >> q[i] >> t[i];
			y.push_back({q[i], t[i]});
		}
		sort(y.rbegin(), y.rend());
		bool ok = true;
		for(auto i : y){
			int dl = -1;
			auto it1 = g[i.second].lower_bound(i.first / 2 + i.first % 2);
			auto it2 = g[i.second ^ 1].lower_bound(i.first);
			if(it1 != g[i.second].end())
				dl = *it1;
			if(it2 != g[i.second ^ 1].end()){
				if(*it2 <= dl || dl == -1){
					dl = *it2;
				}
			}
//			cout << "size: " << x.size() << endl;
//			for(auto j : x)
//				cout << j.first << '-' << j.second << endl;
//			cout << en	dl;
			if(dl == -1){
				ok = false;
				break;
			}
			if(g[0].count(dl) > 0)
				g[0].erase(g[0].find(dl));
			else
				g[1].erase(g[1].find(dl));
		}
		cout << (ok ? "Yes" : "No") << endl;
	}
}