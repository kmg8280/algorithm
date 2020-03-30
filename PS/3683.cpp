#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<map>
#include<stdlib.h>
#include<queue>
#include<stdio.h>
#include<memory.h>
#include<string>
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
int n, m, v;
int s, t;
vector<node> edge[1011];
bool visited[1011];
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
void test_case()
{
	cin >> n >> m >> v;
	string a, b;
	vector<pair<int,int>> c;
	vector<pair<int,int>> d;
	for (int i = 1; i <= v; i++)
	{
		cin >> a >> b;
		int x = stoi(a.substr(1, 1000));
		int y = stoi(b.substr(1, 1000));
		//cout << x << " " << y << '\n';
		if (a[0] == 'C')
		{
			c.push_back({ x,y });
		}
		else if (a[0] == 'D')
		{
			d.push_back({ x,y });
		}
	}
	int p = 500;

	for (int i = 0; i < c.size(); i++)
	{
		for (int j = 0; j < d.size(); j++)
		{
			if (c[i].first == d[j].second)
				add_edge(i + 1, j + 1 + p, 1);
			else if (c[i].second == d[j].first)
				add_edge(i + 1, j + 1 + p, 1);
		}
	}
	for (int i = 1; i <= c.size(); i++)
		add_edge(0, i, 1);

	for (int i = 1; i <= d.size(); i++)
		add_edge(i + p, 1010, 1);

	s = 0;
	t = 1010;

	int ans = 0;
	while (1)
	{
		memset(visited, false, sizeof(visited));
		int f = dfs(s, 0x7fffffff);
		if (f == 0) break;
		//cout << f << '\n';
		ans += f;
	}
	cout << v-ans << '\n';

	for (int i = 0; i <= 1010; i++)
		edge[i].clear();
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