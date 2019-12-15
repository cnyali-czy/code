/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2019.12.15 09:08
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 8e5 + 10;
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

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
char s[maxn];
int n, q;
struct SMT
{
	int sum[maxn << 2], id;
	void build(int p, int l, int r)
	{
		if (l == r) sum[p] = (s[l] == id);
		else
		{
			build(lson);
			build(rson);
			sum[p] = sum[ls] + sum[rs];
		}
	}
	inline void init(int _id)
	{
		id = _id;
		build(1, 1, n);
	}
	void update(int p, int l, int r, int pos, int val)
	{
		sum[p] += val;
		if (l == r) return;
		if (pos <= mid) update(lson, pos, val);
		else			update(rson, pos, val);
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return sum[p];
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}T[13];
int nxt(int x) {return x == 12 ? 1 : x + 1;}
int tot[13];
int dp[13], tmp[13];

int main()
{
#ifdef CraZYali
	file("A");
	freopen("A.err", "w", stderr);
#endif
	cin >> n >> q;
	scanf("%s", s + 1);
	REP(i, 1, n)
		if (!isdigit(s[i])) s[i] = s[i] - 'a' + 10;
		else s[i] = s[i] - '0';
	REP(i, 1, 12) T[i].init(i);
	while (q--)
	{
		int l(read<int>()), r(read<int>());
		REP(i, 1, 12) tot[i] = T[i].query(1, 1, n, l, r);
		T[s[l]].update(1, 1, n, l, -1);
		T[s[l] = nxt(s[l])].update(1, 1, n, l, 1);
		T[s[r]].update(1, 1, n, r, -1);
		T[s[r] = nxt(s[r])].update(1, 1, n, r, 1);
		int rt(0);
		dp[0] = 1;
		REP(i, 1, 12) dp[i] = 0;
		//REP(i, 0, min(tot[1], 12)) dp[i] = ((tot[1] - i) / 13 + 1) & 1;
		REP(i, 1, 12)
		{
			for (int j = 1; j <= tot[i]; j <<= 1)
			{
				tot[i] -= j;
				REP(I, 0, 12) tmp[I] = dp[I];
				REP(I, 0, 12) (tmp[(I + 1ll * i * j % 13) % 13] += dp[I]) &= 1;
				REP(I, 0, 12) dp[I] = tmp[I];
			}
			if (tot[i])
			{
				REP(I, 0, 12) tmp[I] = dp[I];
				REP(I, 0, 12) (tmp[(I + 1ll * tot[i] * i % 13) % 13] += dp[I]) &= 1;
				REP(I, 0, 12) dp[I] = tmp[I];
			}
		}

		REP(i, 0, 12) putchar(dp[i] + 48);putchar(10);
	}
	return 0;
}
