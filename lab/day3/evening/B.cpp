#define REP(i, s, e) for (int i = s; i <= e ;i++)

#include <bits/stdc++.h>
using namespace std;
const int maxnode = 3e7;

struct node
{
	int l, r, order;
	long long s;
	char c;
}t[maxnode];
int cur;
int newnode(char c)
{
	t[++cur] = (node){0, 0, 1, rand(), c};
	return cur;
}
int copy(int x)
{
	t[++cur] = t[x];
	return cur;
}
void pushup(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}
void split(int x, int &a, int &b, long long siz)
{
	if (!x) a = b = 0;
	else
		if (t[t[x].l].s >= siz)
		{
			b = copy(x);
			split(t[b].l, a, t[b].l, siz);
			pushup(b);
		}
		else
		{
			a = copy(x);
			split(t[a].r, t[a].r, b, siz - t[t[x].l].s - 1);
			pushup(a);
		}
}
void merge(int &x, int a, int b)
{
	if (!a || !b) x = a + b;
	else
	{
		if (t[a].order > t[b].order) merge(t[x = b].l, a, t[b].l);
		else merge(t[x = a].r, t[a].r, b);
		pushup(x);
	}
}
void insert(int pre, int &rt, long long pos, char c)
{
	int x(0), y(0);
	split(pre, x, y, pos);
	merge(x, x, newnode(c));
	merge(rt, x, y);
}
void del(int pre, int &rt, long long l, long long r)
{
	int x(0), y(0), z(0);
	split(pre, x, y, l - 1);
	split(y, y, z, r - l + 1);
	merge(rt, x, z);
}
void copy(int pre, int &rt, long long l, long long r, long long pos)
{
	int x(0), y(0), z(0);
	split(pre, x, y, l - 1);
	split(y, y, z, r - l + 1);
	int xx(0), yy(0), zz(0);
	split(pre, xx, yy, pos);
	merge(rt, rt, xx);
	merge(rt, rt, y);
	merge(rt, rt, yy);
}
void output(int p)
{
	if (!p) return;
	output(t[p].l);
	putchar(t[p].c);
	output(t[p].r);
}
void push_back(int &rt, char c) {merge(rt, rt, newnode(c));}

int rt[100000 + 10], now;

int n, m;
char s[100000 + 10];

int read()
{
	char c = getchar();
	int ans = 0, flag = 1;
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c)) ans = ans * 10 + c - 48, c = getchar();
	return ans * flag;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	t[0] = (node){0,0,0,0,'\0'};
	read();
	scanf("%s", s + 1);m = strlen(s + 1);
	REP(i, 1, m) push_back(rt[0], s[i]);
	while (1)
	{
		char c;
		if ((c = getchar()) == EOF) return 0;
		while (c != 'I' && c != 'D' && c != 'C' && c != 'P')
			if ((c = getchar()) == EOF) return 0;
		if (c == 'I')
		{
			long long pos(read());
			c = getchar();
			while (!isdigit(c) && !('a' <= c && c <= 'z') && !('A' <= c && c <= 'Z')) c = getchar();
			++now;
			insert(rt[now-1], rt[now], pos, c);
		}
		else if (c == 'D')
		{
			long long l(read()), r(read());
			++now;
			del(rt[now-1], rt[now], l, r);
		}
		else if (c == 'C')
		{
			long long x(read()), y(read()), z(read());
			++now;
			copy(rt[now-1], rt[now], x, y, z);
		}
		else
		{
			long long ccc(read()), l(read()), r(read());
			int x(0), y(0), z(0);
			split(rt[now-ccc], x, y, l - 1);
			split(y, y, z, r - l + 1);
			output(y);putchar(10);
		}
	}
	return 0;
}
