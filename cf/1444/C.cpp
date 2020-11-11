/*
	Problem:	C.cpp
	Time:		2020-11-07 10:47
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 5e5 + 10, maxm = 5e5 + 10;


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

int n, m, k, u[maxm], v[maxm], b[maxn];

namespace uni
{
	const int maxn = ::maxn << 1;
	int fa[maxn], siz[maxn];
	int u[maxn], v[maxn], top;
	int find(int x) {return fa[x] == x ? fa[x] : find(fa[x]);}
	void uni(int x, int y)
	{
		x = find(x);y = find(y);
		if (x == y)
		{
			u[++top] = 0;
			return;
		}
		if (siz[x] > siz[y]) swap(x, y);
		fa[x] = y;siz[y] += siz[x];
		++top;
		u[top] = x;v[top] = y;
	}
	void undo()
	{
		int x = u[top], y = v[top];top--;
		if (!x) return;
		siz[y] -= siz[x];fa[x] = x;
	}
	bool gg(int x) {return find(x) == find(x + n);}
}
bool ard[maxn];
int cur;
map <pair <int, int>, int> Id;
vector <int> c[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	REP(i, 1, n) b[i] = read<int>();
	REP(i, 1, n + n) uni :: fa[i] = i, uni :: siz[i] = 1;
	REP(i, 1, m)
	{
		u[i] = read<int>(), v[i] = read<int>();
		if (b[u[i]] > b[v[i]]) swap(u[i], v[i]);
		if (b[u[i]] == b[v[i]])
		{
			uni :: uni(u[i], v[i] + n);
			uni :: uni(v[i], u[i] + n);
			if (uni :: gg(u[i]) || uni :: gg(v[i])) ard[b[u[i]]] = 1;
		}
		else
		{
			pair <int, int> here(b[u[i]], b[v[i]]);
			if (!Id[here]) Id[here] = ++cur;
			c[Id[here]].emplace_back(i);
		}
	}
	int K = 0;
	REP(i, 1, k) if (!ard[i]) K++;
	i64 ans = K * (K - 1ll) / 2;
	for (auto A : Id)
	{
		int b1 = A.first.first, b2 = A.first.second, z = A.second;
		if (ard[b1] || ard[b2]) continue;
		bool flag = 0;
		for (int i : c[z])
		{
			uni :: uni(u[i], v[i] + n);
			uni :: uni(v[i], u[i] + n);
			if (uni :: gg(u[i]) || uni :: gg(v[i])) flag = 1;
		}
		ans -= flag;
		REP(i, 1, 2 * c[z].size()) uni :: undo();
	}
	cout << ans << endl;
	return 0;
}
