#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 20000 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	w[e] = z;
	bg[x] = e; } template <typename T> T read()
{
	T ans = 0, p = 1;
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
int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

int n;

bool vis[maxn];
int siz[maxn], Max[maxn], rt, allnode;
void findrt(int x, int fa = -1)
{
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !vis[to[i]])
		{
			findrt(to[i], x);
			siz[x] += siz[to[i]];
			chkmax(Max[x], siz[to[i]]);
		}
	chkmax(Max[x], allnode - Max[x]);
	if (Max[x] <= Max[rt]) rt = x;
}

int ans, cnt[3], depth[maxn];

void getdeep(int x, int fa = -1)
{
	cnt[depth[x]]++;
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !vis[to[i]])
		{
			depth[to[i]] = (depth[x] + w[i]) % 3;
			getdeep(to[i], x);
		}
}

int calc(int x, int now)
{
	cnt[0] = cnt[1] = cnt[2] = 0;
	depth[x] = now;
	getdeep(x);
	return cnt[1] * cnt[2] * 2 + cnt[0] * cnt[0];
}

void solve(int x)
{
	ans += calc(x, 0);
	vis[x] = 1;
	for (int i = bg[x]; i ; i = ne[i])
		if (!vis[to[i]])
		{
			ans -= calc(to[i], w[i]);
			allnode = siz[to[i]];
			rt = 0;
			findrt(to[i]);
			solve(rt);
		}
}

int main()
{
#ifdef CraZYali
	freopen("2634-new.in", "r", stdin);
	freopen("2634-new.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), z(read<int>() % 3);
		add(x, y, z);add(y, x, z);
	}
	allnode = Max[rt] = n;
	findrt(1);
	solve(rt);
	printf("%d/%d", ans / gcd(ans, n * n), n * n / gcd(ans, n * n));
	return 0;
}
