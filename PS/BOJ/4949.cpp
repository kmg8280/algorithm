#include <iostream>
#include <stack>
#include <string.h>
using namespace std;
int main() {
    while(1) {
        char s[200];
        cin.getline(s, 200);
        int len = strlen(s);
        stack<char> stk;
        bool ans = true;
        if(len == 1 && s[0] == '.')
            break;
        for(int i=0; i<len; i++) {
            if(s[i]=='(' || s[i]=='[') {
                stk.push(s[i]);
            }else if(s[i]==')') {
                if(stk.empty())
                    ans = false;
                else
                    if(stk.top() == '(')
                        stk.pop();
                    else
                        ans = false;
            }else if(s[i]==']') {
                if(stk.empty())
                    ans = false;
                else
                    if(stk.top() == '[')
                        stk.pop();
                    else 
                        ans = false;
            }
        }
        if(!stk.empty())
            ans = false;
        if(ans)
            cout << "yes" << '\n';
        else
            cout << "no" << '\n';
        
    }
    return 0;
}