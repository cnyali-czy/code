/*
	Problem:	B.cpp
	Time:		2021-07-13 08:34
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <queue>
#include <iostream>
#include <set>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 2e5 + 10, inf = 1e16;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q, a[maxn];

inline bool chkmax(int &x, int y) { if (x < y) {x = y;return 1;}return 0; }
namespace bf
{
	int f[5005][5005][2];
	int main()
	{
		REP(i, 0, n)
		{
			REP(j, 0, n) f[i][j][0] = f[i][j][1] = -inf;
			f[i][0][0] = 0;
		}
		f[n][1][1] = a[n];
		DEP(i, n - 1, 1) REP(j, 0, n - i + 1)
		{
			f[i][j][0] = max(f[i + 1][j][1], f[i + 1][j][0]);
			if (j) f[i][j][1] = f[i + 1][j - 1][0] + a[i];
		}
		int lstans = 0;
		REP(T, 1, q)
		{
			int i = (lstans + read<int>()) % n + 1, x = (lstans + read<int>()) % n + 1;
			printf("%lld%c", lstans = max(f[i][x][0], f[i][x][1]), T == end_T ? '\n' : ' ');
		}
		return 0;
	}
}
namespace all
{
	int ans[maxn];
	int pre[maxn], nxt[maxn];
	set <pair <int, int> > s;
	int main()
	{
		REP(i, 1, n) pre[i] = i - 1, nxt[i] = n + 1;
		REP(i, 1, n) s.emplace(a[i], i);
		int res = 0;
		REP(i, 1, n + 1 >> 1)
		{
			int x = (--s.end()) -> second;
			res += a[x];ans[i] = res;
			if (i == end_i) break;
			s.erase(--s.end());
			if (pre[x])
			{
				s.erase({a[pre[x]], pre[x]});
				a[pre[x]] -= a[x];
				s.emplace(a[pre[x]], pre[x]);
				nxt[pre[x]] = nxt[x];
			}
			if (nxt[x] <= n)
			{
				s.erase({a[nxt[x]], nxt[x]});
				a[nxt[x]] -= a[x];
				s.emplace(a[nxt[x]], nxt[x]);
				pre[nxt[x]] = pre[x];
			}
		}
		int lstans = 0;
		REP(T, 1, q)
		{
			lstans = 0;
			int i = (lstans + read<int>()) % n + 1, x = (lstans + read<int>()) % n + 1;
			i = 1;x = T;
			printf("%lld%c", lstans = ans[x], T == end_T ? '\n' : ' ');
		}
		return 0;
	}
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();q = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	if (n <= 5000) return bf :: main();
//	else return all :: main();

	return 0;
}
