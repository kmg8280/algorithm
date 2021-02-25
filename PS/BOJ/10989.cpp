#include <iostream>
using namespace std;
int cnt[10001];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, num;
    cin >> n;
    while(n--) {
        cin >> num;
        cnt[num]++;
    }
    for(int i=1; i<=10000; i++) {
        while(cnt[i]--) {
            cout << i << '\n';
        }
    }
    return 0;
}