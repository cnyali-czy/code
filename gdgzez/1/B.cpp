/*
	Problem:	B.cpp
	Time:		2020-03-24 14:31
	Author:		CraZYali
	E-mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUnCTIOn__, __LInE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;

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

#define file(FILE_nAmE) freopen(FILE_nAmE".in", "r", stdin), freopen(FILE_nAmE".out", "w", stdout)

namespace run
{
	const int maxn = 100 + 5;
	const double eps = 1e-7;
	int n, m;
	int to[maxn][26], fail[maxn], nxt[maxn][26], deg[maxn];
	int pid[maxn][maxn], Id[maxn][maxn];
	int lenA, lenB;
	double f[maxn][maxn], g[maxn * maxn];
	char A[maxn], B[maxn];
	bool vis[maxn][maxn][maxn];

	inline int qry(int x, int c) 
	{
		while (x && A[x + 1] != c) x = fail[x];
		return x + (A[x + 1] == c);
	}

	void dfs(int x, int l1, int l2)
	{
		vis[x][l1][l2] = 1;
		if (l1 == lenA && l2 == lenB) return;
		REP (i, 0, 25)
		{
			int nl1 = nxt[l1][i], nl2 = l2 + (B[l2 + 1] == i);
			if (!vis[to[x][i]][nl1][nl2]) dfs(to[x][i], nl1, nl2);
		}
	}

	inline void gauss(int n)
	{
		REP(i, 0, n - 1)
		{
			int k = i;
			REP (j, i + 1, n - 1)
				if (fabs(f[j][i]) > fabs(f[k][i])) k = j;
			swap(f[i], f[k]);
			if (fabs(f[i][i]) < eps) exit(puts("-1"));
			REP (j, i + 1, n - 1) if (fabs(f[j][i]) > eps)
			{
				double t = f[j][i] / f[i][i];
				REP(k, i, n) f[j][k] -= f[i][k] * t;
			}
		}
		DEP(i, n - 1, 0)
		{
			REP (j, i + 1, n - 1) f[i][n] -= f[i][j] * f[j][n];
			f[i][n] /= f[i][i];
		}
	}

	int main ()
	{
		n = read<int>();m = read<int>();
		REP (i, 1, m)
		{
			int u(read<int>()), v(read<int>());
			deg[u]++;
			char c = getchar();
			while (!isalpha(c)) c = getchar();
			to[u][c - 'a'] = v;
		}
		scanf("\n%s%s", A + 1, B + 1);
		lenA = strlen(A + 1);REP(i, 1, lenA) A[i] -= 'a';
		lenB = strlen(B + 1);REP(i, 1, lenB) B[i] -= 'a';
		A[0] = B[0] = A[lenA + 1] = B[lenB + 1] = '#';
		int k = 0;
		REP (i, 2, lenA)
		{
			while (k && A[k + 1] ^ A[i]) k = fail[k];
			fail[i] = (k += (A[k + 1] == A[i]));
		}
		REP(i, 0, lenA - 1) REP(j, 0, 25) nxt[i][j] = qry(i, j);
		dfs(1, 0, 0);
		for (int tot = 0, k = lenB - 1; ~k; --k, tot = 0)
		{
			memset(f, 0, sizeof f);
			REP(i, 1, n) REP(j, 0, lenA) if (vis[i][j][k]) Id[i][j] = tot++;
			REP(i, 1, n) REP(j, 0, lenA) if (vis[i][j][k])
			{
				int id = Id[i][j];
				REP (c, 0, 25) if (to[i][c] && nxt[j][c] < lenA)
				{
					int l1 = nxt[j][c], l2 = k + (B[k + 1] == c);
					if (l2 > k)	f[id][tot] += g[pid[to[i][c]][l1]];
					else		f[id][Id[to[i][c]][l1]]--;
				}
				f[id][tot]	+= deg[i];
				f[id][id]	+= deg[i];
			}
			gauss(tot);
			REP(i, 1, n) REP(j, 0, lenA) if (vis[i][j][k])
			{
				int x = Id[i][j];
				pid[i][j] = x;
				g[x] = f[x][tot];
			}
		}
		printf("%.6lf\n", g[0]);
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	return run::main();
}
