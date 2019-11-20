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
	fLink[1] = -1;
	while (!q.empty())
	{
		int ti = q.front().first;
		int tj = q.front().second;
		q.pop();
		for (auto x : trie[tj])
		{ // x ���´� key value�� pair ���·� ��ȯ
			// x.second �� �������
			// x.first�� ���� ����
			int i = ti;
			int j = tj;

			while (i > 0 && !trie[i].count(x.first) && exist[i])
				i = fLink[i]; // ��ΰ� ������ string�� ��ġ�� ���� ������
			if (i == -1)
				i = 1; // -1�̸� ��Ʈ
			else
				i = trie[i][x.first]; // -1�� �ƴϸ� Ư�� ��忡 �ְ� �����ܰ谡 �ִٴ� ���̴� �̵�

			j = x.second;
			fLink[j] = i;
			if (exist[i]) // exist�� �ִٸ� �ִ� suffix�κ��� �ִٴ� ��
				exist[j] = true; // 
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

	cin >> q;
	while (q--)
	{
		cin >> input;
		int size = input.size();
		cur = root;
		bool check = false;
		for (int i = 0; i < size; i++)
		{
			while (cur > 0 && !trie[cur].count(input[i]) && exist[cur])
				cur = fLink[cur]; // ��Ʈ�� �ƴѵ� ��ΰ� ������ �̵�

			//cout << cur << '\n';
			if (trie[cur].count(input[i]))
				cur = trie[cur][input[i]];

			if (mark[cur])
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