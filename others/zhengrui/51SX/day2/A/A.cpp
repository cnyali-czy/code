/*
	Problem:	A.cpp
	Time:		2020-05-02 08:38
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <ctime>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e6 + 10;

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

int n, q, a[31], lst[31], val[maxn], Time[maxn], qaq;
struct cmp
{
	inline int operator () (int x) const {return hash<int>{}(x ^ qaq);}
};
unordered_map <int, int, cmp> S;

void ins(int x, int t)
{
	DEP(i, n, 0) if (x & (1 << i))
	{
		if (!a[i])
		{
			a[i] = x;
			lst[i] = t;
			return;
		}
		if (t > lst[i])
		{
			swap(t, lst[i]);
			swap(x, a[i]);
		}
		x ^= a[i];
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	srand(time(0));
	qaq = rand();
	n = read<int>();q = read<int>();
	REP(i, 1, q)
	{
		int opt(read<int>()), x(read<int>());
		val[i] = x;
		if (opt == 1)
		{
			S[x] = i;
			Time[i] = q + 1;
		}
		else
		{
			Time[S[x]] = i;
			S.erase(x);
		}
	}
	int ans = 0;
	REP(i, 1, q)
	{
		if (Time[i]) ins(val[i], Time[i]);
		int res = 0;
		REP(j, 0, n) if (a[j] && lst[j] > i) res++;
		ans ^= (1 << n - res);
	}
	cout << ans << endl;
	return 0;
}
