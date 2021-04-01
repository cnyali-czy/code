#include "testlib.h"

const int MAXN = 262245;
typedef long long LL;
int fa[MAXN], n;
LL rs[MAXN];
int getbel(LL x) {
	return std::lower_bound(rs + 1, rs + 1 + n, x) - rs;
}
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int main(){
	registerValidation();
	n = inf.readInt(0,262244,"n");
	inf.readEoln();
	for(int i=1;i<=n;++i){
		rs[i] = inf.readLong(rs[i - 1] + 1, rs[i - 1] + 1000000, "r");
		inf.readEoln();
	}
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1; i < n; ++i) {
		int x = find(getbel(inf.readLong(1, rs[n], "u")));
		inf.readSpace();
		int y = find(getbel(inf.readLong(1, rs[n], "v")));
		inf.readEoln();
		ensuref(x != y, "Should be a tree");
		fa[x] = y;
	}
	int m = inf.readInt(0,262244,"Q");
	inf.readEoln();
	for (int i = 1; i <= m; ++i) {
		inf.readLong(1, rs[n], "u");
		inf.readSpace();
		inf.readLong(1, rs[n], "v");
		inf.readEoln();
	}
	inf.readEof();
}

