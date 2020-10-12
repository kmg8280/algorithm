#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<map>
#include<stdlib.h>
#include<queue>
#include<stdio.h>
#include<memory.h>
#include<stack>
#include<math.h>
using namespace std;
typedef long long  ll;
typedef pair<int, int> P;
#define MAX 10000
#define INF 1000000000
int n;
int AG[MAX], BG[MAX], dist[MAX];
bool used[MAX];
vector<int> adj[MAX];
void bfs()
{
	queue<int> q;
	for (int i = 0; i < n; i++)
	{
		if (!used[i]) // 사용하지 않았다면 level 0이다.
		{
			dist[i] = 0;
			q.push(i); // level 0 인것 queue에 추가.
		}
		else
			dist[i] = INF;
	}

	while (!q.empty())
	{
		int a = q.front();
		q.pop();
		for (int& b : adj[a])
		{
			if (BG[b] != -1 && dist[BG[b]] == INF)
			{
				dist[BG[b]] = dist[a] + 1;
				q.push(BG[b]);
			}
		}
	}
}
bool dfs(int a)
{
	for (int& b : adj[a])
	{
		if (BG[b] == -1 || (dist[BG[b]] == dist[a] + 1 && dfs(BG[b])))
		{
			used[a]=true;
			AG[a] = b;
			BG[b] = a;
			return true;
		}
	}
	return false;
}
int main()
{
	//ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	while (scanf("%d", &n) > 0)
	{
		for (int i = 0; i < n; i++)
		{
			int job, sCnt;
			scanf("%d: (%d)", &job, &sCnt);
			for (int j = 0; j < sCnt; j++)
			{
				int server;
				scanf("%d", &server);
				adj[job].push_back(server - n);
			}
		}
		int match = 0;
		fill(AG, AG + MAX, -1);
		fill(BG, BG + MAX, -1);

		while (1)
		{
			bfs();

			int flow = 0;
			for (int i = 0; i < n; i++)
				if (!used[i] && dfs(i)) flow++;
			if (flow == 0)
				break;
			match += flow;
		}

		printf("%d\n", match);

		fill(used, used + MAX, false);
		for (int i = 0; i < n; i++)
			adj[i].clear();
	}

	return 0;
}