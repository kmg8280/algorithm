#include <iostream>
using namespace std;
int num[10001];
bool check(int a) {
    int cnt = 0;
    while(a > 0) {
        int mod = a % 10;
        if(mod == 6) {
            cnt++;
            if(cnt == 3)
                return true;
        }else {
            cnt = 0;
        }
        a /= 10;
    }
    return false;
}
int main() {
    int n;
    cin >> n;
    int idx = 0;
    int cnt = 666;
    while(1) {
        if(idx == n)
            break;
        bool result = check(cnt);
        if(result) {
            num[idx++] = cnt;
        }
        cnt++;
    }
    cout << num[idx - 1] << '\n';
    return 0;
}