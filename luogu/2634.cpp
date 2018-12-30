#define REP(i, s, e) for(register int i = s; i <= e ; i++)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 20000 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

int allnode, n, k, rt, ans;
int son[maxn], Max[maxn];
bool vis[maxn];

void find(int x, int fa = -1)
{
	son[x] = 1;
	Max[x] = 0;
	for (register int i = bg[x]; i ; i = ne[i])
		if (!vis[to[i]] && to[i] != fa)
		{
			find(to[i], x);
			son[x] += son[to[i]];
			chkmax(Max[x], son[to[i]]);
		}
	chkmax(Max[x], allnode - Max[x]);
	if (Max[x] <= Max[rt]) rt = x;
}

short deep[maxn];int cnt[3];
void getdeep(int x, int fa = -1)
{
	cnt[deep[x]]++;
	for (register int i = bg[x] ; i ; i = ne[i])
		if (!vis[to[i]] && to[i] != fa)
		{
			deep[to[i]] = (deep[x] + w[i]) % 3;
			getdeep(to[i], x);
		}
}

int cal(int x, int now)
{
	cnt[0] = cnt[1] = cnt[2] = 0;
	deep[x] = now;getdeep(x);
	return cnt[1] * cnt[2] * 2 + cnt[0] * cnt[0];
}

void solve(int x)
{
	ans += cal(x, 0);
	vis[x] = 1;
	for (register int i = bg[x]; i ; i = ne[i])
		if (!vis[to[i]])
		{
			ans -= cal(to[i], w[i]);
			allnode = son[to[i]];
			rt = 0;find(to[i]);
			solve(to[i]);
		}
}

int main()
{
#ifdef CraZYali
	freopen("2634.in", "r", stdin);
	freopen("2634.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 2, n)
	{
		register int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z % 3);add(y, x, z % 3);
	}
	allnode = Max[0] = n;
	find(1);
	solve(rt);
	cout << ans / gcd(ans, n * n) << '/' << n * n / gcd(ans, n * n);
	return 0;
}
