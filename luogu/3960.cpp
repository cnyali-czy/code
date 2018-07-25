#define  REP(i, s, e) for (register int i = s; i <= e ; i++)
#define DREP(i, s, e) for (register int i = s; i >= e ; i--)

#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
const int maxn = 3e5 + 10;

#define LL long long
#define info pair<LL, LL>

int n, m, q;

struct Treap
{
	int rt[maxn];
	struct node
	{
		LL l, r;
		int s, order, ls, rs;
		inline void set(LL _l, LL _r) {l = _l;r = _r;ls = rs = 0; order = rand();}
	} t[maxn * 10];
	
	int t_cnt;

	inline void maintain(int x) {t[x].s = t[t[x].ls].s + t[t[x].rs].s + len(x);}

	inline int newnode() {return ++t_cnt;}

	inline int len(int x) {return t[x].r ? t[x].r - t[x].l + 1 : 0; }

	inline int merge(int x, int y)
	{
		if (!(x * y))
		{
			if (!x) maintain(y);
			else maintain(x);
			return x + y;
		}
		
		if (t[x].order >= t[y].order)
		{
			t[x].rs = merge(t[x].rs, y);
			maintain(x);
			return x;
		}
		else
		{
			t[y].ls = merge(x, t[y].ls);
			maintain(y);
			return y;
		}
	}
	inline info split(int x, int siz)
	{
		if (!siz) return make_pair(0, x);	
		else if(siz >= t[t[x].ls].s + len(x))
		{
			register info temp = split(t[x].rs, siz - t[t[x].ls].s - len(x));
			t[x].rs = temp.first;
			maintain(x);
			return make_pair(x, temp.second);
		}
		else if (siz <= t[t[x].ls].s)
		{
			register info temp = split(t[x].ls, siz);
			t[x].ls = temp.second;
			maintain(x);
			return make_pair(temp.first, x);
		}
		else
		{
			register int y = newnode();
			t[y].set(t[x].l + siz - t[t[x].ls].s, t[x].r);
			t[x].r = t[y].l - 1;
			y = merge(y, t[x].rs);
			t[x].rs = 0;
			maintain(x);
			return make_pair(x, y);
		}
	}

	inline void init()
	{
		REP(i, 1, n) t[(rt[i] = newnode())].set(1ll * (i - 1) * m + 1, 1ll * i * m - 1);

		t[(rt[0] = newnode())].set(m, m);

		REP(i, 2, n)
		{
			register int x = newnode();
			t[x].set(1ll * i * m, 1ll * i * m);
			rt[0] = merge(rt[0], x);
		}
	}
	inline void solve(int a, int b)
	{
		register info t1, t2;
		if(b ^ m)
		{
			t1 = split(rt[a], b - 1);
			t2 = split(t1.second, 1);
			rt[a] = merge(t1.first, t2.second);
		}
		register int pos;
		if(b ^ m) pos = t2.first;

		t1 = split(rt[0], a - 1);
		t2 = split(t1.second, 1);
		
		if(b ^ m) rt[a] = merge(rt[a], t2.first);

		rt[0] = merge(t1.first, t2.second);
		if(b == m) pos = t2.first;
		rt[0] = merge(rt[0], pos);
		printf("%lld\n", t[pos].l);
	}
} t;

int main()
{
#ifdef CraZYali
	freopen("3960.in", "r", stdin);
	freopen("3960.out", "w", stdout);
#endif
	cin >> n >> m >> q;
	t.init();
	while (q --> 0)
	{
		register int x, y;
		scanf("%d%d", &x, &y);
		t.solve(x, y);
	}
	return 0;
}
