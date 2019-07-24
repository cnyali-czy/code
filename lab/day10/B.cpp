#define REP(i, s, e) for (register int i = s; i <= e; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)

#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <bitset>
using namespace std;
const int maxn = 40000 + 10, maxq = maxn << 1;

int n, N;
bitset <maxn> G[maxn], ASK[maxn];
unordered_map <int, int> ANS[maxn];
int u, v, q, x[maxq], y[maxq], cnt[maxn], End[maxn];

char c;int res;
int read()
{
	c = getchar();
	res = 0;
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) res = (res << 1) + (res << 3) + c - 48, c = getchar();
	return res;
}
int dis[maxn], Q[maxn], head, tail;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n;N = n-1;
	REP(i, 1, N) G[i][i+1] = G[i+1][i] = 1, chkmax(End[i], i + 1), chkmax(End[i+1], i);
	End[1] = n;
	G[1][n] = G[n][1] = 1;
	REP(i, 4, n)
	{
		u = read(), v = read();
		G[u][v] = G[v][u] = 1;
		chkmax(End[u], v);
		chkmax(End[v], u);
	}
	cin >> q;
	REP(i, 1, q)
	{
		x[i] = read();y[i] = read();
		if (!ASK[x[i]][y[i]])
			++cnt[x[i]], ++cnt[y[i]], ASK[x[i]][y[i]] = ASK[y[i]][x[i]] = 1;
	}
	REP(i, 1, n)
		if (cnt[i])
		{
			REP(j, 1, n) dis[j] = -1;
			dis[Q[head = tail = 1] = i] = 0;
			while (head <= tail)
			{
				u = Q[head++];v = G[u]._Find_first();
				while (v ^ End[u] && v ^ maxn)
				{
					if (dis[v] == -1)
					{
						dis[Q[++tail] = v] = dis[u] + 1;
						if (ASK[i][v])
						{
							ASK[i][v] = ASK[v][i] = 0;
							cnt[i]--;cnt[v]--;
							ANS[i][v] = ANS[v][i] = dis[v];
							if (!cnt[i]) goto ne;
						}
					}
					v = G[u]._Find_next(v);
				}
				if (v == End[u] && dis[v] == -1)
				{
					dis[Q[++tail] = v] = dis[u] + 1;
					if (ASK[i][v])
					{
						ASK[i][v] = ASK[v][i] = 0;
						cnt[i]--;cnt[v]--;
						ANS[i][v] = ANS[v][i] = dis[v];
						if (!cnt[i]) goto ne;
					}
				}
			}
ne:;
		}
	REP(i, 1, q) printf("%d\n", ANS[x[i]][y[i]]);
	return 0;
}
