#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )

const int maxn = 100010;

int n;
char s[maxn];

struct node 
{
	int l, r, Max1, Max2, K1, K2, val, key;
	bool flag;
} Tree[maxn * 2];

void push_up(int root)
{
	if ( Tree[Tree[root].l].Max1 < Tree[Tree[root].r].Max1 ) 
	{
		Tree[root].Max1 = Tree[Tree[root].r].Max1;
		Tree[root].K1 = Tree[Tree[root].r].K1;
		if ( Tree[Tree[root].l].Max1 < Tree[Tree[root].r].Max2 )
		{
			Tree[root].Max2 = Tree[Tree[root].r].Max2;
			Tree[root].K2 = Tree[Tree[root].r].K2;
		}
		else 
		{
			Tree[root].Max2 = Tree[Tree[root].l].Max1;
			Tree[root].K2 = Tree[Tree[root].l].K1;
		}
	}
	else
	{
		Tree[root].Max1 = Tree[Tree[root].l].Max1;
		Tree[root].K1 = Tree[Tree[root].l].K1;
		if ( Tree[Tree[root].r].Max1 < Tree[Tree[root].l].Max2 )
		{
			Tree[root].Max2 = Tree[Tree[root].l].Max2;
			Tree[root].K2 = Tree[Tree[root].l].K2;
		}
		else 
		{
			Tree[root].Max2 = Tree[Tree[root].r].Max1;
			Tree[root].K2 = Tree[Tree[root].r].K1;
		}
	}
}

void Build(int root, int l, int r)
{
	Tree[root].l = l; 
	Tree[root].r = r;
	Tree[root].flag = false;
	if ( l == r ) 
	{
		scanf("%d", &Tree[root].val);
		Tree[root].Max1 = Tree[root].K1 = 
		Tree[root].Max2 = Tree[root].K2 = -1;
		Tree[root].key = Tree[root].key;
		return ;
	}
	int Mid = (l + r) >> 1;
	Build(root << 1, l, Mid);
	Build(root << 1 | 1, Mid + 1, r);
}

void update(int root, int l, int r, int pos, int num)
{
	if ( l == r ) 
	{
		Tree[root].flag = true;
		Tree[root].val = num - Tree[root].key;
		Tree[root].key = num;
		Tree[root].Max1 = Tree[root].val;
		Tree[root].K1 = l;
		return ;
	}
	int Mid = (l + r) >> 1;
	if ( pos <= Mid ) 
	{
		update(root << 1, l, Mid, pos, num);
		if ( Tree[root << 1].flag == true ) Tree[root].flag = true;
	}
	else
	{
		update(root << 1 | 1, Mid + 1, r, pos, num);
		if ( Tree[root << 1 | 1].flag == true ) Tree[root].flag = true;
	}
	if ( Tree[Tree[root].l].flag == Tree[Tree[root].r].flag == false ) return ;
	push_up(root);
}

int main()
{
	freopen("invest.in", "r", stdin);
	freopen("invest.out", "w", stdout);
	scanf("%d", &n);
	Build(1, 1, n);
	while ( scanf("%s", s) )
	{
		getchar();
		if ( s[0] == 'E' ) break ;
		if ( s[0] == 'R' ) 
		{
			printf("%d %d\n", Tree[1].K1, Tree[1].K2);
			continue ;
		}
		int x = 0, p = 0, y;
		while ( s[p] >= '0' && s[p] <= '9' ) 
		{
			x = x * 10 + s[p] - '0';
			++ p;
		}
		scanf("%d", &y);
		update(1, 1, n, x, y);
		REP(i, 1, 7) 
		printf("%d %d %d %d %d %d\n", Tree[i].l, Tree[i].r, Tree[i].Max1, Tree[i].Max2, Tree[i].K1, Tree[i].K2);
		puts("");
	}
	return 0;	
}
