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

vector<node> edge[20050];
bool visited[20050];
char table[101][101];
int base;
int xy[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
int num[101][101];
int n, m;
int s, t;
void add_edge(int from, int to, int cap) 
{
	edge[from].push_back({ from,to,0,cap,(int)edge[to].size() });
	edge[to].push_back({ to,from,0,0,(int)edge[from].size()-1 });
}
bool chk(int x,int y)
{
	if (1 <= x && x <= n && 1 <= y && y <= m)
		return true;
	return false;
}

int dfs(int u, int pushed)
{ // int 로 내가 흘려보낸 플로우 양 리턴
	visited[u] = 1;
	if (u == t)
		return pushed; // 지금까지 흐른 양
	for (auto& v : edge[u])
	{ // 값 직접수정을 위해 &붙임
		if (v.cap - v.flow == 0) continue; // 못흐른다.
		if (visited[v.to]) continue; // 방문함
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
{ // 가상 노드 테크닉, 벽을 가상 노드로 만듬
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int cnt = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			cin >> table[i][j];
			num[i][j] = ++cnt;
			if (table[i][j] == 'K')
				s = num[i][j];
			else if (table[i][j] == 'H')
				t = num[i][j];
		}
	base = cnt;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (table[i][j] == 'K' || table[i][j] == 'H')
			{
				for (int k = 0; k < 4; k++)
				{
					int nxt_i = i + xy[k][0];
					int nxt_j = j + xy[k][1];
					if (chk(nxt_i, nxt_j))
					{
						if (table[i][j] == 'K')
						{
							add_edge(num[i][j], num[nxt_i][nxt_j], 1);
							if (table[nxt_i][nxt_j] == 'H')
							{
								cout << -1 << '\n';
								return 0;
							}
						}
						else
						{
							add_edge((num[nxt_i][nxt_j] + base), num[i][j], 1);
							if (table[nxt_i][nxt_j] == 'K')
							{
								cout << -1 << '\n';
								return 0;
							}
						}
					}
				}
			}
			else
			{
				//cout << i << " " << j << " " << num[i][j] << '\n';
				if (table[i][j] == '.')
				{
					add_edge(num[i][j], num[i][j] + base, 1);
					add_edge(num[i][j] + base, num[i][j],  1);
					for (int k = 0; k < 4; k++)
					{
						int nxt_i = i + xy[k][0];
						int nxt_j = j + xy[k][1];
						if (chk(nxt_i, nxt_j) && table[nxt_i][nxt_j]!='H' && table[nxt_i][nxt_j] != 'K')
						{
							add_edge(num[nxt_i][nxt_j] + base, num[i][j], 1);
						}
					}
				}
				else if(table[i][j]=='#')
				{
					add_edge(num[i][j], num[i][j] + base, 0);
					add_edge(num[i][j] + base, num[i][j], 0);
					for (int k = 0; k < 4; k++)
					{
						int nxt_i = i + xy[k][0];
						int nxt_j = j + xy[k][1];
						if (chk(nxt_i, nxt_j) && table[nxt_i][nxt_j] != 'H' && table[nxt_i][nxt_j] != 'K')
						{
							add_edge(num[nxt_i][nxt_j] + base, num[i][j], 1);
						}
					}
				}
			}
		}
	}

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