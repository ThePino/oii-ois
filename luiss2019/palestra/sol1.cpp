#include <bits/stdc++.h>

using namespace std;

const long long int zero = 0;

#define EVAL

int main(){
	#ifdef EVAL
		freopen("palestra_input_1.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		long long int ans = 0;
		int N;
		cin >> N;
		for(int j = 0; j < N; j++){
			long long int x;
			cin >> x;
			ans += max(zero,x);
		}
		cout << "Case #" << i << ": " << ans << '\n'; 
	}
}
