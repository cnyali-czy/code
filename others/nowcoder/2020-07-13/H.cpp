#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;
const int maxn = 2e5 + 10, inf = 2e9;

struct
{
	int ls, rs, v, s, order;
}t[maxn];
#define v(x) t[x].v
#define s(x) t[x].s
#define ls(x) t[x].ls
#define rs(x) t[x].rs
#define order(x) t[x].order

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

int n, cur, rt;
inline int newnode(int val)
{
	++cur;
	ls(cur) = rs(cur) = 0;
	v(cur) = val;
	s(cur) = 1;
	order(cur) = rand();
	return cur;
}
void pushup(int x) {s(x) = s(ls(x)) + s(rs(x)) + 1;}
void merge(int &x, int a, int b)
{
	if (!a || !b) x = a | b;
	else
	{
		if (order(a) > order(b)) merge(ls(x = b), a, ls(b));
		else merge(rs(x = a), rs(a), b);
		pushup(x);
	}
}
void split(int x, int &a, int &b, int val)
{
	if (!x) a = b = 0;
	else
	{
		if (v(x) > val) split(ls(b = x), a, ls(x), val);
		else split(rs(a = x), rs(x), b, val);
		pushup(x);
	}
}
void ins(int val)
{
	int x(0), y(0);
	split(rt, x, y, val);
	merge(x, x, newnode(val));
	merge(rt, x, y);
}
void del(int val)
{
	int x(0), y(0), z(0);
	split(rt, x, y, val);
	split(x, x, z, val - 1);
	merge(z, ls(z), rs(z));
	merge(x, x, z);
	merge(rt, x, y);
}
int getrank(int val)
{
	int x = rt, ans = 0;
	while (x)
	{
		if (val > v(x))
		{
			ans += s(ls(x)) + 1;
			x = rs(x);
		}
		else x = ls(x);
	}
	return ans + 1;
}
int getkth(int x, int k)
{
	while (1)
	{
		int le = s(ls(x)) + 1;
		if (k == le) return v(x);
		else if (k < le) x = ls(x);
		else
		{
			k -= le;
			x = rs(x);
		}
	}
}
int getkth(int k) {return getkth(rt, k);}
int pre(int val)
{
	int x = rt, ans = -inf;
	while (x)
	{
		if (v(x) < val)
		{
			chkmax(ans, v(x));
			x = rs(x);
		}
		else x = ls(x);
	}
	return ans;
}
int suf(int val)
{
	int x = rt, ans = inf;
	while (x)
	{
		if (v(x) > val)
		{
			chkmin(ans, v(x));
			x = ls(x);
		}
		else x = rs(x);
	}
	return ans;
}
void dfs(int x)
{
	if (ls(x)) dfs(ls(x));
	printf("%d ", v(x));
	if (rs(x)) dfs(rs(x));
}

const int N = 1e9, maxN = 2e7;
unordered_map <int, int> cnt;
int RT;
namespace SMT
{
	int ls[maxN], rs[maxN], Min[maxN], cur;
	struct __init__
	{
		__init__()
		{
			Min[0] = inf;
		}
	}__INIT__;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	void update(int &p, int l, int r, int pos, int val)
	{
		if (!p) p = ++cur, Min[p] = inf;
		if (l == r) Min[p] = val;
		else
		{
			if (pos <= mid)	update(lson, pos, val);
			else			update(rson, pos, val);
			Min[p] = min(Min[ls[p]], Min[rs[p]]);
		}
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (!p) return inf;
		if (L <= l && r <= R) return Min[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return min(query(lson, L, R), query(rson, L, R));
		}
	}
}
using SMT :: update;
using SMT :: query;

void Insert(int x)
{
	cnt[x]++;
	if (cnt[x] > 1) update(RT, 1, N, x, 0);
	else
	{
		int A = pre(x), B = suf(x);
		if (A != -inf) update(RT, 1, N, x, x - A);
		else update(RT, 1, N, x, inf);
		if (B != inf && cnt[B] == 1) update(RT, 1, N, B, B - x);
		ins(x);
	}
}
void Delete(int x)
{
	if (cnt[x] == 1)
	{
		del(x);
		update(RT, 1, N, x, inf);
		int A = pre(x), B = suf(x);
		if (B != inf && cnt[B] == 1)
		{
			if (A != -inf) update(RT, 1, N, B, B - A);
			else update(RT, 1, N, B, inf);
		}
	}
	if (cnt[x] == 2)
	{
		int A = pre(x);
		if (A != -inf) update(RT, 1, N, x, x - A);
		else update(RT, 1, N, x, inf);
	}
	cnt[x]--;
}
bool query1(int x)
{
	int a = pre(x + 1), b;
	if (a == -inf) return 0;
	if (cnt[a] > 1) b = a;
	else
	{
		b = pre(a);
		if (b == -inf) return 0;
	}
	return a + b > x;
}

int times = 0;
bool query2(int x)
{
	int z = suf(x - 1), tmp;
	bool flag = 0;
	if (z == inf) return 0;
//	if (times == 41) cout << "z = " << z << endl;
	if (cnt[z] == 1)
	{
		flag = 1;
		tmp = query(RT, 1, N, z, z);
		update(RT, 1, N, z, inf);
	}
	bool res = ( x > query(RT, 1, N, x, N) );
	/*
	if (times == 184)
	{
		cout << query(RT, 1, N, x, N) << ' ' <<query(RT,1,N,5,5)<<endl;
	}
	*/
	if (flag) update(RT, 1, N, z, tmp);
	return res;
}
int main()
{
#ifdef CraZYali
	file("H");
#endif
	s(0) = 0;
	ins(-inf);ins(inf);
	REP(Case, 1, read<int>())
	{
//		cerr << Case << ' ' <<  cnt[4] << ' ' << query(RT, 1, N, 4, 4) << endl;
		int opt = read<int>(), x = read<int>();
		if (opt == 1) Insert(x);
		else if (opt == 2) Delete(x);
		else
		{
			times++;
			/*
			if(times==184)
			{
			printf("x = %d: ",x);
				for(auto i : cnt)REP(j,1,i.second)printf("%d ",i.first);puts("");
			}
			*/
			if (query1(x)) puts("Yes");
			else if (query2(x)) puts("Yes");
			else puts("No");
		}
	}
	return 0;
}
