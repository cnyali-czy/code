/*
	Problem:	J.cpp
	Time:		2020-07-27 14:39
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 1e5 + 10;

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)
#define per vector <int>
int n, m, cnt[maxn];

int c[maxn];
void add(int x, int y = 1)
{
	while (x <= n)
	{
		c[x] += y;
		x += x & -x;
	}
}
int sum(int x)
{
	int y = 0;
	while (x > 0)
	{
		y += c[x];
		x &= (x - 1);
	}
	return y;
}
int sum(int l, int r)
{
	if (l > r) return 0;
	return sum(r) - sum(l - 1);
}

bool vis[maxn];
per get(int k)
{
	per res(n + 1, 0);
	REP(i, 1, n) vis[i] = 0;
	int lst = n;
	REP(i, 1, n)
	{
		for (int j = 1; j <= k; j++)
		{
			lst++;if (lst == n + 1) lst = 1;
			if (vis[lst])
			{
				j--;
				continue;
			}
		}
		vis[lst] = 1;
		res[i] = lst;
	}
	return res;
}

per good(per source, per p)
{
	per res(n + 1, 0);
	REP(i, 1, n) res[i] = source[p[i]];
	return res;
}

per pow(per base, int b)
{
	per res(n + 1, 0);
	REP(i, 1, n) res[i] = i;
	while (b)
	{
		if (b & 1) res = good(res, base);
		base = good(base, base);
		b >>= 1;
	}
	return res;
}

signed main()
{
	freopen("J.in", "r", stdin);
	freopen("bf.out", "w", stdout);
	n = read<int>();m = read<int>();
	per ans(n + 1, 0);
	REP(i, 1, n) ans[i] = i;
	REP(i, 1, m)
	{
		auto res = get(read<int>());
		res = pow(res, read<int>());
		ans = good(ans, res);
	}
	REP(i, 1, n) printf("%lld%c", ans[i], i == end_i ? '\n' : ' ');
	return 0;
}

