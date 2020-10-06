/**************************************************************
    Problem: 2750
    User: 2018clyz01
    Language: C++
    Result: Accepted
    Time:47 ms
    Memory:240732 kb
****************************************************************/
 
 
#include <bits/stdc++.h>
 
template <class T>
inline void read(T &x) {
    static char ch; 
    while (!isdigit(ch = getchar())); 
    x = ch - '0'; 
    while (isdigit(ch = getchar()))
        x = x * 10 + ch - '0'; 
}
 
template <class T>
inline void tense(T &x, const T &y) {
    if (x > y) x = y; 
}
 
const int MaxN = 255; 
const int MaxQ = 5e4 + 5; 
 
const int MaxV = 2e5 + 5; 
const int MaxE = 3e7 + 5; 
 
int n, m, Q; 
 
std::vector<int> tree[MaxN], son[MaxN]; 
int ect, adj[MaxV], nxt[MaxE], to[MaxE];
 
int dep[MaxN], nV; 
int pos[MaxN][MaxN][2], fa[MaxN]; 
 
inline void addEdge(int u, int v) {
    nxt[++ect] = adj[u]; 
    adj[u] = ect; 
    to[ect] = v; 
}
 
void dfsInit(int u = 1, int pre = 0) {
    for (int i = 0; i < (int)tree[u].size(); ++i) {
        int v = tree[u][i]; 
        if (v == pre) continue; 
         
        fa[v] = u; 
        son[u].push_back(v); 
        dep[v] = dep[u] + 1; 
        dfsInit(v, u); 
    }
}
 
int dfsClock, dfn[MaxV], low[MaxV]; 
int top, nScc, stk[MaxV], scc[MaxV]; 
 
void dfsTarjan(int u) {
    dfn[u] = low[u] = ++dfsClock; 
    stk[++top] = u; 
 
    for (int e = adj[u], v; v = to[e], e; e = nxt[e]) {
        if (!dfn[v]) {
            dfsTarjan(v); 
            tense(low[u], low[v]); 
        } else if (!scc[v])
            tense(low[u], dfn[v]); 
    }
     
    if (low[u] == dfn[u]) {
        ++nScc; 
        do {
            scc[stk[top--]] = nScc; 
        } while (stk[top + 1] != u); 
    }
}
 
int main() {
    freopen("A.in", "r", stdin); 
    freopen("std.out", "w", stdout); 
 
    read(n), read(m), read(Q); 
    for (int i = 1; i < n; ++i) {
        int u, v; 
        read(u), read(v); 
        tree[u].push_back(v); 
        tree[v].push_back(u); 
    }
    dfsInit(); 
 
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int opt = 0; opt <= 1; ++opt) {
                pos[i][j][opt] = ++nV; 
            }
        }
        addEdge(pos[i][1][0], pos[i][1][1]); 
 
        for (int u = 2; u <= n; ++u) {
            int v = fa[u]; 
            addEdge(pos[i][u][1], pos[i][v][1]); 
            addEdge(pos[i][v][0], pos[i][u][0]); 
        }
        for (int u = 1; u <= n; ++u) {
            for (int a = 0; a < (int)son[u].size(); ++a)
                for (int b = a + 1; b < (int)son[u].size(); ++b) {
                    int v1 = son[u][a], v2 = son[u][b]; 
                    addEdge(pos[i][v1][1], pos[i][v2][0]); 
                    addEdge(pos[i][v2][1], pos[i][v1][0]); 
                }
        }
    }
 
    for (int i = 1; i <= Q; ++i) {
        int a, b, u; 
        read(a), read(b), read(u); 
 
        addEdge(pos[a][u][0], pos[b][u][1]); 
        addEdge(pos[b][u][0], pos[a][u][1]); 
        for (int j = 0; j < (int)son[u].size(); ++j) {
            int v = son[u][j]; 
            addEdge(pos[a][v][1], pos[b][v][0]); 
            addEdge(pos[b][v][1], pos[a][v][0]); 
        }
    }
 
    for (int i = 1; i <= nV; ++i)
        if (!dfn[i]) dfsTarjan(i);
	for (int u = 1; u <= nV; u++)
	{
		std :: vector <int> qaq;
		for (int e = adj[u], v; v = to[e], e; e = nxt[e]) qaq.emplace_back(v);
		sort(qaq.begin(), qaq.end());
		for (auto v : qaq) printf("%d %d\n", u, v);
	}
	for (int i = 1; i <= nV; ++i)
		printf("%d%c", scc[i], i == nV ? '\n' : ' ');
	for (int i = 1; i <= m; ++i) {
		int res = 0; 
		for (int u = 1; u <= n; ++u) {
			// assert(scc[pos[i][u][1]] != scc[pos[i][u][0]]); 
			// if (scc[pos[i][u][1]] < scc[pos[i][u][0]]) {
			//  std::cout << ':' << i << ' ' << u << '\n'; 
			// }

			if (scc[pos[i][u][1]] < scc[pos[i][u][0]] && (!res || dep[res] < dep[u]))
				res = u; 
		}
		printf("%d%c", res, " \n"[i == m]); 
	}

	return 0;
}
