/*
	Problem:	B.cpp
	Time:		2020-02-26 21:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

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

namespace run
{
	const int maxn = 3e5 + 10;
	typedef long long i64;

	int ch[maxn][26], cur;
	int dep[maxn], pos[maxn], val[maxn], node;
	int n, m;
	i64 F[maxn], A, B, C;

	int v[maxn], mxlen, len[maxn];
	int g[maxn];
	i64 sum, ans[maxn];
	
	int pre[maxn], suf[maxn];
	int blg[maxn], seq[maxn], top, cnt[maxn];
	struct Query
	{
		int l, r, id;
		inline Query(int l = 0, int r = 0, int id = 0) : l(l), r(r), id(id) {}
		inline bool operator < (const Query &B) const {return blg[l] < blg[B.l] || blg[l] == blg[B.l] && r > B.r;}
	}q[maxn];

	void ins(char s[], int v)
	{
		int u = 0, n = strlen(s + 1);
		REP(i, 1, n)
		{
			int c = s[i] - 'a';
			if (!ch[u][c])
			{
				ch[u][c] = ++cur;
				dep[cur] = dep[u] + 1;
			}
			u = ch[u][c];
			pos[++node] = u;
			val[node] = v;
		}
	}
	bool ck(i64 f, i64 len){ if(f == 0) return 0; return B * f + len * A >= C;}
	i64 calc(int l, int r) {return (r - l + 1ll) * (r - l + 2) / 2;}
	void add(int i)
	{
		int x = pos[i];
		if(!ck(F[x], dep[x]) && ck(F[x] + val[i], dep[x]) && !cnt[g[dep[x]]]++){
			int k = g[dep[x]], l = pre[k], r = suf[k];
			suf[l] = pre[r] = k; sum -= calc(l+1, r-1); sum += calc(l+1, k-1); sum += calc(k+1, r-1);
		} F[x] += val[i];
	}
	void del(int i){
		int x = pos[i];
		if(ck(F[x], dep[x]) && !ck(F[x] - val[i], dep[x]) && !(--cnt[g[dep[x]]])){
			int k = g[dep[x]], l = pre[k], r = suf[k];
			suf[l] = r; pre[r] = l; sum -= calc(l+1, k-1); sum -= calc(k+1, r-1); sum += calc(l+1, r-1);
		} F[x] -= val[i];
	}
	char s[maxn];
	int main(){
		n = read<int>();A = read<int>();B = read<int>();C = read<int>();
		REP(i, 1, n) v[i] = read<int>();
		REP(i, 1, n)
		{
			scanf("%s", s + 1);
			len[i] = strlen(s + 1);
			chkmax(mxlen, len[i]);
			ins(s, v[i]);
			len[i] += len[i-1];
		}
		REP(i, 1, mxlen) g[i] = read<int>();

		const int siz = sqrt(node);
		REP(i, 1, node) blg[i] = (i - 1) / siz + 1;

		m = read<int>();
		REP(i, 1, m)
		{
			int l(read<int>()), r(read<int>());
			q[i] = Query(len[l - 1] + 1, len[r], i);
		}
		sort(q + 1, q + 1 + m);

		REP(i, 1, node)
		{
			int x = pos[i];
			if (!ck(F[x], dep[x]) && ck(F[x] + val[i], dep[x]) && !cnt[g[dep[x]]]++)
				seq[++top] = g[dep[x]]; 
			F[x] += val[i];
		} 
		seq[++top] = 0;
		seq[++top] = mxlen + 1; 
		sort(seq + 1, seq + 1 + top);
		REP(i, 1, top)
		{
			pre[seq[i]] = seq[i - 1];
			suf[seq[i]] = seq[i + 1];
		}
		REP(i, 2, top)
			sum += calc(seq[i - 1] + 1, seq[i] - 1);

		int now = 1, l = 1, r = node;
		for(int i = 1, j = siz; i <= node; i += siz, j += siz)
		{
			while(now <= m && q[now].l >= i && q[now].l <= j)
			{
				while (r > q[now].r) del(r--);
				while (l < q[now].l) del(l++);
				ans[q[now].id] = sum; 
				while (l > i) add(--l);
				now++;
			}
			while(r < node) add(++r);
			while(l <= j) del(l++);
		}
		i64 tmp = mxlen * (mxlen + 1ll) / 2;
		REP(i, 1, m)
		{
			i64 v = tmp - ans[i], g = __gcd(tmp, v);
			cout << v / g << "/" << tmp / g << '\n';
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	return run::main();
}
