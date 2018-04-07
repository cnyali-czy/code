#include <bits/stdc++.h>

using namespace std;

int main()
{
	freopen("math.in", "r", stdin);	
	freopen("math.out", "w", stdout);
	int n, ans(1);
	cin >> n;
	for (register int i = 2; i * i <= n ;i++)
		if (n % i == 0)
		{
			int cnt = 0;
			while (n % i == 0)
			{
				n /= i;
				cnt++;
			}
			ans *= (cnt + 1);
		}
	if (n ^ 1) ans <<= 1;
	cout << ans;
	return 0;
}
