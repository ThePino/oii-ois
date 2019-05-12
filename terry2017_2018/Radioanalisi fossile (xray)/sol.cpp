#include <bits/stdc++.h>

using namespace std;

int solve(int N, vector <int> &v){
	v.push_back(0);
	int ans = 0,i = 0;
	while(i < N){
		if(v[i] != 0){
			int j = i,leva = INT_MAX;
			while(v[j] != 0){
				leva = min(leva,v[j]);
				j++;
			}
			for(int z = i; z < j; z++){
				v[z] -= leva;
			}
			ans += leva;
		}else{
			i++;
		}
	}
	return ans;
}

int main(){
	#ifdef EVAL
		freopen("xray_input_1.txt","r",stdin);
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
		//Case #t: p
		cout << "Case #" << t << ": " << solve(N,v) << '\n';
	}
	return 0;
}