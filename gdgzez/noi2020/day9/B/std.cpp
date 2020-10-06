
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include<bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define fgx cerr<<" ---------------------------------------------- "<<endl
#define LL long long
#define uint unsigned int 
#define ULL unsigned long long
#define LDB long double
#define DB double
#define pii pair<int,int>
#define pli pair<LL,int>
#define mp make_pair
#define pb push_back
using namespace std;
inline LL read(){
    LL nm=0; bool fh=true; char cw=getchar();
    for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
    for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
    return fh?nm:-nm;
}
#define M 100020
#define INF 1000000000
int n,m,Q,val[M],c[M][2];
int fa[M],dfn[M],tk[M],tp[M],cnt,sz[M]; bool ok[M];
inline void dfs1(int x,int last){   
    fa[x]=last,sz[x]=1;
    if(c[x][0]) dfs1(c[x][0],x),sz[x]+=sz[c[x][0]];
    if(c[x][1]) dfs1(c[x][1],x),sz[x]+=sz[c[x][1]];
}
inline void dfs2(int x,int dtp){
    if(!x) return; tp[x]=dtp,dfn[x]=++cnt,tk[cnt]=x;
    int son=(sz[c[x][1]]>sz[c[x][0]]);
    dfs2(c[x][son],dtp),dfs2(c[x][son^1],c[x][son^1]);
}
#define mx first
#define mi second
inline void upd(pii &A,pii &B){(A.mx<B.mx)?(A.mx=B.mx):0;(A.mi>B.mi)?(A.mi=B.mi):0;}
pii gol,gor,R[M<<2],L[M<<2]; bool tag[M<<2];
const pii tmp=mp(-INF,INF);
inline void pushup(int x){
    L[x]=tmp,upd(L[x],L[x<<1]),upd(L[x],L[x<<1|1]);
    R[x]=tmp,upd(R[x],R[x<<1]),upd(R[x],R[x<<1|1]);
}
inline void Rev(int x){tag[x]^=1,swap(L[x],R[x]);}
inline void pushdown(int x){if(tag[x]) Rev(x<<1),Rev(x<<1|1),tag[x]=false;}
inline void build(int x,int l,int r){
    if(l==r){
        int y=tk[l]; L[x]=R[x]=tmp;
        if(c[fa[y]][0]==y) L[x]=mp(val[fa[y]],val[fa[y]]);//debug(0)sp,debug(y)el;
        else R[x]=mp(val[fa[y]],val[fa[y]]);
        return;
    } int mid=((l+r)>>1);
    build(x<<1,l,mid),build(x<<1|1,mid+1,r),pushup(x);
}
inline void rev(int x,int l,int r,int ls,int rs){
    if(ls<=l&&r<=rs){Rev(x);return;} if(r<ls||rs<l) return;
    int mid=((l+r)>>1); pushdown(x);
    rev(x<<1,l,mid,ls,rs),rev(x<<1|1,mid+1,r,ls,rs),pushup(x);
}
inline void chg(int x,int l,int r,int pos){
    if(l==r){
        int w=val[fa[tk[l]]];
        if(R[x]==tmp) L[x]=mp(w,w); else R[x]=mp(w,w);
        return;
    } int mid=((l+r)>>1); pushdown(x);
    (pos<=mid)?chg(x<<1,l,mid,pos):chg(x<<1|1,mid+1,r,pos); pushup(x);
}
inline void qry(int x,int l,int r,int ls,int rs){
    if(ls<=l&&r<=rs){upd(gol,L[x]),upd(gor,R[x]);return;}
    if(r<ls||rs<l) return; int mid=((l+r)>>1); pushdown(x);
    qry(x<<1,l,mid,ls,rs),qry(x<<1|1,mid+1,r,ls,rs);
}
void output(int p, int l, int r)
{
	printf("%d %d %d (%d, %d) (%d, %d)\n", p, l, r, L[p].mi, L[p].mx, R[p].mi, R[p].mx);
	if (l == r) return;
	output(p<<1,l,l+r>>1);output(p<<1|1,(l+r>>1)+1,r);
}
int main(){
    freopen("B.in","r",stdin);
    freopen("std.out","w",stdout);
    n=read(),Q=read(),memset(ok,true,sizeof(ok));
    for(int i=1;i<=n;i++) val[i]=read(),c[i][0]=read(),c[i][1]=read(),ok[c[i][0]]=ok[c[i][1]]=false;
    int op,x,rt=1;
    while(!ok[rt]) ++rt; dfs1(rt,0),dfs2(rt,rt),c[0][1]=rt,val[0]=-INF,build(1,1,n);
	REP(i, 1, n) printf("%d%c", tp[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", tk[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", dfn[i], i == n ? '\n' : ' ');
    while(Q--){
		output(1,1,n);puts("");
        op=read(),x=read();
        if(op==1) val[x]=read(),chg(1,1,n,dfn[c[x][0]]),chg(1,1,n,dfn[c[x][1]]);
        if(op==2) rev(1,1,n,dfn[x]+1,dfn[x]+sz[x]-1);
        if(op==3){
            gol=gor=tmp;
            for(int y=x;y;y=fa[tp[y]]) qry(1,1,n,dfn[tp[y]],dfn[y]);
//          debug(gol.mx)sp,debug(gol.mi)el;
//          debug(gor.mx)sp,debug(gor.mi)el;
            puts((gol.mi>val[x]&&gor.mx<val[x])?"YES":"NO");
        }
    } return 0;
}
