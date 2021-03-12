/*
	Problem:	A.cpp
	Time:		2021-03-08 19:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 500 + 5, MOD = 1e9 + 7;

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

int k, n, a[maxn], t[maxn][maxn];

bool vis[maxn][maxn];
int f[maxn][maxn], g[maxn][maxn], h[maxn][maxn], p[maxn][maxn];
void work(int l, int r)
{
	if (l == r) return void(f[l][r] = 1);
	if (vis[l][r]) return;
	vis[l][r] = 1;
	int k = l;
	DEP(i, r - 1, l) if (t[l][i]) {k = i;break;}

	i64 G = 0, H = 0, P = 0;
	REP(i, l, r - 1) if (t[l][i])
	{
		work(l, i);work(i + 1, r);
		(G += 1ll * f[l][i] * (g[i + 1][r] + f[i + 1][r])) %= MOD;
		(H += 1ll * f[l][i] * f[i + 1][r]) %= MOD;
		if (i < k && t[i + 1][r] && t[l][r])
			(P += 1ll * f[l][i] * (h[i + 1][r] + p[i + 1][r])) %= MOD;
	}
	g[l][r] = G;h[l][r] = H;p[l][r] = P;
	if (t[l][r]) f[l][r] = (G + P) % MOD;
//	printf("%d %d %d %d\n", f[l][r], g[l][r], h[l][r], p[l][r]);
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> k >> n;
	REP(i, 1, k)
	{
		REP(j, 1, n) a[j] = read<int>();
		REP(l, 1, n)
		{
			int mi = a[l], mx = a[l];
			REP(r, l, n)
			{
				mi = min(mi, a[r]);
				mx = max(mx, a[r]);
				if (mx - mi == r - l) t[mi][mx]++;
			}
		}
	}
//	REP(i, 1, n) REP(j, i, n) printf("%d%c",t[i][j],j==end_j?'\n':' ' );
	REP(i, 1, n) REP(j, i, n) t[i][j] = (t[i][j] == k);
	work(1, n);
	cout << f[1][n] << endl;
	return 0;
}
