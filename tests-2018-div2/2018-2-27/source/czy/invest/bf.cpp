#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100000 + 10, inf = (((1 << 30) - 1) << 1) + 1;

inline int turn(string t)
{
	int len = t.size() - 1, ans(0);
	REP(i, 0, len)
		ans = ans * 10 + t[i] - 48;
	return ans;
}
int n, a[maxn], b[maxn];

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

inline void SLEEP(double t)
{
	double now = clock();
	while ((clock() - now) / CLOCKS_PER_SEC < t);
}
bool flag;
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
			int Ml, Mr;
			Ml = Mr = -inf;
			if (L <= mid) Ml = query(lson, L, R);
			if (R >  mid) Mr = query(rson, L, R);
			return max(Ml, Mr);
		}
	}
	inline int find_pos(int p, int l, int r, int x)
	{
		if (flag)
		{
			cerr << l << ' ' << r << ' ' << x << ' ' << Max[p] << endl;
			SLEEP(0.25);
		}
		if (Max[p] < x) return -1;
		if (l == r && Max[p] == x) return l;
		
		if (Max[ls] >= x) return find_pos(lson, x);
		else return find_pos(rson, x);
	}
}T;

inline void update(int x, int y)
{
	b[x] = y - a[x];
	a[x] = y;
	T.update(1, 1, n, x, b[x]);
}

inline void Report()
{
	int Max1 = T.query(1, 1, n, 1, n);
	int pos1 = T.find_pos(1, 1, n, Max1);
	cout << pos1 << ' ' ;
	int temp1(-inf), temp2(-inf);
	if (pos1 > 1) temp1 = T.query(1, 1, n, 1, pos1 - 1);
	if (pos1 < n) temp2 = T.query(1, 1, n, pos1 + 1, n);
	if (temp1 >= temp2) cout << T.find_pos(1, 1, n, temp1) << endl;
	else cout << T.find_pos(1, 1, n, temp2) << endl;
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
		if (t == "EndOfCurrentCase") return 0;
		else if (t == "Report") Report();
		else
		{
			register int x;
			cin >> x;
			update(turn(t), x);
		}
	}
	return 0;
}
