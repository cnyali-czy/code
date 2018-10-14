#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3 + 10;

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

int a[maxn], b[maxn];
bool vis1[maxn << 1], vis2[maxn << 1];

map <int, int> to;
int U;

bool same()
{
	REP(i, 1, n) if (a[i] ^ b[i]) return 0;
	return 1;
}

bool flag;
bool vis[maxn];

void dfs(int x)
{
	if (flag) return;
	if (same())
	{
		flag = 1;
		return;
	}
	if (x == n) return;
	x++;
	REP(i, 1, n - k + 1)
	{
		register int temp = a[i + k - 1];
		DREP(j, i + k - 2, i) a[j + 1] = a[j];
		a[i] = temp;

		dfs(x);

		REP(j, i, i + k - 2) a[j] = a[j + 1];
		a[i + k - 1] = temp;
	}
}

bool check(int mid)
{
	REP(i, 1, n) vis[i] = 0;
	k = mid;
	flag = 0 ;
	dfs(0);
	return flag;
}

int main()
{
#ifdef CraZYali
	freopen("T50761.in", "r", stdin);
	freopen("T50761.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		to.clear();
		U = 0;
		n = read<int>();
		REP(i, 1, n)
		{
			a[i] = read<int>();
			if (!to[a[i]]) to[a[i]] = ++U;
			a[i] = to[a[i]];
		}
		REP(i, 1, n)
		{
			b[i] = read<int>();
			if (!to[b[i]]) to[b[i]] = ++U;
			b[i] = to[b[i]];
		}
		REP(i, 1, U) vis1[i] = vis2[i] = 0;
		REP(i, 1, n) vis1[a[i]] = 1;
		REP(i, 1, n) vis2[b[i]] = 1;
		register int l = 2, r = n, ans = -1;
		REP(i, 1, n)
			if (!vis2[a[i]])
			{
				printf("-1\n");
				goto ne;
			}
		REP(i, 1, n)
			if (!vis1[b[i]])
			{
				printf("-1\n");
				goto ne;
			}
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (check(mid))
			{
				ans = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}

		printf("%d\n", ans);
ne:;
	}

	return 0;
}
