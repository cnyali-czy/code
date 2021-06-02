/*
	Problem:	B.cpp
	Time:		2021-06-02 15:58
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 40 + 2, MOD = 998244353;

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

int n, m, N, a[maxn], b[maxn], n2;
int f[maxn][maxn][maxn * maxn * 2], g[maxn][maxn][maxn * maxn * 2];
//f[前i位][a欠了几个（向后的）][p欠了几个（向后的）][n^2 + 当前的M]
bool vis[maxn];
pair <int, int> s[maxn << 1];
#define fi first
#define se second
inline void reduce(int &x) {x += x >> 31 & MOD;}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();n2 = n * n;
	REP(i, 1, n) a[i] = read<int>();
	int curm = 0;
	REP(i, 1, n)
	{
		b[i] = read<int>();
		if (b[i] == -1) s[++N] = make_pair(a[i], 0);
		else vis[b[i]] = 1, curm += abs(a[i] - b[i]);
	}
	REP(i, 1, n) if (!vis[i]) s[++N] = make_pair(i, 1);
	sort(s + 1, s + 1 + N);
	f[0][0][n2 + curm] = 1;
	int cnt[2] = {0, 0};
	REP(i, 0, N - 1)
	{
		int isp = s[i + 1].se, val = s[i + 1].fi;
		swap(f, g);
		memset(f, 0, sizeof f);
		REP(j, 0, min(N / 2, i))
		{
			int k = cnt[1] - cnt[0] + j;
			if (k < 0 || k > N / 2) continue;
			REP(c, 0, 2 * n2) if (g[j][k][c])
			{
				if (isp) // p
				{
					//往前还一个a，那么贡献一个 +val
					if (j && c + val <= 2 * n2) reduce(f[j - 1][k][c + val] += 1ll * j * g[j][k][c] % MOD - MOD);
					//往后欠一个p，那么贡献一个 -val
					if (c >= val) reduce(f[j][k + 1][c - val] += g[j][k][c] - MOD);
				}
				else // a
				{
					//往前还一个p，那么贡献一个 +val
					if (k && c + val <= 2 * n2) reduce(f[j][k - 1][c + val] += 1ll * k * g[j][k][c] % MOD - MOD);
					//往后欠一个a，那么贡献一个 -val
					if (c >= val) reduce(f[j + 1][k][c - val] += g[j][k][c] - MOD);
				}
			}
		}
		cnt[isp]++;
	}
	int ans = 0;
	REP(i, 0, m) reduce(ans += f[0][0][n2 + i] - MOD);
	cout << ans % MOD << endl;
	return 0;
}
