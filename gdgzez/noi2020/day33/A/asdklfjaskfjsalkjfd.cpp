/*
	Problem:	A.cpp
	Time:		2020-07-24 14:50
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, B = 320, mB = B + 20;

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

int n, w, q, type, tot;
int a[maxn], blg[maxn], L[maxn], R[maxn];

int show[maxn][mB];

int count(int val, int l, int r)
{
	int bl = blg[l], br = blg[r], res = 0;
	if (bl == br)
	{
		REP(i, l, r) res += (a[i] == val);
		return res;
	}
	res = show[val][br - 1] - show[val][bl];
	REP(i, l, R[bl]) res += (a[i] == val);
	REP(i, L[br], r) res += (a[i] == val);
	return res;
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> w >> q >> type;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 0, n) blg[i] = i / B + 1;
	REP(i, 0, n) R[blg[i]] = i;
	DEP(i, n, 0) L[blg[i]] = i;
	tot = blg[n];
	REP(val, 0, n - 1)
		REP(i, 1, tot)
		{
			show[val][i] = show[val][i - 1];
			REP(j, L[i], R[i]) show[val][i] += (a[j] == val);
		}
	//show[val][B] : block (on seq) 1 ... B ---> = val

	int lastans = 0;
	while (q--)
	{
		int l(read<int>()), r(read<int>()), k(read<int>());
		if (type)
		{
			l ^= lastans;
			r ^= lastans;
			k ^= lastans;
			if (l > r) swap(l, r);
		}
		int res = n, tot = 0;
		REP(i, 0, n - 1)
		{
			int tmp = count(i, l, r);
			if (tmp > w) continue;
			else tot += tmp;
			if (tot >= k)
			{
				res = i;
				break;
			}
		}
		printf("%d\n", lastans = res);
	}
	return 0;
}
