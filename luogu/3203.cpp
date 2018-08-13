#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}
const int maxn = 200000 + 10;

int n, m;

int k[maxn];

int belong[maxn], S[maxn], T[maxn], block_siz, block_cnt;
void divide()
{
	block_siz = sqrt(n);
	int l = 1, r = block_siz;
	while (r <= n)
	{
		++block_cnt;
		S[block_cnt] = l;T[block_cnt] = r;
		REP(i, l, r) belong[i] = block_cnt;
		l = r + 1;
		r += block_siz;
	}
	if (l <= n)
	{
		block_cnt++;
		S[block_cnt] = l;T[block_cnt] = n;
		REP(i, l, n) belong[i] = block_cnt;
	}
}

int jumpto[maxn], jumpoutcnt[maxn];

void pre(int block_id)
{
	DREP(i, T[block_id], S[block_id])
		if (i + k[i] > T[block_id])
		{
			jumpto[i] = i + k[i] > n ? -1 : i + k[i];
			jumpoutcnt[i] = 1;
		}
		else
		{
			jumpto[i] = jumpto[i + k[i]];
			jumpoutcnt[i] = jumpoutcnt[i + k[i]] + 1;
		}
}

inline int calc(int x)
{
	int ans = 0;
	while (x != -1)
	{
		ans += jumpoutcnt[x];
		x = jumpto[x];
	}
	return ans;
}

int main()
{
#ifdef CraZYali
	freopen("3203.in", "r", stdin);
	freopen("3203.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d", k + i);
	divide();
	REP(i, 1, block_cnt) pre(i);

	cin >> m;
	while (m --> 0)
	{
		register int opt, x, y;
		scanf("%d%d", &opt, &x);
		if (opt == 1) printf("%d\n", calc(x + 1));
		else
		{
			scanf("%d", &y);
			k[x + 1] = y;
			pre(belong[x + 1]);
		}
	}

	return 0;
}

