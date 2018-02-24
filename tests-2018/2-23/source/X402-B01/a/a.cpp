#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 4e5 + 10;

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

int n, m;
int t[maxn], a[maxn];
bool vis[maxn];

inline void sovle(int l, int r)
{
	REP(i, l, r)
		t[i - l + 1] = a[i];
	register int k = r - l + 1, realmax =- 1, chosedd = 0, chosedi = 0;
	REP(i, 1, k)
	{
		int now = t[i], Max = -1, cd = 0;
		REP(d, 1, k)
		{
			int pos = i, res(0);
			while (pos <= k)
				if (t[pos] ^ now) break;
				else res++, pos += d;
			if (res > Max) {Max = res;cd = d;}
		}
		if (Max > realmax) {realmax = Max;chosedd = cd;chosedi = i;}
	}
	int now = t[chosedi], ans(0);
	for (register int i = chosedi; i <= k ; i += chosedd)
		if (t[i] == t[chosedi]) t[i] = 0;
		else break;

	memset(vis, 0, sizeof(vis));
	REP(i, 1, k)
		if (!vis[t[i]])
		{
			ans++;
			vis[t[i]] = 1;
		}
	printf("%d\n", ans);
}

int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	m = read<int>();
	while (m--)
	{
		int l = read<int>();
		int r = read<int>();
		sovle(l, r);
	}
	return 0;
}
