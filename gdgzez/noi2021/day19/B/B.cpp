#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e6 + 10;

int n, k;
bool a[maxn], b[maxn];

int fa[maxn];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}

int que[maxn << 1];

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> k;
	REP(i, 1, n)
	{
		char c = getchar();
		while (!isdigit(c)) c = getchar();
		a[i] = c - 48;
	}
	REP(i, 1, n) fa[i] = i;

	int c = 0, head = 1, tail = k;
	REP(i, 1, n)
	{
		if (!a[i])
		{
			int t = find(tail);
			if (t >= head)
			{
				c++;
				que[t] = 1;
				fa[t] = t - 1;
			}
		}
		else
		{
			b[i - c] = 1;
			if (que[head]) c--;
			head++;tail++;
		}
	}
	REP(i, 1, n) putchar(b[i] + 48), putchar(' ');
	return 0;
}
