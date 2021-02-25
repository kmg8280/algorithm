#include <iostream>
#include <stack>
using namespace std;
int main() {
    int n, save, num;
    stack<int> stk;
    cin >> n;
    int ans = 0;
    for(int i=0; i<n; i++) {
        cin >> num;
        if(num==0)
            stk.pop();
        else
            stk.push(num);
    }
    while(!stk.empty()) {
        ans += stk.top();
        stk.pop();
    }
    cout << ans << '\n';
    return 0;
}