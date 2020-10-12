#include<iostream>
#include<string>
using namespace std;
typedef long long ll;
#define MOD 1000000009
ll fail[101];
ll dp[101][101];
void makeFail(string &s){
	int i, j;
	i = -1; j = 0;
	int m = s.length();
	fail[0] = -1;
	while (j < m) {
		if (i == -1 || s[i]==s[j]){
			i++;
			j++;
			fail[j] = i;
		}
		else
			i = fail[i];
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string s;
	int n;
	cin >> n;
	cin >> s;
	makeFail(s);
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < s.length(); j++) {
			for (int k = 0; k < 26; k++) {
				int tmp = j;
				while (tmp >= 0 && s[tmp] != k + 'a')
					tmp = fail[tmp];
				tmp++;
				//cout << i << " " << tmp << '\n';
				//cout << dp[i - 1][j] << '\n';
				dp[i][tmp] += dp[i - 1][j];
				dp[i][tmp] %= MOD;
			}
		}
		dp[i][s.length()] += dp[i - 1][s.length()] * 26;
		dp[i][s.length()] %= MOD;
	}

	cout << dp[n][s.length()] << '\n';
	return 0;
}