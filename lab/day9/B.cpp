#define REP(i, s, e) for (int i = s ; i <= e ; i++)

#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 100000 + 10, maxB = 30000 + 10, maxW = 30000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int n, B, W;
int bx[maxB], by[maxB], bv[maxB], wx[maxW], wy[maxW], wv[maxW];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> B >> W;
	REP(i, 2, n)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);add(y, x);
	}
	return 0;
}
