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
		multiset < pair < int , int > > x;
		vector < pair < int , int > > y;
		for(int i = 0; i < n; i++){
			cin >> p[i] >> s[i];
			x.insert({p[i], s[i]});
		}
		for(int i = 0; i < n; i++){
			cin >> q[i] >> t[i];
			y.push_back({q[i], t[i]});
		}
		sort(y.rbegin(), y.rend());
		bool ok = true;
		for(auto i : y){
			pair < int , int > dl = {-1, -1};
			for(auto j : x){
				if(i.second == j.second){
					if(i.first <= j.first * 2){
						if(dl.first == -1)
							dl = {j.first, j.second};
						else {
							if(j.first <= dl.first){
								dl = {j.first, j.second};
							}
						}
					}
				}
				else {
					if(i.first <= j.first){
						if(dl.first == -1)
							dl = {j.first, j.second};
						else {
							if(j.first <= dl.first){
								dl = {j.first, j.second};
							}
						}
					}
				}
			}
//			cout << "size: " << x.size() << endl;
//			for(auto j : x)
//				cout << j.first << '-' << j.second << endl;
//			cout << endl;
			if(dl.first == -1){
				ok = false;
				break;
			}
			x.erase(x.find({dl.first, dl.second}));
		}
		cout << (ok ? "Yes" : "No") << endl;
	}
}