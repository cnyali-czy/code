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
const int maxn = 50000 + 10;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;

int a[maxn];

int belong[maxn], Left[300], Right[300], block = 1;
inline void get_belong()
{
	int size = sqrt(n), i;
	for (i = 1; i + size - 1 <= n ;i += size, block++)
	{
		Left[block] = i;Right[block] = i + size - 1;
		REP(j, i, i + size - 1) belong[j] = block;
	}
	if (i <= n)
	{
		Left[block] = i;Right[block] = n;
		while (i <= n) belong[i++] = block;
	}
}
map <int, int> LS;
int all;

bitset <maxn << 1> sta[300];

inline void calc(int id)
{
	sta[id].reset();
	REP(i, Left[id], Right[id])
	{
		if (!LS[a[i]]) LS[a[i]] = ++all;
		sta[id].set(LS[a[i]]);
	}
}

inline void answer(int l, int r)
{
	sta[0].reset();
	if (belong[l] == belong[r])
	{
		REP(i, l, r) sta[0].set(LS[a[i]]);
		cout << sta[0].count() << endl;
		return;
	}
	
	int first_id = belong[l], second_id = belong[r];
	REP(i, first_id + 1, second_id - 1) sta[0] |= sta[i];
	REP(i, l, Right[first_id]) sta[0].set(LS[a[i]]);
	REP(i, Left[second_id], r) sta[0].set(LS[a[i]]);
	cout << sta[0].count() << endl;
}

inline void replace(int x, int y)
{
	a[x] = y;
	if (!LS[y]) LS[y] = ++all;
	calc(belong[x]);
}

int main()
{
#ifdef CraZYali
	freopen("1903.in", "r", stdin);
	freopen("1903.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m;
    REP(i, 1, n) cin >> a[i];
	
	get_belong();
	REP(i, 1, block) calc(i);

	while (m--)
	{
		register char c;
		int A, B;
		cin >> c >> A >> B;
		if (c == 'Q')	answer(A, B);
		else 			replace(A, B);
	}
	return 0;
}

