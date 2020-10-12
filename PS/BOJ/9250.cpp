#include<iostream>
#include<string>
#include<stack>
#include<math.h>
#include<memory.h>
#include<utility>
#include<algorithm>
#include<vector>
#include<map>
#include<stdlib.h>
#include<queue>
#include<stdio.h>
using namespace std;
typedef long long  ll;
typedef pair<int, int> P;
map<int, int> trie[1000100];
int fLink[1000100];
bool mark[1000100];
bool exist[1000100];
int cur, root = 1;
int cnt = 1;
void makeFailure()
{
	queue<P> q;
	q.push({ -1,1 });
	fill(fLink, fLink + 1000100, -1);
	while (!q.empty())
	{
		int ti = q.front().first;
		int tj = q.front().second;
		q.pop();
		for (auto x : trie[tj])
		{ // x 형태는 key value로 pair 형태로 반환
			int i = ti;
			int j = tj;

			while (i > 0 && !trie[i].count(x.first))
				i = fLink[i]; // 경로가 없으면 string이 겹치는 노드로 가야함
			if (i < 0)
				i = 1; // -1이면 루트
			else
				i = trie[i][x.first]; // -1이 아니면 특정 노드에 있고 다음단계가 있다는 뜻이니 이동

			j = x.second;
			fLink[j] = i;
			if (exist[i])
				exist[j] = true; 
			q.push({ i,j });
		}
	}
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n, q;
	string input;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> input;
		int size = input.size();
		cur = root;
		for (int j = 0; j < size; j++)
		{
			if (!trie[cur].count(input[j]))
			{
				trie[cur][input[j]] = ++cnt;
				cur = trie[cur][input[j]];
			}
			else
				cur = trie[cur][input[j]];
		}
		mark[cur] = true;
		exist[cur] = true;
	}
	makeFailure();
	cin >> q;
	while (q--)
	{
		cin >> input;
		int size = input.size();
		cur = root;
		bool check = false;
		for (int i = 0; i < size; i++)
		{
			while (cur > 0 && !trie[cur].count(input[i]))
				cur = fLink[cur]; // 루트가 아닌데 경로가 없으면 이동

			if (cur == -1)
				cur = 1;

			if (trie[cur].count(input[i]))
				cur = trie[cur][input[i]];

			if (exist[cur])
			{
				check = true;
				break;
			}
		}
		if (check)
			cout << "YES" << '\n';
		else
			cout << "NO" << '\n';
	}
	return 0;
}