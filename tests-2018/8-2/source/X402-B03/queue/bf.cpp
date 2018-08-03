#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 15;
const long long MOD = 20000909;

bool vis[maxn];

int a[maxn], b[maxn], c[maxn];
int m, n, L, ans = 1e9;

inline void calc()
{
	int res = -1;
	REP(i, 1, n)
	{
		chkmax(res, min(abs(a[i] - b[c[i]]), abs(L - abs(a[i] - b[c[i]]))));
		if (res >= ans) return;
	}
	ans = res;
}

void dfs(int x)
{
	if (x == n)
	{
		calc();
		return;
	}
	x++;
	REP(i, 1, n)
		if (!vis[i])
		{
			c[x] = i;
			vis[i] = 1;
			dfs(x);
			vis[i] = 0;
		}
}

int main()
{
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w", stdout);
	cin >> n >> L;
	REP(i, 1, n) scanf("%d", a + i);
	REP(i, 1, n) scanf("%d", b + i);
	dfs(0);
	long long ANS = 1, base = 2;
	while (ans)
	{
		if (ans & 1) ANS *= base, ANS %= MOD;
		base = (base * base) % MOD;
		ans >>= 1;
	}
	cout << ANS;
	return 0;
}
