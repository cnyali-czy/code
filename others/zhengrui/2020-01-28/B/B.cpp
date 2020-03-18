/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.28 15:42
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmymin(a, b) (a > (b) ? a = (b) : a) 

#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 8e4 + 10, B = 500, maxN = 2e7, maxs = maxn / B + 50;

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

int n, m, a[maxn];
int tot, L[maxs], R[maxs], blg[maxn], lst[maxs], rt[maxs][maxn];
int b[maxn];
inline int mymin(int x, int y) {return x < y ? x : y;}
inline void insert(int *p, int x, int val)
{
	while (x <= n)
	{
		p[x] += val;
		x += x & -x;
	}
}
inline int sum(int *p, int x)
{
	int res = 0;
	while (x > 0)
	{
		res += p[x];
		x &= (x - 1);
	}
	return res;
}
void clear(int p, int x)
{
	int ccc = sum(rt[p], x - 1);
	REP(i, x, lst[p])
	{
		int here = sum(rt[p], i) - ccc;
		insert(rt[p], i, -here);
	}
}
int lastans = n;
int main()
{
#ifdef CraZYali
	file("B");
	freopen("B.err","w",stderr);
#endif
	n = read<int>();
	m = read<int>();
	int ccc(B);
	REP(i, 1, n)
	{
		if (ccc == B)
		{
			ccc = 0;
			blg[i] = blg[i-1] + 1;
			R[tot++] = i-1;
			L[tot] = i;
		}
		else blg[i] = blg[i-1];
		insert(rt[tot], a[i] = read<int>(), 1);
		chkmax(lst[tot], a[i]);
		++ccc;
	}
	R[tot] = n;
	while (m--)
	{
		int opt(read<int>()), l(read<int>()), r(read<int>()), x(read<int>()), bl(blg[l]), br(blg[r]);
		if (opt == 1)
		{
			if (x == n) continue;
			int cnt = 0;
			if (bl == br)
			{
				if (lst[bl] <= x) continue;
				REP(i, l, r) if (a[i] > x)
				{
					int zz = mymin(a[i], lst[bl]);
					insert(rt[bl], zz, -1);
					a[i] = x;
					cnt++;
				}
				if (cnt) insert(rt[bl], x, cnt);
				continue;
			}
			if (lst[bl] > x)
			{
				cnt = 0;
				REP(i, l, R[bl]) if (a[i] > x)
				{
					int zz = mymin(a[i], lst[bl]);
					insert(rt[bl], zz, -1);
					++cnt;
					a[i] = x;
				}
				if (cnt) insert(rt[bl], x, cnt);
			}
			if (lst[br] > x)
			{
				cnt = 0;
				REP(i, L[br], r) if (a[i] > x)
				{
					int zz = mymin(a[i], lst[br]);
					insert(rt[br], zz, -1);
					++cnt;
					a[i] = x;
				}
				if (cnt) insert(rt[br], x, cnt);
			}
			REP(i, bl + 1, br - 1) if (lst[i] > x)
			{
				int tot = sum(rt[i], n) - sum(rt[i], x);
				clear(i, x + 1);
				lst[i] = x;
				insert(rt[i], x, tot);
			}
		}
		else
			if (bl == br)
			{
				int m(0);
				REP(i, l, r)
					if (lst[bl] < a[i]) b[++m] = lst[bl];
					else b[++m] = a[i];
				nth_element(b + 1, b + x, b + m + 1);
				printf("%d\n", b[x]);
			}
			else
			{
				int m(0), res(0);
				REP(i, l, R[bl]) b[++m] = mymin(lst[bl], a[i]);
				REP(i, L[br], r) b[++m] = mymin(lst[br], a[i]);
				sort(b + 1, b + 1 + m);
				int _l = 1, _r = n;
				int Res = upper_bound(b + 1, b + 1 + m, lastans) - b - 1;
				REP(i, bl + 1, br - 1)
				{
					Res += sum(rt[i], lastans);
					if (Res >= x) break;
				}
				if (Res >= x) _r = lastans;
				else _l = lastans + 1;
				while (_l <= _r)
				{
					int mid = _l + _r >> 1;

					int lll = 1, rrr = m;
					while (lll <= rrr)
					{
						int mmm = lll + rrr >> 1;
						if (b[mmm] > mid) rrr = mmm - 1;
						else lll = mmm + 1;
					}
					Res = rrr + 1;
					if (Res < x)
						REP(i, bl + 1, br - 1)
						{
							Res += sum(rt[i], mid);
							if (Res >= x) break;
						}
					if (Res >= x) _r = mid - 1;
					else _l = mid + 1;
				}
				printf("%d\n", _r + 1);
			}
	}
	return 0;
}
