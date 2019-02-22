#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxk = 20 + 5, maxn = 1000 + 10, maxN = maxn + maxk + 10, maxE = maxk * maxn;

int bg[maxN], ne[maxE << 1], to[maxE << 1], w[maxE << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> T read()
{
	T ans = 0, p = 1;
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

int k, n, S, T, N;
int need[maxk], total;
vector <int> type[maxn];int cnt[maxn];

int main()
{
#ifdef CraZYali
	freopen("2763.in", "r", stdin);
	freopen("2763.out", "w", stdout);
#endif
	cin >> k >> n;
	REP(i, 1, k) total += (need[i] = read<int>());
	REP(i, 1, n)
	{
		cnt[i] = read<int>();
		REP(i, 1, cnt) type[i].push_back(read<int>());
	}
	return 0;
}
