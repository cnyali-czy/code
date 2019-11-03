#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#include <map>

using namespace std;
const int maxn = 1e5 + 10;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, c, k;
long long a[maxn];

map <long long, int> qaq;

int fa[maxn], siz[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
inline void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (x == y) return;
	fa[x] = y;
	siz[y] += siz[x];
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> c >> k;
	REP(i, 1, n) siz[fa[i] = i] = 1;
	qaq[0] = 1;
	REP(i, 2, n) qaq[a[i] = read<long long>() * k] = i;
	REP(i, 1, n)
		if (qaq.count(a[i] + c)) uni(i, qaq[a[i] + c]);
	REP(i, 1, n) if (i == fa[i] && siz[i] == k)
	{
		cout << "Yes\n";
		return 0;
	}
	cout << "No\n";
	return 0;
}
