#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
vector<pair<int,int> > p;
int main() {
    int n, x, y;
    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> x >> y;
        p.push_back(make_pair(x, y));
    }
        
    sort(p.begin(), p.end());
    for(int i=0; i<n; i++) {
        cout << p[i].first << " " << p[i].second << '\n';
    }
    return 0;
}