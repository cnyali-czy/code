#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;
const int maxn = 100000 + 10, maxm = maxn << 1;

int bg[maxn], ne[maxm], to[maxm], w[maxm], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;

int de[maxn], ot[maxn];

double dp[maxn];
queue <int> q;

int main()
{
#ifdef CraZYali
	freopen("3802.in", "r", stdin);
	freopen("3802.out", "w", stdout);
#endif
	cin >> n >> m;
	while (m --> 0)
	{
		register int x = read<int>(), y = read<int>(), z = read<int>();
		add(y, x, z);
		de[x]++;ot[x]++;
	}

	q.push(n);
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		for (register int i = bg[x]; i ; i = ne[i])
		{
			dp[to[i]] += (dp[x] + w[i]) / de[to[i]];
			ot[to[i]]--;
			if (!ot[to[i]]) q.push(to[i]);
		}
	}
	printf("%.2lf", dp[1]);
	return 0;
}
