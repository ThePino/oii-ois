#include <bits/stdc++.h>

using namespace std;

int solve(int N,vector <int> &v){
	int ans = 0;
	for(int i = 0; i < N; i++){
		ans += max(0,v[i]);
	}
	return ans;
}

int main(){
	#ifdef EVAL
		freopen("party_input_1.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		int N;
		cin >> N;
		vector <int> v(N);
		for(int i = 0; i < N; i++){
			cin >> v[i];
		}
		//Case #t: k
		cout << "Case #" << t << ": " << solve(N,v) << '\n';
	}
	return 0;
}