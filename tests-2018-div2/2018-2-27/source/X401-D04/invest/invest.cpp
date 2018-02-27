#include<bits/stdc++.h>
using namespace std;
const int maxn=(int)2e5+10;
const int inf=2147483647;
int ch[maxn][2],fa[maxn],rec[maxn],sz[maxn],cnt,root;
struct node{
	int vl,id;
}val[maxn];
bool operator<(node x,node y){
	if(x.vl==y.vl)return x.id>y.id;
	return x.vl<y.vl;
}
bool operator==(node x,node y){
	return x.vl==y.vl&&x.id==y.id;
}
bool operator>(node x,node y){
	if(x.vl==y.vl)return x.id<y.id;
	return x.vl>y.vl;
}
bool operator !=(node x,node y){
	return !(x==y);
}
int a[maxn],b[maxn];
int n;
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
inline void pushup(int x){sz[x]=sz[ls(x)]+sz[rs(x)]+rec[x];}
inline void rotate(int x){
	int y=fa[x],f=fa[y],p=x==rs(y);
	ch[y][p]=ch[x][p^1],fa[ch[y][p]]=y;
	ch[x][p^1]=y,fa[y]=x;fa[x]=f;
	if(f)y==ls(f)?ls(f)=x:rs(f)=x;
	pushup(y);
}
inline void splay(int x,int aim){
	for(register int i;(i=fa[x])!=aim;rotate(x)){
		if(fa[i]!=aim)rotate(((ls(i)==x)==(i==ls(fa[i])))?i:x);
	}if(!aim)root=x;
	pushup(x);
}
inline void insert(int x,int k,int idd){
	if(!x){
		root=x=++cnt,ls(x)=rs(x)=fa[x]=0;
		sz[x]=rec[x]=1,val[x].vl=k;val[x].id=idd;
		return;
	}int pos;
	node K;
	K.vl=k,K.id=idd;
	while(true){
		++sz[x];
		if(K==val[x]){
			++rec[x];pos=x;break;
		}pos=ch[x][K>val[x]];
		if(!pos){
			pos=++cnt,fa[pos]=x;
			ls(pos)=rs(pos)=0;
			sz[pos]=rec[pos]=1;
			val[pos].vl=k;
			val[pos].id=idd;
			ch[x][K>val[x]]=pos;
			break;
		}x=pos;
	}splay(pos,0);
}
inline int find(node K){
	int x=root;
	while(x&&val[x]!=K)x=ch[x][K>val[x]];
	splay(x,0);
	return x;
}
inline node rank(int k){
	int x=root;
	while(x){
		if(k>sz[ls(x)]&&k<=sz[ls(x)]+rec[x])return val[x];
		if(k>sz[ls(x)]+rec[x])k-=(sz[ls(x)]+rec[x]),x=rs(x);
		else x=ls(x);
	}
}
inline int pre(node k){
	int x=find(k);
	x=ls(x);
	while(rs(x))x=rs(x);
	return x;
}
inline int nxt(node k){
	int x=find(k);
	x=rs(x);
	while(ls(x))x=ls(x);
	return x;
}
inline void Del(int k,int idd){
	node K;
	K.vl=k,K.id=idd;
	int x=find(K);
	if(k==inf){
		int x=find(K);
		--rec[x];
		return;
	}
	int lst=pre(K),to=nxt(K);
	splay(lst,0),splay(to,lst);
	int del=ls(to);
	if(rec[del]>1){
		--rec[del];
		splay(del,0);
	}else ls(to)=0;
}
inline void out(int x){
	if(!x)return;
	out(ls(x));
	for(register int i=1;i<=rec[x];++i)printf("%d ",val[x].id);
	out(rs(x));
}
inline void init(){
	insert(root,inf,0),insert(root,-inf,0);
	cin>>n;
	for(register int i=1;i<=n;++i)scanf("%d",&a[i]),insert(root,0,i),b[i]=0;
}
string str;
inline void work(int id){
	if(id==1){
		int len=str.length();
		int X=0,Y=0,i=0;
		while(str[i]!=' '){
			X=X*10+str[i]-48;
			++i;
		}++i;
		while(i<len){
			Y=Y*10+str[i]-48;
			++i;
		}
		Del(b[X],X);
		b[X]=a[X]-Y;
		a[X]=Y;
		insert(root,b[X],X);
	}else{
		printf("%d %d\n",rank(2).id,rank(3).id);
	}
}
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	init();
	while(true){
		getline(cin,str);
		if(isdigit(str[0]))work(1);
		if(str[0]=='R')work(2);
		if(str[0]=='E')break;
	}
return 0;
}
