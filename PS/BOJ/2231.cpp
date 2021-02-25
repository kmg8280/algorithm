#include <iostream>
using namespace std;
bool check_gen(int i, int n) {
    int sum = i;
    while(i > 0) {
        sum += i % 10;
        i /= 10;
    }
    if(sum == n)
        return true;
    return false;
}
int main() {
    int n;
    cin >> n;
    bool check = false;
    for(int i=0; i<=n; i++) {
        if(check_gen(i, n)) {
            cout << i << '\n';
            check = true;
            break;
        }
    }
    if(!check)
        cout << 0 << '\n';
    return 0;
}