//orzhh
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 2e5 + 10;
const double eps = 1e-12;

inline double dis(int x1, int y1, int x2, int y2)
{
	return sqrt(1ll * (x1 - x2) * (x1 - x2) + 1ll * (y1 - y2) * (y1 - y2));
}
inline double orzhh(int x1, int y1, int x2, int y2)
{
	return (x2 - x1) / dis(x1, y1, x2, y2);
}
vector <double> rad[maxn];
vector <pair <double, int> > qaq;
int n, m, k, q, op;
int X[maxn], Y[maxn], opt[maxn], x[maxn], y[maxn];
template <typename T>
inline T read()
{
	register T ans(0), flag(1);
	register char c(getchar());
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
int main()
{
#ifdef CraZYali
	freopen("clash-new.in", "r", stdin);
	freopen("clash-new.out", "w", stdout);
#endif
	cin >> n >> k >> q >> op;
	REP(i, 1, n) scanf("%d%d", x + i, y + i);
	REP(i, 1, k)
	{
		int a(read<int>()), b(read<int>()), c(read<int>());
		X[i] = a;Y[i] = c;opt[i] = -1;
		X[i + k] = b;Y[i + k] = c;opt[i + k] = 1;
	}
	REP(i, 1, n)
	{
		qaq.clear();
		REP(j, 1, k + k) if (y[i] > Y[j])
			qaq.emplace_back(orzhh(x[i], y[i], X[j], Y[j]) + eps * opt[j], j);
		sort(qaq.begin(), qaq.end());
		int res(0);
		for (auto j : qaq)
		{
			if (!res) rad[j.second].emplace_back(j.first);
			res += opt[j.second];
			if (!res) rad[j.second].emplace_back(j.first);
		}
	}
	REP(i, 1, k + k) sort(rad[i].begin(), rad[i].end());
	int lastans(0);
	while (q--)
	{
		int x_(read<int>() ^ (lastans * op));
		int y_(read<int>() ^ (lastans * op));
		lastans = n;
		REP(i, 1, k + k)
			lastans += opt[i] * (upper_bound(rad[i].begin(), rad[i].end(), orzhh(X[i], Y[i], x_, y_)) - rad[i].begin());
		printf("%d\n", lastans);
	}
	return 0;
}
