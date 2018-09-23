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
	
	const int maxsq = 720;

	int belong[maxsq], block_siz, block_cnt, left[maxsq], right[maxsq];

	bitset <maxsq> B[maxsq], A;
	
	void getbelong()
	{
		block_siz = sqrt(n);
		register int l = 1, r = block_siz;
		while (r <= n)
		{
			block_cnt++;
			REP(i, l, r) B[belong[i] = block_cnt].set(a[i]);
			left[block_cnt] = l;
			right[block_cnt] = r;
			l += block_siz;r += block_siz;
		}
		if (r > n)
		{
			block_cnt++;
			REP(i, l, n) B[belong[i] = block_cnt].set(a[i]);
			left[block_cnt] = l;right[block_cnt] = r;
		}
	}

	int ans[maxn];
	int vis[maxn];

	void calc(int id)
	{
		REP(i, 1, k) vis[i] = 0;
		REP(i, left[id], right[id])
			vis[a[i]]++;
		ans[id] = 0;
		REP(i, left[id], right[id])
			if (vis[a[i]] == 1) ans[id]++;
	}

	void work()
	{
		REP(i, 1, n) a[i] = read<int>();
		getbelong();
		REP(i, 1, block_cnt) calc(i);
		while (m --> 0)
		{
			register int l = read<int>(), r = read<int>();
			register int bl = belong[l], br = belong[r];
			register int Ans = 0;
			REP(i, bl + 1, br - 1) Ans += ans[i];
			REP(i, bl + 2, br - 1)
			{
				B[0] = B[i] & B[i-1];
				Ans -= B[0].count();
			}
			B[0].reset();
			REP(i, bl + 1, br - 1) B[0] |= B[i];
			A.reset();
			REP(i, l, left[bl+1] - 1) A.set(a[i]);
			REP(i, left[br-1] + 1, r) A.set(a[i]);
			A &= B[0];
			Ans += A.count();
			write(Ans);putchar(10);
		}
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
