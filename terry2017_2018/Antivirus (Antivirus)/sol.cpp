#include <bits/stdc++.h>

using namespace std;

void solve(int N1, int N2, int N3, int N4,int M, string &F1, string &F2, string &F3, string &F4,vector <int> &ans){
	vector <string> files = {F1,F2,F3,F4};
	bool ok = false;
	int i0 = 0;
	while(!ok){
		ok = true;
		string cur = F1.substr(i0,M);
		for(int i = 0; i < 4; i++){
			size_t res = files[i].find(cur);
			if(res == string::npos){
				ok = false;
				break;
			}else{
				ans[i] = res;
			}
		}
		i0++;
	}
}

int main(){
	#ifdef EVAL
		freopen("antivirus_input_1.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		int N1,N2,N3,N4;
		cin >> N1 >> N2 >> N3 >> N4;
		int M;
		cin >> M;
		string F1,F2,F3,F4;
		cin >> F1 >> F2 >> F3 >> F4;
		vector <int> ans(M,0);
		solve(N1,N2,N3,N4,M,F1,F2,F3,F4,ans);
		//Case #t: p1 p2 p3 p4
		cout << "Case #" << t << ": ";
		for(int i = 0; i < 4; i++){
			cout << ans[i] << " ";
		} 
		cout << '\n';
	}
	return 0;
}