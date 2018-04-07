/*
Author: CNYALI_LK
LANG: C++
PROG: match.cpp
Mail: cnyalilk@vip.qq.com
*/
#include<bits/stdc++.h>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define DEBUG printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define all(x) x.begin(),x.end()
using namespace std;
const double eps=1e-8;
const double pi=acos(-1.0);
typedef long long ll;
typedef pair<int,int> pii;
template<class T>int chkmin(T &a,T b){return a>b?a=b,1:0;}
template<class T>int chkmax(T &a,T b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T>T mmin(T a,T b){return a<b?a:b;}
template<class T>T mmax(T a,T b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
#define min mmin
#define max mmax
#define abs aabs
int read(){
	int s=0,base=1;
	char c;
	while(!isdigit(c=getchar()))if(c=='-')base=-base;
	while(isdigit(c)){s=s*10+(c^48);c=getchar();}
	return s*base;
}
char WriteIntBuffer[1024];
template<class T>void write(T a,char end){
	int cnt=0,fu=1;
	if(a<0){putchar('-');fu=-1;}
	do{WriteIntBuffer[++cnt]=fu*(a%10)+'0';a/=10;}while(a);
	while(cnt){putchar(WriteIntBuffer[cnt]);--cnt;}
	putchar(end);
}
char s[1024],t[1024],l[1024];
int match(char *a,char *b){
	while(*a)if(*a!=*b)return 0;else ++a,++b;
	return 1;
}
int main(){
	int T;
	scanf("%d\n",&T);
	while(T){
		scanf("%s%s",s,t);		
		--T;
		int n=strlen(s),m=strlen(t),i=0,q=(*t=='*'),h=0;
		int yes=1;
		for(int j=q;j<m;++j){
			h=0;
			while(isalpha(t[j])){l[++h]=t[j];++j;}
			l[h+1]=0;
			if(q){
				++i;
				while(i+h<=n&&!match(l+1,s+i))++i;
				if(i+h<=n)i+=h;
				else {yes=0;break;}
			}
			else{
				if(!match(l+1,s+i)){yes=0;break;}
				else i+=h;
			}
			q=(t[j]=='*');	
		}
		if(yes&&(!((i==n)&&q)))printf("Maybe\n");
		else printf("Impossible\n");
	}
	return 0;
}

