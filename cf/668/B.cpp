#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1e6 + 10;
int blg[maxn];

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	int a(0), b(1);
	int n, q;
	cin >> n >> q;
	while (q--)
	{
		int opt;
		scanf("%d", &opt);
		if (opt == 2)
		{
			if (b & 1) (b += n - 1) %= n;
			else (b += 1) %= n;
			if (a & 1) (a += n - 1) %= n;
			else (a += 1) %= n;
		}
		else
		{
			int x;
			scanf("%d", &x);
			x %= n;
			(a += n + x) %= n;
			(b += n + x) %= n;
		}
	}
	memset(blg, -1, sizeof blg);
	int qaq = 1;
	while (blg[a] == -1)
	{
		blg[a] = qaq;
		(a += 2) %= n;
		qaq += 2;
	}
	qaq = 2;
	while (blg[b] == -1)
	{
		blg[b] = qaq;
		qaq += 2;
		(b += 2) %= n;
	}
	REP(i, 0, n - 1)
		printf("%d%c", blg[i], i == end_i ? '\n' : ' ');
	return 0;
}
