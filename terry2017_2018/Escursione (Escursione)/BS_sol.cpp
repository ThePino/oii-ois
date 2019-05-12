#include <bits/stdc++.h>

using namespace std;

#define MAXN 100

int R,C,mappa[MAXN][MAXN];
bool visti[MAXN][MAXN];

const int maxvs = 4;
int moves[][2] = {{0,1},{0,-1},{1,0},{-1,0}};

inline bool can_move(int y,int x){
	if(y < 0 || y >= R || x < 0 || x >= C)return false;
	return true;
}

bool dfs(int y,int x,int mid){
	if(y == R - 1 && x == C - 1)return true;
	visti[y][x] = true;
	for(int i = 0; i < maxvs; i++){
		int cy = y + moves[i][0];
		int cx = x + moves[i][1];
		if(can_move(cy,cx) && abs(mappa[y][x] - mappa[cy][cx]) <= mid && !visti[cy][cx]){
			if(dfs(cy,cx,mid))return true;
		}
	}
	return false;
}

int solve(){
	int s = 0,e = 1000001,mid,sol;
	while(s <= e){
		for(int i = 0; i < R; i++){
			for(int j = 0; j < C; j++){
				visti[i][j] = false;
			}
		}
		mid = (s + e) / 2;
		if(dfs(0,0,mid)){
			sol = mid;
			e = mid - 1;
		}else{
			s = mid + 1;
		}
	}
	return sol;
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