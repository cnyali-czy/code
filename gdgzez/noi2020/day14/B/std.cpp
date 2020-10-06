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
#define M 200008
#define MAXN 520
int q[M],hd,tl;
int rt,t[MAXN][26],fd[MAXN],tot,hv[MAXN],cnt;
inline void ins(int &x,char *c,int rem){
    if(x==-1) x=tot++; if(!rem){++hv[x];return;}
    ins(t[x][(*c)-'a'],c+1,rem-1);
}
inline void build(){
    hd=tl=0;
    for(int i=0;i<26;i++) if(t[rt][i]!=-1) q[tl++]=t[rt][i]; else t[rt][i]=rt;
    while(hd<tl){
        int x=q[hd++]; hv[x]+=hv[fd[x]];
        for(int i=0;i<26;i++){
            if(t[x][i]!=-1) fd[t[x][i]]=t[fd[x]][i],q[tl++]=t[x][i];
            else t[x][i]=t[fd[x]][i];
        }
    }
	for(int i=0;i<tot;i++)printf("%d%c",fd[i],i==tot-1?'\n':' ');
	for(int i=0;i<tot;i++)for(int j=0;j<26;j++)printf("%d%c",t[i][j],j==25?'\n':' ');
}
int n,m,Q;
char ch[M];
int len[M],st[M],lt[M];
int g[18][52][M];
inline int tar(int sta){return (sta&63);}
inline int cst(int sta){return (sta>>6);}
inline int sta(int tar,int cst){return (cst<<6)|tar;}
inline void gtin(int id,int l){
    scanf("%s",ch),len[id]=strlen(ch),st[id]=l;
    lt[id]=lt[id-1]+len[id-1];
    for(int x=0;x<tot;x++) for(int i=0;i<len[id];i++)
        g[0][x][i+lt[id]]=sta(t[x][ch[i]-'a'],hv[t[x][ch[i]-'a']]);
    for(int k=1;k<18;k++) for(int x=0;x<tot;x++) for(int i=0;i<len[id];i++){
        int y=tar(g[k-1][x][i+lt[id]]),nxtpos=(i+(1<<(k-1)))%len[id];
        g[k][x][i+lt[id]]=g[k-1][y][nxtpos+lt[id]]+(cst(g[k-1][x][i+lt[id]])<<6);
    }
}
int lev[M<<2],f[M<<2][52],tag[M<<2];
inline void pushup(int x){
    for(int a=0;a<tot;a++){
        int b=tar(f[x<<1][a]),w=cst(f[x<<1][a]);
        f[x][a]=f[x<<1|1][b]+(w<<6);
    }
}
inline void gv(int x,int l,int r,int id){for(int a=0;a<tot;a++) f[x][a]=g[lev[x]][a][(l-st[id])%len[id]+lt[id]];tag[x]=id;}
inline void pushdown(int x,int l,int r){
    if(!tag[x]) return; int mid=((l+r)>>1);
    gv(x<<1,l,mid,tag[x]),gv(x<<1|1,mid+1,r,tag[x]),tag[x]=0;
}
inline void build(int x,int l,int r){
    assert(x<(M<<2));
    if(l==r){lev[x]=0;return;} int mid=((l+r)>>1);
    build(x<<1,l,mid),build(x<<1|1,mid+1,r),lev[x]=lev[x<<1]+1;
}
inline void mdf(int x,int l,int r,int ls,int rs,int kd){
    if(ls<=l&&r<=rs){gv(x,l,r,kd);return;}
    if(r<ls||rs<l) return; int mid=((l+r)>>1); pushdown(x,l,r);
    mdf(x<<1,l,mid,ls,rs,kd),mdf(x<<1|1,mid+1,r,ls,rs,kd),pushup(x);
}
int nd,ans;
inline void qry(int x,int l,int r,int ls,int rs){
    if(ls<=l&&r<=rs){ans+=cst(f[x][nd]),nd=tar(f[x][nd]);return;}
    if(r<ls||rs<l) return; int mid=((l+r)>>1); pushdown(x,l,r);
    qry(x<<1,l,mid,ls,rs),qry(x<<1|1,mid+1,r,ls,rs);
}
int main(){
	freopen("B.in","r",stdin);freopen("std.out","w",stdout);
    n=read(),Q=read(),rt=-1,memset(t,-1,sizeof(t));
    for(int i=1;i<=n;i++){
        scanf("%s",ch); int Len=strlen(ch);
        ins(rt,ch,Len);
    } build(),gtin(cnt=1,1);
    for(m=1;m<len[1];m<<=1); build(1,1,m),gv(1,1,m,1);
    for(int op,l,r;Q;--Q){
        op=read(),l=read(),r=read();
        if(op==1) gtin(++cnt,l),mdf(1,1,m,l,r,cnt);
        else nd=rt,ans=0,qry(1,1,m,l,r),printf("%d\n",ans);
    }
    return 0;
}
