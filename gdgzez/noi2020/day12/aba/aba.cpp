/*
	Problem:	aba.cpp
	Time:		2020-06-13 18:47
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <bitset>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3000 + 5, maxk = 10000 + 10, inf = 1e8;

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

#define ui64 unsigned long long
const ui64 base = 131;
ui64 h1[maxk], h2[maxk], h3[maxk], bin[maxk];
struct __init__
{
	__init__(const int N = maxk - 10)
	{
		bin[0] = 1;
		REP(i, 1, N) bin[i] = bin[i - 1] * base;
	}
}__INIT__;
inline ui64 get(int l, int r) {return h2[r] - h2[l - 1] * bin[r - l + 1];}
inline int lcp(int x, int l, int r)
{
	int res = 0;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (get(x, x + mid - 1) == h1[mid])
		{
			res = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return res;
}
char s[maxn][maxk], f[maxk];
int l[maxn], n, k;
bitset <maxk> suf[maxn], p, P;

template <typename T>
inline bool chkmin(T &a, T b)
{
	if (a >= b) {a = b;return 1;}
	return 0;
}

int main()
{
#ifdef CraZYali
	file("aba");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n)
	{
		scanf("%s", s[i] + 1);
		l[i] = strlen(s[i] + 1);
	}
	suf[n][k] = 1;
	DEP(i, n, 1) suf[i - 1] = suf[i] | (suf[i] >> l[i]);
	REP(i, 1, k) f[i] = 'z' + 1;
	p[0] = 1;
	REP(u, 1, n)
	{
		P = p;p.reset();
		REP(i, 1, l[u])	h1[i] = h1[i - 1] * base + s[u][i];
		REP(i, 1, k)	h2[i] = h2[i - 1] * base + f[i];
		pair <int, char> best(inf, 0);
		int pos = -1;
		REP(i, 1, k - l[u] + 1) if (P[i - 1] && suf[u][i + l[u] - 1])
		{
			int good = lcp(i, 0, l[u]);
			if (good < l[u] && s[u][good + 1] < f[i + good] && chkmin(best, make_pair(i + good - 1, s[u][good + 1])))
				pos = i;
		}
		if (pos > 0)
		{
			REP(i, 0, best.first) if (suf[u][i] && P[i]) p[i] = 1;
			REP(i, pos, pos + l[u] - 1) f[i] = s[u][i - pos + 1];
			REP(i, pos + l[u], k) f[i] = 'z' + 1;
			REP(i, 1, k) h3[i] = h3[i - 1] * base + f[i];
			REP(i, 0, k - l[u])
				if (h1[l[u]] + h2[i] * bin[l[u]] == h3[i + l[u]] && suf[u][i + l[u]] && P[i]) p[i + l[u]] = 1;
		}
		else
		{
			p = P & suf[u];
			REP(i, 0, k - l[u])
				if (h1[l[u]] + h2[i] * bin[l[u]] == h3[i + l[u]] && suf[u][i + l[u]] && P[i]) p[i + l[u]] = 1;
		}
	}
	puts(f + 1);
	return 0;
}
