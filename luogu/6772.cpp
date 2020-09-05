/*
	Problem:	6772.cpp
	Time:		2020-08-31 20:40
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>

#define int long long
inline void chkmax(int &x, int y) {if (x < y) x = y;}
inline void chkmin(int &x, int y) {if (x > y) x = y;}
using namespace std;
const int maxn = 50 + 5, maxm = 500 + 5, maxN = 250 + 5, maxk = 200 + 5, inf = 1e15;

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

struct matrix
{
	int a[maxN][maxN];
	matrix()
	{
		REP(i, 0, maxN - 1) REP(j, 0, maxN - 1) a[i][j] = -inf;
	}
	inline int* operator [] (int x) {return a[x];}
}dp, C, tmp, I, Ans, bin[40];
int N;

bool faster;
inline matrix operator * (matrix a, matrix b)
{
	REP(i, 1, N) REP(j, 1, N) tmp[i][j] = -inf;
	REP(i, 1, faster ? 1 : N) REP(k, 1, N) if (a[i][k] > -inf / 2)
		REP(j, 1, N) chkmax(tmp[i][j], a[i][k] + b[k][j]);
	return tmp;
}
void Mul(matrix &res, int b)
{
	for (int c = 0; b; b >>= 1, c++) if (b & 1)
		res = res * bin[c];
}

int n, m, k, T;

int c[maxn];
int u[maxm], v[maxm], w[maxm];

struct lbhlbh
{
	int t, x, y;
	inline bool operator < (const lbhlbh &B) const {return t < B.t;}
}s[maxk];

inline void add(int x, int y) {C[x][y] = (y <= n ? c[y] : 0);}
namespace FUCK_EDGE
{
	int id[maxn][10];
	void work()
	{
		N = n;
		REP(i, 1, n) id[i][0] = i;
		REP(i, 1, m)
		{
			int Last = u[i];
			REP(j, 1, w[i] - 1)
			{
				int &New = id[u[i]][j];
				if (!New) New = ++N;
				add(Last, New);
				Last = New;
			}
			add(Last, v[i]);
		}
		cerr << N << endl;
		bin[0] = C;
		REP(i, 1, 30) bin[i] = bin[i - 1] * bin[i - 1];
		faster = 1;
		Ans[1][1] = 0;
		int NowTime = 0;
		++k;
		s[k].t = T;
		s[k].x = s[k].y = 0;
		REP(i, 1, k)
		{
			if (NowTime < s[i].t)
			{
				Mul(Ans, s[i].t - NowTime);
				NowTime = s[i].t;
			}
			Ans[1][s[i].x] += s[i].y;
			if (i % 10 == 0) fprintf(stderr, "Done %d / %d = %.2lf%%\n", i, k, i * 100. / k);
		}
		
		int ans = Ans[1][1] + c[1];
		printf("%lld\n", ans > -inf / 2 ? ans : -1);
	}
}

signed main()
{
#ifdef CraZYali
	file("6772");
#endif
	REP(i, 0, maxN - 1) I[i][i] = 0;
	cin >> n >> m >> T >> k;
	REP(i, 1, n) c[i] = read<int>();
	REP(i, 1, m)
	{
		u[i] = read<int>();
		v[i] = read<int>();
		w[i] = read<int>();
	}
	REP(i, 1, k)
	{
		s[i].t = read<int>();
		s[i].x = read<int>();
		s[i].y = read<int>();
	}
	sort(s + 1, s + 1 + k);
	FUCK_EDGE :: work();
	return 0;
}
