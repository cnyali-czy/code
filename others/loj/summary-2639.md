# 典型的动态逆序对
就搞一个线段树套平衡树，然后平衡树按照pos排一下。
每次把小的大的的贡献分开统记一下，然后加一下见一下
对于x-y只要考虑x-y之间的数的贡献。
一个区间内的线段树的话就是保存这个区间内的平衡树。
然后用区间操作快速考虑。
