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
const int maxn = 200000 + 10;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, size;
int k[maxn];

int belong[maxn], Left[500], Right[500], block = 1;

inline void get_belong()
{
	size = sqrt(n);
	register int i;
	for (i = 1; i + size - 1 <= n ; i += size, block++)
	{
		REP(j, i, i + size - 1) belong[j] = block;
		Left[block] = i;Right[block] = i + size - 1;
	}
	if (i <= n)
	{
		Left[block] = i;Right[block] = n;
		while (i <= n) belong[i++] = block;
	}
}

int step[maxn], nxt[maxn];
bool first = 1;

inline void calc(int id)
{
	DREP(i, Right[id], Left[id])
		if (i + k[i] > Right[id])
		{
			nxt[i] = i + k[i] > n ? -1 : i + k[i];
			step[i] = 1;
		}
		else
		{
			nxt[i] = nxt[i + k[i]];
			step[i] = step[i + k[i]] + 1;
		}
}

#ifdef CraZYali
inline void SLEEP(double tim)
{
	tim *= CLOCKS_PER_SEC;
	double now = clock();
	while (clock() - now < tim);
}
#endif

inline void answer(int x)
{
	int ans = 0;
	do
	{
		ans += step[x];
		x = nxt[x];
	}while (x != -1);
	printf("%d\n", ans);
	fflush(stdout);
}

inline void update(int x, int y)
{
	k[x] = y;
	calc(belong[x]);
}

int main()
{
#ifdef CraZYali
	freopen("3203.in", "r", stdin);
	freopen("3203.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 1, n) k[i] = read<int>();
	get_belong();
	REP(i, 1, block) calc(i);

	m = read<int>();
	while (m --> 0)
	{
		int opt = read<int>();
		if (opt == 1) answer(read<int>() + 1);
		else
		{
			register int x(read<int>() + 1), y(read<int>());
			update(x, y);
		}
	}
	return 0;
}
