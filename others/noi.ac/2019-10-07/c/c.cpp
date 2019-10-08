#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10;

int n, q, type, a[maxn];

int sum1[maxn], sum2[maxn], lim1[maxn], lim2[maxn];

inline bool ok(int l, int r) {return r <= max(lim1[l], lim2[l]);}
int ssr1[maxn], ssr2[maxn];

int main()
{
#ifdef CraZYali
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	cin >> n >> type;
	REP(i, 1, n) scanf("%d", a + i);
	sum1[1] = 1;
	REP(i, 2, n) sum1[i] = sum1[i-1] + (a[i-1] <= a[i]);
	REP(i, 1, n)
	{
		int &res = lim1[i];
		res = i;
		int l(i + 1), r(n);
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (sum1[mid] - sum1[i] == mid - i)
			{
				res = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
	}
	if (type == 2)
	{
		sum2[1] = 1;
		REP(i, 2, n) sum2[i] = sum2[i-1] + (a[i-1] >= a[i]);
		REP(i, 1, n)
		{
			int &res = lim2[i];
			res = i;
			int l(i + 1), r(n);
			while (l <= r)
			{
				int mid = l + r >> 1;
				if (sum2[mid] - sum2[i] == mid - i)
				{
					res = mid;
					l = mid + 1;
				}
				else r = mid - 1;
			}
		}
	}
	REP(i, 1, n) printf("%d%c", lim1[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", lim2[i], i == n ? '\n' : ' ');
	REP(i, 1, n)//ssr1
	{
		int &res = ssr1[i];
		int l(1), r(i);
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (ok(i - mid + 1, i + mid - 1))
			{
				res = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
	}
	REP(i, 1, n - 1)
	{
		int &res = ssr2[i];
		int l(1), r(i);
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (ok(i - mid + 1, i + mid - 1))
			{
				res = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
	}
	REP(i,1,n)printf("%d%c",ssr1[i],i==end_i?'\n':' ');
	REP(i,1,-1+n)printf("%d%c",ssr2[i],i==end_i?'\n':' ');
	cin >> q;
	while (q--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		if (ok(l, r)) puts("Bob");
		else
		{
			bool flag;
			if ((l + r) & 1)
			{
				register int k = r - l - 1 >> 1;
				flag = k <= ssr2[l - k];
			}
			else
			{
				register int k = r - l >> 1;
				flag = k <= ssr1[l - k];
			}
			if (flag) puts("Alice");
			else puts("Bob");
		}
	}
	return 0;
}
