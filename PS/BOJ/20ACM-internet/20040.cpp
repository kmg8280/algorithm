#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
typedef long long ll;

int n, m;
int dot[500001];
int find(int x) {
    if(dot[x]==x)
        return x;
    else {
        return dot[x] = find(dot[x]);
    }
}

bool unionDot(int x, int y) {
    x = find(x);
    y = find(y);

    if(x!=y) {
        dot[y] = x;
        return false;
    }else {
        return true;
    }
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i=0; i<n; i++) {
        dot[i] = i;
    }

    int a, b;
    bool ans_check = false;
    int ans = 0;
    for(int i=0; i<m; i++) {
        cin >> a >> b;
        ans_check = unionDot(a,b);
        if(ans_check) {
            ans = i + 1;
            break;
        }
    }

    cout << ans << '\n';
    return 0;
}