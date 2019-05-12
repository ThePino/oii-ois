#include <bits/stdc++.h>

using namespace std;

int N,M,C,R;

#define MAXM 101
int D[MAXM];

#define MAXR 101

int Q[MAXR],B[MAXR],E[MAXR];

long long int solve(){
	long long int ans = 0;
	for(int i = 0; i < N; i++){
		int rubinetto = 0;
		int costo = INT_MAX;
		int qt = 0;
		for(int j = 0; j < R; j++){
			int need = D[B[j]];
			int paga = 0;
			int litri = 0;
			while(need > 0){
				need -= C;
				paga += E[j];
				litri += C;
			}
			if(Q[j] >= litri){
				if(paga < costo){
					costo = paga;
					rubinetto = j;
					qt = litri;
				}
			}
		}
		Q[rubinetto] -= qt;
		ans += costo;
	}
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
		cin >> N >> C >> M >> R;
		for(int j = 0; j < M; j++){
			cin >> D[j];
		}
		for(int j = 0; j < R; j++){
			cin >> Q[j] >> B[j] >> E[j];	
		}
		cout << "Case #" << i << ": " << solve() << endl << endl;
	}
	return 0;
}
