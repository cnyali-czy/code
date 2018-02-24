#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <map>

using namespace std;
const int maxn = 30;

int n, bit[maxn], ans;

inline void Read() {
	memset(bit, 0, sizeof(bit));
	REP(i, 1, n) {
		register char c = getchar();
		while (c ^ '\n') {bit[i] ^= (1 << (c - 'A'));c = getchar();}
	}
}
inline int bitcount(int x) {return !x ? 0 : bitcount(x >> 1) + (x & 1);}

bool vis[maxn];
map <int, int> M;
//	<得到的数，状压结果>

inline void output() {
	printf("%d\n", bitcount(ans));
	
	REP(i, 1, n) if (ans & (1 << (i - 1))) printf("%d ", i);
	printf("\n");
}

inline void work() {
	Read();

	M.clear();
	register int half = n >> 1, hhalf = n - half; ans = 0;
	REP(i, 0, (1 << half) - 1) {
		register int get = 0;
		REP(j, 1, half) if (i & (1 << (j - 1))) get ^= bit[j];
		if (!M.count(get) || bitcount(M[get]) < bitcount(i)) M[get] = i;
	}

	REP(i, 0, (1 << hhalf) - 1) {
		register int get = 0;
		REP(j, 1, hhalf)if (i & (1 << (j - 1))) get ^= bit[j + half];
		if (M.count(get) && bitcount(ans) < bitcount(i) + bitcount(M[get])) ans = (i << half) | M[get];
	}
	output();
}

int main() {
#ifdef CraZYali
	freopen("2965.in", "r", stdin);
	freopen("2965.out", "w", stdout);
#endif
	while (scanf("%d\n", &n) != EOF) work();
	
	return 0;
}
