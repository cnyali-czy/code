/*
	Problem:	632.cpp
	Time:		2021-05-29 20:06
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 8000 + 10, MOD = 998244353;

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

int n;
char a[maxn][maxn / 4];
inline bool G(int x, int y)
{
	if (x > y) swap(x, y);
	y -= x;
	return (a[x][(y + 3) / 4] >> (y - 1 & 3)) & 1;
}
int ans[maxn];
namespace bf
{
	void work()
	{
		REP(S, 1, (1 << n) - 1)
		{
			static int stk[maxn];int t = 0;
			REP(i, 1, n) if (S >> (i - 1) & 1)
			{
				stk[++t] = i;
				REP(j, 1, t - 1) if (!G(stk[j], i)) goto gg;
			}
			ans[t]++;
gg:;
		}
	}
}
int fac[maxn], invs[maxn], Invs[maxn];
void init(int n)
{
	fac[0] = invs[0] = Invs[0] = 1;
	fac[1] = invs[1] = Invs[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Invs[i] = 1ll * invs[i] * Invs[i - 1] % MOD;
	}
}
inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Invs[m] % MOD * Invs[n - m] % MOD;}
namespace full
{
	int u[30], v[30], cnt;
	bool judge()
	{
		REP(i, 1, n) REP(j, i + 1, n) if (!G(i, j))
		{
			cnt++;
			u[cnt] = i;
			v[cnt] = j;
			if (cnt > 20) return 0;
		}
		return !cnt;
	}
	void work()
	{
		REP(i, 1, n) ans[i] = C(n, i);
		/*
		REP(s, 0, (1 << cnt) - 1)
		{
			vector <int> ve;
			REP(i, 1, cnt) if (s >> (i - 1) & 1) ve.emplace_back(u[i]), ve.emplace_back(v[i]);
			sort(ve.begin(), ve.end());ve.resize(unique(ve.begin(), ve.end()) - ve.begin());
			i64 sgn = (__builtin_popcount(s) & 1 ? -1 : 1);
		}*/
	}
}
namespace A
{
	int fa[maxn], siz[maxn];
	int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
	inline void uni(int x, int y)
	{
		x = find(x);y = find(y);
		if (x == y) return;
		fa[x] = y;siz[y] += siz[x];
	}
	void work()
	{
		REP(i, 1, n) fa[i] = i, siz[i] = 1;
		REP(i, 1, n) REP(j, i + 1, n) if (!G(i, j)) uni(i, j);
		ans[0] = 1;
		REP(r, 1, n) if (r == find(r))
			DEP(i, n, 1) ans[i] = (ans[i] + 1ll * ans[i - 1] * siz[r]) % MOD;
	}
}
int main()
{
#ifdef CraZYali
	file("632");
#endif
	n = read<int>();init(n);
	REP(i, 1, n)
	{
		static char str[maxn];
		scanf("%s", str + 1);
		REP(j, 1, (n - i + 3) / 4) a[i][j] = isdigit(str[j]) ? str[j] - '0' : str[j] - 'A' + 10;
	}
	if (n <= 20) bf :: work();
	else if (full :: judge()) full :: work();
	else A :: work();
	REP(i, 1, n) printf("%d%c", ans[i], i == end_i ? '\n' : ' ' );
	return 0;
}
