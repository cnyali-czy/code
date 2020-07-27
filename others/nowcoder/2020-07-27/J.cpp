/*
	Problem:	J.cpp
	Time:		2020-07-27 14:39
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 1e5 + 10;

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
#define per vector <int>
int n, m, cnt[maxn];

int c[maxn];
void add(int x, int y = 1)
{
	while (x <= n)
	{
		c[x] += y;
		x += x & -x;
	}
}
int sum(int x)
{
	int y = 0;
	while (x > 0)
	{
		y += c[x];
		x &= (x - 1);
	}
	return y;
}
int sum(int l, int r)
{
	if (l > r) return 0;
	return sum(r) - sum(l - 1);
}
per qaq[maxn];
per get(int k)
{
	REP(i, 1, n) c[i] = 0;
	REP(i, 1, n) add(i, 1);
	int lst = n;
	per res(1, 0);
	REP(i, 1, n)
	{
		int K = k % (n - i + 1);
		if (!K) K = n - i + 1;
		int left = sum(lst + 1, n), gg = -1;
//		cerr << k << ' ' << K << ' ' << i << ' ' << lst << ' ' << left << endl;
		if (left >= K)
		{
			int l = lst + 1, r = n;
			while (l <= r)
			{
				int mid = l + r >> 1;
				if (sum(lst + 1, mid) >= K)
				{
					gg = mid;
					r = mid - 1;
				}
				else l = mid + 1;
			}
		}
		else
		{
			K -= left;
			int l = 1, r = n;
			while (l <= r)
			{
				int mid = l + r >> 1;
				if (sum(1, mid) >= K)
				{
					gg = mid;
					r = mid - 1;
				}
				else l = mid + 1;
			}
		}
		lst = gg;
		res.emplace_back(gg);
		add(gg, -1);
	}
	return res;
}

per good(const per& source, const per& p)
{
	per res(n + 1, 0);
	REP(i, 1, n) res[i] = source[p[i]];
	return res;
}

per pow(per base, int b)
{
	per res(n + 1, 0);
	REP(i, 1, n) res[i] = i;
	while (b)
	{
		if (b & 1) res = good(res, base);
		base = good(base, base);
		b >>= 1;
	}
	return res;
}


per mem[1000005];
per solve(int l, int r)
{
	if (l == r) return mem[l];
	int mid = l + r >> 1;
	return good(solve(l, mid), solve(mid + 1, r));
}

signed main()
{
#ifdef CraZYali
	file("J");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, m)
	{
		int k = read<int>(), x = read<int>();
		if (!qaq[k].size()) qaq[k] = get(k);
		mem[i] = pow(qaq[k], x);
	}
	/*
#ifdef CraZYali
	REP(i, 1, n)
	{
		auto res = get(i);
		REP(j, 1, n) printf("%lld%c", res[j], j == n ? '\n' : ' ');
		fflush(stdout);
	}
#endif
*/
/*
	REP(i, 1, n) if (cnt[i])
	{
		auto res = get(i);
		res = pow(res, cnt[i]);
		ans = good(ans, res);
	}
*/
	per ans = solve(1, m);
	REP(i, 1, n) printf("%lld%c", ans[i], i == end_i ? '\n' : ' ');
	return 0;
}
