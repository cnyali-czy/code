#include "mythological.h"
#include <stdio.h>

#undef D

#define D(a) dewudhksehdweqi##a

int D(a)[100005];
int D(ans)[2000005];
#define BUF_SIZE (int) (1e5 + 10)

char D(buf)[(int)1e5 + 10];
int D(cur);
struct FILE *D(in), *D(out);

void D(init)() {
    D(cur) = (int)1e5 + 10;
    D(in) = stdin;
    D(out) = stdout;
}

char D(nextChar)() {
    if(D(cur) == (int)1e5 + 10) {
        fread(D(buf), (int)1e5 + 10, 1, D(in));
        D(cur) = 0;
    }
    return D(buf)[D(cur)++];
}

int D(nextInt)() {
    int x = 0;
    char c = D(nextChar)();
    while(!('0' <= c && c <= '9')) c = D(nextChar)();
    while('0' <= c && c <= '9') {
        x = x * 10 + c - '0';
        c = D(nextChar)();
    }
    return x;
}
void D(printChar)(char ch) {
    D(buf)[D(cur)++] = ch;
    if (D(cur) == (int)1e5 + 10) {
        fwrite(D(buf), (int)1e5 + 10, 1, D(out));
        D(cur) = 0;
    }
} 
void D(printInt)(int x) {
    if (x >= 10) D(printInt)(x / 10);
    D(printChar)(x % 10 + '0');
}
void D(close)() {
    if (D(cur) > 0) fwrite(D(buf), D(cur), 1, D(out));
    D(cur) = 0;
}


int main(){
    int i,n,m,q,t;
    D(init)();
    n = D(nextInt)();
    m = D(nextInt)();
    q = D(nextInt)();
    t = D(nextInt)();
    for (i = 1; i <= n; ++i)
        D(a)[i] = D(nextInt)();
    init(n,m,D(a),t);
    for (i = 1; i <= q; ++i) {
        int l,r;
        l = D(nextInt)(); r = D(nextInt)();
        D(ans)[i] = query(l,r);
    }
    D(cur)=0;
    for (i = 1; i <= q; ++i) D(printInt)(D(ans)[i]),D(printChar)('\n');
    D(close)();
    return 0;
}

