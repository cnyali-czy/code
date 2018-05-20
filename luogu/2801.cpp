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
const int maxn = 1000000 + 10;

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
int m, n, k, block = 1;


#define End Right[first_id]
#define Start Left[second_id]

int tag[2000];

pair<int, int> a[maxn];
bool cmp_by_val(pair<int, int> A, pair<int, int> B) {return A.first < B.first;}
bool cmp_by_pos(pair<int, int> A, pair<int, int> B) {return A.second < B.second;}

int belong[maxn], Left[2000], Right[2000];
inline void get_belong(int n)
{
	k = sqrt(n);
	register int i;
	for (i = 1; i + k <= n ;i += k, block++)
	{
		Left[block] = i;
		Right[block] = i + k - 1;
		REP(j, i, i + k - 1) belong[j] = block;
	}
	if (i <= n)
	{
		Left[block] = i;
		Right[block] = n;
		while (i <= n) belong[i++] = block;
	}
}

inline void add(int x, int y, int z)
{
	int first_id = belong[x], second_id = belong[y];
	if (first_id == second_id) { tag[first_id] += z;return;}
	REP(i, first_id + 1, second_id - 1) tag[i] += z;
	if (x <= End)
	{
		sort(a + Left[first_id], a + Right[first_id] + 1, cmp_by_pos);
		REP(i, x, End) a[i].first += z;
		sort(a + Left[first_id], a + Right[first_id] + 1, cmp_by_val);
	}
	if (Start <= y)
	{
		sort(a + Left[second_id], a + Right[second_id] + 1, cmp_by_pos);
		REP(i, Start, y) a[i].first += z;
		sort(a + Left[second_id], a + Right[second_id] + 1, cmp_by_val);
	}
}

inline void answer(int x, int y, int z)
{
	int ans = 0;

	int first_id = belong[x], second_id = belong[y];
	if (first_id == second_id)
	{
		sort(a + Left[first_id], a + Right[first_id] + 1, cmp_by_pos);
		REP(i, x, y) ans += a[i].first >= z - tag[first_id];
		sort(a + Left[first_id], a + Right[first_id] + 1, cmp_by_val);
		printf("%d\n", ans);
		return;
	}
	REP(i, first_id + 1, second_id - 1)
	{
		int l(Left[i]), r(Right[i]), L(l), R(r);
		while (l <= r)
		{
			int mid(l + r >> 1);
			if (a[mid].first < z - tag[i]) l = mid + 1;
			else r = mid - 1;
		}
		ans += R - l + 1;
	}
	if (x <= End)
	{
		sort(a + Left[first_id], a + Right[first_id] + 1, cmp_by_pos);
		REP(i, x, End)	if (a[i].first + tag[first_id] >= z)	ans++;
		sort(a + Left[first_id], a + Right[first_id] + 1, cmp_by_val);
	}
	if (Start <= y)
	{
		sort(a + Left[second_id], a + Right[second_id] + 1, cmp_by_pos);
		REP(i, Start, y)if (a[i].first + tag[second_id] >= z)	ans++;
		sort(a + Left[second_id], a + Right[second_id] + 1, cmp_by_val);
	}
	printf("%d\n", ans);
}
int main()
{
#ifdef CraZYali
	freopen("2801.in", "r", stdin);
	freopen("2801.out", "w", stdout);
	freopen("2801.err", "w", stderr);
#endif
	get_belong(n = read<int>());
	m = read<int>();
	REP(i, 1, n) a[i] = make_pair(read<int>(), i);
	REP(i, 1, block) sort(a + Left[i], a + Right[i] + 1, cmp_by_val);
	
	while (m --> 0)
	{
		char opt = getchar();
		while (opt ^ 'A' && opt ^ 'M') opt = getchar();
		register int x, y, z;
		x = read<int>();y = read<int>();z = read<int>();
		if (opt ^ 'A')	add(x, y, z);
		else			answer(x, y, z);
		
	}
	return 0;
}
