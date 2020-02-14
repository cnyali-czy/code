/*
	Problem:	2978.cpp
	Time:		2020-02-14 10:44
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <vector>
#include <bitset>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 1e7 + 10, N = 450, MOD = 998244353;

int power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
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

int prime[maxn], p_cnt, Max[maxn], id[maxn], to[maxn];
bool notp[maxn];
struct __init__
{
	__init__(const int N = maxn - 10)
	{
		REP(i, 2, N)
		{
			if (!notp[i]) {prime[++p_cnt] = Max[i] = i;id[i] = p_cnt;to[i] = i;}
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];if (tmp > N) break;
				notp[tmp] = 1;
				Max[tmp] = prime[j] > Max[i] ? prime[j] : Max[i];
				if (i % prime[j] == 0) {to[tmp] = to[i];break;}
				else to[tmp] = to[i] * prime[j];
			}
		}
	}
}__INIT__;


bitset <N + 5> p[N + 5];
vector <int> v[maxn], toclear;
bool vis[maxn];
int cnt;

void insert(bitset <N + 5> &x)
{
	DEP(i, N, 1) if (x[i])
		if (p[i].any()) x ^= p[i];
		else
		{
			cnt++;
			p[i] = x;
			return;
		}
}

int count(int l, int r)
{
	int res = 0;
	REP(i, l, r)
		for (int x = to[i]; x > 1; x /= Max[x])
			if (!vis[Max[x]])
			{
				toclear.emplace_back(Max[x]);
				vis[Max[x]] = 1;
				res++;
			}
	for (auto i : toclear) vis[i] = 0;
	return res;
}

int main()
{
#ifdef CraZYali
	file("2978");
#endif
	register int T = read<int>();
	while (T--)
	{
		int l = read<int>(), r = read<int>(), k = 0;
		if (r - l + 1 >= 6660) k = r - l + 1 - count(l, r);
		else
		{
			REP(i, 1, N) p[i].reset();
			toclear.clear();
			REP(i, l, r) v[Max[i]].clear();
			REP(i, l, r)
			{
				v[Max[i]].emplace_back(i);
				if (!vis[Max[i]]) {vis[Max[i]] = 1;toclear.emplace_back(Max[i]);}
			}
			for (auto m : toclear)
				if (id[m] <= N)
					for (auto i : v[m])
					{
						bitset <N + 5> cur;
						for (int x = i; x > 1; x /= Max[x]) cur.flip(id[Max[x]]);
						if (cur.any()) insert(cur);
					}
				else
				{
					cnt++;
					if (v[m].size() > 1)
					{
						bitset <N + 5> fir;
						for (int x = v[m][0]; x > 1 ; x /= Max[x]) if (id[Max[x]] <= N) fir.flip(id[Max[x]]);
						REP(j, 1, v[m].size() - 1)
						{
							bitset <N + 5> cur = fir;
							for (int x = v[m][j]; x > 1; x /= Max[x]) if (id[Max[x]] <= N) cur.flip(id[Max[x]]);
							if (cur.any()) insert(cur);
						}
					}
				}
			for (auto i : toclear) vis[i] = 0;
			k = r - l + 1 - cnt;cnt = 0;
		}
		printf("%d\n", power_pow(2, k));
	}
	return 0;
}
