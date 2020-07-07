#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 525010 + 10;

int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int m, n, k;

int v[maxn];
struct Trie
{
	Trie *ch[2];
	int d, v, s;
	Trie(int d = 0) : d(d), v(0), s(0) {ch[0] = ch[1] = 0;}
	void pushup()
	{
		v = s = 0;
		if (ch[0])
		{
			s += ch[0] -> s;
			v ^= ch[0] -> v;
		}
		if (ch[1])
		{
			s += ch[1] -> s;
			v ^= (ch[1] -> s & 1) << d ^ ch[1] -> v;
		}
	}
	void insert(int val)
	{
		if (d > 25) return void(s++);
		int flag = val >> d & 1;
		if (!ch[flag]) ch[flag] = new Trie(d + 1);
		ch[flag] -> insert(val);
		pushup();
	}
	void modify()
	{
		swap(ch[0], ch[1]);
		if (ch[0]) ch[0] -> modify();
		pushup();
	}
}*T[maxn];
Trie* merge(Trie *a, Trie *b)
{
	if (!a) return b;
	if (!b) return a;
	a -> s += b -> s;
	a -> v ^= b -> v;
	a -> ch[0] = merge(a -> ch[0], b -> ch[0]);
	a -> ch[1] = merge(a -> ch[1], b -> ch[1]);
	delete(b);
	return a;
}
long long ans = 0;

void dfs(int x)
{
	T[x] = new Trie(0);
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs(to[i]);
		T[x] = merge(T[x], T[to[i]]);
	}
	T[x] -> modify();
	T[x] -> insert(v[x]);
	ans += T[x] -> v;
}

int main()
{
#ifdef CraZYali
	file("6623");
#endif
	n = read<int>();
	REP(i, 1, n) v[i] = read<int>();
	REP(i, 2, n) add(read<int>(), i);
	dfs(1);
	cout << ans << endl;
	return 0;
}
