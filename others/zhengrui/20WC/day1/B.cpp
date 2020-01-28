/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.27 16:35
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
const int maxn = 1e5 + 10, inf = 1e9;

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

typedef long long ll;
ll goodmin() {return inf;}
	template <typename ...T>
int goodmin(ll x, T... y)
{
	int z = goodmin(y...);
	return x < z ? x : z;
}
int n, a[maxn];
ll Min = inf, Max;
struct node
{
	int a[2];
	ll l, r;
	inline void operator += (int x)
	{
		if (r == -1) return;
		int tmp = a[0] % 3;
		if (tmp > x)
		{
			r = -1;
			return;
		}
		l += tmp;
		r += tmp;
		a[0] -= tmp;
		a[1] -= tmp;
		x -= tmp;
		tmp = goodmin(a[0], a[1], x) / 3;
		if (a[1] % 3 > x - 3 * tmp)
		{
			tmp--;
			if (tmp < 0)
			{
				r = -1;
				return;
			}
		}
		tmp *= 3;
		r += tmp;
		a[0] = a[1] - tmp;
		a[1] = x - tmp;
	}
	inline node operator + (int x)
	{
		node tmp = *this;
		tmp += x;
		return tmp;
	}
}pre[maxn], suf;
void solve(node L, int x, node R)
{
	if (L.r == -1 || R.r == -1) return;
	L.l += R.l;
	L.r += R.r;
	L += x;
	L += R.a[1];
	L += R.a[0];
	L += 0;
	L += 0;
	if (~L.r)
	{
		chkmin(Min, L.l);
		chkmax(Max, L.r);
	}
}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n)
		pre[i] = pre[i-1] + (a[i] = read<int>());
	DEP(i, n, 1)
	{
		solve(pre[i-1], a[i] - 2, suf);
		suf += a[i];
	}
	if (Min == inf) puts("0");
	else printf("%lld\n", (Max - Min) / 3 + 1);
	return 0;
}
