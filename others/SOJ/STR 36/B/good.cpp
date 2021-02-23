/*
	Problem:	B.cpp
	Time:		2021-02-21 10:52
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <tuple>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10;

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

int n, bst, a[maxn], b[maxn], c[maxn];

const int L = 6, maxN = L * L * L + 10;
tuple <int, int, int> v[maxN];int N;

inline bool ok(int a, int b, int c)
{
	return a + b + c > 2 * max(max(a, b), c);
}

void turn(int pick[])
{
	REP(i, 1, n)
	{
		a[i] = get<0>(v[pick[i]]);
		b[i] = get<1>(v[pick[i]]);
		c[i] = get<2>(v[pick[i]]);
	}
}
int pick[maxn], ans[maxn];
void calc()
{
	turn(pick);
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + n);
	sort(c + 1, c + 1 + n);
	
	int res = 0;
	REP(i, 1, n) if (ok(a[i], b[i], c[i])) res++;
	if (res < bst)
	{
		bst = res;
		REP(i, 1, n) ans[i] = pick[i];
#ifdef CraZYali
		fprintf(stderr, "now best = %d\n", res);
		turn(pick);
		REP(i, 1, n) fprintf(stderr, "%d %d %d\n", a[i], b[i], c[i]);
#endif
	}
#ifdef CraZYali
	else if (res == 1)
	{
		cerr << '\n';
		turn(pick);
		REP(i, 1, n) fprintf(stderr, "%d %d %d\n", a[i], b[i], c[i]);
	}
#endif
}

void dfs(int x, int lst = 1)
{
	if (x == n) calc();
	else
	{
		x++;
		REP(i, lst, N)
		{
			pick[x] = i;
			dfs(x, i);
		}
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n;bst = n + 1;
	/*
	REP(i, 1, n) REP(j, 1, n) REP(k, 1, n) if (ok(i, j, k)) v[++N] = make_tuple(i, j, k);
	dfs(0);
	turn(ans);
	REP(i, 1, n) printf("%d %d %d\n", a[i], b[i], c[i]);
	*/
	REP(i, 2, n) printf("1 %d %d\n", i, i);
	printf("%d 1 %d\n", n, n);

	return 0;
}
