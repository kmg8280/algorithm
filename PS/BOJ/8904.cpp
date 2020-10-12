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
#define INF 10000000
#define S 0
#define E 605
#define TEMP 500
#define MAX 610
int n, m;
int s, d, w;
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
	void addNodes(int count) {
		n += count;
		graph.resize(n);
	}

	void addEdgeSave(int s, int e, cap_t cap, cap_t save) {
		Edge forward = { e, (int)graph[e].size() + (s == e ? 1 : 0), cap, save };
		Edge reverse = { s, (int)graph[s].size(), 0, -1 };
		graph[s].push_back(forward);
		graph[e].push_back(reverse);
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
void test_case()
{
	MaxFlowDinic mf;
	mf.init(MAX);
	cin >> m >> n;
	int max_d = -1;
	int total = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> s >> w >> d;
		if (d > max_d)
			max_d = d;
		total += w;
		for (int j = s; j < d; j++)
			mf.addEdge(j, TEMP + i, 1);
		mf.addEdge(TEMP + i, E, w);
	}
	
	for (int i = 1; i < max_d; i++)
		mf.addEdge(0, i, m);
	
	long long ans = mf.solve(S, E);
	//cout << total << " " << ans << '\n';
	if (total == ans) // 모든 가구 완성
	{
		vector<int> timeArray[101];
		for (int i = 1; i < max_d; i++)
		{
			int size = mf.graph[i].size();
			for (int j = 0; j < size; j++)
			{
				if (mf.graph[i][j].res == 0) // 흐른 곳
				{
					int idx = mf.graph[i][j].next - TEMP;
					if (!timeArray[idx].size())
					{
						timeArray[idx].push_back(i);
						timeArray[idx].push_back(i+1);
					}
					else
					{
						if (i - timeArray[idx][timeArray[idx].size() - 1] >= 1)
						{
							timeArray[idx].push_back(i);
							timeArray[idx].push_back(i + 1);
						}
						else
						{
							timeArray[idx][timeArray[idx].size() - 1] += 1;
						}
					}
					
				}
			}
		}
		for (int i = 1; i <= n; i++)
		{
			cout << timeArray[i].size() / 2 << " ";
			for (int& p : timeArray[i])
				cout << p << " ";
			cout << '\n';
		}
		
	}
	else
		cout << 0 << '\n';
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