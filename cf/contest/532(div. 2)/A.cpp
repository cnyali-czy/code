#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100 + 5;

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
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int m, n, k, a[maxn], ans;

bool del[maxn];

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> k;
	REP(i, 1, n) a[i] = read<int>();
	REP(b, 1, n)
	{
		REP(i, 1, n) del[i] = 0;
		register int res = b;
		int e = 0, s = 0;
		while (res > 0) del[res] = 1, res -= k;
		res = b;
		while (res <= n) del[res] = 1, res += k;
		REP(i, 1, n) if (!del[i])
			if (a[i] == 1) e++;
			else s++;
		chkmax(ans, abs(e - s));
	}
	cout << ans;
	return 0;
}
