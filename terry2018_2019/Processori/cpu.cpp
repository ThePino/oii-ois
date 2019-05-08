#include <bits/stdc++.h>

using namespace std;

#define MAXN 301
#define MAXCPU 201

const int K  = MAXN * MAXCPU - 1;

int dp[MAXN * MAXCPU];
int solve(int N,int B, vector <pair <int,int> > &v){
	for(int i = 0; i < K; i++){
		dp[i] = INT_MAX;
	}
	for(int i = 0; i < N; i++){
		for(int j = K; j >= 0; j--){
			if(dp[j] != INT_MAX){
				int z = j + v[i].first;
				dp[z] = min(dp[z],dp[j] + v[i].second);
			}
		}
		dp[v[i].first] = min(dp[v[i].first],v[i].second);
	}
	int ans = 0;
	for(int i = 0; i < K; i++){
		if(dp[i] <= B){
			ans = i;
		}
	}
	return ans;
}

int main(){
	#ifdef EVAL
		freopen("multicore_input_1.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		int N,B;
		cin >> N >> B;
		vector <pair <int,int>> v(N);
		for(int i = 0; i < N; i++){
			cin >> v[i].first >> v[i].second;
		}
		// Case #1: 2
		cout << "Case #" << t << ": " << solve(N,B,v) << '\n';
	}
	return 0;
}