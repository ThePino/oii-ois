#include <bits/stdc++.h>

using namespace std;

int main(){
  const int MAXC = 200;
  int T;
  cin >> T;
  for(int t = 1; t <= T; t++){
    int N, B;
    cin >> N >> B;
    vector <int> C(N), P(N);
    for(int i = 0; i < N; i++){
      cin >> C[i] >> P[i];
    }
    vector <int> dp(N * MAXC + 1, INT_MAX);
    dp[0] = 0;
    for(int i = 0; i < N; i++){
      for(int j = MAXC * N; j >= 0; j--){
        if(dp[j] != INT_MAX){
          int z = j + C[i];
          int nc = dp[j] + P[i];
          dp[z] = min(dp[z], nc);
        }
      }
    }
    int ans = 0;
    for(int i = 0; i < (int) dp.size(); i++){
      if(dp[i] <= B){
        ans = i;
      }
    }
    cout << "Case #" << t << ": " << ans << '\n';
  }
  return 0;
}
