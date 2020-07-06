#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#define i64 long long
using namespace std;
const int maxn = 2e6 + 10;

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

int m, n;
#define getchar nc
inline char nc(){
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
#define mid (l + r >> 1)
#define lson l, mid
#define rson mid + 1, r
int t[maxn], x[maxn], y[maxn], N, tt[2][maxn];
struct fenwick
{
	i64 s[maxn];
	fenwick() {memset(s, 0, sizeof s);}
	void insert(int x, int y)
	{
		while (x <= N)
		{
			s[x] += y;
			x += x & -x;
		}
	}
	i64 sum(int x)
	{
		i64 y = 0;
		while (x > 0)
		{
			y += s[x];
			x &= (x - 1);
		}
		return y;
	}
	i64 sum(int l, int r)
	{
		l--;
		i64 res = 0;
		while (r > l) res += s[r], r &= (r - 1);
		while (l > r) res -= s[l], l &= (l - 1);
		return res;
	}
}T[2];
inline i64 min(i64 x, i64 y) {if (x < y) return x;return y;}
inline bool chkmax(i64 &x, i64 y)
{
	if (x <= y) {x = y;return 1;}
	return 0;
}
inline bool chkmax(int &x, int y)
{
	if (x <= y) {x = y;return 1;}
	return 0;
}
i64 ans = 0, tot;
int pos;
void query(int l, int r)
{
	i64 al = T[0].sum(1, mid);//a - T[0][rs];//T[0].sum(1 -> mid)
	i64 bl = tot - T[1].sum(mid - 1);
	chkmax(ans, min(al, bl));
	if (l == r) return;
	if (al > bl) query(lson);
	else query(rson);
}
void Query(int l, int r)
{
	i64 al = T[0].sum(1, mid);//a - T[0][rs];//T[0].sum(1 -> mid)
	i64 bl = tot - T[1].sum(mid - 1);
	if (ans == min(al, bl)) chkmax(pos, mid);
	if (l == r) return;
	if (al > bl && ans != min(al, bl)) Query(lson);
	else Query(rson);
}
int b[maxn], opt[maxn], k[maxn];
int Bound(int x)
{
	int l = 1, r = N;
	while (l <= r)
		if (b[mid] == x) return mid;
		else if (b[mid] < x) l = mid + 1;
		else r = mid - 1;
}
void write(i64 x)
{
	if (x / 10) write(x / 10);
	putchar(x % 10 + 48);
}
int main()
{
#ifdef CraZYali
	file("6619");
#endif
	register int Q = read<int>();
	N = 0;
	REP(i, 1, Q)
	{
		opt[i] = read<int>();
		if (opt[i] == 1)
		{
			t[i] = read<int>();
			x[i] = read<int>();
			y[i] = read<int>();
			b[++N] = x[i];
		}
		else k[i] = read<int>();
	}
	sort(b + 1, b + 1 + N);
	N = unique(b + 1, b + 1 + N) - b - 1;
	REP(i, 1, Q)
	{
		if (opt[i] == 1)
		{
			x[i] = Bound(x[i]);
			T[t[i]].insert(x[i], y[i]);
			if (t[i] == 1) tot += y[i];
		}
		else
		{
			int k = ::k[i];
			T[t[k]].insert(x[k], -y[k]);
			if (t[k] == 1) tot -= y[k];
		}
		ans = pos = 0;
		query(1, N);
		if (ans)
		{
			Query(1, N);
			write(b[pos]);putchar(' ');
			write(ans << 1);putchar('\n');
		}
		else puts("Peace");
	}
	return 0;
}
