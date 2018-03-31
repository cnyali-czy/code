#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 15;

template <typename T> T read()
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

int m, n, k, w, h, ans;

pair <int, int> p[maxn];

int face[maxn];

inline void calc()
{
	int sx(0), sy(0), tx(w), ty(h);
	REP(i, 1, n)
	{
		if (face[i] == 1) chkmin(tx, p[i].first);
		if (face[i] == 2) chkmax(sx, p[i].first);
		if (face[i] == 3) chkmin(ty, p[i].second);
		if (face[i] == 4) chkmax(sy, p[i].second);
	}
	chkmax(ans, (tx - sx + ty - sy) << 1);
}
void dfs(int x)
{
	if (x == n)
	{
		calc();
		return;
	}
	x++;
	REP(i, 1, 4)
	{
		face[x] = i;
		dfs(x);
	}
}

int main()
{
	freopen("paint.in", "r", stdin);
	freopen("paint.out", "w", stdout);
	w = read<int>();
	h = read<int>();
	n = read<int>();
	REP(i, 1, n)
		p[i].first = read<int>(), p[i].second = read<int>();
	dfs(0);
	cout << ans << endl;
	return 0;
}
