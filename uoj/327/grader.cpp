#include "mythological.h"
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
const int maxn=100005;
static int c___a[maxn];
static int c___ans[2000005];
const int BUF_SIZE = (int)1e5 + 10;
struct fastIO{
    char buf[BUF_SIZE];
    int cur;
    FILE *in, *out;
    fastIO()
    {
        cur = BUF_SIZE;
        in = stdin;
        out = stdout;
    }
    inline char nextChar()
    {
        if(cur == BUF_SIZE)
        {
            fread(buf, BUF_SIZE, 1, in);
            cur = 0;
        }
        return buf[cur++];
    }
    inline int nextInt()
    {
        int x = 0;
        char c = nextChar();
        while(!('0' <= c && c <= '9')) c = nextChar();
        while('0' <= c && c <= '9')
        {
            x = x * 10 + c - '0';
            c = nextChar();
        }
        return x;
    }
    inline void printChar(char ch)
    {
        buf[cur++] = ch;
        if (cur == BUF_SIZE)
        {
            fwrite(buf, BUF_SIZE, 1, out);
            cur = 0;
        }
    }
    inline void printInt(int x)
    {
        if (x >= 10) printInt(x / 10);
        printChar(x % 10 + '0');
    }
    inline void close()
    {
        if (cur > 0)
        {
            fwrite(buf, cur, 1, out);
        }
        cur = 0;
    }
} IO;
inline void read(int &x){
    x=IO.nextInt();
}
int main(){
    int n,m,q,t;
    read(n);read(m);read(q);read(t);
    rep(i,1,n)read(c___a[i]);
    init(n,m,c___a,t);
    rep(i,1,q){
        int l,r;
        read(l);read(r);
        c___ans[i]=query(l,r);
    }
    IO.cur=0;
    rep(i,1,q)IO.printInt(c___ans[i]),IO.printChar('\n');
    IO.close();
    return 0;
}
