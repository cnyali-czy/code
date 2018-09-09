#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 23, maxnode = 1 << maxn;

int m, n, k, LIM;

bool t[maxnode];
void add(int x)
{
	while (x <= LIM)
	{
		t[x] ^= 1;
		x += x & -x;
	}
}
bool get(int x)
{
	bool now = 0;
	while (x > 0)
	{
		now ^= t[x];
		x -= x & -x;
	}
	return now;
}

#define getchar getchar_unlocked

template <typename T> T read()
{
	register char c = getchar();
	T ans(0), p = 1;
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - '0';
		c = getchar();
	}
	return ans * p;
}

int L(int x, int floor)
{
	if (floor == n + 1) return x;
	return L(x << 1, floor + 1);
}

int R(int x, int floor)
{
	if (floor == n + 1) return x;
	return R(x << 1 | 1, floor + 1);
}

int l[maxnode], r[maxnode];
int idof[maxnode];

int main()
{
#ifdef CraZYali
	freopen("bst.in", "r", stdin);
	freopen("bst.out", "w", stdout);
#endif
	cin >> n >> m;
	LIM = (1 << n + 1) - 1;
	REP(i, 1, LIM) idof[i] = i;
	int ret = 1 << n;ret--;
	REP(i, 1, ret) l[i] = i << 1, r[i] = i << 1 | 1;
	while (m --> 0)
	{
		register int opt = read<int>();
		if (opt == 1)
		{
			register int x = read<int>(), y = read<int>();
			
		}
		else
		{
			register int fi = read<int>();
			fi += (1 << n) -1;
			register int x = 1, floor = 1, id = 1;
			while (floor <= n)
			{
				if (L(x << 1, floor + 1) <= fi && fi <= R(x << 1, floor + 1)) x <<= 1, id = l[id];
				else x = x << 1 | 1, id = r[id];
				floor++;
			}
			printf("%d\n", id - (1 << n) + 1);
		}
	}
	return 0;
}

