#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 10000 + 5;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;
int fa[maxn];

void makeroot(int x, int c = 0)
{
	if (!x) return;
	int f = fa[x];
	fa[x] = c;
	makeroot(f, x);
}

int main()
{
#ifdef CraZYali
	file("D");
#endif
	cin >> n >> m;
	while (m--)
	{
		char s[20];
		scanf("%s", s + 1);
		int x(read<int>()), y(read<int>());
		makeroot(x);
		if (s[1] == 'Q')
		{
			while (y && y ^ x) y = fa[y];
			printf("%s\n", x == y ? "Yes" : "No");
		}
		else if (s[1] == 'C') fa[x] = y;
		else fa[y] = 0;
	}
	return 0;
}
