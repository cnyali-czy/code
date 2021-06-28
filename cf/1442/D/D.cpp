/*
	Problem:	D.cpp
	Time:		2021-06-28 16:25
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define poly vector <int>
#define int long long

using namespace std;
const int maxn = 3000 + 10, inf = 1e18;

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

int n, k;

poly v[maxn], f;int sum[maxn];
inline int deg(poly f) {return (int)f.size() - 1;}

int ans;
void cdq(int l, int r)
{
	if (l == r)
	{
		int sum = 0;
		REP(i, 0, deg(v[l]))
		{
			sum += v[l][i];
			ans = max(ans, sum + f[k - i]);
		}
		return;
	}
	int mid = l + r >> 1;
	auto now = f;
	REP(i, l, mid)
	{
		int siz = deg(v[i]), val = sum[i];
		DEP(j, k, siz) f[j] = max(f[j], f[j - siz] + val);
	}
	cdq(mid + 1, r);
	f = now;
	REP(i, mid + 1, r)
	{
		int siz = deg(v[i]), val = sum[i];
		DEP(j, k, siz) f[j] = max(f[j], f[j - siz] + val);
	}
	cdq(l, mid);
	f = now;
}

signed main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n)
	{
		v[i].resize(read<int>() + 1);
		REP(j, 1, deg(v[i])) v[i][j] = read<int>();
		if (deg(v[i]) > k) v[i].resize(k + 1);
		for (auto j : v[i]) sum[i] += j;
	}
	f.resize(k + 1);
	cdq(1, n);
	cout << ans << endl;
	return 0;
}
