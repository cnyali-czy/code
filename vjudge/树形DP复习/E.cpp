#define  REP(i, s, e) for (register long long i = s; i <= e ; i++)
#define DREP(i, s, e) for (register long long i = s; i >= e ; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const long long maxn = 50000 + 10, maxm = maxn;

long long N, C, W[maxn], T[maxn];
long long DPA[maxn][4], DPB[maxn][4], ans[maxn];

long long bg[maxn], ne[maxm << 1], to[maxm << 1], e;
inline void add(long long x, long long y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

void maintain(long long x)
{
	ans[x] += W[x];
	if (T[x])
	{
		DREP(i, C, 1)
		{
			DPA[x][i] = DPA[x][i-1] + W[x];
			DPB[x][i] = DPB[x][i-1] + W[x];
		}
		DPA[x][0] = DPA[x][0] = 0;
		DPB[x][1] = DPB[x][1] = W[x];
	} 
	else
		DREP(i, C, 0)
		{
			DPA[x][i] += W[x];
			DPB[x][i] += W[x];
		}		
	DPB[x][0] = 0;
}

void dfs(long long x, long long fa = 1)
{
	long long& ret = ans[x];
	ret = 0;
	memset(DPA[x], 0, sizeof(DPA[x]));
	memset(DPB[x], 0, sizeof(DPB[x]));

	for (register long long i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			dfs(to[i], x);

			if (T[x])	REP(j, 0, C - 1)	chkmax(ret, max(DPB[to[i]][j] + DPA[x][C-1-j],	DPB[x][j] + DPA[to[i]][C-1-j]));
			else		REP(j, 1, C)		chkmax(ret, max(DPB[to[i]][j] + DPA[x][C-j],	DPB[x][j] + DPA[to[i]][C-j]));

			REP(j, 0, C)
			{
				chkmax(DPA[x][j], DPA[to[i]][j]);
				chkmax(DPB[x][j], DPB[to[i]][j]);
			}
		}
	maintain(x);
}

int main()
{
#ifdef CraZYali
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	register long long Cases;
	cin >> Cases;
	while (Cases --> 0)
	{
		cin >> N >> C;
		REP(i, 1, N) scanf("%lld%lld", W + i, T + i);

		e = 0;
		REP(i, 1, N) bg[i] = 0;
		REP(i, 2, N)
		{
			register long long x, y;
			scanf("%lld%lld", &x, &y);
			add(x + 1, y + 1);
			add(y + 1, x + 1);
		}
		dfs(1);
		register long long Ans = 0;
		REP(i, 1, N) chkmax(Ans, ans[i]);
		printf("%lld\n", Ans);
	}
	return 0;
}
