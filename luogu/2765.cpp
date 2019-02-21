#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 60 + 5, MAX = 3205;

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

int n, cnt, ans = 1;

bitset <MAX> is;
vector <int> d[maxn];

int main()
{
#ifdef CraZYali
	freopen("2765.in", "r", stdin);
	freopen("2765.out", "w", stdout);
#endif
	cin >> n;
	for (int i = 1; i * i <= MAX; i++) is[i * i] = 1;
	while (1)
	{
		REP(i, 1, cnt)
			if (is[d[i][d[i].size()-1] + ans])
			{
				d[i].push_back(ans);
				ans++;
				i = 0;
				continue;
			}
		if (cnt < n) d[++cnt].push_back(ans++);
		else break;
	}
	cout << ans - 1 << endl;
	REP(i, 1, n)
	{
		REP(j, 0, d[i].size() - 1) printf("%d ", d[i][j]);
		putchar(10);
	}
	return 0;
}
