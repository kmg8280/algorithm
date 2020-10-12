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
#define MAX 201
#define INF 987654321
typedef long long  ll;
typedef pair<int, int> P;
vector<pair<int, int>> range(MAX);
vector<int> adj[MAX];
int A[MAX], B[MAX], dist[MAX];
bool used[MAX];
int n, m;
void bfs()
{
	queue<int> q;

	for (int i = 1; i <= n; i++)
	{
		if (!used[i])
		{
			dist[i] = 0;
			q.push(i);
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
			if (B[b] != -1 && dist[B[b]] == INF)
			{
				dist[B[b]] = dist[a] + 1;
				q.push(B[b]);
			}
		}
	}
}

bool dfs(int a)
{
	for (int& b : adj[a])
	{
		if (B[b] == -1 || (dist[B[b]] == dist[a] + 1 && dfs(B[b])))
		{
			used[a] = true;
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	return false;
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	int tp;
	int x, y, v;
	for (int i = 1; i <= n; i++)
	{
		range[i].first = INF;
		range[i].second = 0;
	}
	for (int i = 0; i < m; i++)
	{
		cin >> tp >> x >> y >> v;
		if (tp == 1)
		{
			for (int j = x; j <= y; j++)
				if (range[j].second < v)
					range[j].second = v;
		}
		else
		{
			for (int j = x; j <= y; j++)
				if (range[j].first > v)
					range[j].first = v;
		}
	}


	for (int i = 1; i <= n; i++)
	{
		int l = 1, r = n;
		if (range[i].first != INF)
			l = range[i].first;
		if (range[i].second != 0)
			r = range[i].second;
		cout << l << " " << r << '\n';
		for (int j = l; j <= r; j++)
			adj[i].push_back(j);
	}

	int match = 0;
	fill(A, A + MAX, -1);
	fill(B, B + MAX, -1);
	while (1)
	{
		bfs();
		int flow = 0;
		for (int i = 1; i <= n; i++)
			if (!used[i] && dfs(i))
				flow++;
		if (flow == 0)
			break;
		match += flow;
	}

	if (match == n)
	{
		for (int i = 1; i <= n; i++)
			cout << A[i] << " ";
		cout << '\n';
	}
	else
		cout << -1 << '\n';
	return 0;
}