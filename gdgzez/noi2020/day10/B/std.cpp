
#include <bits/stdc++.h>
 
#define enter putchar('\n')
#define space putchar(' ')
#define re register
#define N 500020
#define M 1000020
 
using namespace std;
 
const int inf=500005;
 
inline int max(int x,int y){return (x>y?x:y);}
 
inline int min(int x,int y){return (x<y?x:y);}
 
int a[N],n,mn;
 
//向下的曲线必然是不会有停顿的
 
int lim[M];
 
int Getf(int x){
    return x==lim[x]?x:lim[x]=Getf(lim[x]);
}
 
struct BST{
    signed T[M];
    inline void add(int x,int y){
        for(re int i=x;i<M;i+=(i&-i))    T[i]+=y;
        return;
    }
    inline int query(int x){
        int ans=0;
        for(re int i=x;i;i-=(i&-i))     ans+=T[i];
        return ans;
    }
    inline int Query(int l,int r){
        return query(r)-query(l-1);
    }
}tree1,tree2;
 
inline int read(){
    int x=0;char c=getchar();bool y=1;
    for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
    for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
    if(y) return x;
    return -x;
}
 
inline void Input(){
    n=read();
    mn=inf;
    for(re int i=1;i<=n;++i) a[i]=read()+inf,mn=min(mn,a[i]);
    for(re int i=1;i<M;++i)  lim[i]=i;
    return;
}
 
inline void solve(){
    for(re int i=1;i<=n;++i){
        int now=a[i];
        if(now<inf) tree2.add(now,1);
        now=Getf(now);
        if(now){lim[now]=lim[now-1];tree1.add(now,1);}
        int l=mn,r=inf,ret=0;
        while(l<r){
            int mid=(l+r+1)>>1;
            if(tree2.Query(1,mid)>inf-mid)       r=mid-1;
            else                                l=mid;
        }
        while(tree2.Query(1,l)<inf-l) ++l;
        while(tree2.Query(1,l)>inf-l) --l;
        printf("%d\n",tree1.Query(l+1,M)+l-inf);
    }
    return;
}
 
int main(){
    freopen("b.in","r",stdin);
    freopen("std.out","w",stdout);
    Input();
    solve();
    return 0;
}
