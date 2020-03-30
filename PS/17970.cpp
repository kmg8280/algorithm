#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<map>
#include<stdlib.h>
#include<queue>
#include<math.h>
#include<stdio.h>
#include<memory.h>
#include<string>
using namespace std;
typedef long long  ll;
typedef pair<int, int> P;
#define MAX 100010
int pos[100010];
vector<int> road;
vector<int> other_road;
vector<bool> jump;
int n;
bool chkList(std::vector<int> &ans, int& l, int& r, int& ole, int& ori)
{
	if (road[l] == other_road[ole])
	{
		ans.push_back(road[l]);
		jump[l] = true;
		l = (l - 1 + n) % n;
		ole = (ole - 1 + n) % n;
	}
	else if (road[l] == other_road[ori])
	{
		ans.push_back(road[l]);
		jump[l] = true;
		l = (l - 1 + n) % n;
		ori = (ori + 1) % n;
	}
	else if (road[r] == other_road[ole])
	{
		ans.push_back(road[r]);
		jump[r] = true;
		r = (r + 1) % n;
		ole = (ole - 1 + n) % n;
	}
	else if (road[r] == other_road[ori])
	{
		ans.push_back(road[r]);
		jump[r] = true;
		r = (r + 1) % n;
		ori = (ori + 1) % n;
	}
	else
		return false;
	return true;
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;

	road.resize(n);
	other_road.resize(n);

	for (int i = 0; i < n; i++)
		cin >> road[i];
	for (int i = 0; i < n; i++)
	{
		cin >> other_road[i];
		pos[other_road[i]] = i;
	}
	int stp, ostp;
	jump.resize(n + 1, false);
	for (int i = 0; i < n; i++)
	{ 
		if (jump[i])
			continue;
		jump[i] = true;
		stp = i;
		ostp = pos[road[i]];
		int l = (i - 1 + n) % n;
		int r = (i + 1) % n;
		int ole = (ostp - 1 + n) % n;
		int ori = (ostp + 1) % n;
		vector<int> ans;
		bool check = true;
		ans.push_back(road[i]);
		while (ans.size() != n)
		{
			if (!chkList(ans, l, r, ole, ori))
			{
				check = false;
				break;
			}
		}
		if (check)
		{
			for (int& x : ans)
				cout << x << " ";
			cout << '\n';
			return 0;
		}
	}

	cout << -1 << '\n';
	return 0;
}