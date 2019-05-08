#include <bits/stdc++.h>

using namespace std;

pair <int,int> solve(int N,int F,int C){
	int nf = N / F;
	N = N - (nf * F);
	int nc = N / C;
	return {nf,nc};
}

int main(){
	#ifdef EVAL
		freopen("download_input_1.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		int N,F,C;
		cin >> N >> F >> C;
		//Case #1: 3 10
		pair <int,int> ans = solve(N,F,C);
		cout << "Case #" << t << ": " << ans.first << " " << ans.second << '\n';
	}
	return 0;
}