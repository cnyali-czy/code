#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 10000 + 10, maxm = 1e6 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, k, siz[maxn], pt[maxn], flag[maxn], color[maxn];

int main()
{
#ifdef CraZYali
	freopen("1006.in", "r", stdin);
	freopen("1006.out", "w", stdout);
#endif
	cin >> n >> m;
	while (m --> 0)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	DREP(i, n, 1)
	{
		int cur = 0;
		REP(j, 1, n)
			if (!flag[j] && siz[j] >= siz[cur]) cur = j;
		flag[cur] = 1;
		pt[i] = cur;
		for (int i = bg[cur]; i ; i = ne[i])
			siz[to[i]]++;
	}
	REP(i, 1, n) flag[i] = 0;
	int ans = 1;
	DREP(I, n, 1)
	{
		int x = pt[I];
		for (int i = bg[x]; i ; i = ne[i])
			flag[color[to[i]]] = I;
		color[x] = 1;
		while (flag[color[pt[I]]] == I) color[pt[I]]++;
		chkmax(ans, color[pt[I]]);
	}
	cout << ans;
	return 0;
}
