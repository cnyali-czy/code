/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.04 17:35
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cassert>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

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
typedef long long i64;
namespace run
{
	const int maxn = 3000 + 10;
	int n, a[maxn], b[6], c[6], cnt[maxn];
	vector <int> G[maxn];
	i64 solve1()
	{
		//[x^5]\prod (1 + x ^ cnt[a[i]])
		i64 F[6] = {0};F[0] = 1;
		REP(i, 1, n) DEP(j, 5, 1) F[j] += F[j-1] * cnt[i];
		return F[5];
	}
	i64 solve2(int x, int y)
	{
		i64 res = 0;
		REP(u, 1, n) if (cnt[u])
			REP(v, 1, n) if(cnt[v] && u ^ v)
			{
				i64 F[6] = {0};F[0] = 1;
				int i(0), j(0), pre(0);
				while (i < cnt[u] || j < cnt[v])
					if (j == cnt[v] || i < cnt[u] && G[u][i] < G[v][j])
					{
						REP(k, 1, 5) if (b[k] ^ x && b[k] ^ y) F[k] += F[k-1] * (G[u][i] - pre - 1);
						DEP(k, 5, 1) if (b[k] == x) F[k] += F[k-1];
						pre = G[u][i++];
					}
					else
					{
						REP(k, 1, 5) if (b[k] ^ x && b[k] ^ y) F[k] += F[k-1] * (G[v][j] - pre - 1);
						DEP(k, 5, 1) if (b[k] == y) F[k] += F[k-1];
						pre = G[v][j++];
					}
				if (b[5] ^ x && b[5] ^ y) F[5] += F[4] * (n - pre);
				res += F[5];
			}
		return res;
	}
	
	i64 solve3(int x)
	{
		i64 res = 0;
		REP(i, 1, n) if (cnt[i])
		{
			i64 F[6] = {0};F[0] = 1;
			REP(j, 1, n)
				if (a[j] == i) {DEP(k, 5, 1) if (b[k] == x) F[k] += F[k-1];}
				else			DEP(k, 5, 1) if (b[k] != x) F[k] += F[k-1];
			res += F[5];
		}
		REP(i, 1, 5) if (b[i] ^ x)
			REP(j, i + 1, 5) if (b[j] ^ x)
			{
				int t1 = b[j];
				res -= solve2(x, b[j] = b[i]);
				REP(k, j + 1, 5) if (b[k] ^ x)
				{
					int t2 = b[k];
					res -= solve2(x, b[k] = b[i]);
					b[k] = t2;
				}
				b[j] = t1;
			}
		return res;
	}
	int main()
	{
		n = read<int>();
		REP(i, 1, n) {G[a[i] = read<int>()].emplace_back(i);cnt[a[i]]++;}
		int cnt = 0, x = 0, y = 114514;
		REP(i, 1, 5) c[b[i] = read<int>()]++;
		REP(i, 1, 5) if (c[i] >= 2) {cnt++; if (!x) x = i;else y = i;}
		i64 ans;
		if (!cnt) ans = solve1();
		else if (cnt == 1) ans = solve3(x);
		else ans = solve2(x, y);
		cout << ans << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	return run::main();
}
