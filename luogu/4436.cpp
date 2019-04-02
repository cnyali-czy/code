#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6 + 10;

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

int n, m, p;
int pos[maxn], l[maxn], r[maxn], rnd[maxn];

void work(int x)
{
	bool flag = 1;
	while (flag)
	{
		flag = 0;
		if (l[x] <= pos[l[x]-1] && pos[l[x]-1] <= r[x])
		{
			chkmin(l[x], l[l[x]-1]);
			chkmax(r[x], r[r[x]-1]);
			flag = 1;
		}
		if (l[x] <= pos[r[x]] && pos[r[x]] <= r[x])
		{
			chkmin(l[x], l[r[x]+1]);
			chkmax(r[x], r[r[x]+1]);
			flag = 1;
		}
	}
}

int main()
{
#ifdef CraZYali
	freopen("4436.in", "r", stdin);
	freopen("4436.out", "w", stdout);
#endif
	cin >> n >> m >> p;
	while (m --> 0)
	{
		int x(read<int>()), y(read<int>());
		pos[x] = y;
	}
	pos[0] = pos[n+1] = n + 1;
	REP(i, 1, n) l[i] = r[i] = i;
	REP(i, 2, n) if (!pos[i-1]) l[i] = l[i-1];
	DREP(i, n - 1, 1) if (!pos[i]) r[i] = r[i+1];
	REP(i, 1, n) rnd[i] = i;
	random_shuffle(rnd + 1, rnd + 1 + n);
	REP(i, 1, n) work(rnd[i]);
	while (p --> 0)
	{
		int x(read<int>()), y(read<int>());
		puts(l[x] <= y && y <= r[x] ? "YES" : "NO");
	}
	return 0;
}
