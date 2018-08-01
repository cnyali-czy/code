#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6 + 10, maxm = 1e6 + 10, maxL = 1e7 + 10;

int m, n, L, P;

int l[maxn];

namespace bf
{
	bool finish[maxL];
	
	int color[maxL], ans;

	set <int> s[maxn];

	inline void calc()
	{
		REP(i, 1, n) s[i].clear();
		int S = 1, E = l[1], now = 1;
		while (now <= n)
		{
			register int pos = S + 1;
			while (pos <= E)
				if (color[pos - 1] == color[pos]) return;
				else s[now].insert(color[pos - 1]), pos++;
			s[now].insert(color[E]);
			S = E + 1;
			E += l[++now];
		}
		REP(i, 2, n)
			if (s[i - 1] == s[i]) return;
		ans++;ans %= P;
	}

	void dfs(int x)
	{
		if (x == L) calc();
		else
		{
			x++;
			REP(i, 1, m)
			{
				color[x] = i;
				dfs(x);
			}
			color[x] = 0;
		}
	}
	inline void work()
	{
		int cnt = 0;
		dfs(0);
		cout << ans;
	}
}

int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	cin >> n >> m >> P;
	REP(i, 1, n) scanf("%d", l + i), L += l[i];
	if (L <= 10) bf::work();

	return 0;
}
