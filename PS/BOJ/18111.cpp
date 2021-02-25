#include <iostream>
using namespace std;
int main() {
    int n, m, b;
    int mc[501][501];
    int time = 0x7fffffff;
    int ans;
    cin >> n >> m >> b;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> mc[i][j];
    for(int h=256; h>=0; h--) {
        int need_more = 0;
        int get_block = 0;
        int result_time = 0x7fffffff;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(mc[i][j] < h)
                    need_more += (h - mc[i][j]);
                else if(mc[i][j] > h)
                    get_block += (mc[i][j] - h);
            }
        }
        if(need_more <= get_block + b) {
            result_time = need_more + get_block * 2;
        }
        if(result_time < time) {
            time = result_time;
            ans = h;
        }
    }
    cout << time << " " << ans << '\n';
    return 0;
}