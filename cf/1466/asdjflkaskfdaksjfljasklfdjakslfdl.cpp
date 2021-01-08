/*
	Problem:	D.cpp
	Time:		2020-12-30 23:04
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <queue>
#include <set>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10, inf = 1e16;

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

int n, a[maxn];

int deg[maxn];
vector <int> G[maxn];
int u[maxn], v[maxn];
bool in[maxn], may[maxn];
int ans[maxn];

struct cmp1
{
	bool operator () (const int &i, const int &j)
	{
		return a[u[i]] + a[v[i]] < a[u[j]] + a[v[j]];
	}
};
struct cmp2
{
	bool operator () (const int &i, const int &j)
	{
		return a[i] > a[j];
	}
};

signed main()
{
#ifdef CraZYali
	file("D");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		REP(i, 1, n - 1)
			u[i] = read<int>();v[i] = read<int>();
		REP(i, 1, n) in[i] = may[i] = 0;
		int res = 0;
		int j = 0;
		priority_queue <int, vector <int>, cmp2> q2;
		static bool inq[maxn];
		REP(i, 1, n) inq[i] = 0;
		DEP(i, n - 1, 1)
		{
			bool flg = 0;	
			while (q1.size())
			{
				int e = q1.top();q1.pop();
				int u = ::u[e], v = ::v[e];
				if (!in[u] && !in[v])
				{
					res += a[u];res += a[v];
					cerr << T << ' ' << i << endl;
					in[u] = in[v] = 1;
					inq[u] = inq[v] = 1;
					q2.emplace(u);q2.emplace(v);
					flg = 1;
					break;
				}
				else continue;
			}
			if (!flg) while (q2.size())
			{
				int u = q2.top();q2.pop();
				if (in[u])
				{
					for (int v : G[u]) if (!inq[v])
					{
						inq[v] = 1;
						q2.emplace(v);
					}
					continue;
				}
				in[u] = 1;
				res += a[u];
				for (int v : G[u]) if (!inq[v])
				{
					inq[v] = 1;
					q2.emplace(v);
				}
			}
			ans[i] = res;
		}
		REP(i, 1, n - 1) printf("%lld%c", ans[i], i == end_i ? '\n' : ' ');
	}
	return 0;
}
