#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const long long maxn = 1e5 + 10, maxm = 7e6 + 10, inf = 1ll << 60ll;

long long V[maxn + maxm];

long long a[maxn];
long long c[2][maxm];

inline bool cmp(long long A, long long B) {return A > B;}

inline long long read()
{
	register long long temp = 0;
	register char c = getchar_unlocked();
	while (!isdigit(c)) c = getchar_unlocked();
	while (isdigit(c))
	{
		temp = temp * 10 + c - '0';
		c = getchar_unlocked();
	}
	return temp;
}

void write(long long x)
{
	if (!x) return;
	write(x / 10);
	putchar(x % 10 + '0');
}

int main()
{
#ifdef CraZYali
	freopen("2827.in", "r", stdin);
	freopen("2827.out", "w", stdout);
#endif
	register long long m, n, q, t, k, u, v;
	n = read();
	m = read();
	q = read();
	u = read();
	v = read();
	t = read();
	REP(i, 1, n) a[i] = read();
	sort(a + 1, a + 1 + n, cmp);

	register double p = u * 1.0 / v;

	register long long picked[2], A, B, AAA, Max, pick[2], pick1, sig = 0;

	pick[0] = pick[1] = pick1 = 1;
	REP(M, 1, m)
	{
		if (pick1 > n)
			if (c[0][pick[0]] < c[1][pick[1]]) Max = c[1][pick[1]++];
			else Max = c[0][pick[0]++];
		else if (a[pick1] >= max(c[0][pick[0]], c[1][pick[1]])) Max = a[pick1++];
		else if (c[0][pick[0]] >= max(a[pick1], c[1][pick[1]])) Max = c[0][pick[0]++];
		else Max = c[1][pick[1]++];
		/*
		AAA = picked[0] = picked[1] = -inf;
		if (pick1 <= n) AAA = a[pick1];
		picked[0] = c[0][pick[0]];
		picked[1] = c[1][pick[1]];

		Max = max(AAA, max(picked[0], picked[1]));
		if (pick1 <= n && Max == AAA) pick1++;
		else if (picked[0] == Max) pick[0]++;
		else pick[1]++;
		*/
		Max += sig;
		sig += q;

		A = Max * p;
		B = Max - A;
		
		c[0][M] = A - sig;
		c[1][M] = B - sig;
		if (M % t == 0) write(Max), putchar(' ');
	}
	putchar(10);
	register long long v_cnt(0), cnt(t);
	REP(i, pick1, n) V[++v_cnt] = a[i];
	REP(i, 0, 1)
		REP(j, pick[i], m) V[++v_cnt] = c[i][j];
	sort(V + 1, V + 1 + n + m, cmp);
	while (cnt <= n + m) write(V[cnt]+ sig), putchar(' '), cnt += t;
	return 0;
}
