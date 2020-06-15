/*
	Problem:	A.cpp
	Time:		2020-06-15 10:41
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 50000 + 5 << 1, MOD = 998244353;

template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn], k;
int lst[maxn], cnt[maxn];
i64 ans;
pair <int, int> ccc[maxn];
int ok[maxn];
inline int to(int x)
{
	if (x > n) return x - n;
	else return x + n;
}
const unsigned i64 base = 1e9 + 7, bb = 1e9 + 9;
unordered_map <unsigned i64, bool> vis;
void find(int x)
{
	if (!ok[x]) return;
	ok[x] = 0;
	k++;
	find(x == n + n ? 1 : x + 1);
	find(x == 1 ? n + n : x - 1);
}
void calc()
{
	REP(i, 1, n + n) if (i != lst[a[i]])
		ccc[a[i]] = make_pair(lst[a[i]], i);
	sort(ccc + 1, ccc + 1 + n);
	unsigned i64 H = 0;
	REP(i, 1, n) 
		H = H * base + ccc[i].first * bb + ccc[i].second;
	if (vis[H]) return;
	vis[H] = 1;
	REP(i, 1, n + n) ok[i] = 0;
	bool shit = 0;
	REP(i, 1, n + n) if (a[i] == a[to(i)]) ok[i] = ok[to(i)] = -1, shit = 1;
	if (!shit) return;
//	REP(i, 1, n + n) cout << ok[i] << ' ';cout << endl;
	REP(i, 1, n + n) if (ok[i] == -1)
	{
		k = 0;
		find(i);
		if (k > 1) return;
	}
	REP(i, 1, n + n) ok[i] = 1;
	REP(i, 1, n + n) if (a[i] == a[to(i)]) ok[i] = ok[to(i)] = 0, shit = 1;
	i64 tot = 0;
	REP(i, 1, n + n) if (ok[i])
	{
		if (!tot) tot = 1;
		k = 0;
		find(i);
		(tot *= k) %= MOD;
	}
	/*
	REP(i, 1, n + n) printf("%d%s", a[i], i == end_i ? " : " : " ");
	cout << tot << endl;
	REP(i, 1, n) cout << lst[i] << ' ';cout << endl;
	REP(i, 1, n) cout << ccc[i].first << ' ' << ccc[i].second << endl;
	*/
	ans += tot;
}
int dis(int x, int y)
{
	if (x < y) swap(x, y);
	return min(abs(y - x + n + n), abs(x - y));
}
void dfs(int x)
{
	if (x == n + n) calc();
	else
	{
		x++;
		REP(i, 1, n) if (cnt[i] < 2)
		{
			if (!cnt[i]) lst[i] = x;
			else if (x != to(lst[i]) && dis(x, lst[i]) > 2) continue;
			else
			{
				int a = lst[i], b = x;
				int c = to(a), d = to(b);
				if (::a[c] && ::a[d] && ::a[c] != ::a[d]) continue;
			}
			cnt[i]++;
			a[x] = i;
			dfs(x);
			cnt[i]--;
			a[x] = 0;
		}
	}
}

int Ans[] = {2988, 6720};

namespace CCC
{
	bool vis[maxn];
	void dfs(int x)
	{
		if (x == n) calc();
		else
		{
			x++;
			REP(i, 1, n + n) if (!vis[i])
			{
				lst[x] = i;
				vis[i] = 1;
				a[i] = x;
				REP(j, i + 1, n + n) if (!vis[j] && (j == to(i) || dis(i, j) <= 2))
				{
					int c = to(i), d = to(j);
					if (a[c] && a[d] && a[c] != a[d]) continue;
					vis[j] = 1;
					a[j] = x;
					dfs(x);
					vis[j] = a[j] = 0;
				}
				vis[i] = a[i] = 0;
			}
		}
	}
	void work()
	{
		a[1] = vis[1] = lst[1] = 1;
		REP(i, 2, n + n)
		{
			vis[i] = a[i] = 1;
			dfs(1);
			vis[i] = a[i] = 0;
		}
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	CCC :: work();
//	cnt[1] = lst[1] = a[1] = 1;
//	dfs(1);
	cout << ans % MOD << endl;
	return 0;
}
