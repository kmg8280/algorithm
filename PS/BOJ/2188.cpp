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

vector<node> edge[100010];
bool visit[100010];
int s, t;
void add_edge(int from, int to, int cap)
{
	edge[from].push_back({ from,to,0,cap,(int)edge[to].size() });
	edge[to].push_back({ to,from,0,0,(int)(edge[from].size() - 1) });
}
int dfs(int u, int pushed)
{ // int 로 내가 흘려보낸 플로우 양 리턴
	visit[u] = 1;
	if (u == t)
		return pushed; // 지금까지 흐른 양
	for (auto& v : edge[u])
	{ // 값 직접수정을 위해 &붙임
		if (v.cap - v.flow == 0) continue; // 못흐른다.
		if (visit[v.to]) continue; // 방문함
		int tmp = dfs(v.to, min(v.cap - v.flow, pushed));
		if (tmp > 0) {
			v.flow += tmp;
			edge[v.to][v.rev].flow -= tmp;
			return tmp;
		}
	}
	return 0; // 경로가 없다.
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n, m;

	cin >> n >> m;
	s = 0; // 소스
	t = m+n+1; // 싱크
	int k;
	for (int i = 1; i <= n; i++)
	{
		cin >> k;
		add_edge(0, i, 1);
		for (int j = 0; j < k; j++)
		{
			int nxt;
			cin >> nxt;
			add_edge(i, nxt+n, 1);
		}
	}
	for (int i = 1; i <= m; i++)
		add_edge(i + n, n + m + 1, 1);

	int ans = 0;
	while (1)
	{
		memset(visit, false, sizeof(visit));
		int f = dfs(s, 0x7fffffff);
		if (f == 0) break;
		ans += f;
	}
	cout << ans << '\n';
	return 0;
}