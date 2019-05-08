#include <bits/stdc++.h>

using namespace std;

int solve(int N, vector <int> &v){
	if(N == 0)return 0;
	int cur = v[0],maxHigh,maxLow, ans = 1;
	if(cur == 1){
		maxHigh = 1;
		maxLow = 0;
	}else{
		maxHigh = 0;
		maxLow = -1;
	}
	for(int i = 1; i < N; i++){
		cur += v[i];
		if(cur < maxLow){
			maxLow = cur;
			ans++;
		}
		if(cur > maxHigh){
			maxHigh = cur;
			ans++;
		}
	}
	return ans;
}

int main(){
	#ifdef EVAL
		freopen("tornello_input_1.txt","r",stdin);
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
		//Case #1: 3
		cout << "Case #" << t << ": " << solve(N,v) << '\n';
	}
	return 0;
}