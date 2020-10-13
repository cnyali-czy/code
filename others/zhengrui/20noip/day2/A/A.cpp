#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10, maxm = 2e5 + 10, MOD = 998244353;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y)
{
	fa[find(x)] = find(y);
}

int in[maxn], ou[maxn];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	int n = read<int>(), m = n + n;
	REP(i, 1, m) fa[i] = i;
	REP(i, 1, m)
	{
		int x = read<int>(), y = read<int>();
		if (ou[x]) uni(ou[x], i);ou[x] = i;
		if (in[y]) uni(in[y], i);in[y] = i;
	}
	int ans = 1;
	REP(i, 1, m) if (fa[i] == i) ans = 2 * ans % MOD;
	cout << ans << endl;
	return 0;
}
