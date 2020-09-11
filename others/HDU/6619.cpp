/*
	Problem:	6619.cpp
	Time:		2020-09-08 20:16
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long

using namespace std;
const int maxn = 1e4 + 10, maxm = 50 + 5;

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

int n, m, k, ans;
int a[maxn], f[maxn], g[maxn];

void work1()
{
	static int b[maxn];
	REP(i, 1, n) b[i] = (n - i + 1) * a[i];
	sort(b + 1, b + 1 + n);
	reverse(b + 1, b + 1 + n);
	REP(i, 1, m) ans += b[i];
}
const int inf = 1e15;
int ss[maxn], s[maxn];
int calc(int l, int r)
{
	if (l > r) return -inf;
	return s[l - 1] * r;
}
bool chkmin(int &x, int y) {if (x > y) {x = y;return 1;}return 0;}
bool chkmax(int &x, int y) {if (x < y) {x = y;return 1;}return 0;}
void solve(int l, int r, int L, int R)
{
	if (l > r || L > R) return;
	if (l == r)
	{
		int i = l;
		REP(j, L, R)
			chkmax(g[i], f[j] + calc(j + 1, i));
		return;
	}
	int mid = l + r >> 1, bst = L;
	int &res = g[mid];
	REP(j, L, R)
		if (chkmax(res, f[j] + calc(j + 1, mid))) bst = j;
	solve(l, mid - 1, L, bst);
	solve(mid + 1, r, bst, R);
}
double K(int i, int j) {return 1. * (f[i] - f[j]) / (s[i] - s[j]);}
void work2()
{
	REP(i, 1, n)
	{
		s[i] = s[i - 1] + a[i];
		ss[i] = ss[i - 1] + s[i];
		f[i] = calc(1, i);
	}
	static int q[maxn];
	int head, tail;
	REP(times, 1, k)
	{
		REP(i, 1, n) f[i] -= i * s[i];
		REP(i, 0, n) g[i] = -inf;
		q[head = tail = 0] = 1;
		g[1] = f[1];// + s[1];
		REP(i, 2, n)
		{
			while (head < tail && K(q[head], q[head + 1]) <= i) head++;
			g[i] = f[q[head]] + i * s[q[head]];
			while (head < tail && K(q[tail], q[tail - 1]) > K(q[tail], i)) tail--;
			q[++tail] = i;
		}
//		solve(1, n, 1, n);
		swap(f, g);
	}
	ans += f[n];
}

signed main()
{
#ifdef CraZYali
	file("6619");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		k = read<int>();
		m = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		ans = 0;REP(i, 1, n) f[i] = 0;
		work1();work2();
		ans -= ss[n];
		printf("%lld\n", ans);
	}
	return 0;
}
