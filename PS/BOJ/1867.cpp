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
int n, k;
vector<node> edge[1010];
bool visited[1010];
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

	cin >> n >> k;

	int x, y;
	
	for (int i = 0; i < k; i++)
	{
		cin >> x >> y;
		add_edge(x, y + n, 1);
	}

	for (int i = 1; i <= n; i++)
	{
		add_edge(0, i, 1);
		add_edge(i + n, 2 * n + 1, 1);
	}
	s = 0;
	t = 2 * n + 1;

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