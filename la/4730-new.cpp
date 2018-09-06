#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10, maxrange = 1e6 + 10;

int m, n, k;

int f[maxn];
int find(int x) {return f[x] == x ? f[x] : f[x] = find(f[x]);}

int up[maxn], down[maxn], siz[maxn];

int Max;

struct fenwick_tree
{
	int bit[maxrange << 1];
	void clear() {REP(i, 1, Max) bit[i] = 0;}
	void add(int x, int y)
	{
		x++;
		while (x <= Max)
		{
			bit[x] += y;
			x += x & -x;
		}
	}

	int sum(int x)
	{
		x++;
		int ret = 0;
		while (x > 1)
		{
			ret += bit[x];
			x -= x & -x;
		}
		return ret;
	}
}T1, T2;
char s[10];

int main()
{
#ifdef CraZYali
	freopen("4730-new.in", "r", stdin);
	freopen("4730-new.out", "w", stdout);
#endif
	register int T;
	cin >> T;
	while (T --> 0)
	{
		scanf("%d", &n);
		Max = 0;
		REP(i, 1, n)
		{
			f[i] = i;
			register int y;
			scanf("%*d%d", &y);
			up[i] = down[i] = y << 1;
			chkmax(Max, (y << 1));
		}
	
		Max += 5;

		T1.clear();T2.clear();
		REP(i, 1, n)
		{
			siz[i] = 1;
			T1.add(down[i], 1);
			T1.add(up[i] + 1, -1);
			T2.add(down[i], 1);
			T2.add(up[i] + 1, -1);
		}

		scanf("%d", &m);
		while (m --> 0)
		{
			scanf("%s", s);
			if (s[0] == 'r')
			{
				register int a, b;
				scanf("%d%d", &a, &b);
				a++;b++;
				if ((a = find(a)) ^ (b = find(b)))
				{
					register int uup = max(up[a], up[b]);
					register int ddown = min(down[a], down[b]);
					T1.add(down[a], -1);
					T1.add(up[a] + 1, 1);
					
					T2.add(down[a], -siz[a]);
					T2.add(up[a] + 1, siz[a]);

					T1.add(down[b], -1);
					T1.add(up[b] + 1, 1);

					T2.add(down[b], -siz[b]);
					T2.add(up[b] + 1, siz[b]);
					
					f[a] = b;
					siz[b] += siz[a];
					T1.add(ddown, 1);
					T1.add(uup + 1, -1);
					T2.add(ddown, siz[b]);
					T2.add(uup + 1, -siz[b]);
					up[b] = uup;
					down[b] = ddown;
				}
			}
			else
			{
				register int y;
				scanf("%d.5", &y);
				y = y << 1 | 1;
				printf("%d %d\n", T1.sum(y), T2.sum(y));
				fflush(stdout);
			}
		}
	}
	return 0;
}
