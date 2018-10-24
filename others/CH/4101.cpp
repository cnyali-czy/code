#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 5e5 + 10, N = 5e5;

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

int f[maxn], d[maxn], size[maxn];
int find(int x)
{
	if (x == f[x]) return x;
	int root = find(f[x]);
	d[x] += d[f[x]];
	return f[x] = root;
}
void merge(int x, int y)
{
	x = find(x) , y = find(y);
	f[x] = y; d[x] = size[y] ; size[y] += size[x]; 
}

int m, n, k;

int main()
{
#ifdef CraZYali
	freopen("4101.in", "r", stdin);
	freopen("4101.out", "w", stdout);
#endif
	REP(i, 1, N) f[i] = i, size[i] = 1, d[i] = 0;
	cin >> m;
	while (m --> 0)
	{
		register char c = getchar();
		while (c != 'M' && c != 'C') c = getchar();
		register int x = read<int>(), y = read<int>();
		if (c == 'M') merge(x, y);
		else
			if (find(x) != find(y)) printf("-1\n");
			else printf("%d\n", abs(d[x] - d[y])  - 1 );
	}
	
	return 0;
}
