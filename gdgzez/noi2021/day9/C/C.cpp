/*
	Problem:	C.cpp
	Time:		2021-03-12 08:46
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <set>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 2e5 + 10;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn], q, sum, del;
set <int> ssr;
void pop(set <int> :: iterator it, int h, int lst)
{
	for (--it; it != ssr.end(); )
	{
		if (*it & 1 ^ 1) del -= lst - a[*it];
		lst = a[*it];
		if (a[*it] < h) break;
		ssr.erase(it--);
	}
	if (it != ssr.end() && (*it & 1 ^ 1))
		del += h - a[*it];

}
void upd(int x, int y)
{
	auto it = ssr.lower_bound(x);
	int pos = *it;
	if (pos == x)
	{
		if (x < n && (x & 1 ^ 1)) del += y;
		pop(it, a[x], a[x] + y);
	}
	else
	{
		if (a[pos] <= a[x]) return;
		auto fk = ssr.emplace(x).first;
		if (x & 1 ^ 1) del += a[pos] - a[x];
		pop(fk, a[x], a[pos]);
	}
}
namespace bf
{
	const int maxn = 2e5 + 10;

	int n, q, a[maxn];
	int f[maxn], g[maxn], s[maxn];

	int calc()
	{
		DEP(i, n, 1) s[i] = s[i + 1] + a[i];
		f[n] = a[n];f[n - 1] = a[n - 1] + a[n];
		g[n] = a[n];g[n - 1] = max(a[n - 1], a[n]);
		DEP(i, n - 2, 1)
		{
			f[i] = a[i] + s[i + 1] - g[i + 1];
			g[i] = max(s[i] - f[i + 1], s[i + 1] - g[i + 1]);
		}
		return f[1];
	}

	signed main()
	{
		REP(i, 1, n) scanf("%lld", a + i);
		cout << calc() << endl;
		cin >> q;
		while (q--)
		{
			int x, y;scanf("%lld%lld", &x, &y);
			a[x] -= y;
			cout << calc() << '\n';
		}
		return 0;
	}
}

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n;
	if (n <= 10) return bf :: main();
	REP(i, 1, n) a[i] = read<int>();
	cin >> q;
	for (int i = 1; i <= n; i += 2) sum += a[i];
	if (n & 1 ^ 1) sum += a[n];
	int mn = a[n];ssr.emplace(n);
	DEP(i, n - 1, 1)
		if (a[i] < mn)
		{
			if (i & 1 ^ 1) del += mn - a[i];
			mn = a[i];ssr.emplace(i);
		}
	cout << sum - del << endl;
	while (q--)
	{
		int x = read<int>(), y = read<int>();
		a[x] -= y;
		if (x == n || (x & 1)) sum -= y;
		upd(x, y);
		cout << sum - del << '\n';
	}
	return 0;
}
