#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>
#include <bitset>

using namespace std;
const int maxn = 100 + 5 << 1, N = 1e7;

int n, x[maxn];

bitset <N + 5> notp, s;
int p[N], p_cnt;
inline void init()
{
	notp[1] = 1;
	REP(i, 2, N)
	{
		if (!notp[i]) p[++p_cnt] = i;
		REP(j, 1, p_cnt)
		{
			if (i * p[j] > N) break;
			notp[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
}
int a[maxn], b[maxn], cntA, cntB;
bitset <maxn> G[maxn];

int match[maxn], vis[maxn];
int dfs(int x)
{
	REP(i, 1, cntB)
		if (G[x][i] && !vis[i])
		{
			vis[i] = 1;
			if (!match[i] || dfs(match[i])) return match[i] = x;
		}
	return 0;
}

int main()
{
#ifdef CraZYali
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
#endif
	init();
	cin >> n;
	REP(i, 1, n)
	{
		scanf("%d", x + i);
		s.flip(x[i]);
	}
	REP(i, 1, N + 1)
		if (s[i] != s[i-1]) i & 1 ? a[++cntA] = i : b[++cntB] = i;
	REP(i, 1, cntA)
		REP(j, 1, cntB)
		if (!notp[abs(a[i] - b[j])]) G[i][j] = 1;
	int ans(0), temp(0);
	REP(i, 1, cntA)
	{
		memset(vis, 0, sizeof(vis));
		temp += (dfs(i) > 0);
	}
	ans += cntA - temp >> 1 << 1;
	ans += cntB - temp >> 1 << 1;
	ans += temp;
	if ((cntA & 1) ^ (temp & 1)) ans += 3;
	cout << ans << endl;
	return 0;
}
