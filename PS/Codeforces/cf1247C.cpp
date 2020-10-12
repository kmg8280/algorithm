#include<iostream>
#include<string>
#include<stack>
#include<math.h>
#include<memory.h>
#include<utility>
#include<algorithm>
#include<vector>
#include<map>
#include<stdlib.h>
#include<queue>
#include<stdio.h>
using namespace std;
typedef long long  ll;
typedef pair<int, int> P;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n, p;
	cin >> n >> p;
	int check = false;
	int ans = 0;
	for (int i = 1; i <= 31; i++)
	{
		int temp = n - p * i;
		int save = temp;
		int cnt = 0;
		while (temp > 0)
		{
			if (temp % 2 == 1)
				cnt++;
			temp = temp >> 1;
			//cout << temp << '\n';
		}
		if (cnt <= i && save >= i)
		{
			check = true;
			ans = i;
			break;
		}
	}
	if (check)
		cout << ans << '\n';
	else
		cout << -1 << '\n';
	return 0;
}