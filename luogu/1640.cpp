#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000000 + 10;

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

int m, n, k;
int fa[maxn], siz[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

bool cir[maxn];

int main()
{
#ifdef CraZYali
	freopen("1640.in", "r", stdin);
	freopen("1640.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, 1000000) siz[i] = 1, fa[i] = i;
	REP(i, 1, n)
	{
		register int a = find(read<int>()), b = find(read<int>());
		if (a == b) cir[a] = 1;
		else
		{
			cir[a] |= cir[b];
			cir[b] = 0;
			siz[a] += siz[b];
			siz[b] = 0;
			fa[b] = a;
		}
	}
	int ans;
	REP(i, 1, 1000000)
		if (!cir[find(i)])
			if (siz[find(i)] == 1) {ans = i - 1;break;}
			else siz[find(i)]--;
	cout << ans;
	return 0;
}
