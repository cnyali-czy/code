#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 100010, inf = (((1 << 30) - 1) << 1) + 1;

inline int turn(string s)
{
	int len = s.size() - 1, res(0);
	REP(i, 0, len) res = res * 10 + s[i] - 48;
	return res;
}

#define ls p << 1
#define rs p << 1 | 1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

struct seg_tree
{
	int Max[maxn << 2];
	seg_tree() {memset(Max, 0, sizeof(Max));}
	inline void update(int p, int l, int r, int x, int y)
	{
		if (l == r && r == x) Max[p] = y;
		else
		{
			if (x <= mid) update(lson, x, y);
			else update(rson, x, y);
			Max[p] = max(Max[ls], Max[rs]);
		}
	}
	inline int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return Max[p];
		else
		{
			int lans, rans;
			lans = rans = -inf;
			if (L <= mid) lans = query(lson, L, R);
			if (R >  mid) rans = query(rson, L, R);
			return max(lans, rans);
		}
	}
	inline int find_pos(int p, int l, int r, int x)
	{
		if (Max[p] < x) return -1;
		if (l == r)	return Max[p] ^ x ? -1 : l;
		int lans(-1), rans(-1);
		if (Max[ls] >= x) lans = find_pos(lson, x);
		if (Max[rs] >= x) rans = find_pos(rson, x);
		return lans == -1 ? rans : lans;
	}
}T;

int m, n, k;
int a[maxn], b[maxn];

inline void update(int x, int y)
{
	b[x] = y - a[x];
	a[x] = y;
	T.update(1, 1, n, x, b[x]);
}

inline void Report()
{
	int Maxx(T.query(1, 1, n, 1, n));
	int pos(T.find_pos(1, 1, n, Maxx));
	cout << pos << ' ';
	int temp1(-inf), temp2(-inf);
	if (pos > 1) temp1 = T.query(1, 1, n, 1, pos - 1);
	if (pos < n) temp2 = T.query(1, 1, n, pos + 1, n);
	T.update(1, 1, n, pos, -inf);
	if (temp1 >= temp2) cout << T.find_pos(1, 1, n, temp1);
	else cout << T.find_pos(1, 1, n, temp2); 
//	printf(" %d %d", T.find_pos(1, 1, n, temp1), T.find_pos(1, 1, n, temp2));
	T.update(1, 1, n, pos, Maxx);
	cout << '\n';
}

int main()
{
	freopen("invest.in", "r", stdin);
	freopen("invest.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> n;
	REP(i, 1, n) cin >> a[i];
	while (1)
	{
		register string t;
		cin >> t;
		if (t[0] == 'E') return 0;
		else if (t[0] == 'R') Report();
		else
		{
			int x;
			cin >> x;
			update(turn(t), x);
		}
	}
}
