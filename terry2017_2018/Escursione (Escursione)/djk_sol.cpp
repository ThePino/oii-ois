#include <bits/stdc++.h>

using namespace std;

#define MAXN 100

int R,C,mappa[MAXN][MAXN],dista[MAXN][MAXN];
bool visti[MAXN][MAXN];

const int maxvs = 4;
int moves[][2] = {{0,1},{0,-1},{1,0},{-1,0}};

inline bool can_move(int y,int x){
	if(y < 0 || y >= R || x < 0 || x >= C)return false;
	return true;
}

priority_queue <pair <int,pair <int,int>> >q;
int solve(){
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			dista[i][j] = INT_MAX;
			visti[i][j] = false;
		} 
	}
	dista[0][0] = 0;
	q.push({0,{0,0}});
	while(!q.empty()){
		int y = q.top().second.first;
		int x = q.top().second.second;
		q.pop();
		if(visti[y][x])continue;
		visti[y][x] = true;
		for(int i = 0; i < maxvs; i++){
			int cy = y + moves[i][0];
			int cx = x + moves[i][1];
			if(can_move(cy,cx)){
				int w = abs(mappa[y][x] - mappa[cy][cx]);
				w = max(w,dista[y][x]);
				if(w < dista[cy][cx]){
					dista[cy][cx] = w;
					q.push({-w,{cy,cx}});
				}
			}
		}
	}
	return dista[R - 1][C - 1];
}


int main(){
	#ifdef EVAL
		freopen("escursione_input_1.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		cin >> R >> C;
		for(int i2 = 0; i2 < R; i2++){
			for(int i3 = 0; i3 < C; i3++){
				cin >> mappa[i2][i3];
			}
		}
		cout << "Case #" << i << ": " << solve() << '\n';
	}
}