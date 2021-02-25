#include <iostream>
#include <utility>
using namespace std;
int main() {
    int n;
    int ans[51];
    pair<int,int> p[51];
    
    cin >> n;
    for(int i=0; i<n; i++)
        cin >> p[i].first >> p[i].second;

    for(int i=0; i<n; i++) {
        int cnt = 1;
        for(int j=0; j<n; j++) {
            if(j == i)
                continue;
            if(p[i].first < p[j].first && p[i].second < p[j].second)
                cnt++;
        }
        ans[i] = cnt;
    }
    for(int i=0; i<n; i++)
        cout << ans[i] << " ";
    cout << '\n';
    return 0;
}