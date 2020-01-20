#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)

#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	int T;
	cin >> T;
	while (T--)
	{
		int maxa, maxb;
		long long ans = 0;
		cin >> maxa >> maxb;
		for (long long int b = 9; b <= maxb; b = b * 10 + 9) ans += maxa;
		cout << ans<< endl;
	}
	return 0;
}
