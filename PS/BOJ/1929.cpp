#include<iostream>
#include<math.h>
using namespace std;
bool isPrime(int N)
{
	int root = sqrt((double)N);
	if (N == 1)
		return false;
	if (N % 2 == 0)
		return N == 2;
	for (int i = 3; i <= root; i += 2)
	{
		if (N%i == 0)
			return false;
	}
	return true;
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = n; i <= m; i++)
	{
		if (isPrime(i))
			cout << i << '\n';
	}
	return 0;
}