#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 5;

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

int y[maxn][maxn];
int sg[maxn];

int dfs(int x)
{
	if (sg[x] != -1) return sg[x];
	set <int> s;
	register int res = 0;
	REP(i, 1, y[x][0]) res ^= dfs(y[x][i]);
	REP(i, 1, y[x][0]) s.insert(res ^ dfs(y[x][i]));
	for (register int i = 0; ; i++)
		if (s.find(i) == s.end()) return sg[x] = i;
}

int main()
{
#ifdef CraZYali
	freopen("3B16.in", "r", stdin);
	freopen("3B16.out", "w", stdout);
#endif
	REP(i, 1, 1000)
		REP(j, 1, i - 1)
			if (i % j == 0) y[i][++y[i][0]] = j;

	memset(sg, -1, sizeof(sg));
	while (scanf("%d", &n) != EOF)
	{
		register int res = 0;
		REP(i, 1, n) res ^= dfs(read<int>());
		if (res) printf("freda\n");
		else printf("rainbow\n");
	}
	
	return 0;
}
