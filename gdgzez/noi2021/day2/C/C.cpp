#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <vector>
#include <bitset>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5000 + 5;

int n;
bitset <5005> G[maxn];
//bool G[5005][5005];

namespace sub4
{
	bool judge()
	{
		REP(i, 1, n)
		{
			int cnt = 0;
			REP(j, 1, i) cnt += (!G[i][j]);
			if (cnt ^ 1) return 0 ;
		}
		return 1;
	}
	int main()
	{
		REP(i, 1, n)
		{
			char c = '3';
			REP(j, 1, i)
			{
				if (G[i][j]) putchar(c);
				else putchar('-'), c -= 2;
			}
			puts("");
		}
		return 0;
	}
}

vector <int> h[maxn];
char s[maxn][maxn];
int mark[maxn][maxn];

int tot;
namespace SMT
{
	const int maxN = maxn << 2;
	int s[maxN], mx[maxN];
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1
	inline void pushup(int p)
	{
		s[p] = s[ls] + s[rs];
		mx[p] = max(mx[ls], s[ls] + mx[rs]);
	}
	void build(int p, int l, int r)
	{
		if (l == r) s[p] = mx[p] = 1;
		else
		{
			build(lson);
			build(rson);
			pushup(p);
		}
	}
	void update(int p, int l, int r, int pos, int val)
	{
		if (l == r)
		{
			s[p] += val;
			mx[p] += val;
		}
		else
		{
			if (pos <= mid) update(lson, pos, val);
			else update(rson, pos, val);
			pushup(p);
		}
	}
	int query(int p, int l, int r, int x)
	{
		if (l == r) return l + 1;
		if (mx[ls] >= x) return query(lson, x);
		else return query(rson, x - s[ls]);
	}
	int lmost(int i, int j)
	{
		for (int x : h[i - 1])
		{
			if (x > j - i + 1) break;
			update(1, 1, n, x, -1);
			tot++;
		}
		if (tot > j - i + 1) return 0;
		else if (tot == j - i + 1) mark[j][j - i + 1] = 1;
		else
			if (mx[1] < j - i + 1 - tot) mark[j][j - i + 1] = j - i + 2;
			else mark[j][j - i + 1] = query(1, 1, n, j - i + 1 - tot);
		return 1;
	}
}
char ans[maxn][maxn];

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		REP(j, 1, i)
		{
			char c = getchar();
			while (!isdigit(c)) c = getchar();
			if (c == '1') G[i].set(j);
			else h[i - j].emplace_back(j), ans[i][j] = '-';
		}
	}
	if (sub4 :: judge()) return sub4 :: main();
	DEP(i, n, 2)
	{
		vector <int> v;
		REP(j, 1, i) if (!G[i][j]) v.emplace_back(j);
		if (!v.size())
		{
			puts("Impossible!");
			return 0;
		}
		REP(j, 1, v[0] - 1) ans[i][j] = '3';
		REP(j, v.back() + 1, i) ans[i][j] = '1';
		SMT :: build(1, 1, n);
		tot = 0;
		REP(j, 1, v[0] - 1)
			if (!SMT :: lmost(i - j, i - 1))
			{
				puts("Impossible!");
				return 0;
			}
		REP(j, 1, (int)v.size() - 1)
		{
			int p1 = v[j - 1], p2 = v[j], p = p1;
			REP(k, p1, p2 - 1)
			{
				if (!SMT :: lmost(i - k, i - 1))
				{
					puts("Impossible!");
					return 0;
				}
				if (mark[i - 1][k] <= p1) p = k + 1;
			}
			if (p == p2)
			{
				puts("Impossible!");
				return 0;
			}
			G[i - 1][p] = 0;
			ans[i - 1][p] = '2';
			SMT :: update(1, 1, n, p, -1);
			tot++;
			REP(k, p1 + 1, p) ans[i][k] = '1';
			REP(k, p + 1, p2 - 1) ans[i][k] = '3';
		}
	}
	REP(i, 1, n)
	{
		REP(j, 1, i) putchar(ans[i][j]);
		puts("");
	}
	return 0;
}
