/*
 * File Name:	4151.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.18 21:22
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 50000 + 10, maxm = 1e5 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
long long w[maxm << 1];
inline void add(int x, int y, long long z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, m;
long long p[70];
inline void insert(long long x)
{
	DEP(i, 62, 0) if (x & (1ll << i))
		if (p[i]) x ^= p[i];
		else
		{
			p[i] = x;
			return;
		}
}

bool vis[maxn];
long long d[maxn];
void dfs(int x, int fa = -1)
{
	vis[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		if (vis[to[i]]) insert(w[i] ^ d[to[i]] ^ d[x]);
		else
		{
			d[to[i]] = d[x] ^ w[i];
			dfs(to[i], x);
		}
}

int main()
{
#ifdef CraZYali
	file("4151");
#endif
	cin >> n >> m;
	REP(i, 1, m)
	{
		int x(read<int>()), y(read<int>());long long z(read<long long>());
		add(x, y, z);add(y, x, z);
	}
	dfs(1);
	long long ans = d[n];
	DEP(i, 62, 0) chkmax(ans, ans ^ p[i]);
	cout << ans << endl;
	return 0;
}
