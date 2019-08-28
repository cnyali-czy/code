#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = binn(a, b)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5, maxm = 180000 + 10, inf = 1e9, MOD = 20110520;

int n, m, N;
int bin[25];
char mp[maxn][maxn];
int f[maxm], g[maxm];
inline int w(int x, int y) {return x / bin[y] % 3;}
inline int s(int x, int y, int z) {return x - w(x, y) * bin[y] + z * bin[y];}

int main()
{
#ifdef CraZYali
	freopen("2331.in", "r", stdin);
	freopen("2331.out", "w", stdout);
#endif
	bin[0] = 1;
	REP(i, 1, 20) bin[i] = bin[i-1] * 3;
	cin >> n >> m;
	REP(i, 1, n) scanf("%s", mp[i] + 1);
	if (n < m)
	{
		REP(i, 1, n)
			REP(j, i, m) swap(mp[i][j], mp[j][i]);
		swap(n, m);
	}
	f[0] = 1;
	N = bin[m+1];
	REP(i, 1, n)
	{
		REP(j, 1, m)
		{
			memset(g, 0, sizeof(g));
			if (mp[i][j] == '*')
				REP(k, 0, N - 1) g[k] += (!w(k, j-1) && !w(k, j)) * f[k];
			else
				REP(k, 0, N - 1)
				{
					if (!f[k]) continue ;
					int x(w(k, j-1)), y(w(k, j));
					if (!x)
						if (!y)
						{
							(g[s(s(k, j-1, 1), j, 0)] += f[k]) %= MOD;
							(g[s(s(k, j-1, 0), j, 1)] += f[k]) %= MOD;
							(g[s(s(k, j-1, 2), j, 2)] += f[k]) %= MOD;
						}
						else if (y == 1)
						{
							(g[s(s(k, j-1, 1), j, 0)] += f[k]) %= MOD;
							(g[s(s(k, j-1, 0), j, 2)] += f[k]) %= MOD;
						}
						else
						{
							(g[s(s(k, j-1, 0), j, 0)] += f[k]) %= MOD;
							(g[s(s(k, j-1, 2), j, 0)] += f[k]) %= MOD;
						}
					else if (x == 1)
					{
						if (!y)
						{
							(g[s(s(k, j-1, 0), j, 1)] += f[k]) %= MOD;
							(g[s(s(k, j-1, 2), j, 0)] += f[k]) %= MOD;
						}
						else if (y == 1) (g[s(s(k, j-1, 0), j, 0)] += f[k]) %= MOD;
					}
					else if (!y)
					{
						(g[s(s(k, j-1, 0), j, 2)] += f[k]) %= MOD;
						(g[s(s(k, j-1, 0), j, 0)] += f[k]) %= MOD;
					}
				}
			copy(g, g + sizeof(g) / sizeof(g[0]), f);
		}
		memset(g, 0, sizeof(g));
		REP(k, 0, bin[m] - 1) g[k*3] = f[k];
		copy(g, g + sizeof(g) / sizeof(g[0]), f);
	}
	cout << f[0] << endl;
	return 0;
}

