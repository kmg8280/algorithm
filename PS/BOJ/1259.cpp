#include <iostream>
#include <string>
using namespace std;

void test_case(string s) {
    int left = 0;
    int right = s.length() - 1;
    while(left <= right) {
        if(s[left] != s[right]) {
            cout << "no" << '\n';
            return;
        }
        left++;
        right--;
    }
    cout << "yes" << '\n';
}

int main() {
    string s;
    
    while(1) {
        cin >> s;
        if(s == "0")
            break;
        test_case(s);
    }
    return 0;
}