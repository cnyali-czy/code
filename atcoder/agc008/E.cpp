/*
	Problem:	2267.cpp
	Time:		2021-05-11 22:04
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, MOD = 1e9 + 7;

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

int n, a[maxn], d[maxn], vis[maxn], cir[maxn], sum[maxn], fl[maxn], ans = 1;
inline void reduce(int &x) {x += x >> 31 & MOD;}

void fk_circle(int x)
{
	int cur = 0, head = 0, tail = 0, L = 0;
	while (cir[x])
	{
		cur++;
		cir[x] = 0;
		if (fl[x])
		{
			if (!head) head = tail = cur, L = fl[x];
			else
			{
				int k = (fl[x] < cur - tail) + (fl[x] <= cur - tail);
				ans = 1ll * ans * k % MOD;
				tail = cur;
			}
		}
		x = a[x];
	}
	if (!head) sum[cur]++;
	else
	{
		int k = (L < cur - tail + head) + (L <= cur - tail + head);
		ans = 1ll * ans * k % MOD;
	}
}

int main()
{
#ifdef CraZYali
	file("2267");
#endif
	n = read<int>();
	REP(i, 1, n) d[a[i] = read<int>()]++;
	REP(i, 1, n) if (!vis[i])
	{
		int x;
		for (x = i; !vis[x]; x = a[x]) vis[x] = i;
		if (vis[x] ^ i) continue;
		for (; !cir[x]; x = a[x]) cir[x] = 1;
	}
	REP(i, 1, n)
	{
		if ( cir[i] && d[i] > 2) return 0 * puts("0");
		if (!cir[i] && d[i] > 1) return 0 * puts("0");
	}
	REP(i, 1, n) if (!d[i])
	{
		int len = 0, x = i;
		while (!cir[x])
		{
			len++;
			x = a[x];
		}
		fl[x] = len;
	}
	REP(i, 1, n) if (cir[i]) fk_circle(i);
	REP(i, 1, n) if (sum[i])
	{
		static int f[maxn];
		f[0] = 1;
		REP(j, 1, sum[i])
		{
			if (i > 1 && (i & 1)) reduce(f[j] = f[j - 1] + f[j - 1] - MOD);
			else f[j] = f[j - 1];
			if (j > 1) f[j] = (f[j] + (j - 1ll) * f[j - 2] % MOD * i) % MOD;
		}
		ans = 1ll * ans * f[sum[i]] % MOD;
	}
	cout << ans << endl;
	return 0;
}
