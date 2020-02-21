/*
	Problem:	F.cpp
	Time:		2020-02-21 19:41
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
#define i64 long long
using namespace std;
const int maxn = 1e5 + 10;
const i64 inf = 1e12;

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

int n, k, a[maxn];

int cnt[maxn], _l, _r;
i64 W;

inline void add(int val) {W += cnt[val]++;}
inline void del(int val) {W -= --cnt[val];}
i64 f[maxn], g[maxn];

void solve(int l, int r, int L, int R)
{
	if (l > r || L > R) return;
	int mid = l + r >> 1;

	while (_l >   L) add(a[--_l]);
	while (_r < mid) add(a[++_r]);
	while (_l <   L) del(a[_l++]);
	while (_r > mid) del(a[_r--]);

	int good = 0;
	i64 &res = f[mid];
	res = inf;
	REP(i, L, min(mid, R))
	{
		if (res > W + g[i - 1]) res = W + g[(good = i) - 1];
		del(a[_l++]);
	}
	solve(l, mid - 1, L, good);
	solve(mid + 1, r, good, R);
}

int main()
{
#ifdef CraZYali
	file("F");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	_l = _r = 1;add(a[1]);
	REP(i, 1, n) g[i] = inf;
	REP(i, 1, k)
	{
		solve(1, n, 1, n);
		swap(f, g);
		REP(j, 0, n) f[j] = inf;
	}
	cout << g[n] << endl;
	return 0;
}
