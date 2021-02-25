#include <iostream>
#include <queue>
using namespace std;
int main() {
    int n, k;
    queue<int> q;
    cin >> n >> k;
    for(int i=1; i<=n; i++)
        q.push(i);
    cout << "<";
    while(!q.empty()) {
        int cnt = k - 1;
        while(cnt--) {
            q.push(q.front());
            q.pop();
        }
        cout << q.front();
        if(q.size() != 1)
            cout << ", ";
        q.pop();
    }
    cout << ">" << '\n';
}