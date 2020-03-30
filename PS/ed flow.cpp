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
int cost[100010]; // 얼마나 흘렀는지
int s, t;
void add_edge(int from, int to, int cap)
{
	edge[from].push_back({ from,to,0,cap,(int)edge[to].size() });
	edge[to].push_back({ to,from,0,0,(int)(edge[from].size() - 1) });
}
int trace[100010]; // 역추적하는 배열 필요함.
int trace_num[100010];
int bfs(int start, int end)
{ // int 로 내가 흘려보낸 플로우 양 리턴
	queue<int> qu, qpushed;
	visit[start] = 1;
	qu.push(start);
	qpushed.push(0x7fffffff);
	while (!qu.empty())
	{
		int u = qu.front();
		qu.pop();
		int pushed = qpushed.front();
		qpushed.pop();
		if (u == t)
			break;
		for (int i=0; i<edge[u].size(); i++)
		{
			node v = edge[u][i];
			if (visit[v.to]) continue;
			if (v.cap - v.flow == 0) continue;
			qu.push(v.to);
			qpushed.push(min(pushed, v.cap - v.flow));
			visit[v.to] = 1;
			trace[v.to] = v.from;
			trace_num[v.to]=i;
			cost[v.to] = min(pushed, v.cap - v.flow);
		}
	}
	if (visit[t] == 0)
		return 0;

	int cur = end;

	while (cur != start)
	{
		int from = trace[cur];
		int to = cur;

		edge[from][trace_num[cur]].flow += cost[end];
		edge[to][edge[from][trace_num[cur]].rev].flow -= cost[end];

		cur = trace[cur];
	}

	return cost[end];
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n = 256, m;
	s = 'A'; // 소스
	t = 'Z'; // 싱크

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		char from, to;
		int cap;
		cin >> from >> to >> cap;
		add_edge(from, to, cap);
		add_edge(to, from, cap);
	}
	int ans = 0;
	while (1)
	{
		memset(visit, false, sizeof(visit));
		int f = bfs(s, t);
		if (f == 0) break;
		ans += f;
	}
	cout << ans << '\n';
	return 0;
}