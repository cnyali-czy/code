#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define i64 long long
#define unt unsigned int

using namespace std;
const int maxP = 8e4;

int n, q;
unt read()
{
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	unt res = 0;
	while (isdigit(c)) res = res * 10 + (c - 48), c = getchar();
	return res;
}
unt f[maxn];

int prime[maxn], p_cnt;
int H[maxP][21];

void init(int n)
{
	REP(i, 2, n)
	{
		if (!notp[i]) prime[++p_cnt] = i;
		REP(j, 1, p_cnt)
		{
			int t = i * prime[j];if (t > n) break;
			notp[t] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}
void fix(int N)
{
	H[N][0] = 1;
	for (i64 p = prime[N], pk = p * p, k = 2; pk <= n; pk *= p, k++)
	{
	}
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> q;
	REP(i, 1, n) f[i] = read();
	init(n);
	REP(i, 1, p_cnt) fix(i);
	return 0;
}
