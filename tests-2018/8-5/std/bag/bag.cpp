#include<bits/stdc++.h>
#define ll long long
#define maxn 100005
using namespace std;
const int ha=998244353;
void file()
{
	freopen("bag.in","r",stdin);
	freopen("bag.out","w",stdout);
}





















int now,pre,f[2][maxn],n,S;
int g[2][maxn],block[maxn];
 
inline int add(int x,int y){
    x+=y;
    return x>=ha?x-ha:x;
}
 
inline void dp_big(){
    g[0][0]=1,now=0,block[0]++;
     
    for(int i=1;i*S<=n;i++){
        pre=now,now^=1;
        fill(g[now],g[now]+i,0);
        for(int j=i;j<=n;j++){
            g[now][j]=g[now][j-i];
            if(j>=S) g[now][j]=add(g[now][j],g[pre][j-S]);
             
            block[j]=add(block[j],g[now][j]);
        }
    }
}
 
inline void dp_small(){
    now=0,f[0][0]=1;
    for(int i=1,res;i<S;i++){
        pre=now,now^=1,res=i*(i+1);
        for(int j=0;j<i;j++)
            for(int u=j,tmp=0;u<=n;u+=i){
                tmp=add(tmp,f[pre][u]);
                if(u-res>=0) tmp=add(tmp,ha-f[pre][u-res]);
                f[now][u]=tmp;
            }
    }
}
 
inline void output(){
    int ans=0;
    for(int i=0;i<=n;i++) ans=add(ans,f[now][i]*(ll)block[n-i]%ha);
    printf("%d\n",ans);
}
 
int main(){
	file();
    scanf("%d",&n),S=sqrt(n)+1;
    dp_big();
    dp_small();
    output();
    return 0;
}
