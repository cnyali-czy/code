#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)
#define Forr(i, j, k) for (int i = j; i >= k; i--)

using namespace std;

typedef long long LL;

const int N = 1e6 + 10;

LL sumc[N];

struct Segment_Tree {

	const static int NODE = 1 << 21;

	int lc[NODE], rc[NODE], addv[NODE], node;
	LL sum[NODE], sqr[NODE];

	#define M ((L + R) >> 1)

	void modify(int &o, int L, int R, int l, int r) {
		if (!o) o = ++node;
		if (l <= L && R <= r) {
			addv[o]++;
		} else {
			if (l <= M) modify(lc[o], L, M, l, r);
			if (r > M) modify(rc[o], M + 1, R, l, r);
		}

		sum[o] = sum[lc[o]] + sum[rc[o]] + (sumc[R] - sumc[L - 1]) * addv[o];
		sqr[o] = sqr[lc[o]] + sqr[rc[o]] + 2ll * addv[o] * sum[o] - (sumc[R] - sumc[L - 1]) * addv[o] * addv[o];
	}

	#undef M

}T;

struct Suffix_Automaton {

	int pre[N], ch[N][26], Max[N];
	int node, lst;

	void extend(int c) {
		int p = lst;

		if (ch[p][c]) {
			int q = ch[p][c];
			if (Max[q] == Max[p] + 1) {
				lst = q;
				return;
			}
			int nq = ++node;
			For(i, 0, 25) ch[nq][i] = ch[q][i];
			pre[nq] = pre[q];
			pre[q] = nq;
			Max[nq] = Max[p] + 1;
			while (ch[p][c] == q) ch[p][c] = nq, p = pre[p];
			lst = nq;
		} else {
			int np = ++node;
			Max[np] = Max[p] + 1;
			while (!ch[p][c]) ch[p][c] = np, p = pre[p];
			if (ch[p][c] == np) {
				pre[np] = p;
			} else {
				int q = ch[p][c];
				if (Max[q] == Max[p] + 1) {
					pre[np] = q;
				} else {
					int nq = ++node;
					For(i, 0, 25) ch[nq][i] = ch[q][i];
					pre[nq] = pre[q];
					pre[q] = pre[np] = nq;
					Max[nq] = Max[p] + 1;
					while (ch[p][c] == q) ch[p][c] = nq, p = pre[p];
				}
			}
			lst = np;
		}
		
	}

	void insert(char *S) {
		int l = strlen(S);
		For(i, 0, l - 1) extend(S[i] - 'a');
		lst = 0;
	}

	vector<int> G[N];
	int son[N], sz[N];

	void DFS_init(int o) {
		sz[o] = 1;
		for (int v : G[o]) {
			DFS_init(v);
			sz[o] += sz[v];
			if (!son[o] || sz[v] > sz[son[o]]) son[o] = v;
		}
	}
	
	int top[N];
	int id[N], dfn;

	void DFS_decompose(int o) {
		if (o) {
			id[o] = ++dfn;
			sumc[dfn] = sumc[dfn - 1] + Max[o] - Max[pre[o]];
		}
		top[o] = pre[o] && son[pre[o]] == o ? top[pre[o]] : o;
		if (son[o]) DFS_decompose(son[o]);
		for (int v : G[o]) {
			if (v == son[o]) continue;
			DFS_decompose(v);
		}
	}

	void init() {
		For(i, 1, node) G[pre[i]].push_back(i);
		DFS_init(0);
		DFS_decompose(0);
	}

	int root;

	void modify(char *S) {
		int l = strlen(S), o = 0;
		For(i, 0, l - 1) {
			o = ch[o][S[i] - 'a'];
			int p = o;
			while (p) {
				T.modify(root, 1, dfn, id[top[p]], id[p]);
				p = pre[top[p]];
			}
		}
		printf("%lld\n", T.sqr[root]);
	}

}M;

int n;
char *S[N], buffer[N];

int main() {

	scanf("%d", &n);
	char *p = buffer;
	For(i, 1, n) {
		S[i] = p;
		scanf("%s", p);
		p += strlen(S[i]) + 1;
		M.insert(S[i]);
	}
	M.init();
	For(i, 1, n) M.modify(S[i]);

	return 0;
}
