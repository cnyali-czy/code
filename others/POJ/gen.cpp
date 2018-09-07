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

int m, n, k;

int fa[1010];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}

int main()
{
	freopen("1741.in", "w", stdout);
	n = 1000, k = 5000000;
	printf("%d %d\n", n, k);
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, n - 1)
	{
		register int x = rand() % n + 1;
		register int y = rand() % n + 1;
		while (find(x) == find(y)) y = rand() % n + 1;
		printf("%d %d %d\n", x, y, rand() % 500 + 1);
		fa[find(x)] = find(y);
	}
	puts("0 0");
	return 0;
}
