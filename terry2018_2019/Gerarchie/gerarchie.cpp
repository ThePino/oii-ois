#include <bits/stdc++.h>

using namespace std;

#define MAXN 1001

vector <int> adj[MAXN];
int ids[MAXN];
int power[MAXN];
bool hasMoved[MAXN];
int cont = 0;

int dfs(int node){
	for(int &i : adj[node]){
		dfs(i);
	}
	int best = 0,child;
	for(int &i : adj[node]){
		if(best < power[ids[i]]){
			best = power[ids[i]];
			child = i;
		}
	}
	if(!hasMoved[ids[node]]){
		if(power[ids[node]] < best){
			hasMoved[ids[child]] = true;
			cont++;
			swap(ids[node],ids[child]);
			//cout << "scambio " << ids[child] << " " << ids[node] << '\n';
		}
	}
}

int solve(int N,int leader){
	cont = 0;
	for(int i = 0; i < N; i++){
		dfs(leader);
	}
	return cont;
}

void print(int N){
	for(int i = 0; i < N; i++){
		cout << " " << i << " -> ";
		for(int j : adj[i]){
			cout << j << " ";
		}
		cout << '\n';
	}
}

int main(){
	#ifdef EVAL
		freopen("gerarchie_input_1.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		for(int i = 0; i < MAXN; i++){
			adj[i].clear();
			ids[i] = i;
			hasMoved[i] = false;
		}
		int N;
		cin >> N;
		int leader;
		for(int i = 0; i < N; i++){
			int parent,_power;
			cin >> parent >> _power;
			if(parent == -1){
				leader = i;
			}else{
				adj[parent].push_back(i);
			}
			power[i] = _power;
		}
		//print(N);
		// Case #1: 6
		cout << "Case #" << t << ": " << solve(N,leader) << '\n';
	}
	return 0;
}