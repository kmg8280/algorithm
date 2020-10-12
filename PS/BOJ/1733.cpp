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
#define SOURCE 0
#define SINK 2000001
#define MAX 2000010
#define TEMP 1000000
int n;
struct BipartiteMatching
{
	int n, m;
	vector<vector<int> > graph;
	vector<int> matched, match;
	vector<int> edgeview;
	vector<int> level;
	vector<int> reached[2];
	BipartiteMatching(int n, int m) : n(n), m(m), graph(n), matched(m, -1), match(n, -1) {}

	bool assignLevel()
	{
		bool reachable = false;
		level.assign(n, -1);
		reached[0].assign(n, 0);
		reached[1].assign(m, 0);
		queue<int> q;
		for (int i = 0; i < n; i++) {
			if (match[i] == -1) {
				level[i] = 0;
				reached[0][i] = 1;
				q.push(i);
			}
		}
		while (!q.empty()) {
			auto cur = q.front(); q.pop();
			for (auto adj : graph[cur]) {
				reached[1][adj] = 1;
				auto next = matched[adj];
				if (next == -1) {
					reachable = true;
				}
				else if (level[next] == -1) {
					level[next] = level[cur] + 1;
					reached[0][next] = 1;
					q.push(next);
				}
			}
		}
		return reachable;
	}

	int findpath(int nod) {
		for (int& i = edgeview[nod]; i < graph[nod].size(); i++) {
			int adj = graph[nod][i];
			int next = matched[adj];
			if (next >= 0 && level[next] != level[nod] + 1) continue;
			if (next == -1 || findpath(next)) {
				match[nod] = adj;
				matched[adj] = nod;
				return 1;
			}
		}
		return 0;
	}

	int solve()
	{
		int ans = 0;
		while (assignLevel()) {
			edgeview.assign(n, 0);
			for (int i = 0; i < n; i++)
				if (match[i] == -1)
					ans += findpath(i);
		}
		return ans;
	}
};
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n;
	int f, b;
	BipartiteMatching bm(MAX, MAX);
	for (int i = 0; i < n; i++)
	{
		cin >> f >> b;
		bm.graph[i].push_back(n + f);
		bm.graph[i].push_back(n + b);
	}

	int ans = bm.solve();
	if (ans != n)
		cout << -1 << '\n';
	else
	{
		for (int i = 0; i < n; i++)
		{
			cout << bm.match[i]-n << '\n';
		}
	}
	return 0;
}