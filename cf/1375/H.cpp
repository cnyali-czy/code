/*
	Problem:	H.cpp
	Time:		2021-01-20 19:34
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1 << 12 | 10;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

const int B = 1 << 8;
int n, q;
int a[maxn], tot, N;

vector <int> vec[maxn];
inline int blg(int x) {return (x - 1) / B + 1;}

struct seg
{
	vector <int> v;//存储位置
	vector <vector <int> > id;
	int mx;
	seg() {}
	seg(const vector <int> &v, const vector <vector <int> > &id, int mx) : v(v), id(id), mx(mx) {}
	seg(int x)
	{
		mx = a[x];
		v.emplace_back(x);
		id.emplace_back(vector<int>(1, x));
	}
	int query(int l, int r)
	{
		if (r < v[0] || l > v.back()) return 0;
		l = lower_bound(v.begin(), v.end(), l) - v.begin();
		r = upper_bound(v.begin(), v.end(), r) - v.begin() - 1;
		return l > r ? 0 : id[l][r - l];
	}
}EMPTY, mem[maxn];
int MX[2200005];

vector <pair <int, int> > FUCK;
int uni(int x, int y)
{
	if (!x || !y) return x | y;
	if (MX[x] > MX[y]) swap(x, y);
	FUCK.emplace_back(x, y);
	++N;
	MX[N] = MX[y];
	return N;
}
vector <int> merge(const vector <int> &A, const vector <int> &B)
{
	int i = 0, j = 0, n = A.size(), m = B.size();
	vector <int> C;
	while (i < n && j < m)
		if (A[i] < B[j]) C.emplace_back(A[i++]);
		else C.emplace_back(B[j++]);
	while (i < n) C.emplace_back(A[i++]);
	while (j < m) C.emplace_back(B[j++]);
	return C;
}
seg operator + (seg A, seg B)
{
	vector <int> v = merge(A.v, B.v);
	vector <vector <int> > id;
	REP(i, 0, v.size() - 1)
	{
		vector <int> cur(v.size() - i);
		REP(j, i, v.size() - 1)
			cur[j - i] = uni(A.query(v[i], v[j]), B.query(v[i], v[j]));
		id.emplace_back(cur);
	}
	return seg(v, id, max(A.mx, B.mx));
}

seg build(vector <int> v, int l, int r)
{
	if (!v.size())
	{
		cerr << "IMPOSSIBLE!\n";
		return EMPTY;
	}
	if (l == r) return seg(v[0]);
	int mid = l + r >> 1;
	vector <int> vl, vr;
	for (auto i : v)
		if (a[i] <= mid) vl.emplace_back(i);
		else vr.emplace_back(i);
	return build(vl, l, mid) + build(vr, mid + 1, r);
}


int main()
{
#ifdef CraZYali
	file("H");
#endif
	EMPTY.v.emplace_back(-1);
	n = read<int>();q = read<int>();
	REP(i, 1, n)
	{
		a[i] = read<int>();
		vec[blg(a[i])].emplace_back(i);
	}
	REP(i, 1, n) MX[i] = a[i];
	N = n;
	tot = blg(n);
	REP(i, 1, tot)
	{
		int L = (i - 1) * B + 1, R = min(n, i * B);
		mem[i] = build(vec[i], L, R);
		/*
		printf("[%d, %d]\n", L, R);
		REP(l, 1, n) REP(r, l, n)
		{
			printf("%d %d %d\n", l, r, mem[i].query(l, r));
		}
		puts("");
		*/
	}
	static int ans[1 << 16 | 10];
	REP(i, 1, q)
	{
		int l = read<int>(), r = read<int>();
		int cur = 0;
		REP(i, 1, tot) cur = uni(cur, mem[i].query(l, r));
		ans[i] = cur;
	}
	cout << N << endl;
	for (auto i : FUCK) printf("%d %d\n", i.first, i.second);
	REP(i, 1, q) printf("%d%c", ans[i], i == end_i ? '\n' : ' ' );
	return 0;
}
