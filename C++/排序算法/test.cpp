

#include <iostream>
#include "Bubblesort.h"
#include "Mergesort.h"
#include "Selectionsort.h"
#include "Insertsort.h"
#include "Quicksort.h"
#include "Shellsort.h"

using namespace std;
int main(){
    int a[]={9,5,8,6,7,5,4,3,2,1};
    bubblesort1(a,10);

    for(int i=0; i<9; i++){
        cout<<a[i]<<endl;
    }
}