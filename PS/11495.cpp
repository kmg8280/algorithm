#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<map>
#include<stdlib.h>
#include<queue>
#include<stdio.h>
#include<memory.h>
#include<math.h>
using namespace std;
typedef long long  ll;
typedef pair<int, int> P;
#define MAX 30000000
#define SOURCE 0
#define SINK 2545
int xy[4][2] = { {-1,0},{1,0},{0,1},{0,-1} };
struct node {
	int from;
	int to;
	int flow;
	int cap;
	int rev;
};
int n, m;
int table[51][51];
int num[51][51];
bool visit[2550];
void add_edge(int from, int to, int cap, vector<node> edge[])
{
	edge[from].push_back({ from,to,0,cap, (int)edge[to].size() });
	edge[to].push_back({ to,from,0,0, (int)edge[from].size() - 1 });
}
int dfs(int u, int pushed,vector<node> edge[])
{ // int 로 내가 흘려보낸 플로우 양 리턴
	visit[u] = 1;
	if (u == SINK)
		return pushed; // 지금까지 흐른 양
	for (auto& v : edge[u])
	{ // 값 직접수정을 위해 &붙임
		if (v.cap - v.flow == 0) continue; // 못흐른다.
		if (visit[v.to]) continue; // 방문함
		int tmp = dfs(v.to, min(v.cap - v.flow, pushed),edge);
		if (tmp > 0) {
			v.flow += tmp;
			edge[v.to][v.rev].flow -= tmp;
			return tmp;
		}
	}
	return 0; // 경로가 없다.
}
void test_case()
{
	vector<node> edge[2550];
	int cnt = 0;
	int total = 0;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> table[i][j];	
			total += table[i][j];
			num[i][j] = ++cnt;
		}
	}
	

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if ((i + j) % 2 == 0)
				add_edge(SOURCE, num[i][j], table[i][j], edge);
			else
				add_edge(num[i][j], SINK, table[i][j], edge);
			for (int k = 0; k < 4; k++)
			{
				int nxt_x = i + xy[k][0];
				int nxt_y = j + xy[k][1];
				if (!(1 <= nxt_x && nxt_x <= n && 1 <= nxt_y && nxt_y <= m))
					continue;
				if ((i+j) % 2 == 0)
				{
					//cout << "check : " << num[i][j] << " " << num[nxt_x][nxt_y] << '\n';
					add_edge(num[i][j], num[nxt_x][nxt_y], MAX, edge);
				}

			}
		}
	}

	int ans = 0;
	while (1)
	{
		memset(visit, false, sizeof(visit));
		int f = dfs(SOURCE, 0x7fffffff, edge);
		if (f == 0) break;
		ans += f;
	}
	cout << total - ans << '\n';
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