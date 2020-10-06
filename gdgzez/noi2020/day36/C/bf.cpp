/*
	Problem:	C.cpp
	Time:		2020-07-31 10:20
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
#define int long long
using namespace std;
const int maxn = 3e5 + 10;

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

int q, w;

#define Vector pair <int, int>
#define x first
#define y second

inline int operator * (Vector A, Vector B) {return A.x * B.y - B.x * A.y;}
Vector stk[maxn];int n;

void fix()
{
	DEP(i, n, 2)
		if (stk[i] * stk[i - 1] >= w)
		{
			swap(stk[i], stk[i - 1]);
		}
}

signed main()
{
	freopen("C.in", "r", stdin);
	freopen("bf.out", "w", stdout);
	q = read<int>();w = read<int>();
	while (q--)
	{
		int opt = read<int>();
		if (opt == 1)
		{
			int h = read<int>(), m = read<int>();
			stk[++n] = make_pair(h, m);
			fix();
		}
		else
		{
			int k = read<int>();
			printf("%lld %lld\n", stk[k].x, stk[k].y);
		}
	}
	return 0;
}
