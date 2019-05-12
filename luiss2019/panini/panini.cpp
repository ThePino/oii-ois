#include <bits/stdc++.h>

using namespace std;

int N,M;

#define MAXM 12
#define MAXN 10000

int memo[MAXN][MAXN];
int A[MAXM],B[MAXM],C[MAXM],D[MAXM];
int c_vuoto,d_vuoto;

int dp(int n,int m){
	//cout << n << " " << m << '\n';
	if(n == 0 || m == M + 1)return 0;
	if(memo[n][m] != -1)return memo[n][m];
	int massa = 0, g = 0, ripieno = 0,ans = 0;
	while(massa <= n && ripieno <= A[m]){
		ans = max(ans,dp(n - massa,m + 1) + g);
		massa += C[m];
		g += D[m];
		ripieno += B[m];
		//cout << "massa " << massa << " ripieno " << ripieno << " e incremento di " << B[m] << "  " << C[m] << '\n';
	}
	memo[n][m] = ans;
	return ans;
}
#define EVAL

int main(){
	#ifdef EVAL
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		// N grammi di impsato
		// M numero ripieni
		cin >> N >> M >> C[0] >> D[0];
		B[0] = 0;
		A[0] = INT_MAX;
		for(int j = 1; j <= M; j++){
			// A grammi di ripieno rimasti
			// B grammi di ripeino per fare un panino
			// C grammi di impasto per quel panino
			// D vendita
			cin >> A[j] >> B[j] >> C[j] >> D[j]; 
		}
		memset(memo,-1,sizeof(memo));
		cout << "Case #" << i << ": " << dp(N,0) << '\n';
	}
}
