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
map<int, int> check;
int a[200001];
void test_case()
{
	int n, k, d;
	cin >> n >> k >> d;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	int ans;
	int cnt = 0;
	for (int i = 0; i < d; i++)
		if (check[a[i]]==0)
		{
			cnt++;
			check[a[i]]++;
		}
		else
			check[a[i]]++;

	ans = cnt;
	int l, r;
	l = 0;
	r = d;

	while (r < n)
	{
		check[a[l]]--;
		if (check[a[l]] == 0)
			cnt--;
		l++;
		if (check[a[r]] == 0)
		{
			cnt++;
			check[a[r]]++;
		}
		else
			check[a[r]]++;

		if (cnt < ans)
			ans = cnt;
		r++;
	}
	cout << ans << '\n';
	check.clear();
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		test_case();
	return 0;
}