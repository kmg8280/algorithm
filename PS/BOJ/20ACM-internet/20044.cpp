#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> team(n*2);
    for(int i=0; i<n*2; i++) {
        cin >> team[i];
    }
    sort(team.begin(), team.end());

    int ans = 0x7fffffff;
    for(int i=0; i<n; i++) {
        int other = n*2 - (i+1);
        int sum = team[i] + team[other];
        if(ans > sum) {
            ans = sum;
        }
    }
    cout << ans << '\n';
    return 0;
}