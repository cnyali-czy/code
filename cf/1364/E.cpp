#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <random>
#include <cstring>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2050, LIM = 4269;

int read() {int x;cin >> x;return x;}

int n, mem[maxn][maxn], p[maxn], cnt, ans[maxn];
int ask(int i, int j)
{
	assert(i != j);
	if (i > j) swap(i, j);
	if (mem[i][j]) return mem[i][j];
	if (ans[i] >= 0 && ans[j] >= 0) return mem[i][j] = ans[i] | ans[j];
	cnt++;
#ifdef CraZYali
	return mem[i][j] = p[i] | p[j];
#else
	cout << "? " << i << ' ' << j << endl;
	return mem[i][j] = read();
#endif
}

void report()
{
	printf("!");
	REP(i, 1, n) printf(" %d", ans[i]);
	cout << endl;
#ifdef CraZYali
	REP(i, 1, n) if (ans[i] ^ p[i])
	{
		printf("wrong answer (%d, %d, %d)\n", i, ans[i], p[i]);
		return;
	}
	printf("AC with %d / %d\n", cnt, LIM);
	if (cnt > LIM)
		cerr << "exceeded query limit";
#endif
}
mt19937 hh(134810);
vector <int> v;
void ensure(int x)
{
	if (ans[x] >= 0) return;
	int &res = ans[x];

	REP(i, 1, 20)
	{
		int y = hh() % n + 1;
		if (x == y) {i--;continue;}
		if (i == 1) res = ask(x, y);
		else res &= ask(x, y);
	}
}
void zero_found(int x)
{
	REP(i, 1, n) if (ans[i] < 0) ans[i] = ask(x, i);
}

int main()
{
#ifdef CraZYali
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	n = read();
#ifdef CraZYali
	REP(i, 1, n) p[i] = read();
#endif
	v.resize(n);
	REP(i, 0, n - 1) v[i] = i + 1;
	memset(ans, -1, sizeof ans);
	shuffle(v.begin(), v.end(), hh);
	int a = v[0], b = v[1];
	REP(i, 2, n - 1)
	{
		int c = v[i];
		assert(a != b);
		assert(a != c);
		assert(b != c);
		if (ask(a, c) >  ask(a, b))
		{
#ifdef CraZYali
			assert(p[c]);
#endif
		}
		else if (ask(a, c) <  ask(a, b))
		{
#ifdef CraZYali
			assert(p[b]);
#endif
			b = c;
		}
		else if (ask(a, c) == ask(a, b))
		{
#ifdef CraZYali
			assert(p[a]);
#endif
			a = c;
		}
	}

	ensure(a);
	if (ans[a] == 0) zero_found(a);
	else ans[b] = 0, zero_found(b);
	report();
	return 0; 
}
