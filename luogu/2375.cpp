/*
 * File Name:	2375.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.04 11:46
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <bitset>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10, maxN = 9976e3, MOD = 1e9 + 7;
template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int ls[maxN], rs[maxN], cur, s[maxN], rt[maxn];
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r

void insert(int pre, int &p, int l, int r, int pos)
{
	p = ++cur;
	ls[p] = ls[pre];
	rs[p] = rs[pre];
	s[p] = s[pre] + 1;
	if (l == r) return;
	if (pos <= mid) insert(ls[pre], lson, pos);
	else			insert(rs[pre], rson, pos);
}
int query(int p, int l, int r, int L, int R)
{
	if (!s[p]) return 0;
	if (L <= l && r <= R) return s[p];
	else
	{
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}
int n, ne[maxn];
char str[maxn];
bitset <maxn> use;
int main()
{
#ifdef CraZYali
	file("2375");
#endif
	register int T = read<int>();
	while (T--)
	{
		REP(i, 1, cur) ls[i] = rs[i] = s[i] = 0;
		REP(i, 1, n) rt[i] = use[i] = 0;
		cur = 0;
		scanf("%s", str + 1);
		n = strlen(str + 1);
		const int half = n >> 1;
		int k = 0;
		long long ans = 1;
		REP(i, 2, n)
		{
			while (k && str[k + 1] != str[i]) k = ne[k];
			ne[i] = (k += (str[k + 1] == str[i]));
			use[ne[i]] = 1;
		}
		REP(i, 2, n)
		{
			if (use[i])
			{
				if (ne[i] && ne[i] <= half) insert(rt[ne[i]], rt[i], 1, half, ne[i]);
				else rt[i] = rt[ne[i]];
				ans *= (1 + query(rt[i], 1, half, 1, i / 2));
			}
			else
			{
				rt[i] = rt[ne[i]];
				ans *= (1 + (ne[i] <= i / 2 && ne[i]) + query(rt[ne[i]], 1, half, 1, i / 2));
			}
			if (ans >= MOD) ans %= MOD;
		}
		cout << ans;putchar(10);
#ifdef CraZYali
		cerr << cur << endl;
#endif
	}
	return 0;
}
