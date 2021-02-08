#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <cmath>
#include <iostream>
#include <cstdio>
#define i64 long long
#define unt unsigned int

using namespace std;
const int maxP = 8e4, maxn = 1e6 + 10;

int n, q;
inline char nc()
{
	static char buf[100000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline unt read()
{
	char c = nc();
	while (!isdigit(c)) c = nc();
	unt res = 0;
	while (isdigit(c)) res = res * 10 + (c - 48), c = nc();
	return res;
}
unt f[maxn];

int prime[maxn], p_cnt, id[maxn], End[maxn];
bool notp[maxn];

void init(int n)
{
	REP(i, 2, n)
	{
		if (!notp[i]) prime[++p_cnt] = i, id[i] = p_cnt;
		REP(j, 1, p_cnt)
		{
			int t = i * prime[j];if (t > n) break;
			notp[t] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	int k = 0;
	REP(i, 1, n)
	{
		while (k < p_cnt && prime[k + 1] <= i) k++;
		End[i] = k;
	}
}

namespace Block
{
	int blg[maxP], R[maxn], tot;
	unt s1[maxP], s2[maxP];
	void init()
	{
		const int block = sqrt(p_cnt + .5);
		REP(i, 1, p_cnt) R[blg[i] = (i - 1) / block + 1] = i;
		tot = blg[p_cnt];
	}
	inline void add(int x, unt y)
	{
		REP(i, blg[x], tot) s1[i] += y;
		REP(i, x, R[blg[x]]) s2[i] += y;
	}
	inline unt sum(int x)
	{
		if (!x) return 0;
		return s2[x] + s1[blg[x] - 1];
	}
	inline unt sum(int l, int r)
	{
		return sum(r) - sum(l - 1);
	}
}

unt ARD[maxP];
inline unt g(int n, int x, unt ard)
{
	if (prime[x] > n) return 0;
	unt ans = 0;
	if (End[n] > x) ans += ARD[End[n]] + Block :: sum(End[n]) - ard;//ard = sum(x)
	REP(j, x + 1, p_cnt)
	{
		const i64 p = prime[j];if (p * p > n) break;
		ard += f[prime[j]];
		for (i64 e = 1, pe = p; pe <= n; pe *= p, e++)
		{
			const int PE = pe;
			ans += f[pe] * (g(n / PE, j, ard) + (e != 1));
		}
	}
	return ans;
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	n = read();q = read();
	init(n);
	REP(i, 1, n) f[i] = read();
	REP(i, 1, n) if (id[i]) ARD[id[i]] += f[i];//Block :: add(id[i], f[i]);
	REP(i, 1, p_cnt) ARD[i] += ARD[i - 1];
	Block :: init();
	REP(Case, 1, q)
	{
		if (read() == 1)
		{
			unt a = read(), b = read();
			if (a > n) continue;
			if (id[a]) Block :: add(id[a], b - f[a]);
			f[a] = b;
		}
		else printf("%u\n", g(read(), 0, 0) + 1);
		if (Case % 1000 == 0) fprintf(stderr, "Done %d / %d = %.2lf%%\n", Case, q, Case * 100. / q);
	}
	return 0;
}
