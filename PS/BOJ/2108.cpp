#include <iostream>
#include <iomanip>
#include <math.h>
#include <algorithm>
using namespace std;
int arr[500000];
int cnt[8001];
int main() {
    int n;
    cin >> n;

    double sum = 0;
    int max_cnt = 0;
    for(int i=0; i<n; i++) {
        cin >> arr[i];
        sum+=arr[i];
        cnt[arr[i]+4000]++;
        if(max_cnt < cnt[arr[i]+4000])
            max_cnt = cnt[arr[i]+4000];
    }

    sort(arr, arr + n);

    cout << floor(sum / n + 0.5) << '\n';
    cout << arr[n/2] << '\n';
    bool check = false;
    int max_cnt_ans = -1;
    for(int i=0; i<=8000; i++) {
        if(cnt[i] == max_cnt) {
            if(!check) {
                max_cnt_ans = i;
                check = true;
            }else {
                max_cnt_ans = i;
                break;
            }
        }
    }
    cout << max_cnt_ans - 4000 << '\n';
    cout << arr[n-1] - arr[0] << '\n';
    return 0;
}