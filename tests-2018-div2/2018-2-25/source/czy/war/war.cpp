
/**********************************************************
	File:war.cpp
	Author:huhao
	Email:826538400@qq.com
	Created time:2018-2-25 14:19:47
**********************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#define N 30010
#define M 2147483647
int n,q,a[N];
struct tree
{
	tree *l,*r;
	int w;
	tree()
	{
		l=r=NULL;
		w=0;
	}
}*root;
void add(tree *k,int x,int w,int l,int r)
{
	k->w+=w;
	if(l==r)return;
	int mid=(l>>1)+(r>>1)+(l&r&1);
	if(mid>=x)
		add(k->l=k->l==NULL?new tree:k->l,x,w,l,mid);
	else
		add(k->r=k->r==NULL?new tree:k->r,x,w,mid+1,r);
}
int kth(tree *k,int x,int l,int r)
{
//	printf("%d %d\n",l,r);
	if(l==r)return l;
	int mid=(l>>1)+(r>>1)+(l&r&1);
	if(k->l!=NULL&&k->l->w>=x)
		return kth(k->l,x,l,mid);
	else
		return kth(k->r,x-(k->l==NULL?0:k->l->w),mid+1,r);
}
void print(int l,int r,tree *k)
{
	printf("%d %d %d\n",l,r,k->w);
	if(l==r)return;
	int mid=(l>>1)+(r>>1)+(l&r&1);
	if(k->l!=NULL&&k->l->w)
		print(l,mid,k->l);
	if(k->r!=NULL&&k->r->w)
		print(mid+1,r,k->r);
}
int main()
{
	freopen("war.in","r",stdin);
	freopen("war.out","w",stdout);
	n=read();
	root=new tree;
	fr(i,1,n)
	{
		a[i]=read();
		add(root,a[i],1,1,M);
	}
	q=read();
	fr(i,1,q)
	{
		char opt[10];
		scanf("%s",opt);
		if(*opt=='A')
		{
			int pos=read(),w=read();
			add(root,a[pos],-1,1,M);
			a[pos]-=w;
			if(a[pos]>0)
				add(root,a[pos],1,1,M);
			else
				n--;
		}
		if(*opt=='C')
		{
			int pos=read(),w=read();
			add(root,a[pos],-1,1,M);
			a[pos]+=w;
			if(a[pos]>0)
				add(root,a[pos],1,1,M);
			else
				n--;
		}
		int o=0;
//		fr(i,1,n)if(a[i+o]>0)printf("%d ",a[i+o]);else o++,i--;
//		putchar(10);
		if(*opt=='Q')
		{
			int k=read();
//			printf("%d %d\n",n,n-k+1);
//			int o=0;
//			fr(i,1,n)if(a[i+o]>0)printf("%d ",a[i+o]);else o++;
//			putchar(10);
			if(n<k)
				printf("-1\n");
			else
				printf("%d\n",kth(root,n-k+1,1,M));
		}
	}
	printf("%d\n",n);
	return 0;
}
