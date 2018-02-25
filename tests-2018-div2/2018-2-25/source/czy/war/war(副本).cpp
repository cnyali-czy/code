#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 30010;

template <typename T> T read()
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

int m, n, k;
int h[maxn], b[maxn];
const int inf = 1e9;
inline bool cmp(int a, int b) {return a > b;}

int main()
{
	freopen("war.in", "r", stdin);
	freopen("war.out", "w", stdout);
	n = read<int>();int rn = n;
	REP(i, 1, n) h[i] = read<int>();
	m = read<int>();
	while (m--)
	{
		register char c = getchar();
		while (c ^ 'Q' && c ^ 'A' && c ^ 'C') c = getchar();
		if (c == 'A')
		{
			int i, a;
			scanf("%d%d\n", &i, &a);
			h[i] -= a;
			if (h[i] <= 0)
			{
				h[i] = -inf;
				n--;
			}
		}
		else if (c == 'C')
		{
			int i, a;
			scanf("%d%d\n", &i, &a);
			h[i] += a;
		}
		else
		{
			scanf("%d\n", &k);
			if (n >= k)
			{
				REP(i, 1, rn) b[i] = h[i];
				sort(b + 1, b + 1 + rn, cmp);
				printf("%d\n", b[k]);
			}
			else printf("-1\n");
		}
	}
	cout << n;
	
	return 0;
}

