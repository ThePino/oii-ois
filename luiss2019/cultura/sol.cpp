#include <bits/stdc++.h>

using namespace std;

#define EVAL

int N,M;

#define MAXN 1000
#define MAXM 155

// 0 italiano 1 cinese
int tipo[MAXN][2];

vector <int> adj[MAXM];

int best = 0;

void dfs(int node,int p,bool ita,bool cina,int dista){
	if(cina && tipo[node][0]){
		best = max(dista,best);
	}	
	if(ita && tipo[node][1]){
		best = max(dista,best);
	}
	for(int &i : adj[node]){
		if(i == p)continue;
		dfs(i,node,ita,cina,dista + 1);
	}
}

int solve(){
	best = 0;
	for(int i = 0; i <= M; i++){
		dfs(i,-1,tipo[i][0],tipo[i][1],0);
	}
	return best;
}

int main(){
	#ifdef EVAL
		freopen("scambioculturale_input_3.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		memset(tipo,false,sizeof(tipo));
		for(int i = 0; i < MAXM; i++){
			adj[i].clear();
		}
		cin >> N >> M;
		for(int j = 0; j < N; j++){
			int cat,naz;
			cin >> naz >> cat;
			tipo[cat][naz] = true;
		}
		for(int i = 1; i <= M; i++){
			int p;
			cin >> p;
			adj[i].push_back(p);
			adj[p].push_back(i);
		}
		cout << "Case #" << i << ": " << solve() << '\n';
	}		
}
