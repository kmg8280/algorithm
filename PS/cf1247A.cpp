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

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int a, b;
	cin >> a >> b;


	if (a == b)
	{
		a = b = a * 10;
		b = b + 1;
		cout << a << " " << b << '\n';
	}
	else if (a - b == -1)
		cout << a << " " << b << '\n';
	else if (a == 9 && b == 1)
		cout << a << " " << 10 << '\n';
	else
		cout << -1 << '\n';
	return 0;
}