#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#define int long long
using namespace std;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, x = 5e18;
#include <cmath>
int cnt(int x) {return !x ? 0 : x % 10 + cnt(x / 10);}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n;
	REP(sx, 0, 180)
	{
		int delta = sx * sx + 4 * n;
		if (delta < 0) continue;
		int S = sqrt(delta);
		if (S * S == delta)
		{
			int qaq = -sx + S >> 1;
			if (qaq < 0 || qaq * qaq + qaq * cnt(qaq) != n) continue;
			chkmin(x, qaq);
		}
	}
	cout << (x < 5e18 ? x : -1) << endl;
	return 0;
}
