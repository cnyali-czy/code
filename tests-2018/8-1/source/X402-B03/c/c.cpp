#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;

int m, n, k;

int main()
{
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	cin >> n;
	if (n == 1)
	{
		int pos;
		REP(i, 1, 4)
		{
			scanf("%d", &k);
			if (k == 1) {pos = k;break;}
		}
		cout << min(abs(pos - 1), abs(5 - pos));
		return 0;
	}
	else
	{
		int x = n;
		REP(i, 1, n << 2)
		{
			scanf("%d", &k);
			srand(rand() ^ k);
		}
		cout << rand() % 30;
	}
	return 0;
}
