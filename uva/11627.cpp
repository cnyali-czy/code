#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10, maxS = 1e6 + 10; 
template <typename T> inline T read()
{
	register T ans(0), p(1);
	register char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, S, W, vh;
int x1[maxn], x2[maxn], y[maxn], s[maxS];

inline bool judge(int v)
{
	double nL(x1[1]), nR(x2[1]);
	REP(i, 1, n - 1)
	{
		if (nL > nR) return 0;
		double tim = (y[i + 1] - y[i]) * 1.0 / v;
		double L = nL - tim * vh;
		double R = nR + tim * vh;
	//	fprintf(stderr, "%.2lf %.2lf %d.00 %d.00 in %d\n", L, R, x1[i + 1], x2[i + 1], I);
		if (R < x1[i + 1]) return 0;
		else
		{
			nL = max((double)x1[i + 1], L);
			nR = min((double)x2[i + 1], R);
		} }
	return 1;
}

int main()
{
#ifdef CraZYali
	freopen("11627.in", "r", stdin);
	freopen("11627.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T--)
	{
		W = read<int>();
		vh = read<int>();
		n = read<int>();
		REP(i, 1, n)
		{
			x2[i] = (x1[i] = read<int>()) + W;
			y[i] = read<int>();
		}
		S = read<int>();
		REP(i, 1, S) s[i] = read<int>();
		sort(s + 1, s + 1 + S);
		
		int ans = -1, L(1), R(S);

		while (L <= R)
		{
			int mid = L + R >> 1;
			if (judge(s[mid]))
			{
				ans = s[mid];
				L = mid + 1;
			}
			else R = mid - 1;
		}
		if (ans != -1) printf("%d\n", ans);
		else printf("IMPOSSIBLE\n");
	}

	return 0;
}
