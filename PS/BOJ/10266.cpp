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
int p[200001];
int s[400001];
int n;
int fail[200001];
void makeFail()
{
	fail[0] = -1;
	int i, j;
	i = -1; j = 0;
	while (j < n)
	{
		if (i == -1 || p[i] == p[j])
		{
			i++;
			j++;
			fail[j] = i;
		}
		else
			i = fail[i];
	}
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> p[i];
	for (int i = 0; i < n; i++)
		cin >> s[i];
	sort(p, p + n);
	sort(s, s + n);
	p[n] = p[0];
	s[n] = s[0];
	for (int i = 0; i < n; i++)
	{
		p[i] = p[i + 1] - p[i];
		if (p[i] < 0)
			p[i] += 360000;
		s[i] = s[i + 1] - s[i];
		if (s[i] < 0)
			s[i] += 360000;
	}
	for (int i = n; i < 2 * n; i++)
		s[i] = s[i - n];
	makeFail();
	int i, j;
	i = j = 0;
	int ans = false;

	while (j < 2 * n)
	{
		if (i < 0 || p[i] == s[j])
		{
			i++;
			j++;
		}
		else
			i = fail[i];
		if (i == n)
		{
			ans = true;
			break;
		}
	}
	if (ans)
		cout << "possible" << '\n';
	else
		cout << "impossible" << '\n';
	return 0;
}