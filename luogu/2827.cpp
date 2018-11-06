#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5 + 10, maxm = 7e6 + 10, inf = 1ll << 60ll;

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar(); }
	return ans * p;
}
template <typename T> void write(T x)
{
	if (!x) return;
	write(x / 10);
	putchar(x % 10 + '0');
}

int V[maxn + maxm];

int a[maxn];
int c[2][maxm];

inline bool cmp(int A, int B) {return A > B;}


int n, m, q, k, t, u, v;

int picked[2], A, B, AAA, Max, pick[2], pick1, sig;

signed main()
{
#ifdef CraZYali
	freopen("2827.in", "r", stdin);
	freopen("2827.out", "w", stdout);
#endif
	cin >> n >> m >> q >> u >> v >> t;
	REP(i, 1, n) a[i] = read<int>();
	sort(a + 1, a + 1 + n, cmp);
	register double p = u * 1.0 / v;

	pick[0] = pick[1] = pick1 = 1;
	REP(M, 1, m)
	{
		if (pick1 > n)
			if (c[0][pick[0]] < c[1][pick[1]]) Max = c[1][pick[1]++];
			else Max = c[0][pick[0]++];
		else if (a[pick1] >= max(c[0][pick[0]], c[1][pick[1]])) Max = a[pick1++];
		else if (c[0][pick[0]] >= max(a[pick1], c[1][pick[1]])) Max = c[0][pick[0]++];
		else Max = c[1][pick[1]++];
		Max += sig;
		sig += q;
		A = Max * p;
		B = Max - A;
		c[0][M] = A - sig;
		c[1][M] = B - sig;
		if (M % t == 0) write(Max), putchar(' ');
	}
	putchar(10);
	register int v_cnt(0), cnt(t);
	REP(i, pick1, n) V[++v_cnt] = a[i];
	REP(i, 0, 1)
		REP(j, pick[i], m) V[++v_cnt] = c[i][j];
	sort(V + 1, V + 1 + n + m, cmp);
	while (cnt <= n + m) write(V[cnt]+ sig), putchar(' '), cnt += t;
	return 0;
}
