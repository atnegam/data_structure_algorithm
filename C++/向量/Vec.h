#ifndef __VEC__H
#define __VEC__H
#include <iostream>
typedef int Rank;



Rank binSearch(int a[], int e, int lo, int hi){
    while(hi>lo){
        Rank mi=(lo+hi) >> 1;
        (e<a[mi])? hi=mi:lo=mi+1;
    }//出口时,a[lo=hi]为大于e的最小元素
    return --lo;
}

Rank Vsearch(int a[], int n, int e){
    return binSearch(a,e,0,n);
}

Rank Vinsert(int a[], Rank r, int e, int n){
    //扩容还未实现
    for(int i=n; i>r; i--)
        a[i]=a[i-1];
    a[r]=e;
    return r;
}

#endif