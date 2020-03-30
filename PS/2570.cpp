#include<iostream>
#include<algorithm>
#include<math.h>
#include<utility>
#include<memory.h>
#include<queue>
#include<vector>
#include<string>
using namespace std;
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	pair<int, int> s[200];
	int map[600][600];
	// ¡ﬂΩ…¡° 250, 250
	for (int i = 0; i < k; i++)
		cin >> s[i].first >> s[i].second;
	
	int nxt_x, nxt_y;
	pair<int, int> st = { 250,250 };
	for (int i = 0; i < k; i++)
	{
		cin >> nxt_x >> nxt_y;
		int temp_x = s[i].first - nxt_x;
		int tmep_y = s[i].second - nxt_y;

	}

	return 0;
}