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
#define INF 987654321
#define TEMP 50
#define SINK 101
#define MAX 120
int xy[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
int n;
struct MaxFlowDinic {
	typedef long long cap_t;

	struct Edge
	{
		int next;
		int inv; /* inverse edge index */
		cap_t res; /* residual */
		cap_t save; /* save whatever you want. TODO: just remove if you don't need */
	};

	int n;
	vector<vector<Edge>> graph;

	vector<int> q, l, start;

	void init(int _n) {
		n = _n;
		graph.resize(n);
		for (int i = 0; i < n; i++) graph[i].clear();
	}
	void addEdge(int s, int e, cap_t cap, cap_t caprev = 0) {
		Edge forward = { e, (int)graph[e].size() + (s == e ? 1 : 0), cap, -1 };
		Edge reverse = { s, (int)graph[s].size(), caprev, -1 };
		graph[s].push_back(forward);
		graph[e].push_back(reverse);
	}

	bool assignLevel(int source, int sink) {
		int t = 0;
		l.assign(n, 0);
		l[source] = 1;
		q[t++] = source;
		for (int h = 0; h < t && !l[sink]; h++) {
			int cur = q[h];
			for (const auto& edge : graph[cur]) {
				int next = edge.next;
				if (l[next]) continue;
				if (edge.res > 0) {
					l[next] = l[cur] + 1;
					q[t++] = next;
				}
			}
		}
		return l[sink] != 0;
	}

	cap_t blockFlow(int cur, int sink, cap_t currentFlow) {
		if (cur == sink) return currentFlow;
		for (auto& i = start[cur]; i < (int)graph[cur].size(); i++) {
			int next = graph[cur][i].next;
			if (graph[cur][i].res == 0 || l[next] != l[cur] + 1)
				continue;
			if (cap_t res = blockFlow(next, sink, min(graph[cur][i].res, currentFlow))) {
				int inv = graph[cur][i].inv;
				graph[cur][i].res -= res;
				graph[next][inv].res += res;
				return res;
			}
		}
		return 0;
	}

	cap_t solve(int source, int sink)
	{
		if (source == sink) {
			// invalid case
			return -1;
		}
		q.resize(n);
		l.resize(n);
		cap_t ans = 0;
		while (assignLevel(source, sink)) {
			start.assign(n, 0);
			while (cap_t flow = blockFlow(source, sink, numeric_limits<cap_t>::max())) {
				ans += flow;
			}
		}
		return ans;
	}
};
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n;
	MaxFlowDinic mf;
	int row[51], col[51];
	int total = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> row[i];
		total += row[i];
	}
	for (int i = 1; i <= n; i++)
		cin >> col[i];
	int l = 0, r = 10000;
	while (l < r)
	{
		int mid = (l + r) / 2;
		mf.init(MAX);
		for (int i = 1; i <= n; i++)
		{
			mf.addEdge(SOURCE, i, row[i]);
			mf.addEdge(TEMP + i, SINK, col[i]);
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				mf.addEdge(i, TEMP + j, mid);

		int ans = mf.solve(SOURCE, SINK);
		if (ans == total)
		{
			r = mid;
			//cout << mid << '\n';
		}
		else
			l = mid + 1;
	}

	mf.init(MAX);
	for (int i = 1; i <= n; i++)
	{
		mf.addEdge(SOURCE, i, row[i]);
		mf.addEdge(TEMP + i, SINK, col[i]);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			mf.addEdge(i, TEMP + j, r);
	mf.solve(SOURCE, SINK);
	cout << r << '\n';
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << r - mf.graph[i][j].res << " ";
		cout << '\n';
	}
	return 0;
}