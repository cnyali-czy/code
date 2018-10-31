#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2e5 + 10, maxk = 10;

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

int m, n, k, a[maxn];

namespace bf
{
	int calc(int x[])
	{
		int res = 0;
		REP(i, 1, k)
			REP(j, i + 1, k)
			if (x[i] > x[j]) res++;
		return res;
	}
	bool vis[maxn];int p[maxn];
	void dfs(int x)
	{
		if (x == n)
		{
			REP(i, 1, n - k + 1)
				if (calc(p + i - 1) ^ a[i]) return;
			REP(i, 1, n)printf("%d ", p[i]);exit(0);
		}
		x++;
		REP(i, 1, n)
			if (!vis[i])
			{
				vis[i] = 1;
				p[x] = i;
				dfs(x);
				vis[i] = 0;
			}
	}
	void work()	{dfs(0);}
}

int bg[maxn], ne[maxn * maxk * maxk], to[maxn * maxk * maxk], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int in[maxn], q[maxn], head, tail, now, ans[maxn];

namespace c1
{
	void work()
	{
		REP(i, 1, n - 1)
			if (a[i]) add(i, i + 1), in[i+1]++;
			else add(i + 1, i), in[i]++;
		head = 1;now = n;
		REP(i, 1, n)
			if (!in[i]) q[++tail] = i;
		while (head <= tail)
		{
			register int x = q[head++];ans[x] = now--;
			for (register int i = bg[x]; i ; i = ne[i])
			{
				in[to[i]]--;
				if (!in[to[i]]) q[++tail] = to[i];
			}
		}
		REP(i, 1, n) printf("%d ", ans[i]);
	}
}

bool M[maxn][maxk];

namespace c2
{
	void work()
	{
		REP(i, 1, n - k + 1)
		{
			register int l = i, r = i, cnt = 0;
			while (cnt < a[i])
			{
				if (r < i + k - 1) r++;
				else l++, r = l + 1;
				if (!M[l][r - l])
				{
					add(l, r);
					in[r]++;
					M[l][r - l] = 1;
					cnt++;
				}
			}
			REP(j, i, i + k - 1)
				REP(l, j + 1, i + k - 1)
				if (!M[j][l-j])
				{
					M[j][l-j] = 1;
					add(l, j);
					in[j]++;
				}
		}
		head = 1;now = n;
		REP(i, 1, n)
			if (!in[i]) q[++tail] = i;
		while (head <= tail)
		{
			register int x = q[head++];ans[x] = now--;
			for (register int i = bg[x]; i ; i = ne[i])
			{
				in[to[i]]--;
				if (!in[to[i]]) q[++tail] = to[i];
			}
		}
		REP(i, 1, n) printf("%d ", ans[i]);
	}
}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> k;
	REP(i, 1, n - k + 1) a[i] = read<int>();
	if (n <= 5) bf::work();
	else if (k == 2) c1::work();
	else c2::work();
	return 0;
}
