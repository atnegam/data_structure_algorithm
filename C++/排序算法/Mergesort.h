/*
    归并排序 <=O(logN)
    mergesort0：递归实现
    mergesort1：迭代实现
*/

void merge(int a[], int lo, int mi, int hi){//合并 [lo,mi]和(mi,hi]
    int len=mi-lo+1;
    int hen=hi-mi;
    int la[len];
    int ha[hen];

    for(int i=0; i<mi-lo+1; i++){//拷贝[lo,mi]
        la[i]=a[i+lo];
    }
    for(int i=0; i<hi-mi; i++){//拷贝(mi,hi]
        ha[i]=a[i+mi+1];
    }
    int i=0,j=0;
    while(i<len && j<hen){
        if(la[i]<ha[j])
            a[lo++]=la[i++];
        else
            a[lo++]=ha[j++];
    }//比较填入a[]

    while(i<len)
        a[lo++]=la[i++];

    while(j<hen)
        a[lo++]=ha[j++];

}

void _mergesort0(int a[], int lo, int hi){//lo
    if(hi-lo<1) return;
    int mi=(lo+hi)/2;
    _mergesort0(a,lo,mi);   //[lo, mid]
    _mergesort0(a,mi+1,hi);   //(mid, hi]
    merge(a,lo,mi,hi);
}

void mergesort0(int a[], int n){
    _mergesort0(a, 0, n-1);
}