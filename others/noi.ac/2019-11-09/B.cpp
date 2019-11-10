/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.09 21:01
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <bitset>
#include <cstring>

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

namespace run
{
	const int maxn = 1e5 + 10;
#define poly bitset <maxn>
	inline int deg(const poly &x)
	{
		int res(x.size());
		while (res > 1 && !x[res-1]) res--;
		return res;
	}
	inline void print(const poly &x)
	{
		int n = deg(x);
		REP(i, 0, deg(x) - 1)
			printf("%d%c", (bool)x[i], i == end_i ? '\n' : ' ');
	}
	inline poly input(int n)
	{
		poly res;
		REP(i, 0, n - 1) res[i] = read<int>();
		return res;
	}
	int seq[1000005], n, m, cnt;
	int main()
	{
		n = read<int>() + 1;
		m = read<int>() + 1;
		poly A(input(n));
		poly B(input(m));
		memset(seq, -1, sizeof seq);
		while (m)
		{
			cnt++;
			if (n < m)
			{
				swap(A, B);
				swap(n, m);
				continue;
			}
			A ^= B << (seq[cnt] = n - m);
			while (n && !A[n - 1]) n--;
		}
		poly X, Y;
		X.set(0);
		DREP(i, cnt, 1)
			if (seq[i] == -1) swap(X, Y);
			else Y ^= X << seq[i];
		printf("%d %d\n", deg(X) - 1, deg(Y) - 1);
		print(X);
		print(Y);
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	return run::main();
}
