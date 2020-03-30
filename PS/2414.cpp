#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<map>
#include<stdlib.h>
#include<queue>
#include<stdio.h>
#include<memory.h>
using namespace std;
typedef long long  ll;
typedef pair<int, int> P;
struct node {
	int from;
	int to;
	int flow;
	int cap;
	int rev;
};
int n, m;
char table[51][51];
int num[51][51];
pair<int, int> dot[2501];
vector<node> edge[2501];
int p = 500;
bool visited[2501];
int s, t;
void add_edge(int from, int to, int cap)
{
	edge[from].push_back({ from,to,0,cap,(int)edge[to].size() });
	edge[to].push_back({ to,from,0,0,(int)edge[from].size() - 1 });
}
int dfs(int u, int pushed)
{
	visited[u] = 1;
	if (u == t)
		return pushed;
	for (auto& v : edge[u])
	{
		if (v.cap - v.flow == 0) continue;
		if (visited[v.to]) continue;
		int tmp = dfs(v.to, min(v.cap - v.flow, pushed));
		if (tmp > 0) {
			v.flow += tmp;
			edge[v.to][v.rev].flow -= tmp;
			return tmp;
		}
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n >> m;
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> table[i][j];
			if (table[i][j] == '*')
				num[i][j] = ++cnt;
		}
	}
	int number = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if(table[i][j]=='*')
			{
				dot[num[i][j]].first = number;
				if (j + 1 <= m && table[i][j + 1] == '.')
					number++;
				else if (j == m && table[i][j] == '*')
					number++;
			}
		}
	}

	number = 1;

	for (int j = 1; j <= m; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			if (table[i][j] == '*')
			{
				dot[num[i][j]].second = number;
				if (i + 1 <= n && table[i+1][j] == '.')
					number++;
				else if (i == n && table[i][j] == '*')
					number++;
			}
		}
	}

	int max_x = 1;
	int max_y = 1;
	for (int i = 1; i <= cnt; i++)
	{
		add_edge(dot[i].first, dot[i].second + p, 1);
		if (max_x < dot[i].first)
			max_x = dot[i].first;
		if (max_y < dot[i].second)
			max_y = dot[i].second;
	}

	for (int i = 1; i <= max_x; i++)
		add_edge(0, i, 1);
	for (int i = 1; i <= max_y; i++)
		add_edge(i+p, 2500, 1);
	s = 0;
	t = 2500;
	int ans = 0;
	while (1)
	{
		memset(visited, false, sizeof(visited));
		int f = dfs(s, 0x7fffffff);
		if (f == 0) break;
		//cout << f << '\n';
		ans += f;
	}
	cout << ans << '\n';
	return 0;
}