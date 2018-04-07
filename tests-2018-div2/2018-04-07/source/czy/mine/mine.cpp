#define REP(i, s, e) for(register int i = s ; i <= e ; i++)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100 + 5, maxm = 100 + 5, maxs = 20 + 5;

int m, n, s, k;
int sta[maxn][maxm][maxs];

inline void put(int x)
{
	if (!x) putchar('0');
	else if (x == -1) putchar('*');
	else putchar(x - 1 + 'a');
}

int main()
{
	freopen("mine.in", "r", stdin);
	freopen("mine.out", "w", stdout);
	cin >> n >> m >> s >> k;
	while (k --> 0)
	{
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		if (sta[x][y][z] == -1) continue;
		sta[x][y][z] = -1;
		REP(i, x - 1, x + 1)
			REP(j, y - 1, y + 1)
				REP(k, z - 1, z + 1)
					if (sta[i][j][k] != -1)
						sta[i][j][k]++;
	}
	REP(k, 1, s)
		REP(i, 1, n)
		{
			REP(j, 1, m)
				put(sta[i][j][k]);
			putchar(10);
		}
	return 0;
}
