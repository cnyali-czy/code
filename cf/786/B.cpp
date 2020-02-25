/*
	Problem:	B.cpp
	Time:		2020-02-24 21:26
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

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
	const int MAXN=static_cast<int>(1e5)+100;
	const long long INF=0x3f3f3f3f3f3f3f3f;
	const int oo=0x3f3f3f3f;
#define int long long
#define make(x,y) (make_pair(x,y))
#define to first
#define v second
	static vector<pair<int,int>> edge[MAXN*10];
	static int n,q,s,cnt,treeOut[MAXN<<2],treeIn[MAXN<<2];
	inline void build(int k,int l,int r){
		if(l==r){
			treeOut[k]=l;
			treeIn[k]=l;
			return;
		}
		int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		treeOut[k]=++cnt;
		treeIn[k]=++cnt;
		edge[treeOut[k<<1]].push_back make(treeOut[k],0);
		edge[treeOut[k<<1|1]].push_back make(treeOut[k],0);
		edge[treeIn[k]].push_back make(treeIn[k<<1],0);
		edge[treeIn[k]].push_back make(treeIn[k<<1|1],0);
	}
	inline void updateIn(int k,int l,int r,int L,int R,int from,int cost){
		if(L<=l&&r<=R){
			edge[from].push_back(make(treeIn[k],cost));
			return ;
		}
		int mid=(l+r)>>1;
		if(L<=mid){
			updateIn(k<<1,l,mid,L,R,from,cost);
		}
		if(mid<R){
			updateIn(k<<1|1,mid+1,r,L,R,from,cost);
		}
	}
	inline void updateOut(int k,int l,int r,int L,int R,int from,int cost){
		if(L<=l&&r<=R){
			edge[treeOut[k]].push_back(make(from,cost));
			return ;
		}
		int mid=(l+r)>>1;
		if(L<=mid){
			updateOut(k<<1,l,mid,L,R,from,cost);
		}
		if(mid<R){
			updateOut(k<<1|1,mid+1,r,L,R,from,cost);
		}
	}
	struct heapnode{
		int pos,dis;
		bool operator<(heapnode right)const{
			return dis>right.dis;
		}
	};

	static int dis[MAXN*10];
	static priority_queue<heapnode>heap;
	inline void dij(){
		ini(dis,0x3f);
		dis[s]=0;
		heapnode tmp;
		tmp.dis=0;
		tmp.pos=s;
		heap.push(tmp);
		while(!heap.empty()){
			heapnode now=heap.top();
			heap.pop();
			if(dis[now.pos]!=now.dis){
				continue;
			}
			for(auto &i:edge[now.pos]){
				if(i.to==0){
					continue;
				}
				if(i.v+now.dis<dis[i.to]){
					dis[i.to]=i.v+now.dis;
					tmp.pos=i.to;
					tmp.dis=dis[i.to];
					heap.push(tmp);
				}
			}
		}
	}
	signed main(){
		n=read();
		q=read();
		s=read();
		cnt=n;
		build(1,1,n);
		F(i,1,q){
			int com=read();
			if(com==1){
				int from=read(),to=read(),v=read();
				edge[from].push_back(make(to,v));
			}else{
				if(com==2){
					int from=read(),l=read(),r=read(),v=read();
					updateIn(1,1,n,l,r,from,v);
				}else{
					int from=read(),l=read(),r=read(),v=read();
					updateOut(1,1,n,l,r,from,v);
				}
			}
		}
		dij();
		F(i,1,n){
			printf("%lld ",(dis[i]==INF)?-1:dis[i]);
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	return 0;
}
