#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;

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

int m, n, k, T;

namespace bf
{
	const int maxn = 2000 + 10, maxm = 2000 + 10, maxk = 2000 + 10;
	int a[maxn], s[maxk][maxn];
	void work()
	{
		REP(i, 1, n) a[i] = read<int>();
		REP(i, 1, k)
			REP(j, 1, n)
				s[i][j] = s[i][j-1] + (a[j] == i);
		while (m --> 0)
		{
			register int l, r, cnt = 0;
			l = read<int>();r = read<int>();
			REP(i, 1, k)
				if (s[i][r] - s[i][l-1] == T) ++cnt;
			write(cnt);putchar(10);	
		}
	}
}

namespace cheat
{
	const int maxn = 5e5 + 10, maxm = 5e5 + 10, maxk = 5e5 + 10;
	int a[maxn];

	int C[maxn];
	void add(int x, int y)
	{
		while (x > 0)
		{
			C[x] += y;
			x -= x & -x;
		}
	}
	int sum(int x)
	{
		register int y = 0;
		while (x <= n)
		{
			y += C[x];
			x += x & -x;
		}
		return y;
	}

	vector <int> v[maxn];
	
	struct node
	{
		int l, r, id;
		bool operator < (node B) const {return r < B.r;}
	}t[maxm];

	int pos[maxn], ans[maxm];

	void work()
	{
		REP(i, 1, n) v[a[i] = read<int>()].push_back(i);
		REP(i, 1, m)
		{
			t[i].l = read<int>();
			t[i].r = read<int>();
			t[i].id = i;
		}
		sort(t + 1, t + 1 + m);
		register int now = 0;
		REP(i, 1, n)
		{
			register int c = a[i];
			if (pos[c] - T - 1 >= 0)	add(v[c][pos[c] - T - 1],	1);
			if (pos[c] - T >= 0)		add(v[c][pos[c] - T], 		-2);
			if (pos[c] - T + 1 >= 0)	add(v[c][pos[c] - T + 1],	1);
			for (;t[now + 1].r == i;)
			{
				++now;
				ans[t[now].id] = sum(t[now].l);
			}
			pos[c]++;
		}
		REP(i, 1, m) printf("%d\n", ans[i]);
	}
}

int main()
{
#ifdef CraZYali
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
#endif
	cin >> n >> m >> k >> T;
	if (0 && n <= 2000 && m <= 2000 && k <= 2000) bf::work();
	else cheat::work();
	return 0;
}
