# [ZROJ1780 异或和](http://zhengruioi.com/problem/1780)

给定 $R = \sum_{i=1}^k 2^{a_i}$ 求选出 $n$ 个**严格递增**且 $<R$ 的非负整数满足其异或和为 $0$ 的方案数模 $998244353$ 。

$n,k\le 114514,0\le a_i\le 1145141919810,a_i<a_{i+1}$

# 题解

原来的题解写得愚蠢至极，重写一下。

始于盘古开天地。

## 前置知识

### （扩展）拉格朗日反演

#### 复合逆

若形式幂级数 $F(x)$ 满足 $[x^0]F(x)=0,[x^1]F(x)=1$ ，则 $F(x)$ 有复合逆 $F^{-1}(x)$ ，满足 $F(F^{-1}(x))=x$。

同时可以证明，$F(x),F^{-1}(x)$ 互为复合逆。

#### 扩展拉格朗日反演

$$
[x^n]H\left(F(x)\right)=\frac1n[x^{n-1}]H'(x)\left(\frac x{F^{-1}(x)}\right)^n
$$

~~别问后面那个东西是不是不良定义，把 $x$ 往下除一下就知道了。~~

**留坑：$H(x)$ 之类的东西中，什么能当作常数？**

### Polya相关

本质不同：系数都是 $+1$ 。

两两不同：系数是 $(-1)^{\mathrm{sgn}(p)}$ 。

#### 置换环计数

大小为 $n$ 的全排列置换方案，分成大小为 $a_1,a_2\dots a_k$ 的置换环的方案为多少个？保证 $\sum a=n$。

如此考虑：

1.  先分配**集合的**位置，总方案为： $\frac{n!}{\prod a_i!}$
2.  大小相同的环要去除先后顺序： $\frac{n!}{\prod a_i!\prod cnt_i!}$
3.  此时分配的还只是**集合**而不是环，那么依次连出一条没被连过的出边，方案数为：  $(a_i-1)\times(a_i-2)\dots 2\times 1=(a_i-1)!$
4.  **于是总方案为**： $$\frac{n!}{\prod a_i\prod cnt_i!}$$

## 进入正题

**突破口1：两两不同！那么我们对在全排列置换下两两不同的方案计数就好了。**这看起来很憨，但这就是不重不漏的。

那么我们好像有办法了。

### 算法1-预热

1.  枚举划分数。
2.  计算方案数，在前置知识中已给出。
3.  计算贡献……**欸等等我不会算贡献啊？**

贡献怎么算？

考虑你划分出的环，分类讨论：

1.  是个奇数大小，那么相当于 $1$ 个数。
2.  是个偶数大小，那么相当于——没有！也就是说可以任选，贡献是一个 $R$ 。

于是，设划分了 $奇$ 个奇环， $偶$ 个偶环，那么这个贡献就是（除去 $n!$ ）：
$$
\frac1{\prod cnt_i!\prod a_i}\left((-1)^偶R^偶=(-R)^偶\right)f_奇
$$
其中，$f_k$ 表示原题去掉**两两不同**且选的数**有顺序**的答案。

### 所以……怎么算$f_k$？

我们考虑按照**所有数与 $R$ 在二进制下的LCP长度（位置）**来分类计算。

那么有几个要求：

1.  至少得有一个 $0$，否则当前就不是 LCP 了。
2.  $1$ 得有奇数个。
3.  这个位置必然是某个 $a_j$ （因为有些选的数要在这里由 $1$ 变成 $0$，如此才能小于）

那么分开考虑剩下来的贡献。

**突破口2：由于异或和固定，我们可以留那个 $0$ 整个先不填，在其他的数都填好之后直接补位就可以了。**

那么大概是一个 $\sum_{i=0}^{n-1}[2|i]\binom ni forone^iforzero^{n-1-i}$。

$forone$ ：这一位填 $1$ ，那之后的必然要严格小与。

$forzero$ ：这一位填 $0$ ，之后任意就行了。

然后这个大概是要求一个 $\forall i,\sum\frac{a_j^i}{b_j}$。

这是一个经典问题，考虑：
$$
\begin{align*}
ans_i&=[x^i]\sum_j\frac {a_j^i}{b_j}\\
Ans(x)&=\sum_ix^i\sum_j\frac {a_j^i}{b_j}\\
&=\sum_j\frac1{b_j}\sum_i(a_jx)^i\\
&=\sum_j\frac1{b_j}\times\frac{1}{1-a_ix}\\
&=\sum_j\frac1{b_j-a_jb_jx}
\end{align*}
$$
这个分治 FFT 一下就好了 $\frac{u_1}{d_1}+\frac{u_2}{d_2}=\frac{u_1d_2+u_2d_1}{d_1d_2}$

### 算法2

我一看，这个枚举划分太落后了。

考虑有无高效方法把系数处理出来。

一看，可以 dp。同样的 $a_i$ 可以一次性全部加入，于是分奇偶考虑一下就好。

那其实可以变成胜场函数的形式，变成：
$$
F_i(x)=\sum_{j=1}\frac{{\frac{x^i}i}^jy^j}{j!}=\exp(\frac{x^i}iy)\\
G_i(x)=\sum_{j=1}\frac{{\frac{x^i}i}^j(-R)^j}{j!}=\exp(\frac{x^i}i(-R))
$$
然后最后推一推式子，你发现大概可以是一个 $F^i G$ 之类的形式。

并且可以拉反。先鸽着。