#include <iostream>
#include <string>
using namespace std;
string chess[51];
int tpToInt(char tp) {
    if(tp == 'W') {
        return 0;
    }else {
        return 1;
    }
}
int check(int n, int m) {
    int result = 0x7fffffff;
    for(int tp=0; tp<2; tp++) {
        int cnt = 0;
        for(int i=n; i<n+8; i++) {
            int start = (tp + i) % 2;
            for(int j=m; j<m+8; j++) {
                int now_tp = tpToInt(chess[i][j]);
                if(now_tp!=start)
                    cnt++;
                start = (start + 1) % 2;
            }
        }
        if(cnt < result)
            result = cnt;
    }
    return result;
}
int main() {
    int n, m;
    cin >> n >> m;
    for(int i=0; i<n; i++)
        cin >> chess[i];
    int ans = 0x7fffffff;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(i+8<=n && j+8 <=m) {
                int cnt = check(i,j);
                if(cnt < ans)
                    ans = cnt;
            }
        }
    }
    cout << ans << '\n'; 
    return 0;
}